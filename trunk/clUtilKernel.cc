#include "clUtil.h"

void setArg_(cl_kernel kernel, size_t argIndex, clUtil::Memory& curArg)
{
  cl_int err;
  cl_mem memoryHandle = curArg.getMemHandle();

  err = clSetKernelArg(kernel, argIndex, sizeof(memoryHandle), &memoryHandle);
  clUtilCheckError(err);
}

void setArg_(cl_kernel kernel, size_t argIndex, clUtil::Image& curArg)
{
  cl_int err;
  cl_mem memoryHandle = curArg.getMemHandle();

  err = clSetKernelArg(kernel, argIndex, sizeof(memoryHandle), &memoryHandle);
  clUtilCheckError(err);
}

void setArg_(cl_kernel kernel, size_t argIndex, clUtil::Buffer& curArg)
{
  cl_int err;
  cl_mem memoryHandle = curArg.getMemHandle();

  err = clSetKernelArg(kernel, argIndex, sizeof(memoryHandle), &memoryHandle);
  clUtilCheckError(err);
}

void clUtilSetArgs(cl_kernel kernel,
                   const char* kernelName,
                   clUtil::Grid& workGrid,
                   size_t argIndex)
{
}

void gridSetGlobalLocal(size_t* global, 
                        size_t* local, 
                        unsigned int curDim)
{
}
