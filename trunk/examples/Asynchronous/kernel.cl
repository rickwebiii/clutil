#include <../../clUtil.cl>

__kernel void fill(__global float* buffer, int n)
{
  if(get_global_id(0) < n)
  {
    buffer[get_global_id(0)] = get_global_id(0);
  }
}


__kernel void add(__global float* a,
                  __global float* b,
                  __global float* c,
                  int n)
{
  if(get_global_id(0) < n)
  {
    c[get_global_id(0)] = a[get_global_id(0)] + b[get_global_id(0)];
  }
}

