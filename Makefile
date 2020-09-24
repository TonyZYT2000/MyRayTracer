.PHONY: all
.PHONY: driver
.PHONY: driver_fast
.PHONY: clean

CC = g++
CFLAGS = -Wall -g -Og -std=c++11
FASTFLAGS = -O3
HEADERS = vec3.hpp ray.hpp camera.hpp color.hpp hittable.hpp hittable_list.hpp\
		material.hpp rtweekend.hpp sphere.hpp

all: driver driver_fast

driver: driver.exe

driver_fast: driver_fast.exe

driver.exe: $(HEADERS) driver.cpp
	$(CC) $(CFLAGS) -o driver.exe driver.cpp

driver_fast.exe: $(HEADERS) driver.cpp
	$(CC) $(FASTFLAGS) -o driver_fast.exe driver.cpp

clean:
	rm -f driver.exe
	rm -f driver_fast.exe

