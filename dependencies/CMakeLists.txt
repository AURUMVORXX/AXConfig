add_subdirectory(sqapi)
add_subdirectory(union)

target_link_libraries(${PROJECT_NAME}
	PRIVATE
		sqapi
		union
)