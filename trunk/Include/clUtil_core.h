#pragma once
#include "clUtilException.h"
#include "clUtilDevice.h"
#include "clUtilCommon.h"
#include "clUtilUtility.h"

#define kCLUtilMaxDevices 64
#define kCLUtilMaxKernelNameLength 128


typedef struct _clUtilPlatformVersion
{
  unsigned short major;
  unsigned short minor;
}clUtilPlatformVersion;


class clMemPointer
{
  public:
    cl_mem mBase;
    int mOffset;
    clMemPointer(const clMemPointer& copy)
    {
      mBase = copy.mBase;
      mOffset = copy.mOffset;
    }
    clMemPointer(cl_mem base, int offset)
    {
      mBase = base;
      mOffset = offset;
    }

    //Operators
    clMemPointer operator[](int offset)
    {
      return clMemPointer(mBase, mOffset + offset);
    }
    clMemPointer operator=(cl_mem base)
    {
      mBase = base;
      mOffset = 0;
      return clMemPointer(mBase, mOffset);
    }
    clMemPointer operator+=(int offset)
    {
      mOffset += offset;
      return clMemPointer(mBase, mOffset);
    }
    clMemPointer operator-=(int offset)
    {
      mOffset -= offset;
      return clMemPointer(mBase, mOffset);
    }

  protected:
    clMemPointer();
};

//typedef void (*clUtilCallback)(cl_event, cl_int);
//typedef std::function<void (void)> clUtilCallback;
typedef void (*clUtilCallback)();

//Run user callback...
void clUtilRunLambda(cl_event event,
                     cl_int status,
                     void* user_data);

//Init functions
cl_int clUtilInitDevices();
cl_int clUtilInitialize(const char** filenames, 
                        size_t numFiles, 
                        const char* cachename = NULL,
                        const char* options = NULL);
cl_int clUtilFinalize();
void clUtilEnableOOOExecution();

//Info functions
cl_int clUtilSetDeviceNum(cl_uint device);
cl_int clUtilGetDeviceNum();
cl_uint clUtilGetNumDevices();

//For accessing internals
cl_command_queue clUtilGetCommandQueue();
cl_context clUtilGetContext();
cl_program clUtilGetProgram();
cl_kernel clUtilGetKernel(std::string& kernelName, cl_int* err);
cl_device_id clUtilGetDevice();

//Get info crap
cl_int clUtilGetPointerSize();
size_t clUtilGetMaxBlockSize();
char* clUtilGetDeviceName();
char* clUtilGetDeviceVendor();
char* clUtilGetDeviceDriver();
clUtilPlatformVersion clUtilGetPlatformVersion();
const char* clUtilGetPlatformVersionString();
cl_uint clUtilGetMaxWriteImages();
void clUtilGetSupportedImageFormats();

//---Memory crap---
//Allocation
cl_int clUtilAlloc(size_t bytes, cl_mem* gpuBuffer);
cl_int clUtilFree(cl_mem buffer);

//Data transfers
//Synchronous
cl_int clUtilDevicePut(void* buffer, size_t len, cl_mem gpuBuffer);
cl_int clUtilDeviceGet(void* buffer, size_t len, cl_mem gpuBuffer);

//Asynchronous
cl_int clUtilDevicePut(void* buffer, 
                       size_t len,
                       cl_mem gpuBuffer,
                       clUtilCallback&& callback,
                       bool shouldFlush = true);

cl_int clUtilDeviceGet(void* buffer, 
                       size_t len,
                       cl_mem gpuBuffer,
                       clUtilCallback&& callback,
                       bool shouldFlush = true);

//---Image crap---
//Data transfers
//Synchronous
cl_int clUtilPutImage1D(cl_mem image,
                        const size_t offset,
                        const size_t region,
                        void* ptr);

cl_int clUtilGetImage1D(cl_mem image,
                        const size_t offset,
                        const size_t region,
                        void* ptr);

cl_int clUtilCreateImage1D(size_t numPixels,
                           cl_channel_order order,
                           cl_channel_type type,
                           cl_mem* image);

//Matrix copies from global memory to image
cl_int clUtilCopyToImageFloat(cl_mem buffer, 
                              int offset,
                              int m,
                              int n,
                              int ld,
                              cl_mem* image);
cl_int clUtilCopyToImageTransposeFloat(cl_mem buffer, 
                                       int offset,
                                       int m,
                                       int n,
                                       int ld,
                                       cl_mem* image);
cl_int clUtilCopyToImageDouble(cl_mem buffer, 
                               int offset,
                               int m,
                               int n,
                               int ld,
                               cl_mem* image);
cl_int clUtilCopyToImageTransposeDouble(cl_mem buffer, 
                                        int offset,
                                        int m,
                                        int n,
                                        int ld,
                                        cl_mem* image);
cl_int clUtilCopyToImageFloat4(cl_mem buffer, 
                               int offset,
                               int m,
                               int n,
                               int ld,
                               cl_mem* image);
cl_int clUtilCopyToImageTransposeFloat4(cl_mem buffer, 
                                        int offset,
                                        int m,
                                        int n,
                                        int ld,
                                        cl_mem* image);
cl_int clUtilCopyToImageDouble2(cl_mem buffer, 
                                int offset,
                                int m,
                                int n,
                                int ld,
                                cl_mem* image);
cl_int clUtilCopyToImageTransposeDouble2(cl_mem buffer, 
                                         int offset,
                                         int m,
                                         int n,
                                         int ld,
                                         cl_mem* image);
cl_int clUtilDebugPrintImageFloat(cl_mem image);
cl_int clUtilDebugPrintImageDouble(cl_mem image);

//Timing
double clUtilGetTime();
