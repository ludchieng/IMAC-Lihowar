file(GLOB HEADER_FILES *.hpp)
file(GLOB SRC_FILES *.cpp)
file(GLOB_RECURSE SHADER_FILES *.glsl)

# executable filename
set(OUTPUT lihowar)

get_filename_component(FILE main.cpp NAME_WE)
get_filename_component(DIR ${CMAKE_CURRENT_SOURCE_DIR} NAME)
add_executable(${OUTPUT} main.cpp ${HEADER_FILES} ${SHADER_FILES})
target_link_libraries(${OUTPUT} ${ALL_LIBRARIES}) # ALL_LIBRARIES is set in global cmakelists

file(COPY shaders DESTINATION ${EXECUTABLE_OUTPUT_PATH})