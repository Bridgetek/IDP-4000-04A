
add_library(bsp_drivers INTERFACE)

# IDP-4000-04A needs these base device drivers
add_subdirectory(eve_hal)
add_subdirectory(i2c_utils)
add_subdirectory(lcd)
add_subdirectory(max31725)
add_subdirectory(rotary)
add_subdirectory(sdcard)


target_link_libraries(bsp_drivers INTERFACE
    eve_hal
    i2c_utils
    lcd
    max31725
    rotary
    sdcard
)
