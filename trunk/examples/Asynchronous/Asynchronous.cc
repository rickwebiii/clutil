#include <clUtil.h>

const unsigned int kBufferSize = 12345;

int main(int argc, char** argv)
{
  float result[kBufferSize];
  cl_int err;
  cl_mem a;
  cl_mem b;
  cl_mem c;
  char const* kernel = "kernel.cl";
  static volatile unsigned int buffersCopied = 0;
  static volatile bool kernelDone = false;
  static volatile bool readBackDone = false;

  err = clUtilInitialize(&kernel, 1);

  clUtilAlloc(sizeof(float) * kBufferSize, &a);
  clUtilAlloc(sizeof(float) * kBufferSize, &b);
  clUtilAlloc(sizeof(float) * kBufferSize, &c);

  for(size_t i = 0; i < kBufferSize; i++)
  {
    result[i] = i;
  }
 
  auto copyCallback = [&] ()
  {
    __sync_fetch_and_add(&buffersCopied, 1);
    printf("%d Copy done.\n", buffersCopied);
  };

  //Asynchronously issue to host->device copies
  clUtilDevicePut(result, 
                  sizeof(float) * kBufferSize, 
                  a, 
                  copyCallback,
                  false);

  clUtilDevicePut(result, 
                  sizeof(float) * kBufferSize, 
                  b, 
                  copyCallback);

  //Wait for them to complete
  while(buffersCopied < 2) {}

  auto kernelCallback = [&] ()
  {
    kernelDone = true;
    printf("Kernel Done!\n");
  };

  clUtilEnqueueKernel("add",
                      kernelCallback,
                      clUtilGrid(kBufferSize, 64),
                      a,
                      b,
                      c,
                      kBufferSize);
  
  clFlush(clUtil::gCommandQueues[clUtil::gCurrentDevice]);

  //Wait for kernel to complete
  while(kernelDone == false) {}

  auto readoutCallback = [&] ()
  {
    readBackDone = true;
    printf("Read back done!\n");
  };

  clUtilDeviceGet(result,
                  sizeof(float) * kBufferSize,
                  c,
                  readoutCallback);
  
  //Wait for read back to complete
  while(readBackDone == false) {}

  //Check result
  for(size_t i = 0; i < kBufferSize; i++)
  {
    if(result[i] != 2.0f * i)
    {
      printf("Error: index %ld value: %f\n", i, result[i]);
      exit(1);
    }
  }

  printf("Success!\n");
}
