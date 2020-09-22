.PHONY: driver
.PHONY: clean

CC = g++
CFLAGS = -Wall -g -std=c++11
OBJ_DIR = obj
OBJECTS = $(OBJ_DIR)/vec3.o $(OBJ_DIR)/driver.o

driver: driver.exe

driver.exe: $(OBJECTS)
	$(CC) $(CFLAGS) -o driver.exe $(OBJECTS)

$(OBJ_DIR)/vec3.o: vec3.hpp vec3.cpp | $(OBJ_DIR)
	$(CC) $(CFLAGS) -c vec3.cpp
	mv vec3.o $(OBJ_DIR)

$(OBJ_DIR)/driver.o: vec3.hpp ray3.hpp driver.cpp | $(OBJ_DIR)
	$(CC) $(CFLAGS) -c driver.cpp
	mv driver.o $(OBJ_DIR)

$(OBJ_DIR):
	mkdir -p $(OBJ_DIR)

clean:
	rm -f driver.exe
	rm -rf obj/*

