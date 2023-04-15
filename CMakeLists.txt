cmake_minimum_required(VERSION 3.24)

project(fm)

add_executable(fm
	GainContainer.cpp
	main.cpp
	Parser.cpp
	Partition.cpp
	Reader.cpp
	FM.cpp
)
