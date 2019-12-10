#cmake version
cmake_minimum_required(VERSION 3.1)

if(NOT TARGET ${COORDINATE_LIBRARIES})
  #project name
  project(GPS_conversor
  VERSION 1.0.0
  DESCRIPTION "GPS coordinate conversor"
  LANGUAGES CXX C
)

  set(COORDINATE_INCLUDE_DIRS
    ${PROJECT_SOURCE_DIR}
    ${PROJECT_SOURCE_DIR}/include

    CACHE INTERNAL ""
  )
  set(COORDINATE_LIBRARIES ${PROJECT_NAME} CACHE INTERNAL "")

  #add every file to the executable
  add_library(${PROJECT_NAME})

  target_sources(${PROJECT_NAME}
    PRIVATE
      include/ramrod/gps/coordinate_conversor.h
      include/ramrod/gps/types.h
      src/ramrod/gps/coordinate_conversor.cpp
  )

  target_include_directories(${PROJECT_NAME}
    PRIVATE
      include
  )

  set_target_properties(${PROJECT_NAME}
    PROPERTIES
      CXX_STANDARD 11
      CXX_STANDARD_REQUIRED yes
      CXX_EXTENSIONS no
  )
endif(NOT TARGET ${COORDINATE_LIBRARIES})
