cmake_minimum_required(VERSION 3.10)

set(OUTPUT lihowarlib) # executable name

project(${OUTPUT} LANGUAGES C CXX)

file(GLOB_RECURSE source_files "${CMAKE_CURRENT_SOURCE_DIR}/src/*.cpp")
file(GLOB_RECURSE header_files "${CMAKE_CURRENT_SOURCE_DIR}/include/*.hpp")

# Remove template hpp cpp file
list(REMOVE_ITEM source_files "${CMAKE_CURRENT_SOURCE_DIR}/src/_.cpp")
list(REMOVE_ITEM header_files "${CMAKE_CURRENT_SOURCE_DIR}/include/lihowarlib/_.hpp")

# Call documentation (Doxygen)
add_subdirectory(doc)

# Compile as library
add_library(${OUTPUT} ${source_files} ${header_files})

# Compilation flags
target_compile_features(${OUTPUT} PRIVATE cxx_std_11)
target_compile_options(${OUTPUT} PRIVATE -W -Werror -Wall -O2)

# Include directory
target_include_directories(${OUTPUT} PRIVATE "include")

target_link_libraries(${OUTPUT}
        glimac
        ${SDL_LIBRARY}
        ${SDL_MIXER_LIBRARIES}
        ${OPENGL_LIBRARIES}
        ${GLEW_LIBRARY})