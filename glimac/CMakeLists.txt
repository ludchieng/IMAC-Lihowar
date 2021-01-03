cmake_minimum_required(VERSION 3.10)

set(OUTPUT glimac) # executable name

include_directories(include)
file(GLOB_RECURSE SRC_FILES *.cpp *.hpp)
add_library(${OUTPUT} ${SRC_FILES})
target_compile_features(${OUTPUT} PRIVATE cxx_std_11)
target_compile_options(${OUTPUT} PRIVATE -w -O2)