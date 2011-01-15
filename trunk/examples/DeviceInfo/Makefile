include ../../Makefile.inc

OBJ=DeviceInfo.o

#Directory containing OpenCL header files
INCLUDE=-I../.. -I$(OpenCLInclude)

LIB=-lOpenCL -L../.. -lclUtil
CPPFLAGS=-std=c++0x $(INCLUDE) $(USERFLAGS)

Asynchronous: $(OBJ)
	g++ -o DeviceInfo $(OBJ) $(LIB)

.cc.o:
	$(CXX) -c $(CPPFLAGS) -o $@ $<

clean:
	-rm *.o DeviceInfo
