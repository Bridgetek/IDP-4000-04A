
add_library(rotary INTERFACE)

target_include_directories(rotary INTERFACE ${CMAKE_CURRENT_SOURCE_DIR})

target_link_libraries(rotary INTERFACE hardware_i2c pico_stdlib)

target_compile_options(rotary INTERFACE -Wall)

file(GLOB SRC_FILES
	"*.c"
)

# compile everything
target_sources(rotary INTERFACE
	${SRC_FILES}
)