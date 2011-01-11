OBJ=1DImage.o

#Directory containing OpenCL header files
INCLUDE=-I../..

LIB=-lOpenCL -L../.. -lclUtil
CPPFLAGS=-g -Wall -O0 -std=c++0x $(INCLUDE)
CXX=g++

1DImage: $(OBJ)
	g++ -o 1DImage $(OBJ) $(LIB)

.cc.o:
	$(CXX) -c $(CPPFLAGS) -o $@ $<

clean:
	-rm *.o 1DImage
