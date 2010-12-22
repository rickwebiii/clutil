
__kernel void fill(__global float* array, unsigned int arrayLength, float val)
{
  if(get_global_id(0) < arrayLength)
  {
    array[get_global_id(0)] = val;
  }
}
