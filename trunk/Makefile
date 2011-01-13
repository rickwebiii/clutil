include Makefile.inc

OBJ=clUtil.o clUtilImage.o clUtilKernel.o clUtilInit.o

#Directory containing OpenCL header files
OpenCLInclude=/usr/include

LIB=
CPPFLAGS=-g -Wall -O0 -std=c++0x -I$(OpenCLInclude)

libclUtil.a: $(OBJ)
	$(AR) rcs libclUtil.a $(OBJ) $(LIB)

.cc.o:
	$(CXX) -c $(CPPFLAGS) -o $@ $<

clean:
	-rm *.o libclUtil.a
