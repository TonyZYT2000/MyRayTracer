.PHONY: driver
.PHONY: clean

CC = g++
CFLAGS = -Wall -g -std=c++11
HEADERS = vec3.hpp ray.hpp camera.hpp color.hpp hittable.hpp hittable_list.hpp\
		rtweekend.hpp sphere.hpp

driver: driver.exe

driver.exe: $(HEADERS) driver.cpp
	$(CC) $(CFLAGS) -o driver.exe driver.cpp

clean:
	rm -f driver.exe

