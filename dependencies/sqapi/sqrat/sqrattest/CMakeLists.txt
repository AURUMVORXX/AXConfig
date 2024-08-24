# CTest
enable_testing()
include(GoogleTest)

# GoogleTest
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
add_subdirectory(googletest)

file(GLOB SRC
	"*.h"
	"*.cpp"
)

add_executable(sqrattest ${SRC})

target_link_libraries(sqrattest
	PRIVATE
		squirrel
		sqstdlib
		sqrat
		GTest::gtest_main
)

gtest_discover_tests(sqrattest)

add_custom_command(TARGET sqrattest
	POST_BUILD
		COMMAND ${CMAKE_COMMAND} -E copy_directory
			"${CMAKE_CURRENT_SOURCE_DIR}/scripts/"
			"${CMAKE_CURRENT_BINARY_DIR}/scripts/"
)