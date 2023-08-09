# nRF Sniffer for 802.15.4

## Introduction

The nRF Sniffer for 802.15.4 is a tool for learning about and debugging applications that are using protocols based on IEEE 802.15.4, such as Thread and Zigbee. It provides a near real-time display of 802.15.4 packets that are sent back and forth between devices, even when the link is encrypted.

When developing a 802.15.4-compatible product, knowing what happens over-the-air between devices can help you identify and fix issues quickly.

The nRF Sniffer captures packets transmitted by nearby devices on a selected radio channel. You can start the capture manually from Wireshark, a free software tool that captures wireless traffic and reproduces it in a readable format, or using a Python script. Use either of these methods to create packet capture files, from which you can extract data in Wireshark. This data can include destination and source addresses, personal area network identifiers, and packet payloads.

The nRF Sniffer for 802.15.4 comes with an extcap plugin for capturing packets in Wireshark. This plugin can also be installed as a Python module for use in a script.

Wireshark is also able to analyze data exchanged over higher-level protocols, such as Thread and Zigbee. You can configure the Sniffer to report out-of-band metadata, such as channel, received signal strength indicator (RSSI), and link quality inidcator (LQI).

## Requirements

Before you start, check that you have the required hardware and software:

* 1x [nRF52840 MDK USB Dongle](https://makerdiary.com/products/nrf52840-mdk-usb-dongle)(or [w/Case](https://makerdiary.com/products/nrf52840-mdk-usb-dongle-w-case) option)
* Supported operating systems:
    - Windows 10
    - 64-bit OS X/macOS 10.6 or later
    - Linux (check the [Wireshark] prerequisites for version compatibility)
* [Wireshark] v3.4.7 or later
* [Python] v3.7 or later

## Get Involved

The following sections explain how to set up the nRF Sniffer for 802.15.4 and help you get moving with sniffing:

- [Installation](./installation.md)
- [Configuring Wireshark for nRF Sniffer for 802.15.4](./configuring.md)
- [Capturing data with the nRF Sniffer](./capturing.md)
- [Inspecting captured data](./inspecting-data.md)

## Reference

* [nRF Sniffer for 802.15.4 User Guide v0.7.2](https://infocenter.nordicsemi.com/pdf/nRF_Sniffer_802154_User_Guide_v0.7.2.pdf)
* [Wireshark website](https://www.wireshark.org/)

[Wireshark]: https://www.wireshark.org/
[Python]: https://www.python.org/downloads/