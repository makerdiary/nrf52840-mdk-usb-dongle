# Getting Started with OpenSK

## Introduction

This guide details how to get started with the OpenSK using the nRF52840 MDK USB Dongle without going through the complete toolchain installation.

## What you'll need

* An [nRF52840 MDK USB Dongle](https://store.makerdiary.com/search?q=nrf52840+dongle)
* Latest version of Google Chrome browser (or at least version 38) or Firefox browser

## Upgrade to UF2 Bootloader

The nRF52840 MDK USB Dongle was previously shipped with [Open Bootloader](https://github.com/makerdiary/nrf52840-mdk-usb-dongle/tree/master/firmware/open_bootloader) with Device Firmware Update (DFU) functionality.

Currently, the prebuilt OpenSK firmware only works with the UF2 Bootloader. If your dongle is using UF2 Bootloader, just skip this step.

!!! note
	As Open Bootloader update must come from signed packages, the new UF2 Bootloader must be signed.
	The signed package is located in: [firmware/open_bootloader/uf2_bootloader-0.2.13-42-g82464f9-nosd_signed.zip](https://github.com/makerdiary/nrf52840-mdk-usb-dongle/tree/master/firmware/open_bootloader)

Enter DFU mode by holding the dongle's RESET/USR button and connecting to your PC. Use the following command to update firmware:

``` sh
nrfutil dfu usb-serial -pkg uf2_bootloader-0.2.13-42-g82464f9-nosd_signed.zip -p <your-serial-port-name>
```

![](assets/images/upgrade-to-uf2-bootloader.png)

## Flash OpenSK via UF2 Bootloader

The prebuilt OpenSK firmware is located in [firmware/OpenSK](https://github.com/makerdiary/nrf52840-mdk-usb-dongle/tree/master/firmware/OpenSK) with the `.uf2`-format.

Enter DFU mode by holding the dongle's RESET/USR button and connecting to your PC. A flash drive with the name **MDK-DONGLE** will appear.

Copy `opensk_nrf52840_mdk_usb_dongle_gece14d7.uf2` image to **MDK-DONGLE**. 

![](assets/images/copying-opensk-image.png)

When programming is completed, the OpenSK will run automatically. The device named **OpenSK** will detected by the computer.

![](assets/images/checking-opensk-device.png)

## Test OpenSK

Now you can test the OpenSK via [WebAuthn.io](https://webauthn.io/):

<iframe width="560" height="315" src="https://www.youtube.com/embed/XEmEADLu8yk" frameborder="0" allow="accelerometer; autoplay; encrypted-media; gyroscope; picture-in-picture" allowfullscreen></iframe>

## Explore More

The two-factor authentication (2FA) has been successfully deployed by a growing number of websites, including Google, social networks, cloud providers, and many others. Happy trying!

## Create an Issue

Interested in contributing to this project? Want to report a bug? Feel free to click here:

<a href="https://github.com/makerdiary/nrf52840-mdk-usb-dongle/issues/new"><button data-md-color-primary="red-bud"><i class="fa fa-github"></i> Create an Issue</button></a>

