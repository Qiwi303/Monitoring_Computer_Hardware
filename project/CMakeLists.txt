cmake_minimum_required(VERSION 3.10)

project(test LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STDANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

add_executable(cpu 
	main.cpp
	parser.cpp
)

target_compile_options(cpu PRIVATE -Wall -Wextra -pedantic )
