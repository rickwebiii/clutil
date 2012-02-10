#pragma once
#include <map>
#include <memory>
#include <math.h>
#include "clUtilDeviceGroup.h"
#include "clUtilDevice.h"

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

  class ParallelForPerformanceModel
  {
    friend void ParallelFor(size_t start, 
                            size_t stride, 
                            size_t end, 
                            void (*loopBody)(size_t start, size_t end),
                            unsigned int numSamples);

    private:
      std::unique_ptr<unsigned int[]> mCurrentSample;
      size_t mNumSamples;

      ParallelForPerformanceModel(size_t numSamples);

    public:
  };

  void ParallelFor(size_t start,
                   size_t stride,
                   size_t end,
                   void (*loopBody)(size_t start, size_t end),
                   unsigned int numSamples = 10);
}
