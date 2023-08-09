# NFC URI record

## Overview

The NFC URI record sample shows how to use the NFC tag to expose a URL record to NFC polling devices.  It uses the [NFC Data Exchange Format (NDEF)].

When the sample starts, it initializes the NFC tag and generates a URI message with a URI record containing the URL "https://makerdiary.com". Then it sets up the NFC library to use the generated message and sense the external NFC field. 

The only events handled by the application are the NFC events. The Red LED turns on when an NFC field is present.

!!! Warning "Requirement of UF2 Bootloader"
    This sample requires your existing bootloader is at least __0.7.1__, as older versions of UF2 Bootloader use `NFC1` and `NFC2` pins as GPIO functionality. [Update the UF2 Bootloader](../../../../programming/uf2boot.md#updating-the-uf2-bootloader) if you are running the older bootloader.

## Requirements

Before you start, check that you have the required hardware and software:

- 1x [nRF52840 MDK USB Dongle](https://makerdiary.com/products/nrf52840-mdk-usb-dongle)
- A 13.56MHz NFC Antenna
- A smartphone or a tablet with NFC support
- A computer running macOS, Linux, or Windows 7 or newer

## Wiring the NFC antenna

![](../../../../assets/images/wiring_nfc_ant.png)

## Building the sample

Before you start building, remember to [set up the environment](../../setup.md) first.

Use the following steps to build the [NFC URI record] sample on the command line.

1. Open a terminal window.

2. Go to `my-workspace/ncs-playground` directory created in the [Setting up the environment](../../setup.md#get-the-code) section.

    ``` bash linenums="1"
    cd my-workspace/ncs-playground
    ```

3. Build the sample using the `west` command, specifying the board (following the `-b` option) as `dongle_nrf52840`:

    ``` bash linenums="1"
    west build -p always -b dongle_nrf52840 samples/nfc/record_uri
    ```

    !!! Tip
        The `-p always` option forces a pristine build, and is recommended for new users. Users may also use the `-p auto` option, which will use heuristics to determine if a pristine build is required, such as when building another sample.

4. After running the `west build` command, the build files can be found in `build/zephyr`.

## Flashing the firmware

The sample is designed to work with the UF2 Bootloader, so that you can easily flash the sample [using the UF2 Bootloader](../../../../programming/uf2boot.md). The firmware can be found in `build/zephyr` with the name `zephyr.uf2`.

To flash the firmware, complete the following steps:

1. Push and hold the button and plug your dongle into the USB port of your computer. Release the button after your dongle is connected. The RGB LED turns green.

2. It will mount as a Mass Storage Device called __UF2BOOT__.

3. Drag and drop `zephyr.uf2` onto the __UF2BOOT__ volume. The RGB LED blinks red fast during flashing.

4. Re-plug the dongle and the sample will start running.

## Testing

After flashing the firmware to your board, complete the following steps to test it:

1. Plug the dongle into the USB port of your computer.
2. Touch the NFC antenna with the smartphone or tablet and observe that Red LED is lit.
3. Observe that the smartphone or tablet tries to open the URL "https://makerdiary.com" in a web browser.
4. Move the smartphone or tablet away from the NFC antenna and observe that Red LED turns off.

[NFC Data Exchange Format (NDEF)]: https://developer.nordicsemi.com/nRF_Connect_SDK/doc/latest/nrf/libraries/nfc/ndef/index.html#lib-nfc-ndef
[NFC URI record]: https://github.com/makerdiary/ncs-playground/tree/main/samples/nfc/record_uri