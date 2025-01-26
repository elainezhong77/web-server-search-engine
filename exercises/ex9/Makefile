# Copyright 2024 Elaine Zhong
# Elaine Zhong, ezhong4@uw.edu

CXX = g++
CPPFLAGS = -Wall -g -std=c++17
PROGS = ex9

all: $(PROGS)

ex9: ex9.o Vector.o
	$(CXX) $(CPPFLAGS) -o $@ $^

ex9.o: ex9.cc Vector.h
	$(CXX) $(CPPFLAGS) -c $<

Vector.o: Vector.cc Vector.h
	$(CXX) $(CPPFLAGS) -c $<

clean:
	rm -rf *.o *~ *.dSYM $(PROGS)