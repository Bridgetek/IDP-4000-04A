#include <pico.h> // incs stdint,stdbool,stddefs,datetime_t
#include <ctype.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <pico/stdio.h>
#include <hardware/watchdog.h>

#include "cli.h"
#include "bsp_app.h"
#include "cli_hwtests.h"

#include "i2c_utils.h"
#include "sdcard.h"
#include "eve_app.h"
#include "rotary.h"
#include "max31725.h"

int cmd_rotsw(int argc, char *argv[])
{
	uint8_t res = read_rotary();

	printf("\n%s: read_rotary() res=%d\n", argv[0], res);

	return 0;
}

int cmd_sdcard(int argc, char* argv[])
{
	int res = sdCardReady();

	printf("\n%s: SD ready =%d\n", argv[0], res);

	return 0;
}

int cmd_evelogo(int argc, char* argv[])
{
	EVE_logo();

	printf("\nEVE shows LOGO\n");

	return 0;
}

int cmd_buzzer(int argc, char* argv[])
{
	EVE_buzzer();

	printf("\nBuzzer test\n");

	return 0;
}

int cmd_temperature(int argc, char* argv[])
{
	float temp = max31725_deg_C();
	if (temp < -128.0) {
		printf("\nERROR: max31725_deg_C() = %f deg\n", temp);
	}
	else {
		printf("\nmax31725_deg_C() = %f deg_C\n", temp);
	}
	return 0;
}
