#include <clUtil.h>

int main(int argc, char** argv)
{
  char const* kernel = "kernel.cl";
  double time1;
  double time2;
  float* a;
  cl_mem gpuA;
  const unsigned int size = 1024*1024*128;

  clUtilInitialize(&kernel, 1);

  a = new float[size];
  
  for(unsigned int i = 0; i < size; i++)
  {
    a[i] = 0.0f;
  }

  clUtilAlloc(sizeof(a[0]) * size, &gpuA);

  time1 = clUtilGetTime();

  clUtilDevicePut(a, sizeof(a[0]) * size, gpuA);
  
  time2 = clUtilGetTime();

  printf("%lE B/s\n", sizeof(a[0]) * size / (time2 - time1));
}
