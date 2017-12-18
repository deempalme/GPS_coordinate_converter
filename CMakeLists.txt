#cmake version
cmake_minimum_required(VERSION 3.1)

#project name
project(GPS_conversor)
set(COORDINATE_NAME GPS_conversor)

# As moc files are generated in the binary dir, tell CMake
# to always look for includes there:
set(CMAKE_INCLUDE_CURRENT_DIR ON)
# compatibility with c++14
set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

set(COORDINATE_DIRS
  ${PROJECT_SOURCE_DIR}
  ${PROJECT_SOURCE_DIR}/include

  CACHE INTERNAL ""
)
set(COORDINATE_LIB ${COORDINATE_NAME} CACHE INTERNAL "")

#add every file to the executable
add_library(${COORDINATE_NAME}
  include/coordinate_conversor.h
  src/coordinate_conversor.cpp
)
