#include <clUtil.h>
#include <iostream>

using namespace clUtil;
using namespace std;

int main(int argc, char** argv)
{
  const char* filename[] = {"kernel.cl"};

  Device::InitializeDevices(filename, 1);

  ParallelFor(0, 1, 10000, [=](size_t startIdx, size_t endIdx)
  { 
    cout << "device: " << Device::GetCurrentDeviceNum()
         << " start: " << startIdx
         << " end: " << endIdx << endl;
  }, 4);


  return 0;
}
