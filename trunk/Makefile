OBJ=clUtil.o clUtilImage.o clUtilKernel.o

#Directory containing OpenCL header files
OpenCLInclude=/usr/include

LIB=
CPPFLAGS=-g -O0 -std=c++0x -I$(OpenCLInclude)
CXX=g++

libclUtil.a: $(OBJ)
	$(AR) rcs libclUtil.a $(OBJ) $(LIB)

.cc.o:
	$(CXX) -c $(CPPFLAGS) -o $@ $<

clean:
	-rm *.o libclUtil.a
