CC = gcc
CFLAGS = -Wall -pedantic -g -lSDL2 -lpthread
TARGET = target
SRC_DIR = src/source_files
HDR_DIR = src/header_files

all: client_utils.o input_utils.o
	$(CC) $(CFLAGS) $(SRC_DIR)/main.c $(TARGET)/{client_utils.o,input_utils.o} -o $(TARGET)/GameOfLife

client_utils.o:
	$(CC) $(CFLAGS) -c $(SRC_DIR)/client_utils.c -o $(TARGET)/client_utils.o

input_utils.o:
	$(CC) $(CFLAGS) -c $(SRC_DIR)/input_utils.c -o $(TARGET)/input_utils.o

clean:
	rm -rf target/*