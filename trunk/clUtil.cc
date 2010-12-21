#include "clUtil.h"

cl_device_id clUtil::gDevices[kCLUtilMaxDevices];
cl_context clUtil::gContexts[kCLUtilMaxDevices];
cl_program clUtil::gPrograms[kCLUtilMaxDevices];
cl_command_queue clUtil::gCommandQueues[kCLUtilMaxDevices];
cl_kernel* clUtil::gKernels[kCLUtilMaxDevices];
cl_uint clUtil::gNumDevices = 0;
unsigned int clUtil::gCurrentDevice = 0;
std::map<std::string, cl_kernel> clUtil::gKernelNameLookup[kCLUtilMaxDevices];

using namespace clUtil;

const char* clUtilGetErrorCode(cl_int err)
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
      return "Failed to build program.";
    default:
      return "Unknown error.";
  }
}

cl_kernel clUtilGetKernel(std::string& kernelName, cl_int* err)
{
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

char* clUtilGetDeviceName()
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

char* clUtilGetDeviceVendor()
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

char* clUtilGetDeviceDriver()
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

cl_uint clUtilGetMaxWriteImages()
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

void clUtilGetSupportedImageFormats()
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

cl_int clUtilSetDeviceNum(cl_uint device)
{
  if(device >= gNumDevices)
  {
    return CL_INVALID_VALUE;
  }

  gCurrentDevice = device;

  return CL_SUCCESS;
}

cl_int clUtilGetDeviceNum()
{
  if(gCurrentDevice < 0 || gCurrentDevice > gNumDevices)
  {
    return -1;
  }

  return gCurrentDevice;
}

cl_uint clUtilGetNumDevices()
{
  return gNumDevices;
}

cl_program clUtilGetProgram()
{
  if(gNumDevices == 0)
  {
    return 0;
  }

  return gPrograms[gCurrentDevice];
}

cl_command_queue clUtilGetCommandQueue()
{
  if(gCurrentDevice < 0 || gCurrentDevice > gNumDevices)
  {
    return 0;
  }

  return gCommandQueues[gCurrentDevice];
}

cl_int clUtilGetPointerSize()
{
  cl_int err;
  cl_int pointerSize;

  err = clGetDeviceInfo(gDevices[gCurrentDevice],
                        CL_DEVICE_ADDRESS_BITS,
                        sizeof(pointerSize),
                        &pointerSize,
                        NULL);
  clUtilCheckError(err);

  return pointerSize / 8;
}

size_t clUtilGetMaxBlockSize()
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

cl_int clUtilAlloc(size_t len, cl_mem* gpuBuffer)
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

cl_int clUtilDevicePut(void* buffer, size_t len, cl_mem gpuBuffer)
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

cl_int clUtilDeviceGet(void* buffer, size_t len, cl_mem gpuBuffer)
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

cl_int clUtilFree(cl_mem buffer)
{
  cl_int err;

  err = clReleaseMemObject(buffer);
  clUtilCheckError(err);

  return CL_SUCCESS;
}

double clUtilGetTime()
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
