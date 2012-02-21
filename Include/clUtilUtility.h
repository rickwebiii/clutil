#pragma once
#include "clUtilCommon.h"
#include "clUtilException.h"

namespace clUtil
{
  namespace Utility
  {
    std::vector<std::string> split(std::string str, char delimiter);
    cl_int fetchPlatformInfo(cl_platform_id platformID,
                             cl_platform_info paramName,
                             std::string& param);
    cl_int fetchDeviceInfo(cl_device_id deviceID,
                           cl_device_info paramName,
                           std::string& param);
    template <typename T> cl_int fetchDeviceInfo(cl_device_id deviceID,
                                                 cl_device_info paramName, 
                                                 T& param)
    {
      cl_int err;

      err = clGetDeviceInfo(deviceID, 
                            paramName,
                            sizeof(T), 
                            (void*)&param, 
                            NULL);
      clUtilCheckError(err);

      return CL_SUCCESS;
    }

    double getTime();

    template <typename T> class UnsafeQueue
    {
      private:
        volatile size_t mFront;
        volatile size_t mBack;
        size_t mSize;
        size_t mMask;
        std::vector<T> mCyclicQueue;

      public:
        UnsafeQueue(size_t pow2Size) :
          mFront(0),
          mBack(0),
          mSize(1 << pow2Size),
          mMask((0x1 << pow2Size) - 1),
          mCyclicQueue(mSize)
        {
          if(pow2Size > 63)
          {
            throw clUtilException("Internal error: queues cannot be longer than"
                                  "2^63 elements. Report this as a bug.");
          }
        }

        void push(T item)
        {
          mCyclicQueue[mBack & mMask] = item;
          mBack++;
        }

        bool pop(T& item)
        {
          if(mFront >= mBack)
          {
            return false;
          }

          item = mCyclicQueue[mFront & mMask];
          mFront++;

          return true;
        }

        size_t length()
        {
          return mBack - mFront;
        }
    };
  }
}
