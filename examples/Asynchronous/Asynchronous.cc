#include <clUtil.h>

const unsigned int kBufferSize = 12345;

volatile unsigned int buffersCopied = 0;

int main(int argc, char** argv)
{
  float result[kBufferSize];
  cl_int err;
  cl_mem a;
  cl_mem b;
  cl_mem c;
  char const* kernel = "kernel.cl";

  err = clUtilInitialize(&kernel, 1);

  clUtilAlloc(sizeof(float) * kBufferSize, &a);
  clUtilAlloc(sizeof(float) * kBufferSize, &b);
  clUtilAlloc(sizeof(float) * kBufferSize, &c);

  for(size_t i = 0; i < kBufferSize; i++)
  {
    result[i] = i;
  }
 
  auto copyCallback = [&] (cl_event event, cl_int status)
  {
    __sync_fetch_and_add(&buffersCopied, 1);
  };

  //Asynchronously issue to host->device copies
  clUtilDevicePut(result, 
                  sizeof(float) * kBufferSize, 
                  a, 
                  copyCallback);
  clUtilDevicePut(result, 
                  sizeof(float) * kBufferSize, 
                  b, 
                  copyCallback);

  clFlush(clUtil::gCommandQueues[clUtil::gCurrentDevice]);

  //Wait for them to complete
  while(buffersCopied != 2)
  {}

  clUtilEnqueueKernel("add",
                      clUtilGrid(kBufferSize, 64),
                      a,
                      b,
                      c,
                      kBufferSize);

  clUtilDeviceGet(result,
                  sizeof(float) * kBufferSize,
                  c);
  

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
