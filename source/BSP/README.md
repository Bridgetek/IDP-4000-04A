# IDP-4000-04A Board Support Package

## Introduction
This repository offers hardware support for the IDP-4000-04A platform. This BSP can function independently with a test application. A USB console is provided for basic functionality.

## Hardware Features
- RP2040 microcontroller (240kB SRAM, USB, etc) with 8 MByte W25Q64JV serial Flash
- Rotary ID switch interfaced to RP2040 microcontroller
- Micro USB port for RP2040
- Board temperature measurement based on the MAX31725 I2C sensor
- MicroSD card connector for RP2040
- BT815 EVE GPU display controller with 16 MByte serial Flash
- 4" TFT LCD panel with capacitive touchscreen
- Buzzer transducer on submodule, for EVE GPU alert sounds
- Custom 8-pin connector for 9-24Vdc power input

## Software Features
The BSP is designed as a support package for devices. Sample usage can be found in *bsp_test.c*

1. The application calls the BSP’s ```init_bsp()```function to initialize interfaces and peripherals:
    - RP2040 pico-sdk USB interface for debugging
    - RP2040 RTC realtime clock
    - RP2040 watchdog timer
    - RP2040 ADC and internal temperature sensor
    - I2C busses and peripherals
        - MAX31725 temperature sensor
    - SD card device driver & FATFS filesystem library
    - BT815 EVE GPU device drivers 

2. The initialization results for the hardware peripherals listed above are stored in a single global C structure, ```BSPContexts_t dev_contexts```.

3. Periodically, the application calls the BSP's ```do_bsp_task()``` to service the interfaces and peripherals.

### Folder instroduction

```
📂 BSP
├── drivers          | collection of device drivers for IDP-4000-04A peripherals
│   ├── eve_hal      | EVE GPU device drivers
│   ├── i2c_utils    | Helpers for pico-sdk I2C device drivers
│   ├── lcd          | LCD driver
│   ├── max31725     | MAX31725 I2C temperature sensor
│   ├── rotary       | rotary driver
│   └── sdcard       | SD card driver and FATFS filesystem library
├── example_binary   | A pre-compiled binary of this BSP for reference
├── extras           | CLI debug terminal sources
├── include          | configuration and build-time parameters
├── bsp_test.c       | main initialization and tasks routines
├── CMakeLists.txt   | CMake file
├── README.md        | this README file

```

### Software requirements
- This folder does not include Pico toolchain. For information on downloading, installing, and using the toolchain, please visit https://github.com/raspberrypi/pico-setup-windows. This folder used toolchain version is 1.5.1.
- GNU Arm Embedded Toolchain for windows
- Visual Studio 2019

### Build instruction
Because the IDP-4000-04A uses the Winbond QSPI-Flash and custom GPIO pinning, the pico-sdk built-in standard modules' definition files may not work. A replacement header file
```bridgetek_idp_4000_04a.h``` fixes this, but must be copied into the pico-sdk source tree.
```
$ cp include/bridgetek_idp_4000_04a.h <path to pico-sdk>/pico-sdk/src/boards/include/boards
```
 This will give visibility to the CMakelists.txt directive of
```
set(PICO_BOARD "bridgetek_idp_4000_04a")
```
*Build:*

Launch the Developer Command Prompt for VS
```
set PICO_SDK_PATH=[path to pico-sdk]
set PICO_TOOLCHAIN_PATH=[path to GNU Arm Embedded Toolchain\10 2020-q4-major\bin]
mkdir build
cd build
cmake -G "NMake Makefiles" ..
nmake BSP_test
# The artifact BSP_test.uf2 built can be used to flash the RP2040.
```

### Program
1. While holding the **BOOTSEL** button, connect the board to computer via the USB cable, or alternatively, press the **RESET** button while holding the **BOOTSEL** button, then release the **RESET** button.
2. Release the **BOOTSEL** button. the board will enter bootloader mode and appear as a removable storage device (RPI-RP2) on computer.
3. Simply drag and drop the generated .uf2 firmware file onto the RPI-RP2 storage device.

### USB Debug-port Command Line Interface
The BSP supports a command-line interface when used with the USB-debug port and an appropriate Serial Terminal emulator on a host computer. The CLI supports the following commands:
- ```help```     - prints a list of commands
- ```cls```      - clear screen
- ```date```     - view or set datetime
- ```mr```       - pico flash content dump
- ```reboot```   - reboot the board
- ```rot```      - display rotary value 
- ```sd```       - SD card mount detect
- ```eve```      - show Bridgetek LOGO on LCD screen
- ```buzzer```   - play a sound via buzzer
