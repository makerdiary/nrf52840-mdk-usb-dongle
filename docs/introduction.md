# nRF52840 MDK USB Dongle<br/><small>A small, low-cost USB Dongle designed with nRF52840</small>

!!! Warning "Factory Firmware Update Notification"
    The dongle manufactured after July 20 2023 is shipped with the latest [UF2 Bootloader 0.7.1](https://github.com/makerdiary/nrf52840-mdk-usb-dongle/tree/main/firmware/uf2_bootloader/0.7.1) and [BLE Connectivity Firmware](https://github.com/makerdiary/nrf52840-mdk-usb-dongle/tree/main/firmware/ble_connectivity). You may get a dongle without the latest firmware, you can follow the [Programming](programming/index.md) section to update the firmware.

## Description

nRF52840 MDK USB Dongle is a small and low-cost development platform enabled by the nRF52840 multiprotocol SoC in a convenient USB Dongle form factor.

The design features a programmable user button, RGB LED, up to 12 GPIOs and 2.4G Chip antenna on board. It can be used as a low-cost Bluetooth5/Thread/802.15.4/ANT/2.4GHz multiprotocol node or development board. Alternatively the USB Dongle can be used as a Network Co-Processor(NCP) with a simple connection to a PC or other USB enabled device.

It's shipped with the UF2 Bootloader, supports [nRF Connect SDK](guides/ncs/index.md), which integrates the Zephyr RTOS, protocol stacks, samples, hardware drivers and much more. The dongle can work as a [Bluetooth Low Energy](guides/ble-sniffer/index.md) and [IEEE 802.15.4](guides/nrf802154-sniffer/index.md) packet sniffer with Wireshark, and has PCBA and w/Case options to meet various scenarios.

![product hero](assets/images/nrf52840dongle-hero.png)

## Key Features

* Nordic Semiconductor nRF52840 SoC

    - 64 MHz Arm® Cortex-M4 with FPU
    - 1 MB Flash + 256 KB RAM
    - Bluetooth LE, Bluetooth mesh, Thread, Zigbee, 802.15.4, ANT and 2.4 GHz proprietary
    - Arm TrustZone® Cryptocell 310 Security Subsystem
    - 2.4 GHz Transceiver with +8 dBm TX Power
    - GPIO, UART, SPI, TWI(I2C), PDM, I2S, QSPI, PWM, QDEC, 12-bit ADC support
    - Integrated USB 2.0 Full-speed Controller
    - Integrated NFC-A Tag

* Arm Serial Wire Debug (SWD) port via edge pins
* Up to 12 GPIOs available via edge pins
* User programmable Button and RGB LED
* On-board 2.4G chip antenna
* 3.3V regulator with 1A peak current output
* VBUS & VIN Power-Path Management
* Convenient USB dongle form factor
* Breadboard-friendly with dual 10-Pin headers
* Measures 1.65" x 0.7" x 0.15" (42mm x 17.78mm x 3.75mm) without headers soldered in
* w/Case option available to provide protection and ease of use
* Shipped with UF2 Bootloader supporting Drag-and-drop programming over USB drive
* Built on open source, supporting nRF Connect SDK, Zephyr RTOS, Google's OpenSK, etc.

## What's in the box

|Part                                     |Quantity |
|-----------------------------------------|---------|
|nRF52840 MDK USB Dongle PCBA (or w/Case) |1        |
|10 Pin 2.54mm THT Pin Header[^1]         |2        |

[^1]: Only available for the PCBA option
