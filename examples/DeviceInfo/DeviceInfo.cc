#include <clUtil.h>
#include <iostream>

using namespace clUtil;
using namespace std;

int main(int argc, char** argv)
{
  Device::FetchDevices();
  size_t curDeviceNum = 0;

  const vector<Device>& devices = Device::GetDevices();
 
  for(size_t currentDevice = 0; 
      currentDevice < Device::GetDevices().size();
      currentDevice++)
  {

    cout << "Device " << curDeviceNum++ << endl;
    cout << "\tName:" << devices[currentDevice].getDeviceInfo().Name << endl;
    cout << "\tVendor:" << devices[currentDevice].getDeviceInfo().Vendor << endl;
    cout << "\tDriver:" << devices[currentDevice].getDeviceInfo().DriverVersion << endl;
    cout << "\tProfile:" << devices[currentDevice].getDeviceInfo().OpenCLProfile << endl;
    cout << "\tVersion:" << devices[currentDevice].getDeviceInfo().OpenCLVersion << endl;
    cout << "\tCVersion:" << devices[currentDevice].getDeviceInfo().OpenCLCVersion << endl;
  }

  return 0;
}
