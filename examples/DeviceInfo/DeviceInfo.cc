#include <clUtil.h>
#include <iostream>

using namespace clUtil;
using namespace std;

int main(int argc, char** argv)
{
  Device::FetchDevices();
  size_t curDeviceNum = 0;

  for(auto curDevice = Device::Devices.begin();
      curDevice != Device::Devices.end();
      curDevice++)
  {
    cout << "Device " << curDeviceNum++ << endl;
    cout << "\tName:" << (*curDevice).getDeviceInfo().Name << endl;
    cout << "\tVendor:" << (*curDevice).getDeviceInfo().Vendor << endl;
    cout << "\tDriver:" << (*curDevice).getDeviceInfo().DriverVersion << endl;
    cout << "\tProfile:" << (*curDevice).getDeviceInfo().OpenCLProfile << endl;
    cout << "\tVersion:" << (*curDevice).getDeviceInfo().OpenCLVersion << endl;
    cout << "\tCVersion:" << (*curDevice).getDeviceInfo().OpenCLCVersion << endl;
  }

  return 0;
}
