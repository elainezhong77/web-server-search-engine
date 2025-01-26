# Elaine Zhong, ezhong4@uw.edu

ex16: ex16.o Network.o
	g++ -Wall -g -std=c++11 -o ex16 ex16.o Network.o

Network.o: Network.cc Network.h
	g++ -Wall -g -std=c++11 -c Network.cc

ex16.o: ex16.cc Network.h
	g++ -Wall -std=c++11 -g -c ex16.cc

clean:
	rm -rf ex16 *.o *~ *.dSYM

