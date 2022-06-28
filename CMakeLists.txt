cmake_minimum_required(VERSION 3.10.0)
project(design-pattern VERSION 0.1.0)

set(CMAKE_CXX_STANDARD 11)

add_subdirectory(mytest)

include_directories("${PROJECT_SOURCE_DIR}/include")

aux_source_directory(${CMAKE_CURRENT_SOURCE_DIR}/src DIR_SRCS)

add_executable(${PROJECT_NAME} main.cpp ${DIR_SRCS})

include(CTest)
enable_testing()

set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
include(CPack)