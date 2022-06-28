cmake_minimum_required(VERSION 3.10.0)
project(mytest VERSION 0.1.0)

set(CMAKE_CXX_STANDARD 11)

include(CTest)
enable_testing()
add_executable(${PROJECT_NAME}_test template_method_test.cpp)
find_package(GTest REQUIRED)
find_package(Threads REQUIRED)
include_directories(${GTEST_INCLUDE_DIRS})
target_link_libraries(${PROJECT_NAME}_test 
${GTEST_BOTH_LIBRARIES} 
${CMAKE_THREAD_LIBS_INIT}
)

gtest_discover_tests(${PROJECT_NAME}_test)

set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
include(CPack)