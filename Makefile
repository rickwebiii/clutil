include Makefile.inc

OBJ=clUtil.o clUtilImage.o clUtilKernel.o clUtilInit.o
EXAMPLES=$(wildcard examples/*) #Every subdir in examples

#Directory containing OpenCL header files

LIB=
CPPFLAGS=-std=c++0x -I$(OpenCLInclude) $(USERFLAGS)

all:
	make examples

libclUtil.a: $(OBJ)
	$(AR) rcs libclUtil.a $(OBJ) $(LIB)

examples: libclUtil.a
	for dir in $(EXAMPLES); do make -C $$dir; done

.cc.o:
	$(CXX) -c $(CPPFLAGS) -o $@ $<

clean:
	-rm *.o libclUtil.a
	for dir in $(EXAMPLES); do make -C $$dir clean; done
