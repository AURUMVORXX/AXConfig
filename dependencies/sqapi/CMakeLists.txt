cmake_minimum_required(VERSION 3.21)

project(sqapi)

file(GLOB SRC
	"squirrel/include/*.h"
	"sqrat/include/*.h"

	"sqapi.h"
	"sqapi.cpp"
)

add_library(${PROJECT_NAME} INTERFACE)
target_sources(${PROJECT_NAME} INTERFACE ${SRC})

target_include_directories(${PROJECT_NAME}
	INTERFACE
		"squirrel/include/"
		"sqrat/include/"
		"./"
)