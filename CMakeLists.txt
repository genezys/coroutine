project(coroutine)

cmake_minimum_required(VERSION 2.8)

add_definitions(
	-D_XOPEN_SOURCE
)

add_executable(${PROJECT_NAME} 
	Fiber.h
	Generator.h
	Fiber.Posix.cpp
	Fiber.Win32.cpp
	Test.cpp
)



add_executable(BasicPosix
	BasicPosix.cpp
)
