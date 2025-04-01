
add_library(max31725 INTERFACE)

target_include_directories(max31725 INTERFACE ${CMAKE_CURRENT_LIST_DIR})

target_link_libraries(max31725 INTERFACE hardware_i2c pico_stdlib)

target_compile_options(max31725 INTERFACE -Wall)

file(GLOB SRC_FILES
	"*.c"
)
# compile everything 
target_sources(max31725 INTERFACE
	${SRC_FILES}
)

