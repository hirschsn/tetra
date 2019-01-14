
.SUFFIXES:
.SUFFIXES: .o .cpp

# Configuration
#CXXFLAGS = -Og -g3 -ggdb -Wall -Wextra --std=c++11 -fsanitize=address
CXXFLAGS = -O3

CXX = g++
RANLIB = ranlib
AR = ar

###

LIBTETRA = libtetra.a
LIBTETRA_SRC = tetra.cpp
LIBTETRA_OBJ = $(LIBTETRA_SRC:.cpp=.o)
LIBTETRA_HDR = tetra.hpp

PROG_SRC = test.cpp
PROG_OBJ = $(PROG_SRC:.cpp=.o)
PROG = test


all: $(LIBTETRA) test

$(LIBTETRA): $(LIBTETRA_OBJ)
	$(AR) rc $@ $?
	$(RANLIB) $@

$(LIBTETRA_OBJ): $(LIBTETRA_HDR)

$(PROG_OBJ): $(LIBTETRA_HDR)

.cpp.o:
	$(CXX) $(CXXFLAGS) -o $@ -c $<

$(PROG): $(LIBTETRA)

.o:
	$(CXX) $(CXXFLAGS) -L. -I. -o $@ $< -ltetra -lCGAL -lgmp


clean:
	rm -rf $(LIBTETRA) $(LIBTETRA_OBJ) $(PROG) $(PROG_OBJ)

.PHONY: all clean
