cmake_minimum_required(VERSION 3.0.0)
project(design-pattern VERSION 0.1.0)

include(CTest)
enable_testing()

set(CMAKE_CXX_STANDARD 11)
set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
include(CPack)

include_directories(
        "${PROJECT_SOURCE_DIR}/include"
        "${PROJECT_SOURCE_DIR}/src/headers"
)

file(GLOB_RECURSE _headers src/headers/*.h)
file(GLOB_RECURSE _sources src/crawler/*.cpp)

add_executable(design-pattern main.cpp ${_headers} ${_sources})