#pragma once
#include "clUtilCommon.h"
#include "clUtilDevice.h"
#include "clUtilException.h"

#define kCLUtilAllocPinnedBuffer ((void*)0x1)

namespace clUtil
{
  class Memory
  {
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

      cl_mem getMemHandle() const { return mMemHandle; }

      virtual void get(void* pointer, size_t len = 0) = 0;
      virtual void put(void* pointer, size_t len = 0) = 0;
      virtual bool isImage() = 0;
  };  

  class Image : public Memory
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

      virtual void put(void* pointer, size_t len = 0);
      virtual void get(void* pointer, size_t len = 0);
      virtual bool isImage() { return true; }
  };

  class Buffer : public Memory
  {
    private:
      cl_mem mParentBuffer;
      size_t mLength;
    public:

      Buffer(size_t len, 
             void* hostPtr = NULL,
             Device& device = Device::GetCurrentDevice()) : 
        Memory(device),
        mParentBuffer(0),
        mLength(len)
      {
        cl_int err;
        cl_mem_flags flags = CL_MEM_READ_WRITE;

        if(hostPtr == kCLUtilAllocPinnedBuffer)
        {
          flags |= CL_MEM_ALLOC_HOST_PTR;
          hostPtr = NULL;
        }
        else if(hostPtr != NULL)
        {
          flags |= CL_MEM_USE_HOST_PTR;
        }

        mMemHandle = clCreateBuffer(mDevice.getContext(),
                                    flags,
                                    len,
                                    hostPtr,
                                    &err);
        clUtilCheckError(err);
      }

      virtual void put(void* pointer, size_t len = 0);
      virtual void get(void* pointer, size_t len = 0);
      virtual bool isImage(){ return false; }
  };
}

