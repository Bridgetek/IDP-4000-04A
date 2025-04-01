#include <stdio.h>
#include <string.h>
#include <stdint.h>
#include <pico.h>
#include <pico/binary_info.h>

#include "bsp_debug.h"
#include "bsp_hwdefs.h"
#include "i2c_utils.h"

static int			 bus_errors[I2C_TOTAL_BUSSES];
static I2C_DEV_ENTRY i2c_devices[10];
static int			 i2c_dev_cnt = 0;

void i2c_register_device(char *name, i2c_inst_t *bus, uint8_t i2c_addr, i2c_busfailed_cb cb)
{
	for (int i = 0; i < i2c_dev_cnt; i++) {
		if (i2c_devices[i].bus == bus &&
			i2c_devices[i].i2c_addr == i2c_addr) {
			/* just update callback and return */
			i2c_devices[i].cb = cb;
			return;
		}
	}
	/* else install the new device and handler */
	strlcpy(i2c_devices[i2c_dev_cnt].name, name, sizeof(i2c_devices[0].name));
	i2c_devices[i2c_dev_cnt].bus = bus;
	i2c_devices[i2c_dev_cnt].i2c_addr = i2c_addr;
	i2c_devices[i2c_dev_cnt].cb = cb;
	i2c_devices[i2c_dev_cnt].err_count = 0;
	i2c_dev_cnt++;
}

static void i2c_bus_init(i2c_inst_t *bus, int bus_speed, int pin_sda, int pin_scl)
{
	i2c_init(bus, bus_speed);
	gpio_set_function(pin_sda, GPIO_FUNC_I2C);
	gpio_set_function(pin_scl, GPIO_FUNC_I2C);
	gpio_pull_up(pin_sda);
	gpio_pull_up(pin_scl);
	// bi_decl(bi_2pins_with_func(pin_sda, pin_scl, GPIO_FUNC_I2C));
}

/* force a bus recovery action by bit-banging SCL */
void i2c_bus_reset(i2c_inst_t *bus)
{
	int busnum = 0, speed = 0, pin_sda = -1, pin_scl = -1, pin_reset = -1;

	if (bus == i2c0) {
#if defined(I2C_BUS0_PIN_SDA) && defined(I2C_BUS0_PIN_SCL)
		busnum = 0;
		speed = I2C_BUS0_SPEED;
		pin_sda = I2C_BUS0_PIN_SDA;
		pin_scl = I2C_BUS0_PIN_SCL;
#if defined(I2C_BUS0_PIN_RESET)
		pin_reset = I2C_BUS0_PIN_RESET;
#endif
#else
		PR_ERROR("%s(i2c0 bus): error, pins are not defined\n", __func__);
#endif
	}
	else if (bus == i2c1) {
#if defined(I2C_BUS1_PIN_SDA) && defined(I2C_BUS1_PIN_SCL)
		busnum = 1;
		speed = I2C_BUS1_SPEED;
		pin_sda = I2C_BUS1_PIN_SDA;
		pin_scl = I2C_BUS1_PIN_SCL;
#if defined(I2C_BUS1_PIN_RESET)
		pin_reset = I2C_BUS1_PIN_RESET;
#endif
#else
		PR_ERROR("%s(i2c1 bus): error, pins are not defined\n", __func__);
#endif
	}
	if (pin_reset > 0) {
		gpio_put(pin_reset, 0);
		sleep_ms(10);
		gpio_put(pin_reset, 1);
		sleep_ms(10);
		bus_errors[busnum] = 0;
	}
	else if (pin_sda != -1 && pin_scl != -1) {
		gpio_init(pin_sda);
		gpio_init(pin_scl);
		gpio_set_dir(pin_sda, GPIO_OUT);
		gpio_put(pin_sda, 1);
		gpio_set_dir(pin_scl, GPIO_OUT);
		for (int i = 0; i < 10; i++) {
			gpio_put(pin_scl, 0);
			sleep_ms(1);
			gpio_put(pin_scl, 1);
			sleep_ms(1);
		}
		/* release */
		PR_INFO("%s(): bus resetted\n", __func__);
		for (int i = 0; i < i2c_dev_cnt; i++) {
			if (i2c_devices[i].bus == bus) {
				i2c_busfailed_cb callback = i2c_devices[i].cb;
				if (callback != NULL) {
					callback(systime_msec());
				}
			}
		}
		bus_errors[busnum] = 0;
		gpio_init(pin_sda);
		gpio_init(pin_scl);
		i2c_bus_init(bus, speed, pin_sda, pin_scl);
	}
	else {
		PR_ERROR("%s(): pins were not properly defined\n", __func__);
	}
}

void i2c_pins_init()
{
	/* reset device registry and bus-error counts */
	memset(i2c_devices, 0, sizeof(i2c_devices));
	memset(bus_errors, 0, sizeof(bus_errors));

#if defined(I2C_BUS0_SPEED) && defined(I2C_BUS0_PIN_SDA) && defined(I2C_BUS0_PIN_SCL)
	i2c_bus_init(i2c0, I2C_BUS0_SPEED, I2C_BUS0_PIN_SDA, I2C_BUS0_PIN_SCL);
	bi_decl(bi_2pins_with_func(I2C_BUS0_PIN_SDA, I2C_BUS0_PIN_SCL,
							   GPIO_FUNC_I2C));
#endif /* I2C_BUS0 available */

#if defined(I2C_BUS1_SPEED) && defined(I2C_BUS1_PIN_SDA) && defined(I2C_BUS1_PIN_SCL)
	i2c_bus_init(i2c1, I2C_BUS1_SPEED, I2C_BUS1_PIN_SDA, I2C_BUS1_PIN_SCL);
	bi_decl(bi_2pins_with_func(I2C_BUS1_PIN_SDA, I2C_BUS1_PIN_SCL,
							   GPIO_FUNC_I2C));
#endif /* I2C_BUS1 available */
}

static void i2c_bus_errcounter(i2c_inst_t *i2c)
{
	int busnum = (i2c == i2c0) ? 0 : 1;

	int errs = ++bus_errors[busnum];
	if (errs > I2C_MAX_BUS_ERRS) {
		i2c_bus_reset(i2c);
	}
}

int i2c_reg_rd8(i2c_inst_t *i2c, const uint8_t addr, const uint8_t reg, uint8_t *buf, const uint8_t nbytes)
{
	const int char_us = 200; // for slowest 100kHz standard I2C speed
	uint	  read_timeout_us = char_us * nbytes;
	int		  num_bytes_read = 0, err;

	// Check to make sure caller is asking for 1 or more bytes
	if (nbytes < 1) {
		return 0;
	}

	err = i2c_write_timeout_us(i2c, addr, &reg, 1, true, char_us);
	if (err < 0) {
		i2c_bus_errcounter(i2c);
		return err;
	}
	num_bytes_read = i2c_read_timeout_us(i2c, addr, buf, nbytes, false, read_timeout_us);
	if (num_bytes_read < 0) {
		i2c_bus_errcounter(i2c);
	}
	return num_bytes_read;
}

int i2c_reg_wr8(i2c_inst_t *i2c, const uint8_t addr, const uint8_t reg, uint8_t *buf, const uint8_t nbytes)
{
	const int char_us = 200; // for slowest 100kHz standard I2C speed
	uint	  write_timeout_us = char_us * nbytes;
	int		  num_bytes_written;
	uint8_t	  msg[nbytes + 1];

	// Check to make sure caller is sending 1 or more bytes
	if (nbytes < 1) {
		return 0;
	}
	// Append register address to front of data packet
	msg[0] = reg;
	for (int i = 0; i < nbytes; i++) {
		msg[i + 1] = buf[i];
	}
	// Write data to register(s) over I2C
	num_bytes_written = i2c_write_timeout_us(i2c, addr, msg, (nbytes + 1), false, write_timeout_us);
	if (num_bytes_written < 0) {
		i2c_bus_errcounter(i2c);
	}
	return num_bytes_written;
}

/* TODO: FIXME: UNSAFE STANDARD I2C READ/WRITE_BLOCKING ROUTINES */
int i2c_reg_rd16(i2c_inst_t *i2c, const uint8_t addr, const uint8_t reg, uint16_t *buf, const uint8_t nwords)
{
	int num_bytes_read = 0;

	// Check to make sure caller is asking for 1 or more bytes
	if (nwords < 1) {
		return 0;
	}
	// Read data from register(s) over I2C
	i2c_write_blocking(i2c, addr, &reg, 1, true);
	num_bytes_read = i2c_read_blocking(i2c, addr, (uint8_t *)buf, nwords * 2, false);

	return num_bytes_read / 2;
}

/* TODO: FIXME: UNSAFE STANDARD I2C READ/WRITE_BLOCKING ROUTINES */
int i2c_reg_wr16(i2c_inst_t *i2c, const uint8_t addr, const uint8_t reg, uint16_t *buf, const uint8_t nwords)
{
	int		num_bytes_written = 0;
	uint8_t msg[nwords * 2 + 1];

	// Check to make sure caller is sending 1 or more bytes
	if (nwords < 1) {
		return 0;
	}
	// Append register address to front of data packet
	msg[0] = reg;
	for (int i = 0; i < nwords; i++) {
		msg[i * 2 + 1] = buf[i] >> 8;
		msg[i * 2 + 2] = buf[i] & 0xFF;
	}
	// Write data to register(s) over I2C
	num_bytes_written = i2c_write_blocking(i2c, addr, msg, (nwords * 2 + 1), false);

	return num_bytes_written;
}
