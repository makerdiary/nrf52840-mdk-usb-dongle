# nRF52840 MDK USB Dongle Quick Start Guide

## Introduction

This tutorial provides a quick introduction to using the nRF52840 MDK USB Dongle. The dongle is shipped with the [Bluetooth Low Energy Connectivity firmware] after July 20 2023, which allows using nRF Connect Bluetooth Low Energy app to demonstrate Bluetooth Low Energy connectivity.

## Requirements

Before you start, check that you have the required hardware and software:

* 1x [nRF52840 MDK USB Dongle](https://makerdiary.com/products/nrf52840-mdk-usb-dongle)(or [w/Case](https://makerdiary.com/products/nrf52840-mdk-usb-dongle-w-case) option)
* A smartphone or a tablet with [nRF Connect for Mobile](https://www.nordicsemi.com/Products/Development-tools/nRF-Connect-for-mobile) installed
* [nRF Connect Bluetooth Low Energy](https://github.com/NordicPlayground/pc-nrfconnect-ble-standalone/releases/) 4.0.1 or later
* A computer running macOS, Linux, or Windows 7 or newer

??? Warning "Update the BLE Connectivity firmware"
    You may get a dongle without the latest BLE Connectivity firmware, because the dongle manufactured before July 20 2023 was shipped with the [OpenThread NCP firmware]. However, you can change to the latest BLE Connectivity firmware easily by following the steps below:

    1. Download the latest firmware [here](https://github.com/makerdiary/nrf52840-mdk-usb-dongle/tree/main/firmware/ble_connectivity).
    2. Push and hold the button and plug your dongle into the USB port of your computer. Release the button after your dongle is connected. The RGB LED turns green. (If the button has been programmed as RESET functionality, just double-click the button to enter DFU mode.)
    3. It will mount as a Mass Storage Device called __UF2BOOT__ (or __MDK-DONGLE__ for the old bootloader).
    4. Drag and drop `connectivity_4.1.4_usb_with_s132_5.1.0.uf2` onto the __UF2BOOT__ (or __MDK-DONGLE__) volume. The RGB LED blinks red fast during flashing.
    5. Re-plug the dongle and the new BLE Connectivity firmware will start running.


## Installing the nRF Connect Bluetooth Low Energy

The nRF Connect Bluetooth Low Energy app is an easy-to-use cross-platform application for Bluetooth Low Energy connectivity testing. Choose your Desktop platform and select version (latest released version recommended) to download:

[Download](https://github.com/NordicPlayground/pc-nrfconnect-ble-standalone/releases/){ .md-button .md-button--primary }

After starting the nRF Connect Bluetooth Low Energy app, the application window is displayed.

![](./assets/images/pc_nrfconnect_ble_app.png)

## Installing the nRF Connect for Mobile

nRF Connect for Mobile app is a powerful generic tool that allows you to scan and explore your Bluetooth Low Energy devices and communicate with them.

[![App Store](./assets/images/appstore.png){ width='128' display='inline' }](https://itunes.apple.com/us/app/nrf-connect/id1054362403?ls=1&mt=8)
[![Google Play](./assets/images/google-play-badge.png){ width='148' display='inline' }](https://play.google.com/store/apps/details?id=no.nordicsemi.android.mcp)

## Connecting the dongle

The nRF Connect Bluetooth Low Energy app requires a serial port connection to nRF52840 MDK USB Dongle. The dongle is controlled by the app which sends serialized commands to it over a serial port.

To connect the dongle, complete the following steps:

1. Plug your dongle into the USB port of your computer. When the USB device is started, the RGB LED turns blue.

2. Open the nRF Connect Bluetooth Low Energy app, in the navigation bar, click on the __SELECT DEVICE__ menu.

3. Select a device by clicking on its name - __nRF52 Connectivity__ in the drop-down list.

![Connecting the board](./assets/images/nrf_connect_ble_app.gif)

## Establishing Bluetooth Low Energy connections

The nRF Connect Bluetooth Low Energy app can establish and maintain up to eight simultaneous Bluetooth Low Energy connections.

To connect to devices, complete the following steps:

1. To scan for nearby Bluetooth devices, click the __Start scan__ button in the Discovered devices view.

    The advertising devices start to appear in a list in the Discovered devices view. Each entry in the list shows the name, address, and RSSI of the received advertising packet. 

2. To establish a Bluetooth connection with a peer device, click the __Connect__ button associated with the device.

    ![Establishing Bluetooth Low Energy connections](./assets/images/establishing_ble_connections.png)

    When the connection has been established, a new peripheral device appears in the Connection Map, to the right of the local device. The nRF Connect Bluetooth Low Energy app automatically performs an initial service discovery. The discovered services are listed below the connected device.

## Viewing service details

The nRF Connect Bluetooth Low Energy app can discover and display services, characteristics, and descriptors of a connected peer device's attribute table.

- To view the handle and UUID of an attribute, move the mouse pointer over the attribute name. A hover text is displayed.
- To view the characteristics of a service, click the __Expand/collapse__ icon :fontawesome-solid-caret-right:{ .nordic } .
- To view descriptors, expand the characteristics.
- To configure the peer device to start sending notifications, click the __Toggle notifications__ icon :fontawesome-solid-square-caret-right:{ .nordic } . When a device receives a notification, the corresponding attribute is highlighted, and its value is updated.

![Viewing service details](./assets/images/viewing_service.png)

## Setting up advertising

The nRF Connect Bluetooth Low Energy app can also enable the local device to operate as a peripheral that can send connectable advertising packets. The contents of the advertising packets can be configured in the advertising setup.

To start sending advertising packets, complete the following steps:

1. Click the local __Device options__ icon :fontawesome-solid-gear: .
2. Specify the contents of the advertising packets:

    1. To display the Advertising setup dialog, click __Advertising setup__.
    2. From the AD type drop-down menu, select an AD type.
    3. In the Value field, add a data value.
    4. Select __Add to advertising data__ or __Add to scan response__.
    5. Repeat until all wanted fields are present.
    6. Click __Apply__, then click __Close__.

    ![](./assets/images/ble_advertising_setup.png)

3. To start advertising the device, click __Start advertising__.
4. Open nRF Connect for Mobile app, pull down to scan the device:

    ![](./assets/images/nrf_connect_for_mobile.png){ width='250' }

## Next steps

Now, you have finished the nRF52840 MDK USB Dongle quick start guide, it's time to learn more essential developer guides.

To learn how to program the nRF52840 MDK USB Dongle, check out this guide:

* [How to program the nRF52840 MDK USB Dongle](./programming/index.md)

To quickly get started with the nRF Connect SDK development, check the guide below for instructions:

* [Develop with nRF Connect SDK](./guides/ncs/index.md)

You can also make the nRF52840 MDK USB Dongle become a Bluetooth LE or IEEE 802.15.4-based (such as Thread and ZigBee) packet sniffer, which can help identify and fix issues by allowing a view of what is happening on-air. Follow these guides to setup:

* [nRF Sniffer for Bluetooth LE](./guides/ble-sniffer/index.md)
* [nRF Sniffer for 802.15.4](./guides/nrf802154-sniffer/index.md)

nRF52840 MDK USB Dongle also supports Google's OpenSK, a fully open-source implementation for security keys written in Rust that supports both FIDO U2F and FIDO2 standards. Follow the guide below to get started:

* [OpenSK FIDO2 Authenticator Guide](./guides/opensk/index.md)

[Bluetooth Low Energy Connectivity firmware]: https://github.com/makerdiary/nrf52840-mdk-usb-dongle/tree/main/firmware/ble_connectivity
[OpenThread NCP firmware]: https://github.com/makerdiary/nrf52840-mdk-usb-dongle/tree/master/firmware/openthread/ncp
