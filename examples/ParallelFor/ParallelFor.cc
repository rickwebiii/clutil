#include <clUtil.h>
#include <iostream>
#include <memory>

using namespace clUtil;
using namespace std;

const size_t kBigArraySize = 12345;

int main(int argc, char** argv)
{
  const char* filename[] = {"kernel.cl"};

  unique_ptr<float[]> a(new float[kBigArraySize]);
  unique_ptr<float[]> b(new float[kBigArraySize]);
  unique_ptr<float[]> c(new float[kBigArraySize]);
  
  for(size_t i = 0; i < kBigArraySize; i++)
  {
    a[i] = (float)i;
    b[i] = (float)i;
  }

  Device::InitializeDevices(filename, 1);

  ParallelFor(0, 1, kBigArraySize, [&](size_t startIdx, size_t endIdx)
  { 
#if 1
    unsigned int indexCount = endIdx - startIdx + 1;

    Buffer aDevice(sizeof(a[0]) * indexCount);
    Buffer bDevice(sizeof(b[0]) * indexCount);
    Buffer cDevice(sizeof(c[0]) * indexCount);

    aDevice.put(&a[startIdx]);
    bDevice.put(&b[startIdx]);

    clUtilEnqueueKernel("vectorAdd", 
                        clUtilGrid(indexCount, 64),
                        aDevice,
                        bDevice,
                        cDevice,
                        indexCount);

    cDevice.get(&c[startIdx]);
#endif
  });

  Device::DumpProfilingData();

  for(unsigned int i = 0; i < kBigArraySize; i++)
  {
    if(c[i] != 2.0f * (float)i)
    {
      cout << "Element " << i << " is incorrect. Should be " 
           << 2.0f * (float)i << ". Is " << c[i];

      exit(1);
    }
  }

  cout << "Success!" << endl;

  return 0;
}
