#pragma once
#ifdef __APPLE__
#include <OpenCL/cl.h>
#include <mach/mach_time.h>
#include <mach/mach.h>
#include <CoreServices/CoreServices.h>
#else
#include <CL/cl.h>
#include <sys/time.h>
#endif
#include <stdio.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>
#include <signal.h>
#include <new>
#include <map>
#include <string>
#include <math.h>
#include <vector>
#include <sstream>
#include <iostream>
#include <memory>
#include <fstream>
#include <exception>
