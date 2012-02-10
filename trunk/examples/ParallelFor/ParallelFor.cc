#include <clUtil.h>

using namespace clUtil;

int main(int argc, char** argv)
{

  Device::FetchDevices();

  ParallelFor(0, 1, 1000, [=](size_t startIdx, size_t endIdx)
  {

  });


  return 0;
}
