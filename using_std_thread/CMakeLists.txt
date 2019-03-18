PROJECT(using_std_thread)

CMAKE_MINIMUM_REQUIRED(VERSION 3.5)

ADD_DEFINITIONS(-std=c++17)

ADD_EXECUTABLE(using_std_thread src/using_std_thread.cpp)
TARGET_LINK_LIBRARIES(using_std_thread pthread)
