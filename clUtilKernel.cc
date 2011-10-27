#include "clUtil.h"

void clUtilSetArgs(cl_kernel kernel,
                   const char* kernelName,
                   clUtil::Grid& workGrid,
                   size_t argIndex)
{
}

void clUtilRunLambda(cl_event event,
                     cl_int status,
                     void* user_data)
{
  cl_int err;

  clUtilCallback* callback = (clUtilCallback*)user_data;

  (*callback)();

  err = clReleaseEvent(event);
  clUtilCheckError(err);

}

void gridSetGlobalLocal(size_t* global, 
                        size_t* local, 
                        unsigned int curDim)
{
}
