file(GLOB HEADERS ./*.hpp)
add_executable(MyRayTracer driver.cpp ${HEADERS})
