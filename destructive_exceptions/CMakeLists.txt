PROJECT(destructive_exceptions)

CMAKE_MINIMUM_REQUIRED(VERSION 3.5)

ADD_DEFINITIONS(-std=c++17)

ADD_EXECUTABLE(simple_nested_exceptions src/simple_nested_exceptions.cpp)
ADD_EXECUTABLE(simple_throw_catch src/simple_throw_catch.cpp)
ADD_EXECUTABLE(use_uncaught_exception src/use_uncaught_exception.cpp)
TARGET_COMPILE_OPTIONS(use_uncaught_exception PRIVATE -Wno-deprecated-declarations)
ADD_EXECUTABLE(problem_uncaught_exception src/problem_uncaught_exception.cpp)
TARGET_COMPILE_OPTIONS(problem_uncaught_exception PRIVATE -Wno-deprecated-declarations)
ADD_EXECUTABLE(use_uncaught_exceptions src/use_uncaught_exceptions.cpp)
ADD_EXECUTABLE(exception_queue src/exception_queue.cpp)
