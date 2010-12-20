#include "clUtil_kernel.h"

void clUtil_setArgs(cl_kernel kernel,
                    const char* kernelName,
                    size_t dim,
                    size_t* global,
                    size_t* local,
                    size_t argIndex)
{
  cl_int err;

  err = clEnqueueNDRangeKernel(clUtil::getCommandQueue(),
                               kernel,
                               dim,
                               NULL,
                               global,
                               local,
                               0,
                               NULL,
                               NULL);
  clUtilCheckErrorVoid(err);
}
