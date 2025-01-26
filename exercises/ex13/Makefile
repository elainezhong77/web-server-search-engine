# Elaine Zhong ezhong4@uw.edu

CXX = g++
EXE  = ex13
CPPFLAGS = -Wall -g -std=c++17

$(EXE): ex13.o Cartesian.o Polar.o
	$(CXX) $(CPPFLAGS) -o $(EXE) ex13.cc Cartesian.o Polar.o

ex13.o: Cartesian.h Polar.h ex13.cc
	$(CXX) $(CPPFLAGS) -c ex13.cc

Cartesian.o: Cartesian.h Coordinate.h Cartesian.cc
	$(CXX) $(CPPFLAGS) -c Cartesian.cc

Polar.o: Polar.h Coordinate.h Polar.cc
	$(CXX) $(CPPFLAGS) -c Polar.cc

clean:
	rm -rf $(EXE) *.o *~ *.dSYM