.PHONY: all
.PHONY: driver
.PHONY: driver_fast
.PHONY: clean

CC = g++
CFLAGS = -Wall -g -Og -std=c++11
FASTFLAGS = -O3

all: driver driver_fast

driver: driver.exe

driver_fast: driver_fast.exe

driver.exe: src/*.hpp src/driver.cpp
	cd src &&\
	$(CC) $(CFLAGS) -o driver.exe driver.cpp
	mv src/driver.exe .

driver_fast.exe: src/*.hpp src/driver.cpp
	cd src &&\
	$(CC) $(FASTFLAGS) -o driver_fast.exe driver.cpp
	mv src/driver_fast.exe .

clean:
	rm -f driver.exe
	rm -f driver_fast.exe

