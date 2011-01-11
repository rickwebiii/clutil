#include <clUtil.h>

const unsigned int kImageSize = 12345;

int main(int argc, char** argv)
{
  float result[kImageSize];
  cl_mem a;
  cl_mem b;
  cl_mem c;
  char const* kernel = "kernel.cl";

  clUtilInitialize(&kernel, 1);

  clUtilCreateImage1D(kImageSize, CL_A, CL_FLOAT, &a);
  clUtilCreateImage1D(kImageSize, CL_A, CL_FLOAT, &b);
  clUtilCreateImage1D(kImageSize, CL_A, CL_FLOAT, &c);

  clUtilEnqueueKernel("fillImage",
                      clUtilGrid(kImageSize, 64),
                      a,
                      kImageSize);
  
  clUtilEnqueueKernel("fillImage",
                      clUtilGrid(kImageSize, 64),
                      b,
                      kImageSize);

  clUtilEnqueueKernel("sumImages",
                      clUtilGrid(kImageSize, 64),
                      a,
                      b,
                      c,
                      kImageSize);

  clUtilGetImage1D(c, 0, kImageSize, result);

  for(size_t i = 0; i < kImageSize; i++)
  {
    if(result[i] != 2.0f * i)
    {
      printf("Error: index %ld value: %f\n", i, result[i]);
    }
  }

  printf("Success!\n");
}
