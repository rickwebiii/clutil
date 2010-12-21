#include "clUtil_kernel.h"

void clUtilSetArgs(cl_kernel kernel,
                   const char* kernelName,
                   clUtil::Grid& workGrid,
                   size_t argIndex)
{
  cl_int err;

  err = clEnqueueNDRangeKernel(clUtilGetCommandQueue(),
                               kernel,
                               workGrid.getDim(),
                               NULL,
                               workGrid.getGlobal(),
                               workGrid.getLocal(),
                               0,
                               NULL,
                               NULL);
  clUtilCheckErrorVoid(err);
}

void gridSetGlobalLocal(size_t* global, 
                        size_t* local, 
                        unsigned int curDim)
{
}
