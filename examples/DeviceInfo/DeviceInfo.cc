#include <clUtil.h>

int main(int argc, char** argv)
{
  clUtilInitDevices();

  for(auto curDevice = clUtil::gDevices.begin();
      curDevice != clUtil::gDevices.end();
      curDevice++)
  {

  }

  return 0;
}
