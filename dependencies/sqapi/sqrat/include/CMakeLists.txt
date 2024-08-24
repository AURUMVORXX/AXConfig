file(GLOB_RECURSE SRC
	"include/*.h"
)

add_library(sqrat INTERFACE ${SRC})

target_include_directories(sqrat
	INTERFACE
		"./"
)

target_link_libraries(sqrat
	INTERFACE
		squirrel_headers
)