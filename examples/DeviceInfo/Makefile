include ../../Makefile.inc

OBJ=DeviceInfo.o

#Directory containing OpenCL header files
INCLUDE=-I../..

LIB=-lOpenCL -L../.. -lclUtil
CPPFLAGS=-g -Wall -O0 -std=c++0x $(INCLUDE)

Asynchronous: $(OBJ)
	g++ -o DeviceInfo $(OBJ) $(LIB)

.cc.o:
	$(CXX) -c $(CPPFLAGS) -o $@ $<

clean:
	-rm *.o DeviceInfo
