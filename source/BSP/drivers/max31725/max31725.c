/**
 *  @file max31725.c Temperature sensor device driver
 *
 *  @brief
 *   Temperature sensor device driver
 **/

#include <stdio.h>
#include <math.h>
#include "bsp_debug.h"
#include "bsp_hwdefs.h"
#include "i2c_utils.h"
#include "max31725.h"

#define REG_TEMPERATURE		  0x00
#define REG_CONFIG			  0x01
#define REG_TEMP_HYSTERESIS	  0x02
#define REG_TEMP_SHUTDOWN	  0x03
#define BIT_TEMP_DATA_MSBBIT  15
#define MASK_TEMP_DATA_MSBBIT (1 << BIT_TEMP_DATA_MSBBIT)

#define MAX31725_ONESHOT	  (1 << 7)
#define MAX31725_TIMEOUTN	  (1 << 6)
#define MAX31725_DATAFORMAT	  (1 << 5)
#define MAX31725_EXTENDED	  MAX31725_DATAFORMAT
#define MAX31725_FAULT_Q1	  (1 << 4)
#define MAX31725_FAULT_Q2	  (1 << 3)
#define MAX31725_IRQ_POLARITY (1 << 2)
#define MAX31725_COMP_OR_IRQ  (1 << 1)
#define MAX31725_SHUTDOWN	  (1 << 0)

/* In extended format, the measured temperature equals the two's
 * complement value plus 64'C, thereby extending the upper
 * temperature data range to 191.99609375'C and allowing
 * temperatures as high as 150'C to be measured.
 */
#define SENSOR_EXTENDED_DATA_FORMAT
#ifdef SENSOR_EXTENDED_DATA_FORMAT
#define TEMP_OFFSET 0x4000 // Adding 64'c to MSB
/* In extended format, offset addition to be handled
 * for positive temperatures above 128'C
 * */
#define POSITIVE_TEMP_CONDITION_1 0x4000
#define POSITIVE_TEMP_CONDITION_2 0x8000
#endif

#if 0
#define WAIT_FOR_CONVERSION() delayms(7)
#endif
#define SWAP_16(a) ((a >> 8) | (a << 8))

static bool is_registered = false;
static bool is_initialized = false;
static bool is_configured = false;

static int max31725_wrconfig(uint8_t config)
{
	/* Unique property of MAX31725 in that config is written as uint8_t MSB,
	 * but is read back as uint16_t and MSB:LSB being equal. */
	int		res;
	uint8_t rdbuf[2];
	uint8_t wrbuf[2];

	wrbuf[0] = 0;
	wrbuf[1] = config;
	res = i2c_reg_wr8(MAX31725_PICO_I2C_BUS, MAX31725_I2C_ADDR, 1, wrbuf, 2);
	if (res < 0) {
		PR_WARN("%s(): Unable to write config\n", __func__);
		return -1;
	}
	res = i2c_reg_rd8(MAX31725_PICO_I2C_BUS, MAX31725_I2C_ADDR, 1, rdbuf, 2);
	if (res < 2 || (rdbuf[0] != rdbuf[1])) {
		PR_ERROR("%s(): Readback err, expected = 0x%02x%02x, got = 0x%02x%02x\n",
				 __func__, wrbuf[1], wrbuf[1], rdbuf[0], rdbuf[1]);
		return -1;
	}
	return 0;
}

float max31725_deg_C(void)
{
	/* TODO: readback config to determine if sensor is in extended data mode.
	 * If yes, perform the additional calculations. */
	int		res;
	uint8_t readbuf[2];
	float	deg_c = nanf("inf");

	if (!is_configured) {
		res = max31725_wrconfig(0);
		if (res < 0) {
			return deg_c;
		}
	}

	res = i2c_reg_rd8(MAX31725_PICO_I2C_BUS, MAX31725_I2C_ADDR, 0, readbuf, 2);
	if (res < 2) {
		return deg_c;
	}

	char	intpart = (char)readbuf[0];
	uint8_t fract = readbuf[1];
	deg_c = (float)intpart + (float)fract / 256.0f;

	return deg_c;
}

static void bus_resetted(uint32_t msec)
{
	(void)(msec);
	is_configured = false;
	printf("%s(): is called\n", __func__);
}

int max31725_init(void)
{
	if (!is_registered) {
		i2c_register_device("max31725", MAX31725_PICO_I2C_BUS, MAX31725_I2C_ADDR, bus_resetted);
		is_registered = true;
	}
	if (!is_initialized) {
		/* Simple test of MAX31725 in that config is written as uint16_t MSB,
		 * but is read back as MSB:LSB being equal. Then finally write the
		 * default config */
		if (max31725_wrconfig(0x55) < 0 || max31725_wrconfig(0xAA) < 0 ||
			max31725_wrconfig(0)) {
			return -1;
		}
		is_initialized = true;
	}
	return 0;
}
