#include "clUtil.h"

void setArg_(const cl_kernel kernel, 
             const size_t argIndex, 
             const clUtil::Memory* curArg)
{
  cl_int err;
  cl_mem memoryHandle = curArg->getMemHandle();

  err = clSetKernelArg(kernel, argIndex, sizeof(memoryHandle), &memoryHandle);
  clUtilCheckError(err);
}

void setArg_(const cl_kernel kernel, 
             const size_t argIndex, 
             const clUtil::Image& curArg)
{
  cl_int err;
  cl_mem memoryHandle = curArg.getMemHandle();

  err = clSetKernelArg(kernel, argIndex, sizeof(memoryHandle), &memoryHandle);
  clUtilCheckError(err);
}

void setArg_(const cl_kernel kernel, 
             const size_t argIndex, 
             const clUtil::Image&& curArg)
{
  cl_int err;
  cl_mem memoryHandle = curArg.getMemHandle();

  err = clSetKernelArg(kernel, argIndex, sizeof(memoryHandle), &memoryHandle);
  clUtilCheckError(err);
}

void setArg_(const cl_kernel kernel, 
             const size_t argIndex, 
             const clUtil::Buffer& curArg)
{
  cl_int err;
  cl_mem memoryHandle = curArg.getMemHandle();

  err = clSetKernelArg(kernel, argIndex, sizeof(memoryHandle), &memoryHandle);
  clUtilCheckError(err);
}

void setArg_(const cl_kernel kernel, 
             const size_t argIndex, 
             const clUtil::Buffer&& curArg)
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
