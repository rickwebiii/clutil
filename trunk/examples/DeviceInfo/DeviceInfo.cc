#include <clUtil.h>

int main(int argc, char** argv)
{
  char const* kernel = "kernel.cl";
  clUtilPlatformVersion version;

  clUtilInitialize(&kernel, 1);

  version = clUtilGetPlatformVersion();

  printf("OpenCL %hu.%hu\n", version.major, version.minor);
}
