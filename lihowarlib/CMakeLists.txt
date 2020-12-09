cmake_minimum_required(VERSION 3.10)

project(lihowarlib LANGUAGES C CXX)

file(GLOB_RECURSE source_files src/*.cpp)
file(GLOB_RECURSE header_files include/*.hpp)

# Call documentation (Doxygen)
add_subdirectory(doc)

# Compile as library
add_library(lihowarlib ${source_files} ${header_files})

# Compilation flags
target_compile_features(lihowarlib PRIVATE cxx_std_11)
target_compile_options(lihowarlib PRIVATE -Wall -O2)

# Include directory
target_include_directories(lihowarlib PRIVATE "include")

target_link_libraries(lihowarlib
        ${SDL_LIBRARY}
        ${SDL_MIXER_LIBRARIES}
        ${OPENGL_LIBRARIES}
        ${GLEW_LIBRARY})