#pragma once
#include "clUtilCommon.h"
#include "clUtilDevice.h"
#include "clUtilException.h"

namespace clUtil
{
  class Memory
  {
    private:
      Memory operator=(const Memory& b)
      {
        return Memory(b);
      }
    protected:
      cl_mem mMemHandle;
      Device& mDevice;
    public:
      Memory(Device& device = Device::GetCurrentDevice()) :
        mDevice(device)
      {
      }

      Memory(const Memory& b) :
        mMemHandle(b.mMemHandle),
        mDevice(b.mDevice)
      {
        clRetainMemObject(mMemHandle);
      }

      ~Memory()
      {
        clReleaseMemObject(mMemHandle);
      }
  };  

  class Image : Memory
  {
    private:
      size_t mDimensions;
      size_t m1DWidth;
      size_t mWidth;
      size_t mHeight;
      size_t mDepth;
      cl_channel_order mChannelOrder;
      cl_channel_type mChannelType;

      void initialize();
    public:
      Image(size_t width, 
            cl_channel_order channelOrder,
            cl_channel_type channelType,
            Device& device = Device::GetCurrentDevice()) :
        Memory(device),
        mDimensions(1),
        m1DWidth(width),
        mWidth(0),
        mHeight(0),
        mDepth(0),
        mChannelOrder(channelOrder),
        mChannelType(channelType)
      {
        initialize();
      }

      Image(size_t width,
            size_t height,
            cl_channel_order channelOrder,
            cl_channel_type channelType,
            Device& device = Device::GetCurrentDevice()) :
        Memory(device),
        mDimensions(2),
        m1DWidth(0),
        mWidth(width),
        mHeight(height),
        mDepth(1),
        mChannelOrder(channelOrder),
        mChannelType(channelType)
      {
        initialize();
      }

      Image(size_t width,
            size_t height,
            size_t depth,
            cl_channel_order channelOrder,
            cl_channel_type channelType,
            Device& device = Device::GetCurrentDevice()) :
        Memory(device),
        mDimensions(3),
        m1DWidth(0),
        mWidth(width),
        mHeight(height),
        mDepth(depth),
        mChannelOrder(channelOrder),
        mChannelType(channelType)
      {
        initialize();
      }

      void put(void* pointer, size_t len = 0);
      void get(void* pointer, size_t len = 0);

  };
}

