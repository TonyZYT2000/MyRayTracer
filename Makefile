.PHONY: driver
.PHONY: clean

CC = g++
CFLAGS = -Wall -g -std=c++11
OBJ_DIR = obj
OBJECTS = $(OBJ_DIR)/driver.o

driver: $(OBJ_DIR)/driver.o
	$(CC) $(CFLAGS) -o driver.exe $(OBJ_DIR)/driver.o

$(OBJ_DIR)/driver.o: driver.cpp | $(OBJ_DIR)
	$(CC) $(CFLAGS) -c driver.cpp
	mv driver.o $(OBJ_DIR)

$(OBJ_DIR):
	mkdir -p $(OBJ_DIR)

clean:
	rm -f driver.exe
	rm -rf obj/*

