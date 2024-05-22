cmake_minimum_required(VERSION 3.28)
project(untitled)

set(CMAKE_CXX_STANDARD 20)

# user files
file(GLOB_RECURSE sources src/*.cpp src/*.h src/buffers/*)

# stb_image
file(GLOB_RECURSE outsideSources vendor/stb_image/*.cpp vendor/stb_image/*.h)

# adding files from above
add_executable(untitled ${sources} ${outsideSources})


# glfw
find_package(glfw3 REQUIRED)
include_directories(${GLFW_INCLUDE_DIRS})
link_libraries(${GLFW_LIBRARY_DIRS})

# opengl
find_package(OpenGL REQUIRED)
include_directories(${OPENGL_INCLUDE_DIRS})

# glew
find_package(GLEW REQUIRED)
include_directories(${GLEW_INCLUDE_DIRS})

find_library(COCOA_LIBRARY Cocoa)
find_library(OpenGL_LIBRARY OpenGL)
find_library(IOKIT_LIBRARY IOKit)
find_library(COREVIDEO_LIBRARY CoreVideo)
SET(EXTRA_LIBS ${COCOA_LIBRARY} ${OpenGL_LIBRARY} ${IOKIT_LIBRARY} ${COREVIDEO_LIBRARY})

target_link_libraries(untitled GLEW::glew)
target_link_libraries(untitled glfw)
#target_link_libraries(
#        glfw
#        ${OPENGL_LIBRARIES}
#        ${GLEW_LIBRARIES}
#        ${EXTRA_LIBS}
#)
