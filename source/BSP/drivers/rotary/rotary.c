#include <stdio.h>
#include <pico/stdlib.h>
#include "bsp_debug.h"
#include "bsp_hwdefs.h"
#include "rotary.h"

uint8_t read_rotary(void)
{
	static bool rotsw_initialized = false;
	if (!rotsw_initialized) {
		gpio_set_dir(SWITCH_ID0, GPIO_IN);
		gpio_set_dir(SWITCH_ID1, GPIO_IN);
		gpio_set_dir(SWITCH_ID2, GPIO_IN);
		gpio_set_dir(SWITCH_ID3, GPIO_IN);
		rotsw_initialized = true;
	}
	uint32_t v = gpio_get_all();
	uint8_t	 id = (v >> 16) & 0x0f;
	return id;
}