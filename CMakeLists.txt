cmake_minimum_required(VERSION 3.24)

project(fm)

set (CMAKE_CXX_STANDARD 17)

add_executable(fm
	GainContainer.cpp
	main.cpp
	Parser.cpp
	Partition.cpp
	Graph.cpp
	FM.cpp
)
