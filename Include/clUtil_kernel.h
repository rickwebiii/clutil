#pragma once
#include <stdarg.h>

#include "clUtil_core.h"

#ifdef _WIN32
  #define FORMAT_SPECIFIER_SIZE_T "%Iu"
#else
  #define FORMAT_SPECIFIER_SIZE_T "%zu"
#endif

#define clUtilCheckKernelArg(kernelName, paramNum, err)\
  if(err != CL_SUCCESS)\
{\
  printf("__kernel %s(): " FORMAT_SPECIFIER_SIZE_T " parameter: %s\n",\
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
  cl_int err;

  err = clSetKernelArg(kernel, argIndex, sizeof(T), &curArg);
  clUtilCheckKernelArg(kernelName, argIndex, err);

  clUtilSetArgs(kernel,
                kernelName,
                workGrid,
                argIndex + 1,
                args...);
}

//Asynchronous callback version
template<typename... Args> 
void clUtilEnqueueKernel(const char* kernelName,
                         clUtilCallback&& callback,
                         clUtil::Grid&& workGrid,
                         Args... args)
{
  cl_int err;
  cl_kernel kernel;
  std::string kernelNameStr(kernelName);
  cl_event event;

  kernel = clUtilGetKernel(kernelNameStr, &err);
  clUtilCheckErrorVoid(err);

  clUtilSetArgs(kernel,
                kernelName,
                workGrid,
                0,
                args...);
  
  err = clEnqueueNDRangeKernel(clUtilGetCommandQueue(),
                               kernel,
                               workGrid.getDim(),
                               NULL,
                               workGrid.getGlobal(),
                               workGrid.getLocal(),
                               0,
                               NULL,
                               &event);
  clUtilCheckErrorVoid(err);

  err = clSetEventCallback(event,
                           CL_COMPLETE, 
                           clUtilRunLambda, 
                           &callback);
  clUtilCheckErrorVoid(err);
}

//No callback version
template<typename... Args> 
void clUtilEnqueueKernel(const char* kernelName,
                         clUtil::Grid&& workGrid,
                         Args... args)
{
  cl_int err;
  cl_kernel kernel;
  std::string kernelNameStr(kernelName);

  kernel = clUtilGetKernel(kernelNameStr, &err);
  clUtilCheckErrorVoid(err);

  clUtilSetArgs(kernel,
                kernelName,
                workGrid,
                0,
                args...);
  
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
