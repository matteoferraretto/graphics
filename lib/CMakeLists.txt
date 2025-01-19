cmake_minimum_required(VERSION 3.10)
project(MyLibrary)

set(SDL2_INCLUDE_DIR "C:/Users/matte/C++_libraries/SDL2-devel-2.30.11-VC/SDL2-2.30.11/include")
set(SDL2_LIB_DIR "C:/Users/matte/C++_libraries/SDL2-devel-2.30.11-VC/SDL2-2.30.11/lib/x86")

add_library(MyLibrary STATIC src/Circle.cpp src/Rectangle.cpp)
target_include_directories(MyLibrary 
	PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include 
	${SDL2_INCLUDE_DIR}
)
target_link_directories(MyLibrary PUBLIC ${SDL2_LIB_DIR})
