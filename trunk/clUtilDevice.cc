#include "clUtilDevice.h"
#include "clUtilPlatform.h"

using namespace clUtil;
using namespace std;

size_t Device::CurrentDevice = 0;
bool Device::DevicesInitialized = false;
bool Device::DevicesFetched = false;
vector<Device> Device::Devices;

void DeviceInfo::initialize(cl_device_id deviceID)
{
  Utility::fetchDeviceInfo(deviceID, 
                           CL_DEVICE_TYPE, 
                           Type);
  Utility::fetchDeviceInfo(deviceID, 
                           CL_DEVICE_VENDOR_ID, 
                           VendorID);
  Utility::fetchDeviceInfo(deviceID, 
                           CL_DEVICE_MAX_COMPUTE_UNITS, 
                           MaxComputeUnits);
  Utility::fetchDeviceInfo(deviceID, 
                           CL_DEVICE_MAX_WORK_GROUP_SIZE, 
                           MaxWorkGroupSize);
  Utility::fetchDeviceInfo(deviceID, 
                           CL_DEVICE_PREFERRED_VECTOR_WIDTH_CHAR, 
                           PreferredVectorWidthChar);
  Utility::fetchDeviceInfo(deviceID, 
                           CL_DEVICE_PREFERRED_VECTOR_WIDTH_SHORT, 
                           PreferredVectorWidthShort);
  Utility::fetchDeviceInfo(deviceID, 
                           CL_DEVICE_PREFERRED_VECTOR_WIDTH_INT, 
                           PreferredVectorWidthInt);
  Utility::fetchDeviceInfo(deviceID, 
                           CL_DEVICE_PREFERRED_VECTOR_WIDTH_LONG, 
                           PreferredVectorWidthLong);
  Utility::fetchDeviceInfo(deviceID, 
                           CL_DEVICE_PREFERRED_VECTOR_WIDTH_FLOAT, 
                           PreferredVectorWidthFloat);
  Utility::fetchDeviceInfo(deviceID, 
                           CL_DEVICE_PREFERRED_VECTOR_WIDTH_DOUBLE, 
                           PreferredVectorWidthDouble);
  Utility::fetchDeviceInfo(deviceID, 
                           CL_DEVICE_PREFERRED_VECTOR_WIDTH_HALF, 
                           PreferredVectorWidthHalf);
  Utility::fetchDeviceInfo(deviceID,
                           CL_DEVICE_NATIVE_VECTOR_WIDTH_CHAR,
                           NativeVectorWidthChar);
  Utility::fetchDeviceInfo(deviceID,
                           CL_DEVICE_NATIVE_VECTOR_WIDTH_SHORT,
                           NativeVectorWidthShort);
  Utility::fetchDeviceInfo(deviceID,
                           CL_DEVICE_NATIVE_VECTOR_WIDTH_INT,
                           NativeVectorWidthInt);
  Utility::fetchDeviceInfo(deviceID,
                           CL_DEVICE_NATIVE_VECTOR_WIDTH_LONG,
                           NativeVectorWidthLong);
  Utility::fetchDeviceInfo(deviceID,
                           CL_DEVICE_NATIVE_VECTOR_WIDTH_FLOAT,
                           NativeVectorWidthFloat);
  Utility::fetchDeviceInfo(deviceID,
                           CL_DEVICE_NATIVE_VECTOR_WIDTH_DOUBLE,
                           NativeVectorWidthDouble);
  Utility::fetchDeviceInfo(deviceID,
                           CL_DEVICE_NATIVE_VECTOR_WIDTH_HALF,
                           NativeVectorWidthHalf);
  Utility::fetchDeviceInfo(deviceID,
                           CL_DEVICE_MAX_CLOCK_FREQUENCY,
                           MaxClockFrequency);
  Utility::fetchDeviceInfo(deviceID,
                           CL_DEVICE_ADDRESS_BITS,
                           AddressBits);
  Utility::fetchDeviceInfo(deviceID,
                           CL_DEVICE_MAX_MEM_ALLOC_SIZE,
                           MaxMemAllocSize);
  Utility::fetchDeviceInfo(deviceID,
                           CL_DEVICE_IMAGE_SUPPORT,
                           ImageSupport);
  Utility::fetchDeviceInfo(deviceID,
                           CL_DEVICE_MAX_READ_IMAGE_ARGS,
                           MaxReadImageArgs);
  Utility::fetchDeviceInfo(deviceID,
                           CL_DEVICE_MAX_WRITE_IMAGE_ARGS,
                           MaxWriteImageArgs);
  Utility::fetchDeviceInfo(deviceID,
                           CL_DEVICE_IMAGE2D_MAX_WIDTH,
                           Image2DMaxWidth);
  Utility::fetchDeviceInfo(deviceID,
                           CL_DEVICE_IMAGE2D_MAX_HEIGHT,
                           Image2DMaxHeight);
  Utility::fetchDeviceInfo(deviceID,
                           CL_DEVICE_IMAGE3D_MAX_WIDTH,
                           Image3DMaxWidth);
  Utility::fetchDeviceInfo(deviceID,
                           CL_DEVICE_IMAGE3D_MAX_HEIGHT,
                           Image3DMaxHeight);
  Utility::fetchDeviceInfo(deviceID,
                           CL_DEVICE_IMAGE3D_MAX_DEPTH,
                           Image3DMaxDepth);
  Utility::fetchDeviceInfo(deviceID,
                           CL_DEVICE_MAX_SAMPLERS,
                           MaxSamplers);
  Utility::fetchDeviceInfo(deviceID,
                           CL_DEVICE_MAX_PARAMETER_SIZE,
                           MaxParameterSize);
  Utility::fetchDeviceInfo(deviceID,
                           CL_DEVICE_MEM_BASE_ADDR_ALIGN,
                           MemBaseAddrAlign);
  Utility::fetchDeviceInfo(deviceID,
                           CL_DEVICE_MIN_DATA_TYPE_ALIGN_SIZE,
                           MinDataTypeAlignSize);
  Utility::fetchDeviceInfo(deviceID,
                           CL_DEVICE_SINGLE_FP_CONFIG,
                           SingleFPConfig);
  Utility::fetchDeviceInfo(deviceID,
                           CL_DEVICE_GLOBAL_MEM_CACHE_TYPE,
                           GlobalMemCacheType);
  Utility::fetchDeviceInfo(deviceID,
                           CL_DEVICE_GLOBAL_MEM_CACHE_SIZE,
                           GlobalMemCacheSize);
  Utility::fetchDeviceInfo(deviceID,
                           CL_DEVICE_GLOBAL_MEM_SIZE,
                           GlobalMemSize);
  Utility::fetchDeviceInfo(deviceID,
                           CL_DEVICE_MAX_CONSTANT_BUFFER_SIZE,
                           MaxConstantBufferSize);
  Utility::fetchDeviceInfo(deviceID,
                           CL_DEVICE_MAX_CONSTANT_ARGS,
                           MaxConstantArgs);
  Utility::fetchDeviceInfo(deviceID,
                           CL_DEVICE_LOCAL_MEM_TYPE,
                           LocalMemType);
  Utility::fetchDeviceInfo(deviceID,
                           CL_DEVICE_LOCAL_MEM_SIZE,
                           LocalMemSize);
  Utility::fetchDeviceInfo(deviceID,
                           CL_DEVICE_ERROR_CORRECTION_SUPPORT,
                           ErrorCorrectionSupport);
  Utility::fetchDeviceInfo(deviceID,
                           CL_DEVICE_HOST_UNIFIED_MEMORY,
                           HostUnifiedMemory);
  Utility::fetchDeviceInfo(deviceID,
                           CL_DEVICE_PROFILING_TIMER_RESOLUTION,
                           ProfilingTimerResolution);
  Utility::fetchDeviceInfo(deviceID,
                           CL_DEVICE_ENDIAN_LITTLE,
                           EndianLittle);
  Utility::fetchDeviceInfo(deviceID,
                           CL_DEVICE_AVAILABLE,
                           DeviceAvailable);
  Utility::fetchDeviceInfo(deviceID,
                           CL_DEVICE_COMPILER_AVAILABLE,
                           CompilerAvailable);
  Utility::fetchDeviceInfo(deviceID,
                           CL_DEVICE_EXECUTION_CAPABILITIES,
                           ExecutionCapabilities);
  Utility::fetchDeviceInfo(deviceID,
                           CL_DEVICE_QUEUE_PROPERTIES,
                           QueueProperties);

  //Now for the more exciting properties...
  //Work item dimensions
  cl_uint maxWorkItemDimensions;

  Utility::fetchDeviceInfo(deviceID, 
                           CL_DEVICE_MAX_WORK_ITEM_DIMENSIONS, 
                           maxWorkItemDimensions);

  unique_ptr<size_t[]> maxWorkDimensions(new size_t[maxWorkItemDimensions]);

  clGetDeviceInfo(deviceID, 
                  CL_DEVICE_MAX_WORK_ITEM_SIZES,
                  sizeof(size_t) * maxWorkItemDimensions,
                  maxWorkDimensions.get(),
                  NULL);

  for(cl_uint curDimension = 0; 
      curDimension < maxWorkItemDimensions; 
      curDimension++)
  {
    this->MaxWorkItemSizes.push_back(maxWorkDimensions[curDimension]);
  }

  //String information
  Utility::fetchDeviceInfo(deviceID,
                           CL_DEVICE_NAME,
                           Name);
  Utility::fetchDeviceInfo(deviceID,
                           CL_DEVICE_VENDOR,
                           Vendor);
  Utility::fetchDeviceInfo(deviceID,
                           CL_DRIVER_VERSION,
                           DriverVersion);
  Utility::fetchDeviceInfo(deviceID,
                           CL_DEVICE_PROFILE,
                           OpenCLProfile);
  Utility::fetchDeviceInfo(deviceID,
                           CL_DEVICE_VERSION,
                           OpenCLVersion);
  Utility::fetchDeviceInfo(deviceID,
                           CL_DEVICE_OPENCL_C_VERSION,
                           OpenCLCVersion);

  string extensions;

  Utility::fetchDeviceInfo(deviceID,
                           CL_DEVICE_EXTENSIONS,
                           extensions);

  Extensions = Utility::split(extensions, ' ');

}

Device::Device(cl_device_id deviceID) : 
  mDeviceID(deviceID),
  mDeviceInfo(),
  mInfoInitialized(false)
{
}

DeviceInfo& Device::getDeviceInfo()
{
  if(mInfoInitialized == false)
  {
    mDeviceInfo.initialize(mDeviceID);
    mInfoInitialized = true;
  }

  return mDeviceInfo;
}

void Device::FetchDevices()
{
  vector<size_t> embargoList;
  char* embargoEnvString;
  vector<Device> allDevices;

  //Get the device embargo list
  embargoEnvString = getenv("CLUTIL_DEVICE_EMBARGO");

  if(embargoEnvString != NULL)
  {
    vector<string> embargoStrings = 
      Utility::split(string(embargoEnvString), ':');

    for(auto curString = embargoStrings.begin();
        curString != embargoStrings.end();
        curString++)
    {
      size_t embargoValue;

      istringstream(*curString) >> embargoValue;
      
      embargoList.push_back(embargoValue);
    }
  }

  vector<Platform> platforms = Platform::GetPlatforms();
  
  //Collect all devices from all platforms
  for(auto curPlatform = platforms.begin(); 
      curPlatform != platforms.end(); 
      curPlatform++)
  {
    vector<Device> platformDevices = (*curPlatform).getDevices();
    
    allDevices.insert(allDevices.end(), 
                      platformDevices.begin(), 
                      platformDevices.end());

  }

  //Embargo devices
  for(size_t curDevice = 0; curDevice < allDevices.size(); curDevice++)
  {
    bool deviceIsEmbargoed = false;

    for(auto curEmbargo = embargoList.begin();
        curEmbargo != embargoList.end();
        curEmbargo++)
    {
      if(curDevice == *curEmbargo)
      {
        deviceIsEmbargoed = true;
        break;
      }
    }

    if(deviceIsEmbargoed == false)
    {
      Device::Devices.push_back(allDevices[curDevice]);
    }
  }

  //Number each device
  for(size_t curDevice = 0; curDevice < Device::Devices.size(); curDevice++)
  {
    Device::Devices[curDevice].mDeviceNumber = curDevice;
  }

  Device::DevicesFetched = true;
}

void Device::InitializeDevices(const char** filenames, 
                               size_t numFiles,
                               const char* cachename,
                               const char* options)
{
  //If we haven't initialized the devices, initialize them
  if(Device::DevicesInitialized == false)
  {
    //If we haven't fetched the devices, fetch them
    if(Device::DevicesFetched == false)
    {
      Device::FetchDevices();
      Device::DevicesFetched = true;
    }
    
    for(size_t curDevice = 0; curDevice < Device::Devices.size(); curDevice++)
    {
      Device::Devices[curDevice].initialize(filenames,
                                            numFiles,
                                            cachename,
                                            options);
    }

    Device::DevicesInitialized = true;
  }
}

void Device::initialize(const char** filenames,
                        size_t numFiles,
                        const char* cachename,
                        const char* options)
{
  cl_int err;

  //Create context and command queue
  mContext = clCreateContext(NULL, 1, &mDeviceID, NULL, NULL, &err);
  clUtilCheckError(err);

  mCommandQueue = clCreateCommandQueue(mContext, mDeviceID, 0, &err);
  clUtilCheckError(err);

  if(cachename != NULL)
  {
    cl_int err = this->loadBinary(cachename);
    
    //If we loaded the binary, then good. We'll use it.
    if(err == CL_SUCCESS)
    {
      return;
    }
    else
    {
      printf("Info: clUtil could not load binaries due to error: %s. Building "
             "program from source.\n",
             clUtilGetErrorCode(err));
    }
  }

  this->buildProgram(filenames, numFiles, options);
  this->getKernels();
}

cl_kernel Device::getKernel(std::string&& kernelName) const
{
  auto kernel = mKernels.find(kernelName);

  if(kernel == mKernels.end())
  {
    clUtilCheckError(CL_INVALID_KERNEL_NAME);
  }

  return kernel->second;
}
