# nRF52840 MDK USB Dongle
[![Current Version](https://img.shields.io/github/tag/makerdiary/nrf52840-mdk-usb-dongle.svg)](https://github.com/makerdiary/nrf52840-mdk-usb-dongle/tags)
[![Documentation](https://github.com/makerdiary/nrf52840-mdk-usb-dongle/actions/workflows/documentation.yml/badge.svg?branch=main)](https://wiki.makerdiary.com/nrf52840-mdk-usb-dongle)
[![PRs Welcome](https://img.shields.io/badge/PRs-welcome-brightgreen.svg?color=informational)](/.github/CONTRIBUTING.md)

> A small, low-cost USB Dongle designed with nRF52840

## Description

nRF52840 MDK USB Dongle is a small and low-cost development platform enabled by the nRF52840 multiprotocol SoC in a convenient USB Dongle form factor.

The design features a programmable user button, RGB LED, up to 12 GPIOs and 2.4G Chip antenna on board. It can be used as a low-cost Bluetooth5/Thread/802.15.4/ANT/2.4GHz multiprotocol node or development board. Alternatively the USB Dongle can be used as a Network Co-Processor(NCP) with a simple connection to a PC or other USB enabled device.

It's shipped with the UF2 Bootloader, supports [nRF Connect SDK][ncs-guide], which integrates the Zephyr RTOS, protocol stacks, samples, hardware drivers and much more. The dongle can work as a [Bluetooth Low Energy][ble-sniffer] and [IEEE 802.15.4][nrf802154-sniffer] packet sniffer with Wireshark, and has PCBA and w/Case options to meet various scenarios.

![product hero](./docs/assets/images/nrf52840dongle-hero.png)

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

## Hardware diagram

The following figure illustrates the nRF52840 MDK USB Dongle hardware diagram.

[![](./docs/assets/images/nrf52840-mdk-usb-dongle-pinout.png)][pinout-diagram]

## Mechanical dimensions

nRF52840 MDK USB Dongle PCBA is a single sided 42mm x 17.78mm (1.65" x 0.7") 2.0mm thick PCB with a USB-A port and dual castellated/through-hole pins. nRF52840 MDK USB Dongle w/Case includes a high-quality plastic case in 50.8mm x 21.1mm (2.0" x 0.83") 7.6mm thick.

![](./docs/assets/images/mechanical_specs.png)

## Documentation

We offer an extensive set of documentation such as getting started guides and developer guides, which can help you save big by reducing development effort.

* [nRF52840 MDK USB Dongle Wiki][wiki]
* [nRF52840 MDK USB Dongle Product Brief][product-brief]
* [nRF52840 MDK USB Dongle Quick Start Guide][quickstart]
* [How to program the nRF52840 MDK USB Dongle][programming]
* [Develop with nRF Connect SDK & Zephyr RTOS][ncs-guide]
* [nRF Sniffer for Bluetooth LE][ble-sniffer]
* [nRF Sniffer for 802.15.4][nrf802154-sniffer]
* [OpenSK FIDO2 Authenticator Guide][opensk]

## Where to buy

| Official Store | Buy Now |
|:--------------:|:-------:|
| <a href="https://makerdiary.com"><img alt="makerdiary store" display="inline" src="./docs/assets/images/makerdiary-store.png" width="160"></a> | [![PCBA](https://img.shields.io/badge/PCBA-AC2E45)](https://makerdiary.com/products/nrf52840-mdk-usb-dongle) [![w/Case](https://img.shields.io/badge/w%2FCase-AC452E)](https://makerdiary.com/products/nrf52840-mdk-usb-dongle-w-case) |
| <a href="https://www.tindie.com/stores/makerdiary/"><img alt="Tindie" display="inline" src="./docs/assets/images/tindie-store.png" width="80"></a> | [![PCBA](https://img.shields.io/badge/PCBA-AC2E45)](https://www.tindie.com/products/makerdiary/nrf52840-micro-dev-kit-usb-dongle) [![w/Case](https://img.shields.io/badge/w%2FCase-AC452E)](https://www.tindie.com/products/makerdiary/nrf52840-mdk-usb-dongle-w-case/) |
| <a href="https://zaowubang.taobao.com"><img alt="Taobao" display="inline" src="./docs/assets/images/taobao-store.png" width="80"></a> | [![PCBA](https://img.shields.io/badge/PCBA-AC2E45)](https://item.taobao.com/item.htm?spm=a1z10.1-c.w4004-2992523845.4.7e39796cobENAV&id=578378054977) [![w/Case](https://img.shields.io/badge/w%2FCase-AC452E)](https://item.taobao.com/item.htm?spm=a1z10.3-c.w4002-2992521588.13.629e3f9aZAbOdL&id=597968842403) |

| Approved Distributor | Buy Now |
|:--------------:|:-------:|
| <img alt="seeedstudio" display="inline" src="./docs/assets/images/amazon_logo.png" width="120"> | [![PCBA](https://img.shields.io/badge/PCBA-AC2E45)](https://www.amazon.com/gp/product/B07MJ12XLG) [![w/Case](https://img.shields.io/badge/w/Case-AC452E)](https://www.amazon.com/GeeekPi-nRF52840-MDK-Dongle-Case/dp/B07TSJHTSY) |
| <img alt="seeedstudio" display="inline" src="./docs/assets/images/seeedstudio.png" width="160"> | [![PCBA](https://img.shields.io/badge/PCBA-AC2E45)](https://www.seeedstudio.com/nRF52840-MDK-USB-Dongle-p-3184.html) [![w/Case](https://img.shields.io/badge/w/Case-AC452E)](https://www.seeedstudio.com/nRF52840-MDK-USB-Dongle-w-Case-p-4094.html) |

## Community Support

Community support is provided via [GitHub Discussions][discussions]. We would love to have more developers contribute to this project! If you're passionate about making this project better, see our [Contributing Guidelines][contributing] for more information.

## License

Copyright (c) 2016-2023 Makerdiary. See [LICENSE](./LICENSE) for further details.

[ncs-guide]: https://wiki.makerdiary.com/nrf52840-mdk-usb-dongle/guides/ncs
[ble-sniffer]: https://wiki.makerdiary.com/nrf52840-mdk-usb-dongle/guides/ble-sniffer
[nrf802154-sniffer]: https://wiki.makerdiary.com/nrf52840-mdk-usb-dongle/guides/nrf802154-sniffer
[pinout-diagram]: https://wiki.makerdiary.com/nrf52840-mdk-usb-dongle/assets/attachments/nrf52840-mdk-usb-dongle-pinout_v1_1.pdf
[wiki]: https://wiki.makerdiary.com/nrf52840-mdk-usb-dongle
[product-brief]: https://wiki.makerdiary.com/nrf52840-mdk-usb-dongle/introduction
[quickstart]: http://wiki.makerdiary.com/nrf52840-mdk-usb-dongle/getting-started
[programming]: http://wiki.makerdiary.com/nrf52840-mdk-usb-dongle/programming
[opensk]: http://wiki.makerdiary.com/nrf52840-mdk-usb-dongle/guides/opensk
[discussions]: https://github.com/makerdiary/nrf52840-mdk-usb-dongle/discussions
[contributing]: https://wiki.makerdiary.com/nrf52840-mdk-usb-dongle/CONTRIBUTING