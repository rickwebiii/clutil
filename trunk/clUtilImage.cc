#include "clUtil.h"

cl_int clUtil::copyToImageFloat(cl_mem buffer, 
                                int offset, 
                                int m, 
                                int n, 
                                int ld,
                                cl_mem* image)
{
  cl_int err;
  static int lastDevice = -1;
  static cl_kernel kernel = 0;
  size_t globalWork[2];
  size_t localWork[2];
  cl_image_format format;
  int imageWidth;
  size_t maxWorkSize;

  if(lastDevice != gCurrentDevice)
  {
    kernel = clCreateKernel(getProgram(),
                            "copyToImageFloat",
                            &err);
    clUtilCheckError(err);
  }

  imageWidth = m;

  //Set image format
  format.image_channel_order = CL_A;
  format.image_channel_data_type = CL_FLOAT;

  *image = clCreateImage2D(gContexts[gCurrentDevice],
                           CL_MEM_READ_WRITE,
                           &format,
                           imageWidth,
                           n,
                           0,
                           NULL,
                           &err);
  clUtilCheckError(err);

  err = clSetKernelArg(kernel, 0, sizeof(buffer), &buffer);
  clUtilCheckError(err);
  err = clSetKernelArg(kernel, 1, sizeof(offset), &offset);
  clUtilCheckError(err);
  err = clSetKernelArg(kernel, 2, sizeof(m), &m);
  clUtilCheckError(err);
  err = clSetKernelArg(kernel, 3, sizeof(n), &n);
  clUtilCheckError(err);
  err = clSetKernelArg(kernel, 4, sizeof(ld), &ld);
  clUtilCheckError(err);
  err = clSetKernelArg(kernel, 5, sizeof(*image), image);
  clUtilCheckError(err);

  maxWorkSize = getMaxBlockSize();
  localWork[0] = maxWorkSize < 64 ? 1 : 8;
  localWork[1] = localWork[0];

  globalWork[0] = imageWidth % localWork[0] == 0 && imageWidth >= localWork[0] ?
    imageWidth :
    (imageWidth/localWork[0] + 1) * localWork[0];
  globalWork[1] = n % localWork[0] == 0 && n >= localWork[0] ?
    n :
    (n/localWork[0] + 1) * localWork[0];

  err = clEnqueueNDRangeKernel(getCommandQueue(),
                               kernel,
                               2,
                               NULL,
                               globalWork,
                               localWork,
                               0,
                               NULL,
                               NULL);
  clUtilCheckError(err);
  clFinish(getCommandQueue());

  return CL_SUCCESS;
}

cl_int clUtil::copyToImageTransposeFloat(cl_mem buffer, 
                                         int offset, 
                                         int m, 
                                         int n, 
                                         int ld,
                                         cl_mem* image)
{
  cl_int err;
  static int lastDevice = -1;
  static cl_kernel kernel = 0;
  size_t globalWork[2];
  size_t localWork[2];
  cl_image_format format;
  int imageWidth;
  size_t maxWorkSize;

  if(lastDevice != gCurrentDevice)
  {
    kernel = clCreateKernel(getProgram(),
                            "copyToImageTransposeFloat",
                            &err);
    clUtilCheckError(err);
  }

  imageWidth = n;

  //Set image format
  format.image_channel_order = CL_A;
  format.image_channel_data_type = CL_FLOAT;

  *image = clCreateImage2D(gContexts[gCurrentDevice],
                           CL_MEM_READ_WRITE,
                           &format,
                           imageWidth,
                           m,
                           0,
                           NULL,
                           &err);
  clUtilCheckError(err);

  err = clSetKernelArg(kernel, 0, sizeof(buffer), &buffer);
  clUtilCheckError(err);
  err = clSetKernelArg(kernel, 1, sizeof(offset), &offset);
  clUtilCheckError(err);
  err = clSetKernelArg(kernel, 2, sizeof(m), &m);
  clUtilCheckError(err);
  err = clSetKernelArg(kernel, 3, sizeof(n), &n);
  clUtilCheckError(err);
  err = clSetKernelArg(kernel, 4, sizeof(ld), &ld);
  clUtilCheckError(err);
  err = clSetKernelArg(kernel, 5, sizeof(*image), image);
  clUtilCheckError(err);

  maxWorkSize = getMaxBlockSize();
  localWork[0] = maxWorkSize < 64 ? 1 : 8;
  localWork[1] = localWork[0];

  globalWork[1] = n % localWork[0] == 0 && n >= localWork[0] ?
    n :
    (m/localWork[0] + 1) * localWork[0];
  globalWork[0] = imageWidth % localWork[1] == 0 && imageWidth >= localWork[1] ?
    imageWidth :
    (imageWidth/localWork[1] + 1) * localWork[1];

  err = clEnqueueNDRangeKernel(getCommandQueue(),
                               kernel,
                               2,
                               NULL,
                               globalWork,
                               localWork,
                               0,
                               NULL,
                               NULL);
  clUtilCheckError(err);
  clFinish(getCommandQueue());

  return CL_SUCCESS;
}

cl_int clUtil::copyToImageDouble(cl_mem buffer, 
                                 int offset, 
                                 int m, 
                                 int n, 
                                 int ld,
                                 cl_mem* image)
{
  cl_int err;
  static int lastDevice = -1;
  static cl_kernel kernel = 0;
  size_t globalWork[2];
  size_t localWork[2];
  cl_image_format format;
  int imageWidth;
  size_t maxWorkSize;

  if(lastDevice != gCurrentDevice)
  {
    kernel = clCreateKernel(getProgram(),
                            "copyToImageDouble",
                            &err);
    clUtilCheckError(err);
  }

  imageWidth = m;

  //Set image format
  format.image_channel_order = CL_RG;
  format.image_channel_data_type = CL_FLOAT;

  *image = clCreateImage2D(gContexts[gCurrentDevice],
                           CL_MEM_READ_WRITE,
                           &format,
                           imageWidth,
                           n,
                           0,
                           NULL,
                           &err);
  clUtilCheckError(err);

  err = clSetKernelArg(kernel, 0, sizeof(buffer), &buffer);
  clUtilCheckError(err);
  err = clSetKernelArg(kernel, 1, sizeof(offset), &offset);
  clUtilCheckError(err);
  err = clSetKernelArg(kernel, 2, sizeof(m), &m);
  clUtilCheckError(err);
  err = clSetKernelArg(kernel, 3, sizeof(n), &n);
  clUtilCheckError(err);
  err = clSetKernelArg(kernel, 4, sizeof(ld), &ld);
  clUtilCheckError(err);
  err = clSetKernelArg(kernel, 5, sizeof(*image), image);
  clUtilCheckError(err);

  maxWorkSize = getMaxBlockSize();
  localWork[0] = maxWorkSize < 64 ? 1 : 8;
  localWork[1] = localWork[0];

  globalWork[0] = imageWidth % localWork[0] == 0 && imageWidth >= localWork[0] ?
    imageWidth :
    (imageWidth/localWork[0] + 1) * localWork[0];
  globalWork[1] = n % localWork[0] == 0 && n >= localWork[0] ?
    n :
    (n/localWork[0] + 1) * localWork[0];

  err = clEnqueueNDRangeKernel(getCommandQueue(),
                               kernel,
                               2,
                               NULL,
                               globalWork,
                               localWork,
                               0,
                               NULL,
                               NULL);
  clUtilCheckError(err);
  clFinish(getCommandQueue());

  return CL_SUCCESS;
}

cl_int clUtil::copyToImageTransposeDouble(cl_mem buffer, 
                                          int offset, 
                                          int m, 
                                          int n, 
                                          int ld,
                                          cl_mem* image)
{
  cl_int err;
  static int lastDevice = -1;
  static cl_kernel kernel = 0;
  size_t globalWork[2];
  size_t localWork[2];
  cl_image_format format;
  int imageWidth;
  size_t maxWorkSize;

  if(lastDevice != gCurrentDevice)
  {
    kernel = clCreateKernel(getProgram(),
                            "copyToImageTransposeDouble",
                            &err);
    clUtilCheckError(err);
  }

  imageWidth = n;

  //Set image format
  format.image_channel_order = CL_RG;
  format.image_channel_data_type = CL_FLOAT;

  *image = clCreateImage2D(gContexts[gCurrentDevice],
                           CL_MEM_READ_WRITE,
                           &format,
                           imageWidth,
                           m,
                           0,
                           NULL,
                           &err);
  clUtilCheckError(err);

  err = clSetKernelArg(kernel, 0, sizeof(buffer), &buffer);
  clUtilCheckError(err);
  err = clSetKernelArg(kernel, 1, sizeof(offset), &offset);
  clUtilCheckError(err);
  err = clSetKernelArg(kernel, 2, sizeof(m), &m);
  clUtilCheckError(err);
  err = clSetKernelArg(kernel, 3, sizeof(n), &n);
  clUtilCheckError(err);
  err = clSetKernelArg(kernel, 4, sizeof(ld), &ld);
  clUtilCheckError(err);
  err = clSetKernelArg(kernel, 5, sizeof(*image), image);
  clUtilCheckError(err);

  maxWorkSize = getMaxBlockSize();
  localWork[0] = maxWorkSize < 64 ? 1 : 8;
  localWork[1] = localWork[0];

  globalWork[1] = n % localWork[0] == 0 && n >= localWork[0] ?
    n :
    (m/localWork[0] + 1) * localWork[0];
  globalWork[0] = imageWidth % localWork[1] == 0 && imageWidth >= localWork[1] ?
    imageWidth :
    (imageWidth/localWork[1] + 1) * localWork[1];

  err = clEnqueueNDRangeKernel(getCommandQueue(),
                               kernel,
                               2,
                               NULL,
                               globalWork,
                               localWork,
                               0,
                               NULL,
                               NULL);
  clUtilCheckError(err);
  clFinish(getCommandQueue());

  return CL_SUCCESS;
}

cl_int clUtil::copyToImageFloat4(cl_mem buffer, 
                                 int offset, 
                                 int m, 
                                 int n, 
                                 int ld,
                                 cl_mem* image)
{
  cl_int err;
  static int lastDevice = -1;
  static cl_kernel kernel = 0;
  size_t globalWork[2];
  size_t localWork[2];
  cl_image_format format;
  int imageWidth;
  size_t maxWorkSize;

  if(lastDevice != gCurrentDevice)
  {
    kernel = clCreateKernel(getProgram(),
                            "copyToImageFloat4",
                            &err);
    clUtilCheckError(err);
  }

  imageWidth = m % 4 == 0 ? m / 4 : m / 4 + 1;

  //Set image format
  format.image_channel_order = CL_RGBA;
  format.image_channel_data_type = CL_FLOAT;

  *image = clCreateImage2D(gContexts[gCurrentDevice],
                           CL_MEM_READ_WRITE,
                           &format,
                           imageWidth,
                           n,
                           0,
                           NULL,
                           &err);
  clUtilCheckError(err);

  err = clSetKernelArg(kernel, 0, sizeof(buffer), &buffer);
  clUtilCheckError(err);
  err = clSetKernelArg(kernel, 1, sizeof(offset), &offset);
  clUtilCheckError(err);
  err = clSetKernelArg(kernel, 2, sizeof(m), &m);
  clUtilCheckError(err);
  err = clSetKernelArg(kernel, 3, sizeof(n), &n);
  clUtilCheckError(err);
  err = clSetKernelArg(kernel, 4, sizeof(ld), &ld);
  clUtilCheckError(err);
  err = clSetKernelArg(kernel, 5, sizeof(*image), image);
  clUtilCheckError(err);

  maxWorkSize = getMaxBlockSize();
  localWork[0] = maxWorkSize < 64 ? 1 : 8;
  localWork[1] = localWork[0];

  globalWork[0] = imageWidth % localWork[0] == 0 && imageWidth >= localWork[0] ?
    imageWidth :
    (imageWidth/localWork[0] + 1) * localWork[0];
  globalWork[1] = n % localWork[0] == 0 && n >= localWork[0] ?
    n :
    (n/localWork[0] + 1) * localWork[0];

  err = clEnqueueNDRangeKernel(getCommandQueue(),
                               kernel,
                               2,
                               NULL,
                               globalWork,
                               localWork,
                               0,
                               NULL,
                               NULL);
  clUtilCheckError(err);
  clFinish(getCommandQueue());

  return CL_SUCCESS;
}

cl_int clUtil::copyToImageTransposeFloat4(cl_mem buffer, 
                                          int offset, 
                                          int m, 
                                          int n, 
                                          int ld,
                                          cl_mem* image)
{
  cl_int err;
  static int lastDevice = -1;
  static cl_kernel kernel = 0;
  size_t globalWork[2];
  size_t localWork[2];
  cl_image_format format;
  int imageWidth;
  size_t maxWorkSize;

  if(lastDevice != gCurrentDevice)
  {
    kernel = clCreateKernel(getProgram(),
                            "copyToImageTransposeFloat4",
                            &err);
    clUtilCheckError(err);
  }

  imageWidth = n % 4 == 0 ? n / 4 : n / 4 + 1;

  //Set image format
  format.image_channel_order = CL_RGBA;
  format.image_channel_data_type = CL_FLOAT;

  *image = clCreateImage2D(gContexts[gCurrentDevice],
                           CL_MEM_READ_WRITE,
                           &format,
                           imageWidth,
                           m,
                           0,
                           NULL,
                           &err);
  clUtilCheckError(err);

  err = clSetKernelArg(kernel, 0, sizeof(buffer), &buffer);
  clUtilCheckError(err);
  err = clSetKernelArg(kernel, 1, sizeof(offset), &offset);
  clUtilCheckError(err);
  err = clSetKernelArg(kernel, 2, sizeof(m), &m);
  clUtilCheckError(err);
  err = clSetKernelArg(kernel, 3, sizeof(n), &n);
  clUtilCheckError(err);
  err = clSetKernelArg(kernel, 4, sizeof(ld), &ld);
  clUtilCheckError(err);
  err = clSetKernelArg(kernel, 5, sizeof(*image), image);
  clUtilCheckError(err);

  maxWorkSize = getMaxBlockSize();
  localWork[0] = maxWorkSize < 64 ? 1 : 8;
  localWork[1] = localWork[0];

  globalWork[1] = n % localWork[0] == 0 && n >= localWork[0] ?
    n :
    (m/localWork[0] + 1) * localWork[0];
  globalWork[0] = imageWidth % localWork[1] == 0 && imageWidth >= localWork[1] ?
    imageWidth :
    (imageWidth/localWork[1] + 1) * localWork[1];

  err = clEnqueueNDRangeKernel(getCommandQueue(),
                               kernel,
                               2,
                               NULL,
                               globalWork,
                               localWork,
                               0,
                               NULL,
                               NULL);
  clUtilCheckError(err);
  clFinish(getCommandQueue());

  return CL_SUCCESS;
}

cl_int clUtil::copyToImageDouble2(cl_mem buffer, 
                                  int offset, 
                                  int m, 
                                  int n, 
                                  int ld,
                                  cl_mem* image)
{
  cl_int err;
  static int lastDevice = -1;
  static cl_kernel kernel = 0;
  size_t globalWork[2];
  size_t localWork[2];
  cl_image_format format;
  int imageWidth;
  size_t maxWorkSize;

  if(lastDevice != gCurrentDevice)
  {
    kernel = clCreateKernel(getProgram(),
                            "copyToImageDouble2",
                            &err);
    clUtilCheckError(err);
  }

  imageWidth = m % 2 == 0 ? m / 2 : m / 2 + 1;

  //Set image format
  format.image_channel_order = CL_RGBA;
  format.image_channel_data_type = CL_FLOAT;

  *image = clCreateImage2D(gContexts[gCurrentDevice],
                           CL_MEM_READ_WRITE,
                           &format,
                           imageWidth,
                           n,
                           0,
                           NULL,
                           &err);
  clUtilCheckError(err);

  err = clSetKernelArg(kernel, 0, sizeof(buffer), &buffer);
  clUtilCheckError(err);
  err = clSetKernelArg(kernel, 1, sizeof(offset), &offset);
  clUtilCheckError(err);
  err = clSetKernelArg(kernel, 2, sizeof(m), &m);
  clUtilCheckError(err);
  err = clSetKernelArg(kernel, 3, sizeof(n), &n);
  clUtilCheckError(err);
  err = clSetKernelArg(kernel, 4, sizeof(ld), &ld);
  clUtilCheckError(err);
  err = clSetKernelArg(kernel, 5, sizeof(*image), image);
  clUtilCheckError(err);

  maxWorkSize = getMaxBlockSize();
  localWork[0] = maxWorkSize < 64 ? 1 : 8;
  localWork[1] = localWork[0];

  globalWork[0] = imageWidth % localWork[0] == 0 && imageWidth >= localWork[0] ?
    imageWidth :
    (imageWidth/localWork[0] + 1) * localWork[0];
  globalWork[1] = n % localWork[0] == 0 && n >= localWork[0] ?
    n :
    (n/localWork[0] + 1) * localWork[0];

  err = clEnqueueNDRangeKernel(getCommandQueue(),
                               kernel,
                               2,
                               NULL,
                               globalWork,
                               localWork,
                               0,
                               NULL,
                               NULL);
  clUtilCheckError(err);
  clFinish(getCommandQueue());

  return CL_SUCCESS;
}

cl_int clUtil::copyToImageTransposeDouble2(cl_mem buffer, 
                                           int offset, 
                                           int m, 
                                           int n, 
                                           int ld,
                                           cl_mem* image)
{
  cl_int err;
  static int lastDevice = -1;
  static cl_kernel kernel = 0;
  size_t globalWork[2];
  size_t localWork[2];
  cl_image_format format;
  int imageWidth;
  size_t maxWorkSize;

  if(lastDevice != gCurrentDevice)
  {
    kernel = clCreateKernel(getProgram(),
                            "copyToImageTransposeDouble2",
                            &err);
    clUtilCheckError(err);
  }

  imageWidth = n % 2 == 0 ? n / 2 : n / 2 + 1;

  //Set image format
  format.image_channel_order = CL_RGBA;
  format.image_channel_data_type = CL_FLOAT;

  *image = clCreateImage2D(gContexts[gCurrentDevice],
                           CL_MEM_READ_WRITE,
                           &format,
                           imageWidth,
                           m,
                           0,
                           NULL,
                           &err);
  clUtilCheckError(err);

  err = clSetKernelArg(kernel, 0, sizeof(buffer), &buffer);
  clUtilCheckError(err);
  err = clSetKernelArg(kernel, 1, sizeof(offset), &offset);
  clUtilCheckError(err);
  err = clSetKernelArg(kernel, 2, sizeof(m), &m);
  clUtilCheckError(err);
  err = clSetKernelArg(kernel, 3, sizeof(n), &n);
  clUtilCheckError(err);
  err = clSetKernelArg(kernel, 4, sizeof(ld), &ld);
  clUtilCheckError(err);
  err = clSetKernelArg(kernel, 5, sizeof(*image), image);
  clUtilCheckError(err);

  maxWorkSize = getMaxBlockSize();
  localWork[0] = maxWorkSize < 64 ? 1 : 8;
  localWork[1] = localWork[0];

  globalWork[1] = n % localWork[0] == 0 && n >= localWork[0] ?
    n :
    (m/localWork[0] + 1) * localWork[0];
  globalWork[0] = imageWidth % localWork[1] == 0 && imageWidth >= localWork[1] ?
    imageWidth :
    (imageWidth/localWork[1] + 1) * localWork[1];

  err = clEnqueueNDRangeKernel(getCommandQueue(),
                               kernel,
                               2,
                               NULL,
                               globalWork,
                               localWork,
                               0,
                               NULL,
                               NULL);
  clUtilCheckError(err);
  clFinish(getCommandQueue());

  return CL_SUCCESS;
}

cl_int clUtil::debugPrintImageFloat(cl_mem image)
{
  size_t width;
  size_t height;
  cl_int err;
  float* data;
  size_t origin[3] = {0, 0, 0};
  size_t region[3] = {1, 1, 1};
  cl_image_format channelFormat;
  size_t channelSize;

  err = clGetImageInfo(image,
                       CL_IMAGE_WIDTH,
                       sizeof(width),
                       &width,
                       NULL);
  clUtilCheckError(err);

  err = clGetImageInfo(image,
                       CL_IMAGE_HEIGHT,
                       sizeof(height),
                       &height,
                       NULL);
  clUtilCheckError(err);
  
  err = clGetImageInfo(image,
                       CL_IMAGE_ELEMENT_SIZE,
                       sizeof(channelSize),
                       &channelSize,
                       NULL);
  clUtilCheckError(err);

  //Get number of floats per channel (4 or 1) in the image
  channelSize = channelFormat.image_channel_order == CL_RGBA ? 4 : 1;

  data = new float[channelSize * width * height];
  region[0] = width;
  region[1] = height;

  err = clEnqueueReadImage(getCommandQueue(),
                           image,
                           CL_TRUE,
                           origin,
                           region,
                           0,
                           0,
                           data,
                           0,
                           NULL,
                           NULL);
  clUtilCheckError(err);

  for(size_t i = 0; i < channelSize * width; i++)
  {
    for(size_t j = 0; j < height; j++)
    {
      printf("%6.5E ", data[i + j * channelSize * width]);
    }
    printf("\n");
  }

  delete[] data;

  return CL_SUCCESS;
}

cl_int clUtil::debugPrintImageDouble(cl_mem image)
{
  size_t width;
  size_t height;
  cl_int err;
  double* data;
  size_t origin[3] = {0, 0, 0};
  size_t region[3] = {1, 1, 1};
  cl_image_format channelFormat;
  size_t channelSize;

  err = clGetImageInfo(image,
                       CL_IMAGE_WIDTH,
                       sizeof(width),
                       &width,
                       NULL);
  clUtilCheckError(err);

  err = clGetImageInfo(image,
                       CL_IMAGE_HEIGHT,
                       sizeof(height),
                       &height,
                       NULL);
  clUtilCheckError(err);
  
  err = clGetImageInfo(image,
                       CL_IMAGE_ELEMENT_SIZE,
                       sizeof(channelSize),
                       &channelSize,
                       NULL);
  clUtilCheckError(err);

  //Get number of doubles per channel (2 or 1) in the image
  channelSize = channelFormat.image_channel_order == CL_RGBA ? 2 : 1;

  data = new double[channelSize * width * height];
  region[0] = width;
  region[1] = height;

  err = clEnqueueReadImage(getCommandQueue(),
                           image,
                           CL_TRUE,
                           origin,
                           region,
                           0,
                           0,
                           data,
                           0,
                           NULL,
                           NULL);
  clUtilCheckError(err);

  for(size_t i = 0; i < channelSize * width; i++)
  {
    for(size_t j = 0; j < height; j++)
    {
      printf("%6.5E ", data[i + j * channelSize * width]);
    }
    printf("\n");
  }

  delete[] data;

  return CL_SUCCESS;
}
