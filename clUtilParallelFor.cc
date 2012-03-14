#include "clUtilParallelFor.h"

#define STRINGIFY(arg) #arg
#define __WHERE__ __FILE__ ":" STRINGIFY(__LINE__)

using namespace std;
using namespace clUtil;
using namespace clUtil::Utility;

bool DeviceGroupInfo::singletonInitialized = false;
DeviceGroupInfo DeviceGroupInfo::deviceGroupInfoSingleton;

static const double kModelFraction = 0.1;
static const size_t kMaxQueueLengthPow2 = 8; //2^8 = 256

ParallelForPerformanceModel::ParallelForPerformanceModel(size_t numSamples,
                                                         size_t start,
                                                         size_t end) :
  mPendingSampleQueues(DeviceGroupInfo::Get().numGroups(), 
                       UnsafeQueue<PendingTask>(kMaxQueueLengthPow2)),
  mModel(DeviceGroupInfo::Get().numGroups(), vector<Sample>(numSamples)),
  mRemainingWork(numSamples - 1),
  mNumSamples(numSamples),
  mStart(start),
  mEnd(end)
{
  size_t numDeviceGroups = DeviceGroupInfo::Get().numGroups();

  //Partition the initial sample workload to different device groups
  size_t sampleIterationCount = kModelFraction * (end - start) / numSamples;

  for(size_t curSample = 0; curSample < numSamples; curSample++)
  {
    size_t iterationOffset = 0;

    for(size_t curDeviceGroup = 0; 
        curDeviceGroup < numDeviceGroups; 
        curDeviceGroup++)
    {
      PendingTask newTask;

      if(iterationOffset == 0 && curSample < numSamples - 1)
      {
        iterationOffset = 
          mStart + curSample * (mEnd + mEnd / numSamples) 
          / numSamples + iterationOffset;
      }
      else if(iterationOffset == 0 && curSample == numSamples - 1)
      {
        iterationOffset = mEnd - sampleIterationCount;
      }

      newTask.SampleNumber = curSample;
      newTask.StartIndex = iterationOffset;
      
      //Last device group on the last sample only goes til last iteration.
      //Others take their iterations as usual
      if(curSample == numSamples - 1 && curDeviceGroup == numDeviceGroups - 1)
      {
        newTask.EndIndex = end - 1;
      }
      else
      {
        newTask.EndIndex = 
          iterationOffset + sampleIterationCount / numDeviceGroups;
      }

      iterationOffset = newTask.EndIndex + 1;

      mPendingSampleQueues[curDeviceGroup].push(newTask);
 
      //Mark remaining work vector
      if(curDeviceGroup == 0 && curSample > 0)  
      {
        mRemainingWork[curSample - 1].End = newTask.StartIndex - 1;
      }

      if(curDeviceGroup == numDeviceGroups - 1 && curSample < numSamples - 1)
      {
        mRemainingWork[curSample].Start = newTask.EndIndex + 1;
      }

#if 0
      cout << "DeviceGroup: " << curDeviceGroup
           << " Start: " << newTask.StartIndex
           << " End : " << newTask.EndIndex
           << endl;
#endif
    }
  }
}

PendingTask ParallelForPerformanceModel::getWork(size_t deviceGroup)
{
  PendingTask work;

  //Pull from the sample queues first.
  if(mPendingSampleQueues[deviceGroup].length() > 0)
  {
    mPendingSampleQueues[deviceGroup].pop(work);

    return work;
  }
  else //If empty, use model to get work
  {
    vector<Sample>& curDeviceModel = mModel[deviceGroup];
    //size_t bestSample = 0;
    //bool leftOfSample = false;

    for(size_t curSample = 0; curSample < curDeviceModel.size(); curSample++)
    {
      //Check to the left of the sample
      if(curSample > 0 && 
         mRemainingWork[curSample - 1].Start <= 
         mRemainingWork[curSample - 1].End)
      {
        
      }
      if(curSample < curDeviceModel.size() - 1) //Check to the right of sample
      {
      }

    }

    return work;
  }
}

double ParallelForPerformanceModel::interpolate(double t0, 
                                                double t1,
                                                size_t x0,
                                                size_t x1,
                                                size_t location)
{
  double slope = (t1 - t0) / (double)(x1 - x0);

  return slope * (double)(location - x0) + t0;
}

void ParallelForPerformanceModel::updateModel(size_t start, 
                                              size_t end, 
                                              size_t sampleNumber,
                                              size_t devGroup,
                                              double time)
{
  Sample& curSample = mModel[devGroup][sampleNumber];
  vector<Sample>& deviceModel = mModel[devGroup];
  double averageTime = time / (double)(end - start);

  if(curSample.IsValid == false) //Creating new sample
  {
    curSample.Start = start;
    curSample.End = end;
    curSample.Center = averageTime;
    curSample.IsValid = true;

    //Interpolate using previous sample if it exists
    if(sampleNumber > 0 && deviceModel[sampleNumber - 1].IsValid == true)
    {
      Sample& previousSample = deviceModel[sampleNumber - 1];

      curSample.Left = interpolate(previousSample.Right,
                                   curSample.Center,
                                   previousSample.End,
                                   (end + start) / 2,
                                   curSample.Start);

      previousSample.Right = interpolate(previousSample.Right,
                                         curSample.Center,
                                         previousSample.End,
                                         (end + start) / 2,
                                         previousSample.End);
    }
    else //Don't if it doesn't
    {
      curSample.Left = curSample.Center;
    }

    //Interpolate using next sample if it exists
    if(sampleNumber < deviceModel.size() - 1 &&
       deviceModel[sampleNumber + 1].IsValid == true)
    {
      Sample& nextSample = deviceModel[sampleNumber + 1];

      curSample.Right = interpolate(curSample.Center,
                                    nextSample.Left,
                                    (end + start) / 2,
                                    nextSample.Start,
                                    curSample.End);

      nextSample.Left = interpolate(curSample.Center,
                                    nextSample.Left,
                                    (end + start) / 2,
                                    nextSample.Start,
                                    nextSample.Start);

    }
    else //Don't if it doesn't
    {
      curSample.Right = curSample.Center;
    }
  }
  else //Updating existing sample
  {
    if(start > curSample.End) //Work appears to right of sample
    {
      Sample& nextSample = deviceModel[sampleNumber + 1];

      curSample.Right = interpolate(averageTime,
                                    nextSample.Left,
                                    (end + start) / 2,
                                    nextSample.Start,
                                    end);
      
      curSample.End = end;
    }
    else if(end < curSample.Start) //Work appears to left of sample
    {
      Sample& previousSample = deviceModel[sampleNumber - 1];

      curSample.Left = interpolate(previousSample.Right,
                                   averageTime,
                                   previousSample.End,
                                   (end + start) / 2,
                                   end);

      curSample.Start = start;
    }
    //If it appears somewhere in middle (possible if another device finishes
    //before this one), don't do anything
  }
}

void clUtil::ParallelFor(size_t start, 
                         size_t stride, 
                         size_t end, 
                         void (*loopBody)(size_t start, size_t end),
                         unsigned int numSamples)
{
  struct DeviceStatus
  {
    double Time1;
    double Time2;
    size_t StartIndex;
    size_t EndIndex;
    size_t SampleNumber;
    cl_event WaitEvent;
    bool IsBusy;

    DeviceStatus() : 
      Time1(0.0), 
      Time2(0.0), 
      StartIndex(0), 
      EndIndex(0), 
      SampleNumber(0),
      WaitEvent(NULL),
      IsBusy(false)
    {
    }
  };

  size_t oldDeviceNum = Device::GetCurrentDeviceNum();
  ParallelForPerformanceModel model(numSamples, start, end);
  size_t iterationsRemaining = end - start;
  vector<DeviceStatus> deviceStatuses(Device::GetDevices().size());

  //Parallel for scheduling loop
  while(iterationsRemaining > 0)
  {
    for(size_t curDevice = 0; 
        curDevice < Device::GetDevices().size(); 
        curDevice++)
    {
      DeviceStatus& curDeviceStatus = deviceStatuses[curDevice];

      //If this device isn't busy, get some work from the model and run it
      if(curDeviceStatus.IsBusy == false)
      {
        size_t deviceGroup = DeviceGroupInfo::Get()[curDevice];

        PendingTask work;

        work = model.getWork(deviceGroup);

        Device::SetCurrentDevice(curDevice);

        curDeviceStatus.StartIndex = work.StartIndex;
        curDeviceStatus.EndIndex = work.EndIndex;
        curDeviceStatus.SampleNumber = work.SampleNumber;
        curDeviceStatus.Time1 = getTime();
        curDeviceStatus.IsBusy = true;

        loopBody(work.StartIndex, work.EndIndex);

        clEnqueueMarker(Device::GetCurrentDevice().getCommandQueue(),
                        &curDeviceStatus.WaitEvent);

        clFlush(Device::GetCurrentDevice().getCommandQueue());
      }

      if(curDeviceStatus.WaitEvent != NULL)
      {
        cl_int eventStatus;

        cl_int err = clGetEventInfo(curDeviceStatus.WaitEvent,
                                    CL_EVENT_COMMAND_EXECUTION_STATUS,
                                    sizeof(eventStatus),
                                    &eventStatus,
                                    NULL);
        if(err != CL_SUCCESS)
        {
          throw clUtilException("ParallelFor internal error: could not get "
                                "event info " __WHERE__ "\n");
        }

        if(eventStatus == CL_COMPLETE)
        {
          size_t curDeviceGroup = DeviceGroupInfo::Get()[curDevice];

          curDeviceStatus.Time2 = getTime();
          model.updateModel(curDeviceStatus.StartIndex,
                            curDeviceStatus.EndIndex,
                            curDeviceStatus.SampleNumber,
                            curDeviceGroup,
                            curDeviceStatus.Time2 - curDeviceStatus.Time1);

          curDeviceStatus.IsBusy = false;

          clReleaseEvent(curDeviceStatus.WaitEvent);
          curDeviceStatus.WaitEvent = NULL;
        }
      }
    }
  }

  Device::SetCurrentDevice(oldDeviceNum);
}
