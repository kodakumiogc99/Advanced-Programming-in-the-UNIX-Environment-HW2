CC=gcc
CFLAG=-g -Wall -O3 -Iinclude
DIR=include/
OBJ=$(patsubst %cpp, %o, $(patsubst %c, %o, $(wildcard *.cpp *.c)))
SUBOBJ=$(patsubst %cpp, %o, $(patsubst %c, %o, $(wildcard $(DIR)*.cpp $(DIR)*.c)))
SRC=$(basename $(notdir $(wildcard *.cpp *.c)))
all: $(SRC)
	@echo SUCCESFUL

$(SRC): $(SUBOBJ) $(OBJ)
	$(CC) $(CFLAG) -o $@ $^

%.o: %.c
	$(CC) $(CFLAG) -c -o $@ $<


clean:
	rm -rf $(OBJ) $(SRC) $(SUBOBJ)
