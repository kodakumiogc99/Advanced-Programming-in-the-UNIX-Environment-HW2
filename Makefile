DIR=include/
TOOL=tool/
CC=gcc
CFLAG=-g -Wall -O3
OBJ=$(patsubst %cpp, %o, $(patsubst %c, %o, $(wildcard *.cpp *.c)))
SUBOBJ=$(patsubst %cpp, %o, $(patsubst %c, %o, $(wildcard $(DIR)*.cpp $(DIR)*.c)))
TOOLOBJ=$(addprefix $(TOOL), $(basename $(notdir $(wildcard $(TOOL)*.cpp $(TOOL)*.c))))
SRC=$(basename $(notdir $(wildcard *.cpp *.c)))
all: logger logger.so $(TOOLOBJ)
	@echo SUCCESFUL

logger.so: hw2so.c include/format.c
	$(CC) -o $@ -shared -fPIC -I$(DIR) hw2so.c include/format.c -ldl

logger: hw2.c
	$(CC) $(CFLAG) -o $@ $^

%: %.c
	$(CC) -o $@ $<

%.o: %.c
	$(CC) -c -o $@ $<


clean:
	rm -rf $(OBJ) $(SRC) $(SUBOBJ) $(TOOLOBJ) *.so
