# Copyright 2024 Elaine Zhong
# Elaine Zhong, ezhong4@uw.edu

CXX = g++
OBJS = Vector.o ex10.o
EXE  = ex10
HEADERS = Vector.h
CPPFLAGS = -Wall -g -std=c++17

# default target
$(EXE): $(OBJS)
	$(CXX) $(CPPFLAGS) -o $(EXE) $(OBJS)

# source files
%.o: %.cc $(HEADERS)
	$(CXX) $(CPPFLAGS) -c $<

# phony target - remove generated files and backups
clean:
	rm -rf $(EXE) *.o *~ *.dSYM
