#include <clUtil.h>
#include <stdlib.h>
#include <stdio.h>


void fillKeys(unsigned int* array, unsigned int length)
{
  for(unsigned int i = 0; i < length; i++)
  {
    array[i] = i % 10;
  }
}

void fillVals(unsigned int* array, unsigned int length)
{
  for(unsigned int i = 0; i < length; i++)
  {
    array[i] = i;
  }
}


void usage()
{
  printf("Usage:Sort rows cols [deviceNum]\n");
  exit(1);
}

int main(int argc, char** argv)
{
  unsigned int rows;
  unsigned int cols;
  char const* kernel = "kernel.cl";
  unsigned int* keys;
  unsigned int* vals;
  cl_mem keysDevice1;
  cl_mem keysDevice2;
  cl_mem valsDevice1;
  cl_mem valsDevice2;
  size_t size;
  unsigned int deviceNum = 0;

  if(argc < 3)
  {
    usage();
  }
  if(sscanf(argv[1], "%u", &rows) != 1)
  {
    usage();
  }
  if(sscanf(argv[2], "%u", &cols) != 1)
  {
    usage();
  }
  if(argc >= 4)
  {
    if(sscanf(argv[3], "%u", &deviceNum) != 1)
    {
      usage();
    }
  }

  keys = new unsigned int[rows * cols];
  vals = new unsigned int[rows * cols];

  //Fill the arrays
  for(unsigned int curRow = 0; curRow < rows; curRow++)
  {
    fillKeys(&keys[curRow * cols], cols);
    fillVals(&vals[curRow * cols], cols);
  }

  clUtilInitialize(&kernel, 1);

  clUtilSetDeviceNum(deviceNum);

  size = sizeof(unsigned int) * rows * cols;

  printf("Running on device %d %s\n",
         clUtilGetDeviceNum(),
         clUtilGetDeviceName());

  clUtilAlloc(size, &keysDevice1);
  clUtilAlloc(size, &keysDevice2);
  clUtilAlloc(size, &valsDevice1);
  clUtilAlloc(size, &valsDevice2);

  clUtilDevicePut(keys, size, keysDevice1);
  clUtilDevicePut(vals, size, valsDevice1);

  clUtilEnqueueKernel("sort",
                      clUtilGrid(1, 1, rows, 1),
                      keysDevice1,
                      keysDevice2,
                      valsDevice1,
                      valsDevice2,
                      cols);

  clUtilDeviceGet(keys, size, keysDevice2);
  clUtilDeviceGet(vals, size, valsDevice2);

  for(unsigned int curRow = 0; curRow < rows; curRow++)
  {
    for(unsigned int curCol = 0; curCol < cols; curCol++)
    {
      printf("{%u, %u} ", 
             keys[curRow * cols + curCol],
             vals[curRow * cols + curCol]);
#if VERIFY
      if(curCol < cols - 1 &&
         keys[curRow * cols + curCol] < keys[curRow * cols + curCol + 1])
      {
        printf("Error, element %u, %u\n", curRow, curCol);
        exit(1);
      }
#endif
    }

    printf("\n");
  }

  printf("Success!\n");


  return 0;
}
