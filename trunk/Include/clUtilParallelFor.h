#pragma once
#include <map>
#include <memory>
#include <math.h>
#include "clUtilDeviceGroup.h"
#include "clUtilDevice.h"
#include "clUtilUtility.h"

namespace clUtil
{
  struct ParallelForSample
  {
    float Left;
    float Center;
    float Right;

    ParallelForSample() :
      Left(NAN),
      Center(NAN),
      Right(NAN)
    {
    }
  };

  struct CompletedTask
  {
    double Time;
    size_t SampleNumber;
    size_t StartIndex;
    size_t EndIndex;
  };

  struct PendingTask
  {
    size_t StartIndex;
    size_t EndIndex;
  };

  class ParallelForPerformanceModel
  {
    friend void ParallelFor(size_t start, 
                            size_t stride, 
                            size_t end, 
                            void (*loopBody)(size_t start, size_t end),
                            unsigned int numSamples);

    private:
      std::vector<Utility::UnsafeQueue<PendingTask>> mPendingSampleQueues;
      size_t mNumSamples;
      size_t mStart;
      size_t mEnd;

      ParallelForPerformanceModel(size_t numSamples,
                                  size_t start,
                                  size_t end);

      PendingTask getWork(size_t deviceGroup);
    public:
  };

  void ParallelFor(size_t start,
                   size_t stride,
                   size_t end,
                   void (*loopBody)(size_t start, size_t end),
                   unsigned int numSamples = 10);
}
