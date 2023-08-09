# Bluetooth Low Energy: Peripheral HIDS mouse

## Overview 
The BLE Peripheral HIDS mouse sample demonstrates how to use the [GATT Human Interface Device (HID) Service] to implement a mouse input device that you can connect to your computer. This sample also shows how to perform directed advertising.

## Requirements

Before you start, check that you have the required hardware and software:

- 1x [nRF52840 MDK USB Dongle](https://makerdiary.com/products/nrf52840-mdk-usb-dongle)(or [w/Case](https://makerdiary.com/products/nrf52840-mdk-usb-dongle-w-case) option)
- A computer running macOS, Linux, or Windows 7 or newer, with Bluetooth LE supported

## Building the sample

Before you start building, remember to [set up the environment](../../setup.md) first.

Use the following steps to build the [BLE Peripheral HIDS mouse] sample on the command line.

1. Open a terminal window.

2. Go to `my-workspace/ncs-playground` directory created in the [Setting up the environment](../../setup.md#get-the-code) section.

    ``` bash linenums="1"
    cd my-workspace/ncs-playground
    ```

3. Build the sample using the `west` command, specifying the board (following the `-b` option) as `dongle_nrf52840`:

    ``` bash linenums="1"
    west build -p always -b dongle_nrf52840 samples/ble/peripheral_hids_mouse
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

After flashing the firmware to your dongle, complete the following steps to test it:

1. Plug the dongle into the USB port of your computer.
2. On your computer, search for Bluetooth devices and connect to the device named __`Nordic_HIDS_mouse`__.
3. When pairing, press the button to confirm the passkey value.
4. Push the button on the dongle. Observe that the mouse pointer on the computer moves to the left.

[GATT Human Interface Device (HID) Service]: https://developer.nordicsemi.com/nRF_Connect_SDK/doc/latest/nrf/libraries/bluetooth_services/services/hids.html#hids-readme
[BLE Peripheral HIDS mouse]: https://github.com/makerdiary/ncs-playground/tree/main/samples/ble/peripheral_hids_mouse