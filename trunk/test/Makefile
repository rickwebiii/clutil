OBJ=test.o

#Directory containing OpenCL header files
INCLUDE=-I..

LIB=-lOpenCL -L.. -lclUtil
CPPFLAGS=-g -Wall -O0 -std=c++0x $(INCLUDE)
CXX=g++

test: $(OBJ)
	g++ -o test $(OBJ) $(LIB)

.cc.o:
	$(CXX) -c $(CPPFLAGS) -o $@ $<

clean:
	-rm *.o test
