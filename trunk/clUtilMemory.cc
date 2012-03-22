#include "clUtilMemory.h"

using namespace clUtil;

void Image::initialize()
{
  cl_int err;

  if(mDimensions == 1) //1D image
  {
    //Map the 1D image to a 2D image
    mWidth = mDevice.getDeviceInfo().Image2DMaxWidth;
    mHeight = m1DWidth % mWidth == 0 ? 
      m1DWidth / mWidth : 
      m1DWidth / mWidth + 1;

    cl_image_format imageFormat = {mChannelOrder, mChannelType};

    mMemHandle = clCreateImage2D(mDevice.getContext(),
                                 CL_MEM_READ_WRITE,
                                 &imageFormat,
                                 mWidth,
                                 mHeight,
                                 0,  
                                 NULL,
                                 &err);
    clUtilCheckError(err);
  }
  else if(mDimensions == 2) //2D image
  {
    cl_image_format imageFormat = {mChannelOrder, mChannelType};

    mMemHandle = clCreateImage2D(mDevice.getContext(),
                                 CL_MEM_READ_WRITE,
                                 &imageFormat,
                                 mWidth,
                                 mHeight,
                                 0,  
                                 NULL,
                                 &err);
    clUtilCheckError(err);
  }
  else if(mDimensions == 3) //3D image
  {
    cl_image_format imageFormat = {mChannelOrder, mChannelType};

    mMemHandle = clCreateImage3D(mDevice.getContext(),
                                 CL_MEM_READ_WRITE,
                                 &imageFormat,
                                 mWidth,
                                 mHeight,
                                 mDepth,
                                 0,
                                 0,
                                 NULL,
                                 &err);
    clUtilCheckError(err);
  }
  else //This should never be reached
  {
    throw clUtilException("Invalid image dimensionality. This should never "
                          "happen; please report this as a bug.");
  }
}

void Image::put(void const* pointer, const size_t len)
{
  cl_int err;
  cl_event nextEvent = NULL;

  if(mDimensions == 1) //1D image
  {
    size_t origin[3] = {0, 0, 0};
    size_t region[3] = {mWidth, mHeight, 1};
    size_t imageElementSize;
    //size_t actualLength; //TODO allow fetching arbitrary regions

    //actualLength = len == 0 ? m1DWidth : len;

    err = clGetImageInfo(mMemHandle,
                         CL_IMAGE_ELEMENT_SIZE,
                         sizeof(imageElementSize),
                         &imageElementSize,
                         NULL);
    clUtilCheckError(err);

    //Copy all but the last row to the device
    if(mHeight > 1)
    {
      region[1] = mHeight - 1;

      err = clEnqueueWriteImage(mDevice.getCommandQueue(),
                                mMemHandle,
                                CL_FALSE,
                                origin,
                                region,
                                0,
                                0,
                                pointer,
                                mLastAccess != NULL ? 1 : 0,
                                mLastAccess != NULL ? &mLastAccess : NULL,
                                &nextEvent);

      clUtilCheckError(err);

      setLastAccess(nextEvent);
    
      mDevice.addProfilingEvent(nextEvent);

      err = clReleaseEvent(nextEvent);
      clUtilCheckError(err);
    }

    //Copy the last row to the device
    origin[1] = mHeight - 1;

    region[0] = m1DWidth % mWidth == 0 ? mWidth : m1DWidth % mWidth;
    region[1] = 1;

    err = clEnqueueWriteImage(mDevice.getCommandQueue(),
                              mMemHandle,
                              CL_FALSE,
                              origin,
                              region,
                              0,
                              0,
                              &((char*)pointer)[imageElementSize * 
                              (mHeight - 1) * mWidth],
                              mLastAccess != NULL ? 1 : 0,
                              mLastAccess != NULL ? &mLastAccess : NULL,
                              &nextEvent);
    clUtilCheckError(err);

    setLastAccess(nextEvent);   
    
    mDevice.addProfilingEvent(nextEvent);

    err = clReleaseEvent(nextEvent);
    clUtilCheckError(err);
  }
  else if(mDimensions == 2 || mDimensions == 3)
  {
    size_t origin[3] = {0, 0, 0};
    size_t region[3] = {mWidth, mHeight, mDepth};

    err = clEnqueueWriteImage(mDevice.getCommandQueue(),
                              mMemHandle,
                              CL_FALSE,
                              origin,
                              region,
                              0,
                              0,
                              pointer,
                              mLastAccess != NULL ? 1 : 0,
                              mLastAccess != NULL ? &mLastAccess : NULL,
                              &nextEvent);
    clUtilCheckError(err);

    setLastAccess(nextEvent);
    
    mDevice.addProfilingEvent(nextEvent);

    err = clReleaseEvent(nextEvent);
    clUtilCheckError(err);
  }
  else
  {
    throw clUtilException("Invalid image dimensionality. This should never "
                          "happen; please report this as a bug.");
  }
}

void Image::get(void* const pointer, const size_t len)
{
  cl_int err;
  cl_event nextEvent;

  if(mDimensions == 1) //1D image
  {
    size_t origin[3] = {0, 0, 0};
    size_t region[3] = {mWidth, mHeight, 1};
    size_t imageElementSize; 
    //size_t actualLength;

    //actualLength = len == 0 ? m1DWidth : len;

    err = clGetImageInfo(mMemHandle,
                         CL_IMAGE_ELEMENT_SIZE,
                         sizeof(imageElementSize),
                         &imageElementSize,
                         NULL);
    clUtilCheckError(err);

    //Copy all but the last row to the device
    if(mHeight > 1)
    {
      region[1] = mHeight - 1;

      err = clEnqueueReadImage(mDevice.getCommandQueue(),
                               mMemHandle,
                               CL_FALSE,
                               origin,
                               region,
                               0,
                               0,
                               pointer,
                               mLastAccess != NULL ? 1 : 0,
                               mLastAccess != NULL ? &mLastAccess : NULL,
                               &nextEvent);
      clUtilCheckError(err);

      setLastAccess(nextEvent);
    
      mDevice.addProfilingEvent(nextEvent);

      err = clReleaseEvent(nextEvent);
      clUtilCheckError(err);
    }

    //Copy the last row to the device
    origin[1] = mHeight - 1;

    region[0] = m1DWidth % mWidth == 0 ? mWidth : m1DWidth % mWidth;
    region[1] = 1;

    err = clEnqueueReadImage(mDevice.getCommandQueue(),
                             mMemHandle,
                             CL_FALSE,
                             origin,
                             region,
                             0,
                             0,
                             &((char*)pointer)[imageElementSize * 
                             (mHeight - 1) * mWidth],
                             mLastAccess != NULL ? 1 : 0,
                             mLastAccess != NULL ? &mLastAccess : NULL,
                             &nextEvent);
    clUtilCheckError(err);

    setLastAccess(nextEvent);   
    
    mDevice.addProfilingEvent(nextEvent);

    err = clReleaseEvent(nextEvent);
    clUtilCheckError(err);
  }
  else if(mDimensions == 2 || mDimensions == 3)
  {
    size_t origin[3] = {0, 0, 0};
    size_t region[3] = {mWidth, mHeight, mDepth};

    err = clEnqueueReadImage(mDevice.getCommandQueue(),
                             mMemHandle,
                             CL_FALSE,
                             origin,
                             region,
                             0,
                             0,
                             pointer,
                             mLastAccess != NULL ? 1 : 0,
                             mLastAccess != NULL ? &mLastAccess : NULL,
                             &nextEvent);
    clUtilCheckError(err);

    setLastAccess(nextEvent);   
  
    mDevice.addProfilingEvent(nextEvent);

    err = clReleaseEvent(nextEvent);
    clUtilCheckError(err);
  }
  else
  {
    throw clUtilException("Invalid image dimensionality. This should never "
                          "happen; please report this as a bug.");
  }
}

void Buffer::put(const void* const pointer, const size_t len)
{
  cl_int err;
  size_t length = len == 0 ? mLength : len;
  cl_event nextEvent;

  err = clEnqueueWriteBuffer(mDevice.getCommandQueue(),
                             mMemHandle,
                             CL_FALSE,
                             0,
                             length,
                             pointer,
                             mLastAccess != NULL ? 1 : 0,
                             mLastAccess != NULL ? &mLastAccess : NULL,
                             &nextEvent);
  clUtilCheckError(err);

  setLastAccess(nextEvent);

  mDevice.addProfilingEvent(nextEvent);

  err = clReleaseEvent(nextEvent);
  clUtilCheckError(err);
}

void Buffer::get(void* const pointer, const size_t len)
{
  cl_int err;
  size_t length = len == 0 ? mLength : len;
  cl_event nextEvent;

  err = clEnqueueReadBuffer(mDevice.getCommandQueue(),
                            mMemHandle,
                            CL_FALSE,
                            0,
                            length,
                            pointer,
                            mLastAccess != NULL ? 1 : 0,
                            mLastAccess != NULL ? &mLastAccess : NULL,
                            &nextEvent);
  clUtilCheckError(err);

  setLastAccess(nextEvent);

  mDevice.addProfilingEvent(nextEvent);

  err = clReleaseEvent(nextEvent);
  clUtilCheckError(err);
}
