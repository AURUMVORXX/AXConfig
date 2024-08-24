cmake_minimum_required(VERSION 3.21)

project(sqrat
	VERSION 1.0
	HOMEPAGE_URL "https://scrat.sourceforge.net/"
)

option(SQRAT_GENERATE_IMPORT "This option includes sqimport implementation in sqrat target. By default this option is set to OFF" OFF)
option(SQRAT_GENERATE_INTERPRETER "This option generates squirrel interpreter project. By default this option is set to OFF" OFF)
option(SQRAT_GENERATE_THREAD "This option generates sqrat thread project. By default this option is set to OFF" OFF)
option(SQRAT_GENERATE_TEST "This option generates sqrat unit tests project. By default this option is set to OFF" OFF)

add_subdirectory(include)

if (SQRAT_GENERATE_IMPORT)
	add_subdirectory(sqimport)
endif()

if (SQRAT_GENERATE_INTERPRETER)
	add_subdirectory(sq)
endif()

if (SQRAT_GENERATE_THREAD)
	add_subdirectory(sqratthread)
endif()

if (SQRAT_GENERATE_TEST)
	add_subdirectory(sqrattest)
endif()