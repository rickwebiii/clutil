#include "clUtil.h"

cl_device_id clUtil::gDevices[kCLUtilMaxDevices];
cl_context clUtil::gContexts[kCLUtilMaxDevices];
cl_program clUtil::gPrograms[kCLUtilMaxDevices];
cl_command_queue clUtil::gCommandQueues[kCLUtilMaxDevices];
cl_kernel* clUtil::gKernels[kCLUtilMaxDevices];
cl_uint clUtil::gNumDevices = 0;
int clUtil::gCurrentDevice = -1;
std::map<std::string, cl_kernel> clUtil::gKernelNameLookup[kCLUtilMaxDevices];

const char* clUtil::getErrorCode(cl_int err)
{
  switch(err)
  {
    case CL_SUCCESS:
      return "No Error.";
    case CL_INVALID_MEM_OBJECT:
      return "Invalid memory object.";
    case CL_INVALID_ARG_INDEX:
      return "Invalid argument index for this kernel.";
    case CL_INVALID_ARG_VALUE:
      return "Invalid argument value.";
    case CL_INVALID_SAMPLER:
      return "Invalid sampler.";
    case CL_INVALID_ARG_SIZE:
      return "Invalid argument size.";
    case CL_INVALID_BUFFER_SIZE:
      return "Invalid buffer size.";
    case CL_INVALID_HOST_PTR:
      return "Invalid host pointer.";
    case CL_INVALID_DEVICE:
      return "Invalid device.";
    case CL_INVALID_VALUE:
      return "Invalid value.";
    case CL_INVALID_CONTEXT:
      return "Invalid Context.";
    case CL_INVALID_KERNEL:
      return "Invalid kernel.";
    case CL_INVALID_PROGRAM:
      return "Invalid program object.";
    case CL_INVALID_BINARY:
      return "Invalid program binary.";
    case CL_INVALID_OPERATION:
      return "Invalid operation.";
    case CL_INVALID_BUILD_OPTIONS:
      return "Invalid build options.";
    case CL_INVALID_PROGRAM_EXECUTABLE:
      return "Invalid executable.";
    case CL_INVALID_COMMAND_QUEUE:
      return "Invalid command queue.";
    case CL_INVALID_KERNEL_ARGS:
      return "Invalid kernel arguments.";
    case CL_INVALID_WORK_DIMENSION:
      return "Invalid work dimension.";
    case CL_INVALID_WORK_GROUP_SIZE:
      return "Invalid work group size.";
    case CL_INVALID_WORK_ITEM_SIZE:
      return "Invalid work item size.";
    case CL_INVALID_GLOBAL_OFFSET:
      return "Invalid global offset (should be NULL).";
    case CL_OUT_OF_RESOURCES:
      return "Insufficient resources.";
    case CL_MEM_OBJECT_ALLOCATION_FAILURE:
      return "Could not allocate mem object.";
    case CL_INVALID_EVENT_WAIT_LIST:
      return "Invalid event wait list.";
    case CL_OUT_OF_HOST_MEMORY:
      return "Out of memory on host.";
    case CL_INVALID_KERNEL_NAME:
      return "Invalid kernel name.";
    case CL_INVALID_KERNEL_DEFINITION:
      return "Invalid kernel definition.";
    case CL_BUILD_PROGRAM_FAILURE:
      return "Failed to build program."
    default:
      return "Unknown error.";
  }
}

static char* fileToString(const char* filename, size_t * filesize)
{
  int fid = open(filename, O_RDONLY);
  struct stat fileInfo;
  char* fileBuffer;

  if(fid == -1) 
  {
    printf("%s:%d::Could not open file %s.\n", __FILE__, __LINE__, filename);
    return NULL;
  }

  //Get the file's size and allocate a buffer to hold its text
  if(fstat(fid, &fileInfo) != 0)
  {
    printf("%s:%d::Could not stat file %s.\n", __FILE__, __LINE__, filename);
    return NULL;
  }

  *filesize = fileInfo.st_size;

  fileBuffer = new char[fileInfo.st_size + 1]; 

  if(read(fid, fileBuffer, fileInfo.st_size) != fileInfo.st_size)
  {
    printf("%s:%d::Could not read file %s.\n", __FILE__, __LINE__, filename);
    delete[] fileBuffer;
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

cl_int clUtil::LoadBinaryFromDisk(const char *filename)
{
	if (filename == NULL)
	{
		printf("%s:%d:%s\n", __FILE__, __LINE__, "empty filename");
		return 1;
	}

	cl_int err;
	size_t binary_size;

	// read binary from file
	char *ptx_code = fileToString (filename, &binary_size);

	// create program from binary
	gPrograms[gCurrentDevice] = clCreateProgramWithBinary (gContexts[gCurrentDevice], 
			1,
			gDevices, 
			&binary_size, 
			(const unsigned char **)&ptx_code, 
			NULL, 
			&err);
	clUtilCheckError(err);

  err = clBuildProgram(gPrograms[gCurrentDevice], 0, NULL, NULL, NULL, NULL);
  if(err != CL_SUCCESS)
  {
	  char errString[32768];

	  err = clGetProgramBuildInfo(gPrograms[gCurrentDevice],
			  gDevices[gCurrentDevice],
			  CL_PROGRAM_BUILD_LOG,
			  sizeof(errString),
			  errString,
			  NULL);
	  clUtilCheckError(err);
	  printf("%s", errString);
	  return err;
  }

  delete [] ptx_code;

  return CL_SUCCESS;

}

cl_kernel clUtil::getKernel(std::string& kernelName, cl_int* err)
{
  cl_kernel theKernel;
  std::map<std::string, cl_kernel>::iterator item;

  item = gKernelNameLookup[gCurrentDevice].find(kernelName);

  if(item == gKernelNameLookup[gCurrentDevice].end())
  {
    *err = CL_INVALID_KERNEL_NAME;
  }
  else
  {
    *err = CL_SUCCESS;
  }

  return item->second;
}

char* clUtil::getDeviceName()
{
  static char devName[256];
  cl_int err;

  err = clGetDeviceInfo(gDevices[gCurrentDevice],
                        CL_DEVICE_NAME,
                        sizeof(devName),
                        devName,
                        NULL);
  if(err != CL_SUCCESS)
  {
    return NULL;
  }

  return devName;
}

char* clUtil::getDeviceVendor()
{
  static char vendorName[256];
  cl_int err;

  err = clGetDeviceInfo(gDevices[gCurrentDevice],
                        CL_DEVICE_VENDOR,
                        sizeof(vendorName),
                        vendorName,
                        NULL);
  if(err != CL_SUCCESS)
  {
    return NULL;
  }

  return vendorName;
}

char* clUtil::getDeviceDriver()
{
  static char devName[256];
  cl_int err;

  err = clGetDeviceInfo(gDevices[gCurrentDevice],
                        CL_DRIVER_VERSION,
                        sizeof(devName),
                        devName,
                        NULL);
  if(err != CL_SUCCESS)
  {
    return NULL;
  }

  return devName;
}

cl_uint clUtil::getMaxWriteImages()
{
  cl_uint imageCount;
  cl_int err;

  err = clGetDeviceInfo(gDevices[gCurrentDevice],
                        CL_DEVICE_MAX_WRITE_IMAGE_ARGS,
                        sizeof(imageCount),
                        &imageCount,
                        NULL);
  if(err != CL_SUCCESS)
  {
    return 0;
  }

  return imageCount;
}

void clUtil::dumpBinary(const char* filename)
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
    printf("%s:%d:%s", __FILE__, __LINE__, getErrorCode(err));
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
    printf("%s:%d:%s", __FILE__, __LINE__, getErrorCode(err));
    return;
  }

  fd = open(filename, 
            O_WRONLY | O_CREAT | O_TRUNC, 
            S_IRWXU | S_IRGRP | S_IROTH);
  if(fd == -1) {goto CL_UTIL_DUMP_ERROR1;}

  if(write(fd, binary[0], binarySize[0]) != binarySize[0]) 
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

void clUtil::getSupportedImageFormats()
{
  cl_int err;
  cl_uint numEntries;
  cl_image_format formats[128];

  err = clGetSupportedImageFormats(gContexts[gCurrentDevice],
                                   CL_MEM_READ_WRITE,
                                   CL_MEM_OBJECT_IMAGE2D,
                                   128,
                                   formats,
                                   &numEntries);
  clUtilCheckErrorVoid(err);

  printf("Supported image formats:\n");

  for(cl_uint i = 0; i < numEntries; i++)
  {
    switch(formats[i].image_channel_order)
    {
      case CL_R:
        printf("\tRed - ");
        break;
      case CL_INTENSITY:
        printf("\tIntensity - ");
        break;
      case CL_LUMINANCE:
        printf("\tLuminance - ");
        break;
      case CL_A:
        printf("\tAlpha - ");
        break;
      case CL_RG:
        printf("\tRed Green - ");
        break;
      case CL_RA:
        printf("\tRed Alpha - ");
        break;
      case CL_RGB:
        printf("\tRed Green Blue - ");
        break;
      case CL_RGBA:
        printf("\tRed Green Blue Alpha - ");
        break;
      case CL_ARGB:
        printf("\tAlpha Red Green Blue - ");
        break;
      case CL_BGRA:
        printf("\tBlue Green Red Alpha - ");
        break;
      default:
        printf("\tUnknown format - ");
        break;
    }
    switch(formats[i].image_channel_data_type)
    {
      case CL_SNORM_INT8:
        printf("Normalized SINT8\n");
        break;
      case CL_SNORM_INT16:
        printf("Normalized SINT16\n");
        break;
      case CL_UNORM_INT8:
        printf("Normalized UINT8\n");
        break;
      case CL_UNORM_INT16:
        printf("Normalized UINT16\n");
        break;
      case CL_UNORM_SHORT_565:
        printf("Normalized 565\n");
        break;
      case CL_UNORM_SHORT_555:
        printf("Normalized 555\n");
        break;
      case CL_UNORM_INT_101010:
        printf("Normalized 10-10-10\n");
        break;
      case CL_SIGNED_INT8:
        printf("Unnormalized SINT8\n");
        break;
      case CL_SIGNED_INT16:
        printf("Unnormalized SINT16\n");
        break;
      case CL_SIGNED_INT32:
        printf("Unnormalized SINT32\n");
        break;
      case CL_UNSIGNED_INT8:
        printf("Unnormalized UINT8\n");
        break;
      case CL_UNSIGNED_INT16:
        printf("Unnormalized UINT16\n");
        break;
      case CL_UNSIGNED_INT32:
        printf("Unnormalized UINT32\n");
        break;
      case CL_HALF_FLOAT:
        printf("Half precision\n");
        break;
      case CL_FLOAT:
        printf("Single precision\n");
        break;
      default:
        printf("Unknown data type\n");
        break;
    }
  }
}

cl_int clUtil::initDevices()
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
    cl_uint platformDevices = 0;

    err = clGetDeviceIDs(platforms[i],
                         CL_DEVICE_TYPE_GPU,
                         kCLUtilMaxDevices - gNumDevices,
                         &gDevices[i],
                         &platformDevices);
    clUtilCheckError(err);

    char platformVersion[256];

    clGetPlatformInfo(platforms[i],
                      CL_PLATFORM_VERSION,
                      sizeof(platformVersion),
                      platformVersion,
                      NULL);

    //printf("%s\n", platformVersion);

    gNumDevices += platformDevices;
  }

  //Create contexts for each device
  for(cl_uint i = 0; i < gNumDevices; i++)
  {
    gContexts[i] = clCreateContext(NULL,
                                   1,
                                   &gDevices[i],
                                   NULL,
                                   NULL,
                                   &err);
    clUtilCheckError(err);

    gCommandQueues[i] = clCreateCommandQueue(gContexts[i],
                                             gDevices[i],
                                             0,
                                             &err);
    clUtilCheckError(err);
  }

  return CL_SUCCESS;
}

cl_int clUtil::buildPrograms(const char** filenames, 
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
      printf("%s:%d::Could load source %s.\n", 
             __FILE__, 
             __LINE__, 
             files[curFile]);
      return CL_INVALID_VALUE;
    }
  }

  for(size_t curDevice = 0; curDevice < gNumDevices; curDevice++)
  {
    char deviceFlags[256];
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

    //printf("%s\n", deviceVendor);

    snprintf(deviceFlags, 
             sizeof(deviceFlags) - 1, 
             "-cl-mad-enable -D%s %s",	//(1) by default -cl-nv-opt-level=3 
																		//(2) -cl-nv-verbose
																		//	Output will be reported in the build log (accessible through the
																		//	callback parameter to clBuildProgram).
             deviceVendor,
             options);

    err = clBuildProgram(gPrograms[curDevice],
                         1,
                         &gDevices[curDevice],
                         deviceFlags,
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
      clUtilCheckError(err);
      printf("%s", errString);
      return err;
    }
  }

  for(size_t curFile = 0; curFile < numFiles; curFile++)
  {
    delete files[curFile];
  }

  delete[] files;

  return CL_SUCCESS;
}

cl_int clUtil::getKernels()
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
}

cl_int clUtil::initialize(const char** filenames, 
                          size_t numFiles, 
                          const char* cachename,
                          const char* options)
{
  cl_int err;

  err = initDevices();
  clUtilCheckError(err);
  
  gCurrentDevice = 0;

  if (filenames == NULL && cachename != NULL)
	  LoadBinaryFromDisk(cachename);
  else if (filenames != NULL)
	  err = buildPrograms(filenames, numFiles, options);
  else
  {
	  printf ("fail to initialize, check filenames and cachename\n");
	  return 1;
  }
  clUtilCheckError(err);

  getKernels();

  return err;
}

cl_int clUtil::setDeviceNum(cl_int device)
{
  if(device >= gNumDevices || device < 0)
  {
    return CL_INVALID_VALUE;
  }

  gCurrentDevice = device;

  return CL_SUCCESS;
}

cl_int clUtil::getDeviceNum()
{
  if(gCurrentDevice < 0 || gCurrentDevice > gNumDevices)
  {
    return -1;
  }

  return gCurrentDevice;
}

cl_uint clUtil::getNumDevices()
{
  return gNumDevices;
}

cl_program clUtil::getProgram()
{
  if(gNumDevices == 0)
  {
    return 0;
  }

  return gPrograms[gCurrentDevice];
}

cl_command_queue clUtil::getCommandQueue()
{
  if(gCurrentDevice < 0 || gCurrentDevice > gNumDevices)
  {
    return 0;
  }

  return gCommandQueues[gCurrentDevice];
}

cl_int clUtil::getPointerSize()
{
  cl_int err;
  static cl_int pointerSize;
  static int lastDevice = -1;

  //Cache results if we haven't changed devices
  if(lastDevice == gCurrentDevice)
  {
    return pointerSize / 8;
  }

  err = clGetDeviceInfo(gDevices[gCurrentDevice],
                        CL_DEVICE_ADDRESS_BITS,
                        sizeof(pointerSize),
                        &pointerSize,
                        NULL);
  clUtilCheckError(err);

  return pointerSize / 8;
}

size_t clUtil::getMaxBlockSize()
{
  cl_int err;
  size_t localSize;
  
  err = clGetDeviceInfo(gDevices[gCurrentDevice],
                        CL_DEVICE_MAX_WORK_GROUP_SIZE,
                        sizeof(localSize),
                        &localSize,
                        NULL);
  return localSize;
}

cl_int clUtil::alloc(size_t len, cl_mem* gpuBuffer)
{
  cl_int err;

  *gpuBuffer = clCreateBuffer(gContexts[gCurrentDevice],
                              CL_MEM_READ_WRITE,
                              len,
                              NULL,
                              &err);
  clUtilCheckError(err);

  return CL_SUCCESS;
}

cl_int clUtil::devicePut(void* buffer, size_t len, cl_mem gpuBuffer)
{
  cl_int err;

  err = clEnqueueWriteBuffer(gCommandQueues[gCurrentDevice],
                             gpuBuffer,
                             CL_TRUE,
                             0,
                             len,
                             buffer,
                             0,
                             NULL,
                             NULL);
  clUtilCheckError(err);

  return CL_SUCCESS;
}

cl_int clUtil::deviceGet(void* buffer, size_t len, cl_mem gpuBuffer)
{
  cl_int err;

  err = clEnqueueReadBuffer(gCommandQueues[gCurrentDevice],
                            gpuBuffer,
                            CL_TRUE,
                            0,
                            len,
                            buffer,
                            0,
                            NULL,
                            NULL);
  clUtilCheckError(err);

  return CL_SUCCESS;
}

cl_int clUtil::free(cl_mem buffer)
{
  cl_int err;

  err = clReleaseMemObject(buffer);
  clUtilCheckError(err);

  return CL_SUCCESS;
}

double clUtil::getTime()
{
#ifdef __APPLE__ //Apple just has to be a PITA with timer interfaces
  uint64_t time;
  Nanoseconds ns; 

  time = mach_absolute_time();

  ns = AbsoluteToNanoseconds(*(AbsoluteTime*)&time);

  return ((double)*(uint64_t*)&ns) / 1e9;
#else
  struct timeval time;

  gettimeofday(&time, NULL);
  return (double)time.tv_sec + (double)time.tv_usec / 1e6;
#endif

}
