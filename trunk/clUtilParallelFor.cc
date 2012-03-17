#include "clUtilParallelFor.h"
#include <math.h>

#define STRINGIFY(arg) #arg
#define __WHERE__ __FILE__ ":" STRINGIFY(__LINE__)

using namespace std;
using namespace clUtil;
using namespace clUtil::Utility;

bool DeviceGroupInfo::singletonInitialized = false;
DeviceGroupInfo DeviceGroupInfo::deviceGroupInfoSingleton;

static const double kModelFraction = 0.1;
static const size_t kMaxQueueLengthPow2 = 8; //2^8 = 256
static const double kDefaultSpeedup = 10;
static const size_t kDefaultChunkSize = 1024;

ParallelForPerformanceModel::ParallelForPerformanceModel(size_t numSamples,
                                                         size_t start,
                                                         size_t end) :
  mPendingSampleQueues(DeviceGroupInfo::Get().numGroups(), 
                       UnsafeQueue<PendingTask>(kMaxQueueLengthPow2)),
  mModel(DeviceGroupInfo::Get().numGroups(), vector<Sample>(numSamples)),
  mRemainingWork(numSamples - 1),
  mNumSamples(numSamples),
  mStart(start),
  mEnd(end),
  mUnassignedIterations(end - start + 1)
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
        newTask.EndIndex = end;
      }
      else
      {
        newTask.EndIndex = 
          iterationOffset + sampleIterationCount / numDeviceGroups;
      }

      iterationOffset = newTask.EndIndex + 1;

      mPendingSampleQueues[curDeviceGroup].push(newTask);

      //Iterations sitting in queues are assigned to a device group
      mUnassignedIterations -= newTask.EndIndex - newTask.StartIndex + 1;

      if(newTask.EndIndex < newTask.StartIndex)
      {
        cout << "Uh oh." << endl;
      }

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

bool ParallelForPerformanceModel::workRemains(size_t deviceGroup) const
{
  //If the sample queue for the device is empty and there is no more work to do,
  //we're done
  return mPendingSampleQueues[deviceGroup].length() > 0 || 
         mUnassignedIterations > 0 ?
           true :
           false;
}

PendingTask ParallelForPerformanceModel::getWork(const size_t deviceGroup)
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
    double bestSpeedup = 0.0;
    size_t bestSample = 0;
    bool leftOfSample = false;
    size_t bestChunkSize = 0;

    for(size_t curSample = 0; curSample < curDeviceModel.size(); curSample++)
    {
      if(curSample > 0 && 
         mRemainingWork[curSample - 1].Start <= 
         mRemainingWork[curSample - 1].End) //Check to the left of the sample
      {
        size_t chunkSize = mRemainingWork[curSample - 1].End -
                           mRemainingWork[curSample - 1].Start;

        chunkSize = chunkSize > kDefaultChunkSize ? 
                    kDefaultChunkSize : 
                    chunkSize;

        IndexRange& curWork = mRemainingWork[curSample - 1];

        double curSpeedup = normSpeedup(deviceGroup,
                                        curSample - 1,
                                        curSample,
                                        curWork.End - chunkSize,
                                        curWork.End);
        if(curSpeedup > bestSpeedup)
        {
          bestSpeedup = curSpeedup;
          bestSample = curSample;
          leftOfSample = true;
          bestChunkSize = chunkSize;
        }
      }

      if(curSample < curDeviceModel.size() - 1 &&
         mRemainingWork[curSample].Start <=
         mRemainingWork[curSample].End) //Check to the right of sample
      {
        size_t chunkSize = mRemainingWork[curSample].End -
                           mRemainingWork[curSample].Start;

        chunkSize = chunkSize > kDefaultChunkSize ? 
                    kDefaultChunkSize : 
                    chunkSize;

        IndexRange& curWork = mRemainingWork[curSample];

        double curSpeedup = normSpeedup(deviceGroup,
                                        curSample,
                                        curSample + 1,
                                        curWork.Start,
                                        curWork.Start + chunkSize);
        if(curSpeedup > bestSpeedup)
        {
          bestSpeedup = curSpeedup;
          bestSample = curSample;
          leftOfSample = false;
          bestChunkSize = chunkSize;
        }
      }
    }

    if(leftOfSample == true)
    {
      work.StartIndex = mRemainingWork[bestSample - 1].End - bestChunkSize;
      work.EndIndex = mRemainingWork[bestSample - 1].End;
      work.SampleNumber = bestSample;

      mRemainingWork[bestSample - 1].End -= bestChunkSize + 1;
    }
    else
    {
      work.StartIndex = mRemainingWork[bestSample].Start;
      work.EndIndex = mRemainingWork[bestSample].Start + bestChunkSize;
      work.SampleNumber = bestSample;

      mRemainingWork[bestSample].Start += bestChunkSize + 1;
    }

    mUnassignedIterations -= work.EndIndex - work.StartIndex + 1;

    if(work.EndIndex < work.StartIndex)
    {
      cout << "Well shit." << endl;
    }

    return work;
  }
}

double ParallelForPerformanceModel::normSpeedup(const size_t thisDeviceGroup, 
                                                const size_t sample0,
                                                const size_t sample1,
                                                const size_t start,
                                                const size_t end) const
{
  const vector<Sample>& thisDeviceModel = mModel[thisDeviceGroup];

  double normSpeedup = 0.0;
  double t0;
  double t1;
  double thisChunkTime;
  double thatChunkTime;

  //Compute the estimated execution time for this device
  t0 = interpolate(thisDeviceModel[sample0].Right,
                   thisDeviceModel[sample1].Left,
                   thisDeviceModel[sample0].End,
                   thisDeviceModel[sample1].Start,
                   start);
  
  t1 = interpolate(thisDeviceModel[sample0].Right,
                   thisDeviceModel[sample1].Left,
                   thisDeviceModel[sample0].End,
                   thisDeviceModel[sample1].Start,
                   start);

  //Use trapezoidal integration to get estimated chunk execution time
  thisChunkTime = 0.5 * (t0 + t1) * (double)(end - start);

  //Compute a two norm of the speedup over all other device groups
  for(size_t thatDeviceGroup = 0; 
      thatDeviceGroup < mModel.size(); 
      thatDeviceGroup++)
  {
    if(thisDeviceGroup == thatDeviceGroup)
    {
      continue;
    }

    const vector<Sample>& thatDeviceModel = mModel[thatDeviceGroup];

    //If samples are valid, compute the speedup of this device over that
    if(thatDeviceModel[sample1].IsValid == true &&
       thatDeviceModel[sample0].IsValid == true)
    {
      //Fetch start and end timing points from the other device's model
      t0 = interpolate(thatDeviceModel[sample0].Right,
                       thatDeviceModel[sample1].Left,
                       thatDeviceModel[sample0].End,
                       thatDeviceModel[sample1].Start,
                       start);

      t1 = interpolate(thatDeviceModel[sample0].Right,
                       thatDeviceModel[sample1].Left,
                       thatDeviceModel[sample0].End,
                       thatDeviceModel[sample1].Start,
                       end);

      //Do trapezoidal integration to get estimated execution time
      thatChunkTime = 0.5 * (t0 + t1) * (double)(end - start);
      
      double speedup = thatChunkTime / thisChunkTime;

      normSpeedup += speedup * speedup;
    }
    else //If samples aren't valid, use the default speedup value
    {
      normSpeedup += kDefaultSpeedup * kDefaultSpeedup;
    }
  }

  return sqrt(normSpeedup);
}

double ParallelForPerformanceModel::interpolate(const double t0, 
                                                const double t1,
                                                const size_t x0,
                                                const size_t x1,
                                                const size_t location) const
{
  double slope = (t1 - t0) / (double)(x1 - x0);

  return slope * (double)(location - x0) + t0;
}

void ParallelForPerformanceModel::updateModel(const size_t start, 
                                              const size_t end, 
                                              const size_t sampleNumber,
                                              const size_t devGroup,
                                              const double time)
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

void ParallelForPerformanceModel::printRemainingWork() const
{
  cout << "Remaining:" << endl;

  for(size_t i = 0; i < mRemainingWork.size(); i++)
  {
    cout << "\t" << mRemainingWork[i].Start 
      << " to " << mRemainingWork[i].End << endl;
  }
}

void clUtil::ParallelFor(const size_t start, 
                         const size_t stride, 
                         const size_t end, 
                         function<void (size_t, size_t)> loopBody,
                         const size_t numSamples)
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
  size_t iterationsRemaining = end - start + 1;

  //model.printRemainingWork();

  vector<DeviceStatus> deviceStatuses(Device::GetDevices().size());

  //Parallel for scheduling loop
  while(iterationsRemaining > 0)
  {
    for(size_t curDevice = 0; 
        curDevice < Device::GetDevices().size(); 
        curDevice++)
    {
      DeviceStatus& curDeviceStatus = deviceStatuses[curDevice];
      size_t deviceGroup = DeviceGroupInfo::Get()[curDevice];

      //cout << "\tremaining " << iterationsRemaining << endl;

      //If this device isn't busy, get some work from the model and run it
      if(curDeviceStatus.IsBusy == false && 
         model.workRemains(deviceGroup) == true)
      {
        PendingTask work;

        work = model.getWork(deviceGroup);

#if 0
        cout << "device " << curDevice
             << " start " << work.StartIndex 
             << " end " << work.EndIndex << endl;
        model.printRemainingWork();
#endif
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

          iterationsRemaining -= curDeviceStatus.EndIndex - 
                                 curDeviceStatus.StartIndex + 
                                 1;
        }
      }
    }
  }

  Device::SetCurrentDevice(oldDeviceNum);
}
