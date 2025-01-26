# Elaine Zhong, ezhong4@uw.edu

CXX = g++
OBJS = SimpleQueue.o ex17.o
EXE  = ex17
HEADERS = SimpleQueue.h
CPPFLAGS = -Wall -g -std=c++17
LDFLAGS += -pthread

# default target
$(EXE): $(OBJS)
	$(CXX) $(CPPFLAGS) -o $(EXE) $(OBJS) $(LDFLAGS)

# source files
%.o: %.cc $(HEADERS)
	$(CXX) $(CPPFLAGS) -c $<

# phony target - remove generated files and backups
clean:
	rm -rf $(EXE) *.o *~ *.dSYM