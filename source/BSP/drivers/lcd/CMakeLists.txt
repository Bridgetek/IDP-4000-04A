add_library(lcd INTERFACE)

target_include_directories(lcd INTERFACE ${CMAKE_CURRENT_LIST_DIR})

# Add the standard library to the build
TARGET_LINK_LIBRARIES(lcd INTERFACE pico_stdlib)

target_compile_options(lcd INTERFACE -Wall)

file(GLOB SRC_FILES
	"*.c"
)

# compile everything
target_sources(lcd INTERFACE
	${SRC_FILES}
)
