CPP = g++
CPPFLAGS= -std=c++11
SRC_DIR = src
SRC = FixedPoint.cpp PeriodicRepresentation.cpp main.cpp
EXEC = exec_mult

ifdef DEBUG
	CPPFLAGS += -D DEBUG
endif



exec: build
	./$(EXEC)


build:
	cd $(SRC_DIR) && $(CPP) $(CPPFLAGS)  $(SRC) -o ../$(EXEC) && cd ..