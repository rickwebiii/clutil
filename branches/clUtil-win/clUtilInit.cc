#include "clUtil.h"

using namespace clUtil;
using namespace std;

static cl_command_queue_properties commandQueueFlags = 0;

static char* fileToString(const char* filename, size_t * filesize)
{
  int fid = open(filename, O_RDONLY);
  struct stat fileInfo;
  char* fileBuffer;

  if(fid == -1) 
  {
    //printf("%s:%d::Could not open file %s.\n", __FILE__, __LINE__, filename);
    return NULL;
  }

  //Get the file's size and allocate a buffer to hold its text
  if(fstat(fid, &fileInfo) != 0)
  {
    //printf("%s:%d::Could not stat file %s.\n", __FILE__, __LINE__, filename);
    return NULL;
  }

  *filesize = fileInfo.st_size;

  fileBuffer = new char[fileInfo.st_size + 1]; 

  if(read(fid, fileBuffer, fileInfo.st_size) != fileInfo.st_size)
  {
    printf("%s:%d::Could not read file %s.\n", __FILE__, __LINE__, filename);
    delete[] fileBuffer;
    close(fid);
    return NULL;
  }

  //Terminate the string
  fileBuffer[fileInfo.st_size] = '\0';

  if(close(fid) != 0)
  {
    printf("%s:%d::Could not close file %s.\n", __FILE__, __LINE__, filename);
    delete[] fileBuffer;
    return NULL;
  }

  return fileBuffer;
}

static cl_int loadBinaries(const char* cachename)
{
  char binaryFileName[256];
  cl_int err;

  for(unsigned int curDevice = 0; curDevice < gNumDevices; curDevice++)
  {
    size_t fileSize;
    char* binaryFile;

    snprintf(binaryFileName, 
             sizeof(binaryFileName) - 1, 
             "%s.device%u",
             cachename,
             curDevice);

    binaryFile = fileToString(binaryFileName, &fileSize);

    if(binaryFile == NULL)
    {
      return CL_INVALID_BINARY;
    }

    gPrograms[curDevice] = 
      clCreateProgramWithBinary(gContexts[curDevice],
                                1,
                                &gDevices[curDevice],
                                &fileSize,
                                (const unsigned char**)&binaryFile,
                                NULL,
                                &err);
    if(err != CL_SUCCESS)
    {
      return err;
    }

    err = clBuildProgram(gPrograms[curDevice],
                         1,
                         &gDevices[curDevice],
                         NULL,
                         NULL,
                         NULL);
    if(err != CL_SUCCESS)
    {
      char errString[32768];

      err = clGetProgramBuildInfo(gPrograms[curDevice],
                                  gDevices[curDevice],
                                  CL_PROGRAM_BUILD_LOG,
                                  sizeof(errString),
                                  errString,
                                  NULL);
      return err;
    }
  }

  return CL_SUCCESS;
}

static void dumpBinary(const char* filename)
{
  int fd;
  size_t binarySize[kCLUtilMaxDevices];
  char* binary[kCLUtilMaxDevices];
  cl_int err;

  err = clGetProgramInfo(gPrograms[gCurrentDevice],
                         CL_PROGRAM_BINARY_SIZES,
                         sizeof(binarySize),
                         binarySize,
                         NULL);
  if(err != CL_SUCCESS)
  {
    printf("%s:%d:%s", __FILE__, __LINE__, clUtilGetErrorCode(err));
    return;
  }

  for(size_t i = 0; i < gNumDevices; i++)
  {
    binary[i] = new(std::nothrow) char[binarySize[i]];
    if(binary == NULL) {goto CL_UTIL_DUMP_ERROR0;}
  }

  err = clGetProgramInfo(gPrograms[gCurrentDevice],
                         CL_PROGRAM_BINARIES,
                         sizeof(binary),
                         &binary,
                         NULL);
  if(err != CL_SUCCESS)
  {
    printf("%s:%d:%s", __FILE__, __LINE__, clUtilGetErrorCode(err));
    return;
  }

  fd = open(filename, 
            O_WRONLY | O_CREAT | O_TRUNC, 
            S_IRWXU | S_IRGRP | S_IROTH);
  if(fd == -1) {goto CL_UTIL_DUMP_ERROR1;}

  if(write(fd, binary[0], binarySize[0]) != (ssize_t)binarySize[0]) 
  {
    goto CL_UTIL_DUMP_ERROR2;
  }
  
  if(close(fd) == -1) {goto CL_UTIL_DUMP_ERROR1;}

  delete[] binary[0];

  return;

  //Cleanup stuff in case of error
CL_UTIL_DUMP_ERROR2:
  close(fd);
CL_UTIL_DUMP_ERROR1:
  delete[] binary[0];
CL_UTIL_DUMP_ERROR0:
  perror("Error clUtilDumpBinary:");
  return;

}

static cl_int initDevices()
{
  cl_int err;
  cl_platform_id platforms[kCLUtilMaxDevices];
  cl_uint numPlatforms;

  err = clGetPlatformIDs(kCLUtilMaxDevices,
                         platforms,
                         &numPlatforms);
  clUtilCheckError(err);

  //Get devices from each platform
  for(cl_uint i = 0; i < numPlatforms; i++)
  {
    //Skip the platform if it's not at least version 1.1
    char platformVersion[256];
    clUtilPlatformVersion version;

    err = clGetPlatformInfo(platforms[i],
                            CL_PLATFORM_VERSION,
                            sizeof(platformVersion),
                            platformVersion,
                            NULL);
    if(err != CL_SUCCESS)
    {
      version = {0, 0};
    }
    else
    {
      sscanf(platformVersion, "OpenCL %hu.%hu", &version.major, &version.minor);
    }

    if(version.major <= 1 && version.minor == 0)
    {
      continue;
    }

    cl_uint platformDevices = 0;

    err = clGetDeviceIDs(platforms[i],
                         CL_DEVICE_TYPE_ALL,
                         kCLUtilMaxDevices - gNumDevices,
                         &gDevices[gNumDevices],
                         &platformDevices);
    clUtilCheckError(err);

    gNumDevices += platformDevices;
  }

  //Create contexts for each device
  for(cl_uint i = 0; i < gNumDevices; i++)
  {
    cl_command_queue_properties properties;
    bool canExecuteOOO;

    gContexts[i] = clCreateContext(NULL,
                                   1,
                                   &gDevices[i],
                                   NULL,
                                   NULL,
                                   &err);
    clUtilCheckError(err);

    err = clGetDeviceInfo(gDevices[i],
                          CL_DEVICE_QUEUE_PROPERTIES,
                          sizeof(properties),
                          &properties,
                          NULL);
    clUtilCheckError(err);

    canExecuteOOO = (properties & CL_QUEUE_OUT_OF_ORDER_EXEC_MODE_ENABLE) != 0 ?
                    true : 
                    false;

    gCommandQueues[i] = clCreateCommandQueue(gContexts[i],
                                             gDevices[i],
                                             canExecuteOOO == true ? 
                                               commandQueueFlags : 0,
                                             &err);
    clUtilCheckError(err);
  }

  return CL_SUCCESS;
}

static cl_int buildPrograms(const char** filenames, 
                            size_t numFiles, 
                            const char* options)
{
  cl_int err;

  char** files = new char*[numFiles];

  for(size_t curFile = 0; curFile < numFiles; curFile++)
  {
    size_t filesize;
    files[curFile] = fileToString(filenames[curFile], &filesize);
    if(files[curFile] == NULL)
    {
      printf("%s:%d::Could not load source %s.\n", 
             __FILE__, 
             __LINE__, 
             files[curFile]);
      return CL_INVALID_VALUE;
    }
  }

  for(size_t curDevice = 0; curDevice < gNumDevices; curDevice++)
  {
    char deviceFlags[512];
    char deviceVendor[256];

    gPrograms[curDevice] = clCreateProgramWithSource(gContexts[curDevice],
                                                     numFiles,
                                                     (const char**)files,
                                                     NULL,
                                                     &err);
    clUtilCheckError(err);

    clGetDeviceInfo(gDevices[curDevice],
                    CL_DEVICE_VENDOR,
                    sizeof(deviceVendor),
                    deviceVendor,
                    NULL);
    clUtilCheckError(err);

    //Replace spaces with underscores and make the string uppercase
    for(size_t i = 0; i < strlen(deviceVendor); i++)
    {
      if(deviceVendor[i] == ' ')
      {
        deviceVendor[i] = '_';
      }
      else if(deviceVendor[i] <= 'z' && deviceVendor[i] >= 'a')
      {
        deviceVendor[i] -= 32;
      }
      else if(deviceVendor[i] == ',' || deviceVendor[i] == '.')
      {
        deviceVendor[i] = '_';
      }
    }

    snprintf(deviceFlags, 
             sizeof(deviceFlags) - 1, 
             "-cl-mad-enable -I/usr/include/clutil/kernels -D%s %s",
             deviceVendor,
             options == NULL ? "" : options);

    err = clBuildProgram(gPrograms[curDevice],
                         1,
                         &gDevices[curDevice],
                         deviceFlags,
                         NULL,
                         NULL);
    if(err != CL_SUCCESS)
    {
      char errString[32768];
      cl_int err1;

      err1 = clGetProgramBuildInfo(gPrograms[curDevice],
                                   gDevices[curDevice],
                                   CL_PROGRAM_BUILD_LOG,
                                   sizeof(errString),
                                   errString,
                                   NULL);
      clUtilCheckError(err1);
      printf("%s", errString);
      return err;
    }
  }

  for(size_t curFile = 0; curFile < numFiles; curFile++)
  {
    delete[] files[curFile];
  }

  delete[] files;

  return CL_SUCCESS;
}

static cl_int getKernels()
{
  for(size_t curDevice = 0; curDevice < gNumDevices; curDevice++)
  {
    cl_uint numKernels;
    cl_int err;

    //Get the number of kernels in the program
    err = clCreateKernelsInProgram(gPrograms[curDevice], 0, NULL, &numKernels);
    clUtilCheckError(err);

    //Actually create the kernels
    gKernels[curDevice] = new cl_kernel[numKernels];

    err = clCreateKernelsInProgram(gPrograms[curDevice], 
                                   numKernels,
                                   gKernels[curDevice],
                                   NULL);
    
    //Put all them there kernels in a hash table
    for(size_t curKernel = 0; curKernel < numKernels; curKernel++)
    {
      char kernelName[kCLUtilMaxKernelNameLength];

      err = clGetKernelInfo(gKernels[curDevice][curKernel], 
                            CL_KERNEL_FUNCTION_NAME,
                            kCLUtilMaxKernelNameLength,
                            kernelName,
                            NULL);
      clUtilCheckError(err);

      gKernelNameLookup[curDevice][std::string(kernelName)] = 
        gKernels[curDevice][curKernel];
    }
  }

  return CL_SUCCESS;
}

cl_int clUtilInitialize(const char** filenames, 
                        size_t numFiles, 
                        const char* cachename,
                        const char* options)
{
  cl_int err;
  bool loadBinariesSucceeded = false;

  err = initDevices();
  clUtilCheckError(err);
  
  gCurrentDevice = 0;

  if(cachename != NULL)
  {
    loadBinariesSucceeded = true;

    if(loadBinaries(cachename) != CL_SUCCESS)
    {
      loadBinariesSucceeded = false;
    }
  }

  if(filenames != NULL && loadBinariesSucceeded == false)
  {
	  err = buildPrograms(filenames, numFiles, options);
    
    //If cachename isn't NULL, dump binaries to disk
    if(cachename != NULL)
    {
      for(unsigned int curDevice = 0; curDevice < gNumDevices; curDevice++)
      {
        char binaryFileName[256];

        snprintf(binaryFileName, 
                 sizeof(binaryFileName) - 1, 
                 "%s.device%u",
                 cachename,
                 curDevice);
        gCurrentDevice = curDevice;

        dumpBinary(binaryFileName);
      }
    }
  }

  clUtilCheckError(err);

  getKernels();
  gCurrentDevice = 0;

  return err;
}

cl_int clUtilFinalize()
{
  cl_int err;

  //Free willy
  for(unsigned int curDevice = 0; curDevice < gNumDevices; curDevice++)
  {
    for(map<string, cl_kernel>::iterator curKernel = 
          gKernelNameLookup[curDevice].begin();
        curKernel != gKernelNameLookup[curDevice].end();
        curKernel++)
    {
      err = clReleaseKernel(curKernel->second);
      clUtilCheckError(err);
    }

    delete[] gKernels[curDevice];
    
    err = clReleaseContext(gContexts[curDevice]);
    clUtilCheckError(err);

    err = clReleaseProgram(gPrograms[curDevice]);
    clUtilCheckError(err);

    err = clReleaseCommandQueue(gCommandQueues[curDevice]);
    clUtilCheckError(err);
  }

  return CL_SUCCESS;
}

void clUtilEnableOOOExecution()
{
  commandQueueFlags |= CL_QUEUE_OUT_OF_ORDER_EXEC_MODE_ENABLE;
}
