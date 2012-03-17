#pragma once
#include <map>
#include <memory>
#include <math.h>
#include <functional>
#include "clUtilDeviceGroup.h"
#include "clUtilDevice.h"
#include "clUtilUtility.h"

namespace clUtil
{

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
    size_t SampleNumber;
  };

  class ParallelForPerformanceModel
  {
    struct Sample
    {
      size_t Start;
      size_t End;
      double Left;
      double Center;
      double Right;
      bool IsValid;

      Sample() :
        Start(0),
        End(0),
        Left(NAN),
        Center(NAN),
        Right(NAN),
        IsValid(false)
      {
      }
    };

    struct IndexRange
    {
      size_t Start;
      size_t End;
    };

    friend void ParallelFor(const size_t start, 
                            const size_t stride, 
                            const size_t end, 
                            std::function<void (size_t, size_t)> loopBody,
                            const size_t numSamples);

    private:
      std::vector<Utility::UnsafeQueue<PendingTask>> mPendingSampleQueues;
      std::vector<std::vector<Sample>> mModel;
      std::vector<IndexRange> mRemainingWork;
      size_t mNumSamples;
      size_t mStart;
      size_t mEnd;
      size_t mUnassignedIterations;

      ParallelForPerformanceModel(const size_t numSamples,
                                  const size_t start,
                                  const size_t end);

      PendingTask getWork(const size_t deviceGroup);
 
      void updateModel(const size_t start, 
                       const size_t end, 
                       const size_t sampleNumber,
                       const size_t devGroup, 
                       const double time);

      double interpolate(const double t0,
                         const double t1,
                         const size_t x0,
                         const size_t x1,
                         const size_t location) const;
      
      double normSpeedup(const size_t deviceGroup, 
                         const size_t sample0,
                         const size_t sample1,
                         const size_t start, 
                         const size_t end) const;

      bool workRemains(size_t deviceGroup) const;

      void printRemainingWork() const;

    public:
  };

  void ParallelFor(const size_t start,
                   const size_t stride,
                   const size_t end,
                   std::function<void (size_t, size_t)> loopBody,
                   //void (*loopBody)(size_t start, size_t end),
                   const size_t numSamples = 10);
}
