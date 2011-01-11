//Enable double precision
#ifdef GENUINEINTEL
#pragma OPENCL EXTENSION cl_amd_fp64 : enable
#else
#ifdef ADVANCED_MICRO_DEVICES__INC_
#pragma OPENCL EXTENSION cl_amd_fp64 : enable
#else
#pragma OPENCL EXTENSION cl_khr_fp64 : enable
#endif
#endif

//Declare a bunch of samplers
#ifdef NVIDIA_CORPORATION
const sampler_t s0 = CLK_NORMALIZED_COORDS_FALSE | \
                     CLK_ADDRESS_CLAMP | \
                     CLK_FILTER_NEAREST;
const sampler_t s1 = CLK_NORMALIZED_COORDS_FALSE | \
                     CLK_ADDRESS_CLAMP | \
                     CLK_FILTER_NEAREST;
const sampler_t s2 = CLK_NORMALIZED_COORDS_FALSE | \
                     CLK_ADDRESS_CLAMP | \
                     CLK_FILTER_NEAREST;
const sampler_t s3 = CLK_NORMALIZED_COORDS_FALSE | \
                     CLK_ADDRESS_CLAMP | \
                     CLK_FILTER_NEAREST;
const sampler_t s4 = CLK_NORMALIZED_COORDS_FALSE | \
                     CLK_ADDRESS_CLAMP | \
                     CLK_FILTER_NEAREST;
const sampler_t s5 = CLK_NORMALIZED_COORDS_FALSE | \
                     CLK_ADDRESS_CLAMP | \
                     CLK_FILTER_NEAREST;
const sampler_t s6 = CLK_NORMALIZED_COORDS_FALSE | \
                     CLK_ADDRESS_CLAMP | \
                     CLK_FILTER_NEAREST;
const sampler_t s7 = CLK_NORMALIZED_COORDS_FALSE | \
                     CLK_ADDRESS_CLAMP | \
                     CLK_FILTER_NEAREST;
#else
__constant sampler_t s0 = CLK_NORMALIZED_COORDS_FALSE | \
                          CLK_ADDRESS_CLAMP | \
                          CLK_FILTER_NEAREST;
__constant sampler_t s1 = CLK_NORMALIZED_COORDS_FALSE | \
                          CLK_ADDRESS_CLAMP | \
                          CLK_FILTER_NEAREST;
__constant sampler_t s2 = CLK_NORMALIZED_COORDS_FALSE | \
                          CLK_ADDRESS_CLAMP | \
                          CLK_FILTER_NEAREST;
__constant sampler_t s3 = CLK_NORMALIZED_COORDS_FALSE | \
                          CLK_ADDRESS_CLAMP | \
                          CLK_FILTER_NEAREST;
__constant sampler_t s4 = CLK_NORMALIZED_COORDS_FALSE | \
                          CLK_ADDRESS_CLAMP | \
                          CLK_FILTER_NEAREST;
__constant sampler_t s5 = CLK_NORMALIZED_COORDS_FALSE | \
                          CLK_ADDRESS_CLAMP | \
                          CLK_FILTER_NEAREST;
__constant sampler_t s6 = CLK_NORMALIZED_COORDS_FALSE | \
                          CLK_ADDRESS_CLAMP | \
                          CLK_FILTER_NEAREST;
__constant sampler_t s7 = CLK_NORMALIZED_COORDS_FALSE | \
                          CLK_ADDRESS_CLAMP | \
                          CLK_FILTER_NEAREST;
#endif

#ifndef NVIDIA_CORPORATION
typedef image2d_t image1d_t;
#else
#define image1d_t image2d_t
#endif


float4 read_1Dimagef(image1d_t image,
                     sampler_t sampler,
                     int coord)
{
  int2 imageDim = get_image_dim(image);
  int2 sampleCoord;

  sampleCoord.x = coord % imageDim.x;
  sampleCoord.y = coord / imageDim.x;

  return read_imagef(image, sampler, sampleCoord);
}

int4 read_1Dimagei(image1d_t image,
                   sampler_t sampler,
                   int coord)
{
  int2 imageDim = get_image_dim(image);
  int2 sampleCoord;

  sampleCoord.x = coord % imageDim.x;
  sampleCoord.y = coord / imageDim.x;

  return read_imagei(image, sampler, sampleCoord);
}

uint4 read_1Dimageui(image1d_t image,
                     sampler_t sampler,
                     int coord)
{
  int2 imageDim = get_image_dim(image);
  int2 sampleCoord;

  sampleCoord.x = coord % imageDim.x;
  sampleCoord.y = coord / imageDim.x;

  return read_imageui(image, sampler, sampleCoord);
}

void write_1Dimagef(image1d_t image,
                    int coord,
                    float4 color)
{
  int2 imageDim = get_image_dim(image);
  int2 sampleCoord;

  sampleCoord.x = coord % imageDim.x;
  sampleCoord.y = coord / imageDim.x;

  write_imagef(image, sampleCoord, color);
}

__kernel void copyToImageFloat(__global float* aBase,
                               int offset,
                               int m,
                               int n,
                               int ld,
                               write_only image2d_t aImage)
{
  __global float* a = &aBase[offset];

  int2 coord;

  coord.x = get_global_id(0);
  coord.y = get_global_id(1); 
  float4 output = {0.0f, 0.0f, 0.0f, 0.0f};
  size_t row = coord.x;
  size_t col = coord.y;


  //If we're in the matrix, write to our location in the image
  if(row <  m && col < n)
  {
    //Write the alpha component only
    output.w = a[row + col * ld];
    
    write_imagef(aImage, coord, output);
  }
}

__kernel void copyToImageTransposeFloat(__global float* aBase,
                                        int offset,
                                        int m,
                                        int n,
                                        int ld,
                                        write_only image2d_t aImage)
{
  __global float* a = &aBase[offset];

  int2 coord;

  coord.x = get_global_id(0);
  coord.y = get_global_id(1); 
  float4 output = {0.0f, 0.0f, 0.0f, 0.0f};
  size_t row = coord.x;
  size_t col = coord.y;

  //If we're in the matrix, write our location in the image
  if(row <  n && col < m)
  {
    //Write alpha component only
    output.w = a[col + row * ld];
    
    write_imagef(aImage, coord, output);
  }
}

__kernel void copyToImageDouble(__global float* aBase,
                                int offset,
                                int m,
                                int n,
                                int ld,
                                write_only image2d_t aImage)
{
  int2 coord;

  coord.x = get_global_id(0);
  coord.y = get_global_id(1); 
  float4 output = {0.0f, 0.0f, 0.0f, 0.0f};
  size_t row = coord.x;
  size_t col = coord.y;
  __global float* a = &aBase[2 * offset];

  ld *= 2;

  if(row <  m && col < n)
  {
    //The concatnation of two floats is a double in this case
    output.x = a[2 * row + 0 + col * ld];
    output.y = a[2 * row + 1 + col * ld];

    write_imagef(aImage, coord, output);
  }
}

__kernel void copyToImageTransposeDouble(__global float* a,
                                         int offset,
                                         int m,
                                         int n,
                                         int ld,
                                         write_only image2d_t aImage)
{
  a = &a[offset];

  int2 coord;

  coord.x = get_global_id(0);
  coord.y = get_global_id(1); 
  float4 output = {0.0f, 0.0f, 0.0f, 0.0f};
  size_t row = coord.x;
  size_t col = coord.y;

  ld *= 2;

  if(row <  n && col < m)
  {
    //The concatnation of two floats is a double in this case
    output.x = a[2 * col + 0 + row * ld];
    output.y = a[2 * col + 1 + row * ld];
    
    write_imagef(aImage, coord, output);
  }
}

__kernel void copyToImageFloat4(__global float* aBase,
                                int offset,
                                int m,
                                int n,
                                int ld,
                                write_only image2d_t aImage)
{
  __global float* a = &aBase[offset];
  //__global float* a = aBase;

  int2 coord;

  coord.x = get_global_id(0);
  coord.y = get_global_id(1); 
  float4 output = {0.0f, 0.0f, 0.0f, 0.0f};
  size_t row = coord.x * 4;
  size_t col = coord.y;


  // *** 
  // *** If we're in top block...
  // ...
  if(row + 3 <  m && col < n)
  {
    output.x = a[row + 0 + col * ld];
    output.y = a[row + 1 + col * ld];
    output.z = a[row + 2 + col * ld];
    output.w = a[row + 3 + col * ld];
    
    write_imagef(aImage, coord, output);
  }
  // ...
  // ... Else if we're in the bottom block...
  // ***
  else if(row < m && col < n)
  {
    switch(m % 4)
    {
      case 3:
        output.z = a[row + 2 + col * ld];
      case 2:
        output.y = a[row + 1 + col * ld];
      case 1:
        output.x = a[row + 0 + col * ld];
    }

    write_imagef(aImage, coord, output);
  }
}

__kernel void copyToImageTransposeFloat4(__global float* aBase,
                                         int offset,
                                         int m,
                                         int n,
                                         int ld,
                                         write_only image2d_t aImage)
{
  __global float* a = &aBase[offset];

  int2 coord;

  coord.x = get_global_id(0);
  coord.y = get_global_id(1); 
  float4 output = {0.0f, 0.0f, 0.0f, 0.0f};
  size_t row = coord.x * 4;
  size_t col = coord.y;


  //*** 
  //*** If we're in top block...
  //...
  if(row + 3 <  n && col < m)
  {
    output.x = a[col + (row + 0) * ld];
    output.y = a[col + (row + 1) * ld];
    output.z = a[col + (row + 2) * ld];
    output.w = a[col + (row + 3) * ld];
    write_imagef(aImage, coord, output);
  }
  //...
  //... Else if we're in the bottom block...
  //***
  else if(row < n && col < m)
  {
    switch(n % 4)
    {
      case 0:
        output.w = a[col + (row + 3) * ld];
      case 3:
        output.z = a[col + (row + 2) * ld];
      case 2:
        output.y = a[col + (row + 1) * ld];
      case 1:
        output.x = a[col + (row + 0) * ld];
    }

    write_imagef(aImage, coord, output);

  }
}

#ifndef NVIDIA_CORPORATION

__kernel void copyToImageDouble2(__global double* a,
                                 int offset,
                                 int m,
                                 int n,
                                 int ld,
                                 write_only image2d_t aImage)
{
  a = &a[offset];

  int2 coord;

  coord.x = get_global_id(0);
  coord.y = get_global_id(1); 
  double2 output = {0.0, 0.0};
  size_t row = coord.x * 2;
  size_t col = coord.y;


  // *** 
  // *** If we're in top block...
  // ...
  if(row + 1 <  m && col < n)
  {
    output.x = a[row + 0 + col * ld];
    output.y = a[row + 1 + col * ld];
    
    write_imagef(aImage, coord, as_float4(output));
  }
  // ...
  // ... Else if we're in the bottom block...
  // ***
  else if(row < m && col < n)
  {
    output.x = a[row + 0 + col * ld];

    write_imagef(aImage, coord, as_float4(output));
  }
}

__kernel void copyToImageTransposeDouble2(__global double* a,
                                          int offset,
                                          int m,
                                          int n,
                                          int ld,
                                          write_only image2d_t aImage)
{
  a = &a[offset];

  int2 coord;

  coord.x = get_global_id(0);
  coord.y = get_global_id(1); 
  double2 output = {0.0, 0.0};
  size_t row = coord.x * 2;
  size_t col = coord.y;


  //*** 
  //*** If we're in top block...
  //...
  if(row + 1 <  n && col < m)
  {
    output.x = a[col + (row + 0) * ld];
    output.y = a[col + (row + 1) * ld];
    
    write_imagef(aImage, coord, as_float4(output));
  }
  //...
  //... Else if we're in the bottom block...
  //***
  else if(row < n && col < m)
  {
    output.x = a[col + (row + 0) * ld];

    write_imagef(aImage, coord, as_float4(output));
  }
}

#endif
