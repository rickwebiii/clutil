#pragma once
#include "clUtilCommon.h"
#include "clUtilUtility.h"

namespace clUtil
{
  struct DeviceInfo
  {
    public:
      cl_device_type Type;
      cl_uint VendorID;
      cl_uint MaxComputeUnits;
      std::vector<size_t> MaxWorkItemSizes;
      size_t MaxWorkGroupSize;
      cl_uint PreferredVectorWidthChar;
      cl_uint PreferredVectorWidthShort;
      cl_uint PreferredVectorWidthInt;
      cl_uint PreferredVectorWidthLong;
      cl_uint PreferredVectorWidthFloat;
      cl_uint PreferredVectorWidthDouble;
      cl_uint PreferredVectorWidthHalf;
      cl_uint NativeVectorWidthChar;
      cl_uint NativeVectorWidthShort;
      cl_uint NativeVectorWidthInt;
      cl_uint NativeVectorWidthLong;
      cl_uint NativeVectorWidthFloat;
      cl_uint NativeVectorWidthDouble;
      cl_uint NativeVectorWidthHalf;
      cl_uint MaxClockFrequency;
      cl_uint AddressBits;
      cl_ulong MaxMemAllocSize;
      cl_bool ImageSupport;
      cl_uint MaxReadImageArgs;
      cl_uint MaxWriteImageArgs;
      size_t Image2DMaxWidth;
      size_t Image2DMaxHeight;
      size_t Image3DMaxWidth;
      size_t Image3DMaxHeight;
      size_t Image3DMaxDepth;
      cl_uint MaxSamplers;
      size_t MaxParameterSize;
      cl_uint MemBaseAddrAlign;
      cl_uint MinDataTypeAlignSize;
      cl_device_fp_config SingleFPConfig;
      cl_device_mem_cache_type GlobalMemCacheType;
      cl_uint GlobalMemCachelineSize;
      cl_ulong GlobalMemCacheSize;
      cl_ulong GlobalMemSize;
      cl_ulong MaxConstantBufferSize;
      cl_uint MaxConstantArgs;
      cl_device_local_mem_type LocalMemType;
      cl_ulong LocalMemSize;
      cl_bool ErrorCorrectionSupport;
      cl_bool HostUnifiedMemory;
      size_t ProfilingTimerResolution;
      cl_bool EndianLittle;
      cl_bool DeviceAvailable;
      cl_bool CompilerAvailable;
      cl_device_exec_capabilities ExecutionCapabilities;
      cl_command_queue_properties QueueProperties;
      std::string Name;
      std::string Vendor;
      std::string DriverVersion;
      std::string OpenCLProfile;
      std::string OpenCLVersion;
      std::string OpenCLCVersion;
      std::vector<std::string> Extensions;

      void initialize(cl_device_id deviceID);
    private:
  };

  class Device
  {
    private:
      cl_device_id mDeviceID;
      cl_context mContext;
      cl_command_queue mCommandQueue;
      cl_program mProgram;
      std::map<std::string, cl_kernel> mKernels;
      DeviceInfo mDeviceInfo;
      bool mInfoInitialized;
      size_t mDeviceNumber;     

      static size_t CurrentDevice;
      static bool DevicesInitialized;
      static bool DevicesFetched;
      static std::vector<Device> Devices;
      
      std::string fileToString(const char* filename);
      cl_int loadBinary(const char* cachename);
      cl_int buildProgram(const char** filenames, 
                          size_t numFiles,
                          const char* options);
      void initialize(const char** sourceFiles,
                      size_t numFiles,
                      const char* cachename,
                      const char* options);
      void dumpBinary(const char* filename);
      void getKernels();
    public:
      Device(cl_device_id deviceID);
      const DeviceInfo& getDeviceInfo() const {return mDeviceInfo;}
      cl_device_id getDeviceID() const {return mDeviceID;}
      cl_context getContext() const {return mContext;}
      cl_command_queue getCommandQueue() const {return mCommandQueue;}
      cl_kernel getKernel(std::string&& kernelName) const;
      size_t getDeviceNumber() const {return mDeviceNumber;}

      static const std::vector<Device>& GetDevices() {return Devices; }
      static void FetchDevices();
      static void InitializeDevices(const char** sourceFiles, 
                                    size_t numFiles,
                                    const char* cachename = NULL,
                                    const char* options = "");
      static Device& GetCurrentDevice() { return Devices[CurrentDevice]; }
      static size_t GetCurrentDeviceNum() { return CurrentDevice; }
      static void SetCurrentDevice(size_t deviceNum) 
      {
        if(deviceNum > Devices.size())
        {
          throw clUtilException("SetCurrentDevice():Invalid device.");
        }

        CurrentDevice = deviceNum;
      };
  };
}
