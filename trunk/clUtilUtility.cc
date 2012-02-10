#include "clUtilUtility.h"

using namespace std;

namespace clUtil
{
  namespace Utility
  {
    std::vector<std::string> split(std::string str, char delimiter)
    {
      std::istringstream strStream(str);
      std::vector<std::string> fields;

      while(strStream.good() == true)
      {
        std::string currentField;

        getline(strStream, currentField, delimiter);

        fields.push_back(currentField);
      }

      return fields;
    }

    cl_int fetchDeviceInfo(cl_device_id deviceID,
                           cl_device_info paramName,
                           std::string& param)
    {
      size_t propertySize;
      cl_int err;

      err = clGetDeviceInfo(deviceID,
                            paramName,
                            0,
                            NULL,
                            &propertySize);
      clUtilCheckError(err);

      std::unique_ptr<char[]> propertyString(new char[propertySize]);

      err = clGetDeviceInfo(deviceID,
                            paramName,
                            propertySize,
                            propertyString.get(),
                            NULL);
      clUtilCheckError(err);

      param = std::string(propertyString.get(), 
                          strnlen(propertyString.get(), propertySize));

      return CL_SUCCESS;
    }

    cl_int fetchPlatformInfo(cl_platform_id platformID,
                             cl_platform_info paramName,
                             std::string& param)
    {
      cl_int err;
      size_t paramSize;

      err = clGetPlatformInfo(platformID, paramName, 0, NULL, &paramSize);
      clUtilCheckError(err);

      std::unique_ptr<char[]> paramString(new char[paramSize]);

      err = clGetPlatformInfo(platformID,
                              paramName,
                              paramSize,
                              paramString.get(),
                              NULL);
      clUtilCheckError(err);

      param = std::string(paramString.get(), paramSize);

      return CL_SUCCESS;
    }
  }
}
