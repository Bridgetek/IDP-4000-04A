# Overview

**Smart home control hub app** is a software package created by EVE Screen Designer (ESD).

# Folder introduction
```
📂 smart_home_control_hub_app
    ├───Data                           | Converted bitmap resource data and flash data which is used by application
    ├───Esd_Core                       | The application core files
    ├───FT_Esd_Framework               | The application framework files
    ├───FT_Esd_Widgets                 | The widget files
    ├───FT_Eve_Hal                     | Hardware Abstraction layer for interfacing the RP2040 platform with EVE control support
    ├───sample_binary                  | A pre-compiled binary of this application for reference
    ├───SmartHomeControlHub            | The application specific source code
    ├───ThirdPartyLib                  | Third party library
    ├───CMakeLists.txt                 | Cmake file
    ├───pico_sdk_import.cmake          | SDK import file from pico
```
# Usage
IDP2040-40A is using EVE BT815 with Raspberry Pi Pico RP2040 host platform. Users are expected to be familiar with the BT81X programming guide and data sheet for EVE BT815 chip.

## Hardware requirement
* USB cable
* power supply
* IDP2040-40A develop board

![IDP2040-40A](https://github.com/user-attachments/assets/ebc59966-4767-4e1a-af5b-ad39de4deaa4)


## Software requirement
* This folder does not include Pico toolchain. For information on downloading, installing, and using the toolchain, please visit https://github.com/raspberrypi/pico-setup-windows. This folder used toolchain version is **1.5.1**.
* cmake
* Visual Studio
* GNU Arm Embedded Toolchain for windows

## Build instruction
1. Launch the *Developer Command Prompt for VS* in Visual Studio
```sh
set PICO_SDK_PATH=[path to pico-sdk]
set PICO_TOOLCHAIN_PATH=[path to GNU Arm Embedded Toolchain\10 2020-q4-major\bin]
cd smart_home_control_hub_app
mkdir build
cd build
[path to cmake] -G "NMake Makefiles" -DCMAKE_BUILD_TYPE=Debug ..
nmake
```
2. SmartHomeControlHub.uf file will be generated in **build** folder

## Program
1. While holding the **BOOTSEL** button, connect the board to computer via the USB cable, or alternatively, press the **RESET** button while holding the **BOOTSEL** button, then release the **RESET** button.
2. Release the **BOOTSEL** button. the board will enter bootloader mode and appear as a removable storage device (RPI-RP2) on computer.
3. Simply drag and drop the generated .uf2 firmware file onto the RPI-RP2 storage device.
