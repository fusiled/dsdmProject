CPP = g++
SRC_DIR = src
SRC = PeriodicRepresentation.cpp main.cpp
EXEC = exec_mult





build:
	cd $(SRC_DIR) && $(CPP)  $(SRC) -o ../$(EXEC) && cd ..