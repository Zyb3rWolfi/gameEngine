cmake_minimum_required(VERSION 3.27)
project(untitled)

set(CMAKE_CXX_STANDARD 14)

set(SDL2_INCLUDE_DIR C://sdl/include)
set(SDL2_LIB_DIR C://sdl/lib/x64)

set(GLEW_INCLUDE_DIR C://glew/include/GL)
set(GLEW_LIB_DIR C://glew/lib/Release/x64)

include_directories(${SDL2_INCLUDE_DIR} ${GLEW_INCLUDE_DIR})
link_directories(${SDL2_LIB_DIR} ${GLEW_LIB_DIR})

find_package(OpenGL REQUIRED)
include_directories(${OPENGL_INCLUDE_DIRS})

add_executable(untitled
        main.cpp
        mainGame.h
        mainGame.cpp
        sprites.cpp
        sprites.h
        GLSLProgram.cpp
        GLSLProgram.h
        vertex.h

)
target_link_libraries(${PROJECT_NAME} SDL2main SDL2 opengl32 glew32)
