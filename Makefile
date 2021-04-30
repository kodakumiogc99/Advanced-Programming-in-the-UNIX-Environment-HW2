CC=gcc
CFLAG=-g -Wall -O3 -Iinclude
DIR=include/
OBJ=$(patsubst %cpp, %o, $(patsubst %c, %o, $(wildcard *.cpp *.c)))
SUBOBJ=$(patsubst %cpp, %o, $(patsubst %c, %o, $(wildcard $(DIR)*.cpp $(DIR)*.c)))
SRC=$(basename $(notdir $(wildcard *.cpp *.c)))
all: hw2.so sample
	@echo SUCCESFUL

hw2.so:
	$(CC) -o hw2.so -shared -fPIC hw2.c -ldl

sample:
	$(CC) -o sample sample.c

%.o: %.c
	$(CC) $(CFLAG) -c -o $@ $<


clean:
	rm -rf $(OBJ) $(SRC) $(SUBOBJ) *.so
