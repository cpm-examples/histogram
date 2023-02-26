cmake_minimum_required(VERSION 3.1.0)
project(histogram VERSION 0.1.2 LANGUAGES C)

set(CMAKE_C_STANDARD 11)
set(CMAKE_C_STANDARD_REQUIRED TRUE)

add_library(histogram
	src/histogram.c
)

add_subdirectory(lib/ppm)

target_include_directories(histogram
	PUBLIC
		${CMAKE_CURRENT_SOURCE_DIR}/include
		${CMAKE_CURRENT_SOURCE_DIR}/lib/
)

target_link_libraries(histogram
	PRIVATE
		ppm
)
