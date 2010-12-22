#include <clUtil.h>

int main(int argc, char** argv)
{
  const char* kernelFiles[] = {"kernel.cl"};
  cl_mem buffer;
  float array[2000];
  unsigned int length = 2000;
  float val = 20.0f;

  clUtilInitialize(kernelFiles, 1, "test");
  clUtilAlloc(sizeof(array), &buffer);

  clUtilEnqueueKernel("fill", 
                      clUtilGrid(length, 64), 
                      buffer, 
                      length, 
                      val);

  clUtilDeviceGet(array, sizeof(array), buffer);

  clUtilFree(buffer);

  for(unsigned int i = 0; i < 2000; i++)
  {
    if(array[i] != 20.0f)
    {
      printf("Test failed. Element %u", i);
      return 1;
    }
  }

  printf("Test Succeeded!\n");
  
  return 0;
}
