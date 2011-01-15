#include <clUtil.h>

int main(int argc, char** argv)
{
  char const* kernel = "kernel.cl";
  clUtilPlatformVersion version;

  clUtilInitialize(&kernel, 1);

  for(unsigned int i = 0; i < clUtil::gNumDevices; i++)
  {
    clUtilSetDeviceNum(i);

    version = clUtilGetPlatformVersion();

    printf("OpenCL %hu.%hu\n", version.major, version.minor);
    printf("%s\n", clUtilGetPlatformVersionString());
    printf("Device Vendor: %s\n", clUtilGetDeviceVendor());
    printf("Device Name: %s\n", clUtilGetDeviceName());
    printf("\n");
  }
}
