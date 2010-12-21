#pragma once
#ifdef __APPLE__
#include <OpenCL/cl.h>
#include <mach/mach_time.h>
#include <mach/mach.h>
#include <CoreServices/CoreServices.h>
#else
#include <CL/cl.h>
#include <sys/time.h>
#endif
#include <stdio.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>
#include <signal.h>
#include <new>
#include <map>
#include <string>

#define kCLUtilMaxDevices 64
#define kCLUtilMaxKernelNameLength 128

#define clUtilCheckErrorVoid(err)\
{\
  if(err != CL_SUCCESS)\
  {\
    printf("%s:%d::%s\n", __FILE__, __LINE__, clUtil::getErrorCode(err));\
    raise(SIGTRAP);\
    return;\
  }\
}

#define clUtilCheckError(err)\
{\
  if(err != CL_SUCCESS)\
  {\
    printf("%s:%d::%s\n", __FILE__, __LINE__, clUtil::getErrorCode(err));\
    raise(SIGTRAP);\
    return err;\
  }\
}

typedef struct _DeviceSize_t
{
  size_t deviceWidth;
  union
  {
    size_t host;
    long long device;
    unsigned int devicePart[2];
  };
}DeviceSize_t;

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

class clUtil
{
  protected:
    static cl_device_id gDevices[kCLUtilMaxDevices];
    static cl_context gContexts[kCLUtilMaxDevices];
    static cl_program gPrograms[kCLUtilMaxDevices];
    static cl_command_queue gCommandQueues[kCLUtilMaxDevices];
    static cl_uint gNumDevices;
    static int gCurrentDevice;
    static cl_kernel* gKernels[kCLUtilMaxDevices];
    static std::map<std::string, cl_kernel> 
      gKernelNameLookup[kCLUtilMaxDevices];

    //Make constructors inaccessable; everything in this class is static
    clUtil();
    clUtil(const clUtil& copy);
    
    //Helper functions that should never be called by others
    static cl_int initDevices();
    static cl_int buildPrograms(const char** filenames, 
                                size_t numFiles,
                                const char* options);
    static cl_int getKernels();
    static cl_int loadBinaries(const char* cachename);
  public:
    //Init and management crap
    static cl_int initialize(const char** filenames, 
                             size_t numFiles, 
                             const char* cachename = NULL,
                             const char* options = NULL);
    static cl_int setDeviceNum(cl_int device);
    static cl_int getDeviceNum();
    static cl_uint getNumDevices();
    static cl_program getProgram();
    static cl_command_queue getCommandQueue();
    static cl_int LoadBinaryFromDisk(const char *);
    static cl_kernel getKernel(std::string& kernelName, cl_int* err);

    //Get info crap
    static cl_int getPointerSize();
    static size_t getMaxBlockSize();
    static char* getDeviceName();
    static char* getDeviceVendor();
    static char* getDeviceDriver();
    static cl_uint getMaxWriteImages();
    static void dumpBinary(const char* filename);
    static void getSupportedImageFormats();

    //Turns error code into string
    static const char* getErrorCode(cl_int err);

    //Memory crap
    static cl_int alloc(size_t bytes, cl_mem* gpuBuffer);
    static cl_int devicePut(void* buffer, size_t len, cl_mem gpuBuffer);
    static cl_int deviceGet(void* buffer, size_t len, cl_mem gpuBuffer);
    static cl_int free(cl_mem buffer);

    //Image copy crap
    static cl_int copyToImageFloat(cl_mem buffer, 
                                   int offset,
                                   int m,
                                   int n,
                                   int ld,
                                   cl_mem* image);
    static cl_int copyToImageTransposeFloat(cl_mem buffer, 
                                            int offset,
                                            int m,
                                            int n,
                                            int ld,
                                            cl_mem* image);
    static cl_int copyToImageDouble(cl_mem buffer, 
                                    int offset,
                                    int m,
                                    int n,
                                    int ld,
                                    cl_mem* image);
    static cl_int copyToImageTransposeDouble(cl_mem buffer, 
                                             int offset,
                                             int m,
                                             int n,
                                             int ld,
                                             cl_mem* image);
    static cl_int copyToImageFloat4(cl_mem buffer, 
                                    int offset,
                                    int m,
                                    int n,
                                    int ld,
                                    cl_mem* image);
    static cl_int copyToImageTransposeFloat4(cl_mem buffer, 
                                             int offset,
                                             int m,
                                             int n,
                                             int ld,
                                             cl_mem* image);
    static cl_int copyToImageDouble2(cl_mem buffer, 
                                     int offset,
                                     int m,
                                     int n,
                                     int ld,
                                     cl_mem* image);
    static cl_int copyToImageTransposeDouble2(cl_mem buffer, 
                                              int offset,
                                              int m,
                                              int n,
                                              int ld,
                                              cl_mem* image);
    static cl_int debugPrintImageFloat(cl_mem image);
    static cl_int debugPrintImageDouble(cl_mem image);

    //Timing
    static double getTime();
};
