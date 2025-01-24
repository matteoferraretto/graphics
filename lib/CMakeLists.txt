cmake_minimum_required(VERSION 3.10)
project(MyLibrary)

set(SDL2_INCLUDE_DIR "C:/Users/matte/C++_libraries/SDL2-devel-2.30.11-VC/SDL2-2.30.11/include")
set(SDL2_LIB_DIR "C:/Users/matte/C++_libraries/SDL2-devel-2.30.11-VC/SDL2-2.30.11/lib/x86")
set(SDL2_TTF_INCLUDE_DIR "C:/Users/matte/C++_libraries/SDL2_ttf-devel-2.24.0-VC/SDL2_ttf-2.24.0/include")
set(SDL2_TTF_LIB_DIR "C:/Users/matte/C++_libraries/SDL2_ttf-devel-2.24.0-VC/SDL2_ttf-2.24.0/lib/x86")

add_library(MyLibrary STATIC src/Circle.cpp src/Rectangle.cpp src/Pong.cpp)
target_include_directories(MyLibrary 
	PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include 
	${SDL2_INCLUDE_DIR}
	${SDL2_TTF_INCLUDE_DIR}
)
target_link_directories(MyLibrary PUBLIC ${SDL2_LIB_DIR} PUBLIC ${SDL2_TTF_LIB_DIR})
