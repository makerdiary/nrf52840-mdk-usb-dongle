# nRF52840 MDK USB Dongle <br><small>A small and low-cost nRF52840 Micro Development Kit in USB Dongle Form Factor</small>

## Description

The nRF52840 MDK USB Dongle is a small and low-cost development platform enabled by the nRF52840 multiprotocol SoC in a convenient USB dongle form factor.

The design features a programmable user button, RGB LED, up to 12 GPIOs and 2.4G Chip antenna on board. It can be used as a low-cost Bluetooth5/Tread/802.15.4/ANT/2.4GHz multiprotocol node or development board. Alternatively the USB Dongle can be used as a Network Co-Processor(NCP) with a simple connection to a PC or other USB enabled device.

[![](assets/images/dongle_pcba_case.jpg)](https://store.makerdiary.com/search?q=nrf52840+dongle)

## Hardware Features

* Nordic nRF52840 System-on-Chip
	- ARM® Cortex®-M4F processor optimized for ultra-low power operation
	- Combining *Bluetooth 5*, *Bluetooth Mesh*, *Thread*, *IEEE 802.15.4*, *ANT* and *2.4GHz proprietary*
	- On-chip NFC-A tag
	- On-chip USB 2.0 (Full speed) controller
	- ARM TrustZone® Cryptocell 310 security subsystem
	- 1 MB FLASH and 256 kB RAM
* Up to 12 GPIOs available via headers
* User programmable Button and RGB LED
* On-board 2.4G chip antenna 
* 3.3V regulator with 1A peak current output
* VBUS & VIN Power-Path Management
* Convenient USB dongle form factor
* Breadboard-friendly with dual 10-Pin headers
* Measures 1.65" x 0.7" x 0.16" (42mm x 18mm x 4mm) without headers soldered in

## Pinout Diagram

[![](assets/images/nrf52840-mdk-usb-dongle-pinout.png)](assets/images/nrf52840-mdk-usb-dongle-pinout.png)

## Software Resource

The nRF52840 MDK USB Dongle can be used to play with : *nRF5 SDK*, *OpenThread*, *Web Bluetooth*, *iBeacon*, *Eddystone*, and more.

| Software  | Brief Description |
| ---------- | ----- |
| [nRF5 SDK](nrf5-sdk.md) | Offical Software Development Kit for nRF51 and nRF52 Series |
| [OpenThread Border Router](OTBR.md) | An open source border router, designed to work with OpenThread |
| [Thread Network Sniffer](thread-sniffer.md) | Help you to efficiently analyze Thread network traffic|
| [Web Bluetooth](https://webbluetoothcg.github.io/web-bluetooth/) | Bluetooth support for the Web |
| [iBeacon](https://developer.apple.com/ibeacon/) | A Bluetooth low energy advertising message format designed by Apple |
| [Eddystone](https://github.com/google/eddystone) | A protocol specification that defines a Bluetooth low energy message format for proximity beacon messages |
| [CircuitPython](https://circuitpython.org/board/makerdiary_nrf52840_mdk_usb_dongle/) | A programming language designed to simplify experimenting and learning to code on low-cost microcontroller boards |
| [TinyGo](https://tinygo.org/microcontrollers/nrf52840-mdk-usb-dongle) | Go compiler for small devices, based on LLVM |
| [Rust for nrf52840-mdk](https://github.com/nrf-rs/nrf52840-mdk-rs) | Rust support for the nrf52840-mdk development board |
| [Web Device CLI](https://github.com/makerdiary/web-device-cli) | A Web Command Line Interface via NUS (Nordic UART Service) using Web Bluetooth API |
| [nRF52 FIDO U2F Security Key](https://github.com/makerdiary/nrf52-u2f) | An Open-Source FIDO U2F implementation on nRF52 SoC |
| [OpenSK](https://github.com/makerdiary/OpenSK) | An open-source implementation for security keys written in Rust that supports both FIDO U2F and FIDO2 standards released by [Google](https://github.com/google/OpenSK) |


## Hardware Resource

| Releases | Design Files                   |
| -------- | ------------------------------ |
| V1.0     | [nRF52840 MDK USB Dongle V1.0 Pinout Diagram](hardware/nrf52840-mdk-usb-dongle-pinout_v1_0.pdf)<br/>[nRF52840 MDK USB Dongle V1.0 Schematic](hardware/nrf52840-mdk-usb-dongle-sch_v1_0.pdf)<br/>[nRF52840 MDK USB Dongle V1.0 Board File](hardware/nrf52840-mdk-usb-dongle-board_v1_0.pdf)<br/>[nRF52840 MDK USB Dongle V1.0 3D STEP](hardware/nrf52840-mdk-usb-dongle-3d_v1_0.step)|

## Create an Issue

Interested in contributing to this project? Want to report a bug? Feel free to click here:

<a href="https://github.com/makerdiary/nrf52840-mdk-usb-dongle/issues/new"><button data-md-color-primary="red-bud"><i class="fa fa-github"></i> Create an Issue</button></a>

