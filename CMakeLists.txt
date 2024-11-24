
set( CMAKE_CXX_COMPILER "/bin/x86_64-pc-linux-gnu-c++" )
set( CMAKE_C_COMPILER "/bin/x86_64-pc-linux-gnu-gcc-14.2.1" )

cmake_minimum_required(VERSION 3.0.0)
project(painter VERSION 0.1.0)

set(CMAKE_BUILD_TYPE Debug)
include(CTest)
enable_testing()


find_package(SFML 2.5 COMPONENTS system window graphics REQUIRED)

add_executable(painter FlappyBird.cpp ai.cpp bird.cpp game.cpp neuron.cpp pipe.cpp)


target_link_libraries(painter sfml-system sfml-window sfml-graphics)

set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
include(CPack)
