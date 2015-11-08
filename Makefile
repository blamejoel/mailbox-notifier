DIR 	= src
TARGET 	= notify
BIN	= bin/

CC	= g++
WFLAGS	= -Wall -Werror
LFLAGS	=
CFLAGS	= -ansi -pedantic $(WFLAGS)
LIBS	= src/rs-232/rs232.c

HDRS	= src/rs-232/rs232.h
SRCS	= 
OBJS	= $(SRCS:.cpp=.o) $(shell find $(DIR) -name '*.o')

all: clean notify

notify: 
	mkdir -p bin
	$(CC) $(CFLAGS) $(LIBS) $(SRCS) -o $(BIN)$(TARGET)

tx: clean
	mkdir -p bin
	$(CC) $(CFLAGS) $(LIBS) src/tx.cpp -o $(BIN)$(TARGET)

rx: clean
	mkdir -p bin
	$(CC) $(CFLAGS) $(LIBS) src/rx.cpp -o $(BIN)$(TARGET)

debug: clean
	mkdir -p bin
	$(CC) -g $(CFLAGS) $(LIBS) $(SRCS) -o $(BIN)$(TARGET)

clean: 
	rm -rf $(BIN)$(TARGET) bin 
