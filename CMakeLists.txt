cmake_minimum_required(VERSION 4.2.3)
project(tcxx-23)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_FLAGS_INIT "-Wall -Wno-overflow -pendantic -std=c++23")

set(CMAKE_INCLUDE_PATH ${CMAKE_SOURCE_DIR}/include)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

list(APPEND CMAKE_MODULE_PATH "${CMAKE_CURRENT_SOURCE_DIR}/cmake")

include(Dependencies)

SET(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/bin)
SET(TRC ${CMAKE_CURRENT_SOURCE_DIR}/rc)

file(GLOB SOURCES "include/*.h")

enable_testing()
#tests
add_subdirectory(test)
#tool for coverage
include(Coverage)
#tool for documentation
include(Doxygen)
