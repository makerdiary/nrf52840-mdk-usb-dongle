
## DFU via Open Bootloader

The nRF52840 MDK USB Dongle was previously shipped with [Open Bootloader](https://github.com/makerdiary/nrf52840-mdk-usb-dongle/tree/master/firmware/open_bootloader) with Device Firmware Update (DFU) functionality. You can easily program the Dongle using the following tools:

* [nRF Connect for Desktop](https://www.nordicsemi.com/Software-and-tools/Development-Tools/nRF-Connect-for-desktop)
* [nrfutil](https://github.com/NordicSemiconductor/pc-nrfutil/) from the command line.

See the [Wiki](https://wiki.makerdiary.com/nrf52840-mdk-usb-dongle/programming/#dfu-via-open-bootloader) page for information on how to use Open Bootloader.

## Upgrade to UF2 Bootloader from Open Bootloader

UF2 Bootloader is available for the nRF52840 MDK USB Dongle. You can upgrade to UF2 Bootloader to take advantage of the latest features.

**Note:** As Open Bootloader update must come from signed packages, the new UF2 Bootloader must be signed. The signed package is `uf2_bootloader-0.2.13-44-gb2b4284-nosd_signed.zip`.

Enter DFU mode by holding the dongle's RESET/USR button and connecting to your PC. Use the following command to update firmware:

``` sh
nrfutil dfu usb-serial -pkg uf2_bootloader-0.2.13-44-gb2b4284-nosd_signed.zip -p <your-serial-port-name>
```

![](../../docs/assets/images/upgrade-to-uf2-bootloader.png)