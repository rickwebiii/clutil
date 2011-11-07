#pragma once
#include <stdarg.h>

#include "clUtilCommon.h"
#include "clUtilDevice.h"
#include "clUtilMemory.h"

#define clUtilCheckKernelArg(kernelName, paramNum, err)\
  if(err != CL_SUCCESS)\
{\
  printf("__kernel %s(): %ld parameter: %s\n",\
         kernelName,\
         paramNum,\
         clUtilGetErrorCode(err));\
  raise(SIGTRAP);\
  return;\
}

void gridSetGlobalLocal(size_t* global, 
                        size_t* local, 
                        unsigned int curDim);

template<typename TGlobal, typename TLocal, typename...Args> 
void gridSetGlobalLocal(size_t* global, 
                        size_t* local, 
                        unsigned int curDim, 
                        TGlobal globalDimVal,
                        TLocal localDimVal,
                        Args... args)
{
  global[curDim] = globalDimVal % localDimVal == 0 ?
    globalDimVal :
    (globalDimVal / localDimVal + 1) * localDimVal;
  local[curDim] = localDimVal;

  gridSetGlobalLocal(global, local, curDim + 1, args...);
}

//Grid class definitions for defining work items
namespace clUtil
{
  //Base class. Exists for virtual function overloading.
  class Grid
  {
    public:
      virtual size_t getDim() = 0;
      virtual size_t* getGlobal() = 0;
      virtual size_t* getLocal() = 0;
  };

  //Created by clUtilGrid(). Actually contains work group information.
  template<typename... Args> class _Grid : public Grid
  {
    public:
      _Grid(Args... args)
      {
        gridSetGlobalLocal(mGlobal,
                           mLocal,
                           0,
                           args...);
      }

      size_t getDim(){return sizeof...(Args) / 2;}
      size_t* getGlobal(){return mGlobal;}
      size_t* getLocal(){return mLocal;}

    private:
      size_t mGlobal[sizeof...(Args) / 2];
      size_t mLocal[sizeof...(Args) / 2];

      _Grid();
  };
};

//Wrapper function to create a grid object of the correct type so you don't
//have to fuck with template arguments.
template<typename... Args> clUtil::_Grid<Args...> clUtilGrid(Args... args)
{
  return clUtil::_Grid<Args...>(args...);
}

//This function is a hack needed because variadic partial specialization doesn't
//seem to work quite right as of g++-4.5.2
template<typename T> void setArg_(cl_kernel kernel, size_t argIndex, T curArg)
{
  cl_int err;

  err = clSetKernelArg(kernel, argIndex, sizeof(curArg), &curArg);
  clUtilCheckError(err);
}

//void setArg_(cl_kernel kernel, size_t argIndex, clUtil::Memory&& curArg);
void setArg_(cl_kernel kernel, size_t argIndex, clUtil::Memory* curArg);
void setArg_(cl_kernel kernel, size_t argIndex, clUtil::Image&& curArg);
void setArg_(cl_kernel kernel, size_t argIndex, clUtil::Buffer&& curArg);

void clUtilSetArgs(cl_kernel kernel,
                   const char* kernelName,
                   clUtil::Grid& workGrid,
                   size_t argIndex);

template<typename T, typename... Args> 
void clUtilSetArgs(cl_kernel kernel,
                   const char* kernelName,
                   clUtil::Grid& workGrid,
                   size_t argIndex,
                   T curArg,
                   Args... args)
{
  setArg_(kernel, argIndex, curArg);

  clUtilSetArgs(kernel,
                kernelName,
                workGrid,
                argIndex + 1,
                args...);
}

template<typename... Args> 
void clUtilEnqueueKernel(const char* kernelName,
                         clUtil::Grid&& workGrid,
                         Args... args)
{
  cl_int err;
  clUtil::Device& currentDevice = clUtil::Device::GetCurrentDevice();
  cl_kernel kernel = currentDevice.getKernel(std::string(kernelName));

  clUtilSetArgs(kernel,
                kernelName,
                workGrid,
                0,
                args...);
  
  err = clEnqueueNDRangeKernel(currentDevice.getCommandQueue(),
                               kernel,
                               workGrid.getDim(),
                               NULL,
                               workGrid.getGlobal(),
                               workGrid.getLocal(),
                               0,
                               NULL,
                               NULL);
  clUtilCheckError(err);
}
