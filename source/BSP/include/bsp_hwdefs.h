/*
 * bsp_hwdefs.h
 */
#ifndef _BSP_HWDEFS_H_
#define _BSP_HWDEFS_H_

#include <hardware/i2c.h>
#include <hardware/spi.h>
#include <hardware/uart.h>
#include <hardware/gpio.h>

#ifdef PATH_MAX
#undef PATH_MAX
#endif
#define PATH_MAX	  255
#define PD_PATH_MAX	  255
#define OPENFILES_MAX 8

// clang-format off
#define WATCHDOG_TIMEOUT    3000    // msecs

#define RP2040_FLASH_W25QXX		1
#define FLASH_SIZE			    (8 * 1048576) // based on W25Q64JV

#define LCD_WIDTH				480
#define LCD_HEIGHT				480
#define LCD_BRIGHTNESS_PWM_MIN	12		// out of 128
#define LCD_BRIGHTNESS_PWM_MAX	96		// out of 128
#define LCD_BRIGHTNESS_DEFAULT	80		// percent within above min-max
#define BT81X_ENABLE
#define BT815_ENABLE
#define LCD_MODEL_T040HCSA_10CP 1
#define BT_FLASH_SIZE			(16 * 1048576)
#define BT_FLASH_PAGE_SIZE		4096

#define SWITCH_ID0				16
#define SWITCH_ID1				17
#define SWITCH_ID2				18
#define SWITCH_ID3				19

#define I2C_BUS0_PIN_SDA		20
#define I2C_BUS0_PIN_SCL		21
#define I2C_BUS0_SPEED			(400*1000)
#define I2C_BUS0_PIN_RESET		-1

#define MAX31725_PICO_I2C_BUS	i2c0
#define MAX31725_I2C_ADDR		(0x98 >> 1)

#define LCD_CS 22

// clang-format on

typedef enum {
	dvr_rtc = 0,	  // 0x000001 hard err...
	dvr_eve,		  // 0x000002
	dvr_fatfs,		  // 0x000004
	dvr_temp,         // 0x000008
	dvr_max
} DRIVER_FAILFLAG_BITNUM;

#endif // _BSP_HWDEFS_H_