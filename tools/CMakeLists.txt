cmake_minimum_required(VERSION 3.10)

set(OUTPUT normalShifter) # executable name

file(MAKE_DIRECTORY "${EXECUTABLE_OUTPUT_PATH}/tools")
set(EXECUTABLE_OUTPUT_PATH ${PROJECT_BINARY_DIR}/bin/tools)

get_filename_component(FILE normalShifter.cpp NAME_WE)
get_filename_component(DIR ${CMAKE_CURRENT_SOURCE_DIR} NAME)
add_executable(${OUTPUT} normalShifter.cpp stb_image_write.h)
target_compile_features(${OUTPUT} PRIVATE cxx_std_11)
target_compile_options(${OUTPUT} PRIVATE -w -O2)
target_link_libraries(${OUTPUT} ${ALL_LIBRARIES}) # ALL_LIBRARIES is set in global cmakelists
