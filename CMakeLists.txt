cmake_minimum_required(VERSION 3.10)
project(untitled)

set(CMAKE_CXX_STANDARD 20)

# user files
file(GLOB_RECURSE sources src/*.cpp src/*.h src/buffers/*)

# stb_image
file(GLOB_RECURSE outsideSources vendor/stb_image/*.cpp vendor/stb_image/*.h)

# adding files from above
add_executable(untitled ${sources} ${outsideSources}
        src/Camera.cpp
        src/Camera.h
        src/models/Cube.h
        src/util/ByteHelper.h
        src/debug/PerformanceTest.h
        src/models/Quadrilateral.cpp
        src/models/Quadrilateral.h
        src/map/ChunkManager.cpp
        src/map/ChunkManager.h
        src/buffers/Texture.cpp
        src/buffers/Texture.h
        src/models/Triangle.cpp
        src/models/Triangle.h
        vendor/uuid/uuid_v4.h
        src/buffers/DynamicIndexBuffer.cpp
        src/buffers/DynamicIndexBuffer.cpp
        src/util/ModelIdManager.h
        src/buffers/DynamicVertexBuffer.h
        src/buffers/DynamicBuffer.h
        src/util/ModelIdManager.cpp
        src/util/OBJLoader.cpp
        src/util/OBJLoader.h
        src/models/OBJModel.h
        src/util/FileHelper.h
        src/buffers/DynamicSkyBoxBuffer.h
        src/map/MarchingCubesLookupTable.h
        src/util/ThreadPool.cpp
        src/util/ThreadPool.h)

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

target_link_libraries(untitled GLEW::GLEW)
target_link_libraries(untitled glfw)
target_link_libraries(untitled OpenGL::GL)