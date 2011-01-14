include ../../Makefile.inc

OBJ=Asynchronous.o

#Directory containing OpenCL header files
INCLUDE=-I../..

LIB=-lOpenCL -L../.. -lclUtil
CPPFLAGS=-std=c++0x $(INCLUDE) $(USERFLAGS)

Asynchronous: $(OBJ)
	g++ -o Asynchronous $(OBJ) $(LIB)

.cc.o:
	$(CXX) -c $(CPPFLAGS) -o $@ $<

clean:
	-rm *.o Asynchronous
