/*
 * bsp_test.c
 */

#include <pico.h> // incs stdint,stdbool,stddefs,datetime_t
#include <stdio.h>
#include <string.h>
#include <pico/stdlib.h>
#include <hardware/watchdog.h>
#include <hardware/rtc.h>
#include <hardware/adc.h>

/* Drivers */
#include "max31725.h"
#include "sdcard.h"
#include "eve_app.h"
#include "rotary.h"
#include "i2c_utils.h"

/* sys utils */
#include "cli.h"

#include "bsp_hwdefs.h"
#include "bsp_debug.h"
#include "bsp_app.h"

BSPContexts_t  dev_contexts;
BSPContexts_t* dev_contexts_gptr = &dev_contexts;

#define SW_BUILDDATE_STR __DATE__
#define SW_BUILDTIME_STR __TIME__
#define SW_TIMESTAMP_STR __DATE__ " " __TIME__
#define APP_TITLE_STR	 KGRN1 "IDP-4000-04A Application"

#define ENABLE_WATCHDOG 0
#define ENABLE_TEMP     1
#define ENABLE_SD       1
#define ENABLE_EVE      1

// Debugging flags & settings
int dbg_fps_msec = 0;

int init_bsp(void);
int do_bsp_tasks(void);

int main()
{
	init_bsp();

	while (true) {
		do_bsp_tasks();
	}
}

int do_bsp_tasks()
{
	BSPContexts_t*ctx = &dev_contexts;

	if (ctx->op_state != op_rebooting) {
#if ENABLE_WATCHDOG
		watchdog_update();
#endif
		do_nonblock_cli();
	}

	ctx->rotarysw_id = read_rotary();
#ifdef USE_MCU_TEMPERATURE
	uint16_t adc_raw = adc_read();
	float	 conversion_factor = 3.3f / (1 << 12);
	float	 adc_volts = (float)adc_raw * conversion_factor;
	float	 cpu_temp = 27.0f - (adc_volts - 0.706f) / 0.001721f;
	ctx->dev_temperature = cpu_temp;
#else
	ctx->dev_temperature = max31725_deg_C();
#endif

	return ctx->op_state;
}

int init_bsp(void)
{
	__unused int res;

	dev_contexts_gptr = &dev_contexts;
	BSPContexts_t*ctx = dev_contexts_gptr;
	/* clear and setup defaults for BSP context state */
	memset(ctx, 0, sizeof(BSPContexts_t));

	ctx->op_state = op_no_comms;

	stdio_init_all();
	sleep_ms(1500);
	printf("\n\n\n%s" KNRM "\n", APP_TITLE_STR);
	printf("Build date: %s, %s\n", SW_BUILDDATE_STR, SW_BUILDTIME_STR);
	printf("PICO_BOARD = %s\n", PICO_BOARD);
	printf("gcc __version__ = %s\n", __VERSION__);
	printf("pico_sdk_version_string = %s\n", PICO_SDK_VERSION_STRING);
	// https://forums.raspberrypi.com/viewtopic.php?t=300003
	extern char __flash_binary_start;
	extern char __flash_binary_end;
	uintptr_t	flash_begin = (uintptr_t)&__flash_binary_start;
	uintptr_t	flash_end = (uintptr_t)&__flash_binary_end;
	printf("Application binary 0x%08x..0x%08x len = %d\n",
		   flash_begin, flash_end, flash_end - flash_begin);

	// Start the RTC
	datetime_t t = {
			.year = 2025,
			.month = 01,
			.day = 01,
			.dotw = 3, // 0 is Sunday, so 5 is Friday
			.hour = 00,
			.min = 00,
			.sec = 00
	};
	rtc_init();
	rtc_set_datetime(&t);
	if (rtc_running()) {
		PR_INFO("RTC initialised\n");
	}
	else {
		ctx->dev_badflags |= (1 << dvr_rtc);
		PR_ERROR("RTC_IS_NOT_RUNNING\n");
	}

#if ENABLE_WATCHDOG
	// Start the Watchdog. By default the SDK assumes a 12MHz XOSC.
	// watchdog_start_tick(12);
	watchdog_enable(WATCHDOG_TIMEOUT, 1);
	PR_INFO("WATCHDOG initialised\n");
#endif /* ENABLE_WATCHDOG */

	adc_init();
	adc_set_temp_sensor_enabled(true);
	adc_select_input(4);
	PR_INFO("CPU Temp initialised\n");

	i2c_pins_init();
	PR_INFO("I2C Busses initialised\n");

	ctx->rotarysw_id = read_rotary();
	PR_INFO("Rotary switch ID = %d\n", ctx->rotarysw_id);

#if ENABLE_TEMP
	int err = 0;
	for (int i = 0; i < 3; i++) {
		err = max31725_init();
		if (err == 0)
			break;
		else
			i2c_bus_reset(MAX31725_PICO_I2C_BUS);
	}
	if (err < 0) {
		ctx->dev_badflags |= (1 << dvr_temp);
		PR_ERROR("Temperature sensor max31725_init(): err = %d\n", err);
	}
	else {
		PR_INFO("Temperature sensor initialised\n");
		float temp = max31725_deg_C();
		if (temp < -128.0) {
			PR_ERROR("ERROR: max31725_deg_C() = %f deg\n", temp);
		}
		else {
			PR_INFO("max31725_deg_C() = %f deg_C\n", temp);
		}
	}
#endif
#if ENABLE_WATCHDOG
	watchdog_update();
#endif

#if ENABLE_SD
	if (!loadSdCard()) {
		ctx->dev_badflags |= (1 << dvr_fatfs);
		PR_WARN("FATFS mount fail\n");
	}
	else {
		PR_INFO("FATFS mounted\n");
	}
#endif /* ENABLE_SD */

#if ENABLE_EVE
	if (!Gpu_Init())
	{
		ctx->dev_badflags |= (1 << dvr_eve);
		PR_WARN("EVE initial fail\n");
	}
	else {
		PR_INFO("EVE initialised\n");
	}
#if ENABLE_WATCHDOG
	watchdog_update();
#endif

	Eve_Calibrate();
	EVE_logo();
#endif /* ENABLE_EVE */

	return ctx->op_state;
}