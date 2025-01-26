# Elaine Zhong, ezhong4@uw.edu

CXX = g++
CPPFLAGS = -Wall -g -std=c++17

ex15: netcopy.o SocketUtil.o
	$(CXX) $(CPPFLAGS) -o ex15 netcopy.o SocketUtil.o

netcopy.o: netcopy.cc
	$(CXX) $(CPPFLAGS) -c netcopy.cc

SocketUtil.o: SocketUtil.cc
	$(CXX) $(CPPFLAGS) -c SocketUtil.cc

clean:
	/bin/rm -f -r *~ *.o ex15 ex15.dSYM
	rm -rf .o~ *.dSYM ex15 output.bytes