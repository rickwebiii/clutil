__kernel void bzero(__global float* a, unsigned int count)
{
  if(get_global_id(0) < count)
  {
    a[get_global_id(0)] = 0.0f;
  }
}

__kernel void acc(__global float* a, __global float* b, unsigned int count)
{
  if(get_global_id(0) < count)
  {
    a[get_global_id(0)] += b[get_global_id(0)];
  }
}
