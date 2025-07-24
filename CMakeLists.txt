cmake_minimum_required(VERSION 3.10)
project(cpp_rest_api)

set(CMAKE_CXX_STANDARD 17)

include_directories(crow/include)
include_directories(/usr/include)
include_directories(include)

add_executable(cpp_rest_api 
	       main.cpp
	       src/product_manager.cpp)
