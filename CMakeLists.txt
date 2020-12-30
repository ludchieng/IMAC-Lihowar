cmake_minimum_required(VERSION 3.10)

project(lihowar)

add_definitions(-std=c++11 -Wall -O2)

set(CMAKE_MODULE_PATH ${CMAKE_SOURCE_DIR}/cmake)

find_package(SDL2 REQUIRED)
set(OpenGL_GL_PREFERENCE LEGACY) # Policy CMP0072
find_package(OpenGL REQUIRED)
find_package(GLEW REQUIRED)
find_package(SDL_mixer REQUIRED)

include_directories(
        ${SDL2_INCLUDE_DIR}
        ${SDL_MIXER_INCLUDE_DIRS}
        ${OPENGL_INCLUDE_DIR}
        ${GLEW_INCLUDE_DIR}
        glimac/include
        third-party/include
        lihowarlib/include)

# Set variable containing lib names
set(ALL_LIBRARIES
        ${SDL2_LIBRARIES}
        ${SDL_MIXER_LIBRARIES}
        ${OPENGL_LIBRARIES}
        ${GLEW_LIBRARY}
        glimac
        lihowarlib)

# Change executable files directory
set(EXECUTABLE_OUTPUT_PATH ${PROJECT_BINARY_DIR}/bin)

# Add glimac
message(STATUS "Adding glimac..." )
add_subdirectory(glimac)

# Add lihowarlib
message(STATUS "Adding lihowarlib...")
add_subdirectory(lihowarlib)

# Compile global main
message(STATUS "Adding main...")
file(GLOB main_files "src")
add_subdirectory(${main_files})

# Add tools
message(STATUS "Adding tools...")
add_subdirectory(tools)

# Copy directories into bin
file(COPY assets DESTINATION ${EXECUTABLE_OUTPUT_PATH})
file(COPY config DESTINATION ${EXECUTABLE_OUTPUT_PATH})
file(COPY scenes DESTINATION ${EXECUTABLE_OUTPUT_PATH})

#######

# (optional) debug or release
#set(CMAKE_BUILD_TYPE Debug)
set(CMAKE_BUILD_TYPE Release)

