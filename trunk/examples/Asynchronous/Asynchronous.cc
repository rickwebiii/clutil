#include <clUtil.h>

const unsigned int kBufferSize = 12345;

int main(int argc, char** argv)
{
  float result[kBufferSize];
  cl_mem a;
  cl_mem b;
  cl_mem c;
  char const* kernel = "kernel.cl";
  unsigned int buffersCopied = 0;

  clUtilInitialize(&kernel, 1);

  clUtilAlloc(sizeof(float) * kBufferSize, &a);
  clUtilAlloc(sizeof(float) * kBufferSize, &b);
  clUtilAlloc(sizeof(float) * kBufferSize, &c);

#if 0
  for(size_t i = 0; i < kBufferSize; i++)
  {
    result[i] = i;
  }
#endif
  
  printf("%s\n", clUtilGetPlatformVersion());

  cl_event test = clCreateUserEvent(clUtil::gContexts[0], NULL);

  /*
  clUtilDevicePut(result, 
                  sizeof(float) * kBufferSize, 
                  a, 
                  [&buffersCopied] (cl_event event, cl_int status)
                  {
                    printf("Hello!\n");
                    buffersCopied++;
                  });
 */

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
