#pragma once
#include <stdarg.h>

#include "clUtil_core.h"

#define clUtilCheckKernelArg(kernelName, paramNum, err)\
  if(err != CL_SUCCESS)\
  {\
    printf("__kernel %s(): %ld parameter: %s",\
           kernelName,\
           paramNum,\
           clUtil::getErrorCode(err));\
    raise(SIGTRAP);\
    return;\
  }

void clUtil_setArgs(cl_kernel kernel,
                    const char* kernelName,
                    size_t dim,
                    size_t* global,
                    size_t* local,
                    size_t argIndex);

  template<typename T, typename... Args> 
void clUtil_setArgs(cl_kernel kernel,
                    const char* kernelName,
                    size_t dim,
                    size_t* global,
                    size_t* local,
                    size_t argIndex,
                    T curArg,
                    Args... args)
{
  cl_int err;

  err = clSetKernelArg(kernel, argIndex, sizeof(T), &curArg);
  clUtilCheckKernelArg(kernelName, argIndex, err);

  clUtil_setArgs(kernel,
                 kernelName,
                 dim,
                 global,
                 local,
                 argIndex + 1,
                 args...);
}

  template<typename... Args> 
void clUtil_enqueueKernel(const char* kernelName,
                          size_t dim, 
                          size_t* global,
                          size_t* local,
                          Args... args)
{
  cl_int err;
  cl_kernel kernel;
  std::string kernelNameStr(kernelName);

  kernel = clUtil::getKernel(kernelNameStr, &err);
  clUtilCheckErrorVoid(err);

  clUtil_setArgs(kernel,
                 kernelName,
                 dim,
                 global,
                 local,
                 0,
                 args...);
}
