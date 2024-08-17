cmake_minimum_required(VERSION 3.21)
project(LearnSTL)

set(CMAKE_CXX_STANDARD 14)

add_executable(myAllocator myAllocator.cpp)
add_executable(myVector myVector.cpp)
add_executable(mySharedPtr mySharedPtr.cpp)
add_executable(myUniquePtr myUniquePtr.cpp)
add_executable(myList myList.cpp)
add_executable(myHashmap myHashmap.cpp)