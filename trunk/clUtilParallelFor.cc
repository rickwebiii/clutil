#include "clUtilParallelFor.h"

using namespace std;
using namespace clUtil;

bool DeviceGroupInfo::singletonInitialized = false;
DeviceGroupInfo DeviceGroupInfo::deviceGroupInfoSingleton;

ParallelForPerformanceModel::ParallelForPerformanceModel(size_t numSamples) :
  mNumSamples(numSamples)
{
  size_t numDeviceGroups = DeviceGroupInfo::Get().numGroups();

  unique_ptr<unsigned int[]> 
    currentSample(new unsigned int[numDeviceGroups]);

  //Initialize the current sample array
  for(unsigned int curDeviceGroup = 0;
      curDeviceGroup < numDeviceGroups; 
      curDeviceGroup++)
  {
    currentSample[curDeviceGroup] = 0u;
  }

  mCurrentSample = move(currentSample);
}

void clUtil::ParallelFor(size_t start, 
                         size_t stride, 
                         size_t end, 
                         void (*loopBody)(size_t start, size_t end),
                         unsigned int numSamples)
{
  ParallelForPerformanceModel model(numSamples);
}
