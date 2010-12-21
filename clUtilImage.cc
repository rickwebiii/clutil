#include "clUtil.h"

using namespace clUtil;

cl_int clUtilCopyToImageFloat(cl_mem buffer, 
                                int offset, 
                                int m, 
                                int n, 
                                int ld,
                                cl_mem* image)
{
  cl_int err;
  cl_image_format format;
  int imageWidth;

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
  
  clUtilEnqueueKernel("copyToImageFloat",
                      clUtilCreateGrid(imageWidth, 8, n, 8),
                      buffer,
                      offset,
                      m,
                      n,
                      ld,
                      image);
  
  return CL_SUCCESS;
}

cl_int clUtilCopyToImageTransposeFloat(cl_mem buffer, 
                                         int offset, 
                                         int m, 
                                         int n, 
                                         int ld,
                                         cl_mem* image)
{
  cl_int err;
  cl_image_format format;
  int imageWidth;

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
  
  clUtilEnqueueKernel("copyToImageTransposeFloat",
                      clUtilCreateGrid(imageWidth, 8, m, 8),
                      buffer,
                      offset,
                      m,
                      n,
                      ld,
                      image);
  
  return CL_SUCCESS;
}

cl_int clUtilCopyToImageDouble(cl_mem buffer, 
                                 int offset, 
                                 int m, 
                                 int n, 
                                 int ld,
                                 cl_mem* image)
{
  cl_int err;
  cl_image_format format;
  int imageWidth;

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

  clUtilEnqueueKernel("copyToImageDouble",
                      clUtilCreateGrid(imageWidth, 8, n, 8),
                      buffer,
                      offset,
                      m,
                      n,
                      ld,
                      image);

  return CL_SUCCESS;
}

cl_int clUtilCopyToImageTransposeDouble(cl_mem buffer, 
                                          int offset, 
                                          int m, 
                                          int n, 
                                          int ld,
                                          cl_mem* image)
{
  cl_int err;
  cl_image_format format;
  int imageWidth;

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
  
  clUtilEnqueueKernel("copyToImageTransposeDouble",
                      clUtilCreateGrid(imageWidth, 8, m, 8),
                      buffer,
                      offset,
                      m,
                      n,
                      ld,
                      image);



  return CL_SUCCESS;
}

cl_int clUtilCopyToImageFloat4(cl_mem buffer, 
                                 int offset, 
                                 int m, 
                                 int n, 
                                 int ld,
                                 cl_mem* image)
{
  cl_int err;
  cl_image_format format;
  int imageWidth;

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

  clUtilEnqueueKernel("copyToImageFloat4",
                      clUtilCreateGrid(imageWidth, 8, n, 8),
                      buffer,
                      offset,
                      m,
                      n,
                      ld,
                      image);
  
  return CL_SUCCESS;
}

cl_int clUtilCopyToImageTransposeFloat4(cl_mem buffer, 
                                          int offset, 
                                          int m, 
                                          int n, 
                                          int ld,
                                          cl_mem* image)
{
  cl_int err;
  cl_image_format format;
  int imageWidth;

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

  clUtilEnqueueKernel("copyToImageTransposeFloat4",
                      clUtilCreateGrid(imageWidth, 8, m, 8),
                      buffer,
                      offset,
                      m,
                      n,
                      ld,
                      image);

  return CL_SUCCESS;
}

cl_int clUtilCopyToImageDouble2(cl_mem buffer, 
                                  int offset, 
                                  int m, 
                                  int n, 
                                  int ld,
                                  cl_mem* image)
{
  cl_int err;
  cl_image_format format;
  int imageWidth;

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
  
  clUtilEnqueueKernel("copyToImageDouble2",
                      clUtilCreateGrid(imageWidth, 8, n, 8),
                      buffer,
                      offset,
                      m,
                      n,
                      ld,
                      image);

  return CL_SUCCESS;
}

cl_int clUtilCopyToImageTransposeDouble2(cl_mem buffer, 
                                           int offset, 
                                           int m, 
                                           int n, 
                                           int ld,
                                           cl_mem* image)
{
  cl_int err;
  cl_image_format format;
  int imageWidth;

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

  clUtilEnqueueKernel("copyToImageTransposeDouble2",
                      clUtilCreateGrid(imageWidth, 8, m, 8),
                      buffer,
                      offset,
                      m,
                      n,
                      ld,
                      image);
  
  return CL_SUCCESS;
}

cl_int clUtilDebugPrintImageFloat(cl_mem image)
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

  err = clEnqueueReadImage(clUtilGetCommandQueue(),
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

cl_int clUtilDebugPrintImageDouble(cl_mem image)
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

  err = clEnqueueReadImage(clUtilGetCommandQueue(),
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
