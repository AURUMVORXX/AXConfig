target_sources(sqrat INTERFACE "sqratimport.cpp")

target_link_libraries(sqrat 
	INTERFACE
		squirrel
		sqstdlib
		$<$<PLATFORM_ID:Linux>:dl>
)