cmake_minimum_required(VERSION 3.15...4.2)
project(RaylibCPP)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

include(FetchContent)
FetchContent_Declare(
    raylib
    URL https://github.com/raysan5/raylib/archive/refs/tags/5.0.tar.gz
)

set(BUILD_EXAMPLES OFF CACHE BOOL "Build Examples" FORCE)
set(BUILD_GAMES OFF CACHE BOOL "Build Games" FORCE)
set(OPENGL_VERSION "4.3" CACHE STRING "OpenGL version" FORCE)
 
FetchContent_MakeAvailable(raylib)

add_executable(${PROJECT_NAME} 
src/main.cpp 
src/utility/FVector2.cpp 
src/core/Game.cpp 
src/core/GameObject.cpp 
src/core/InputManager.cpp 
src/pong/PongGame.cpp
src/pong/Ball.cpp
src/pong/Paddle.cpp
src/core/CollisionManager.cpp
src/core/Collider.cpp
src/pong/ScoreUI.cpp
)


target_link_libraries(${PROJECT_NAME} PRIVATE raylib)
target_include_directories(${PROJECT_NAME} PRIVATE include)

if(WIN32)
    target_link_libraries(${PROJECT_NAME} PRIVATE winmm gdi32)
endif()


if (APPLE)
    target_link_libraries(${PROJECT_NAME} PRIVATE
        "-framework OpenGL"
        "-framework Cocoa"
        "-framework IOKit"
        "-framework CoreVideo"
    )
endif()