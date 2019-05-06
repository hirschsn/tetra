
.SUFFIXES:
.SUFFIXES: .o .cpp

# Configuration
#CXXFLAGS = -Og -g3 -ggdb -Wall -Wextra --std=c++14
CXXFLAGS = -O3 -g3 -ggdb --std=c++14

CXX = g++
RANLIB = ranlib
AR = ar

###

LIBTETRA = libtetra.a
LIBTETRA_SHR = libtetra.so
LIBTETRA_SRC = tetra.cpp
LIBTETRA_OBJ = $(LIBTETRA_SRC:.cpp=.o)
LIBTETRA_HDR = tetra.hpp

PROG_SRC = test.cpp
PROG_OBJ = $(PROG_SRC:.cpp=.o)
PROG = test


all: $(LIBTETRA) $(LIBTETRA_SHR) test

$(LIBTETRA): $(LIBTETRA_OBJ)
	$(AR) rc $@ $?
	$(RANLIB) $@

$(LIBTETRA_SHR): $(LIBTETRA_OBJ)
	$(CXX) -shared -o $@ $<

$(LIBTETRA_OBJ): $(LIBTETRA_HDR)

$(PROG_OBJ): $(LIBTETRA_HDR)

.cpp.o:
	$(CXX) -fPIC $(CXXFLAGS) -o $@ -c $<

$(PROG): $(LIBTETRA_SHR)

.o:
	$(CXX) $(CXXFLAGS) -L. -I. -o $@ $< -ltetra -lCGAL -lgmp


clean:
	rm -rf $(LIBTETRA) $(LIBTETRA_SHR) $(LIBTETRA_OBJ) $(PROG) $(PROG_OBJ)

check: all
	env LD_LIBRARY_PATH=.:$LD_LIBRARY_PATH ./test

.PHONY: all clean check

