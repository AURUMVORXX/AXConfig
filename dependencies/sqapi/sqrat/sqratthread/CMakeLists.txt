file(GLOB SRC
	"*.h"
	"*.cpp"
)

add_library(sqratthread SHARED)
target_sources(sqratthread PRIVATE ${SRC})

target_link_libraries(sqratthread
	PRIVATE
		sqrat
)