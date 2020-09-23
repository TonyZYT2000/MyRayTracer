.PHONY: driver
.PHONY: clean

CC = g++
CFLAGS = -Wall -g -std=c++11
HEADERS = vec3.hpp ray.hpp hitable.hpp sphere.hpp hitable_list.hpp

driver: driver.exe

driver.exe: $(HEADERS) driver.cpp
	$(CC) $(CFLAGS) -o driver.exe driver.cpp $(HEADERS)

clean:
	rm -f driver.exe

