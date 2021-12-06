cmake_minimum_required(VERSION 3.4.3)
#===============================================================================
# 1. LOAD LLVM CONFIGURATION
#===============================================================================
find_package(LLVM REQUIRED CONFIG)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")
add_definitions(${LLVM_DEFINITIONS})
include_directories(${LLVM_INCLUDE_DIRS})

add_library(LLVMIR2SourceMapping MODULE IR2SourceMapping.cpp)


