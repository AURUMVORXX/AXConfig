add_executable(sqratsq "sq.c")

target_link_libraries(sqratsq 
	PRIVATE
		squirrel
		sqstdlib
		sqrat
)