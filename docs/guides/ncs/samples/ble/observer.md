# Bluetooth Low Energy: Observer

## Overview

The BLE Observer sample demonstrates Bluetooth Low Energy Observer role functionality. The application will periodically scan for devices nearby. If any found, prints the address of the device, the RSSI value, the Advertising type, and the Advertising data length to the console.

If the used Bluetooth Low Energy Controller supports Extended Scanning, you may enable `CONFIG_BT_EXT_ADV` in the project configuration file. Refer to the project configuration file for further details.

## Requirements

Before you start, check that you have the required hardware and software:

- 1x [nRF52840 MDK USB Dongle](https://makerdiary.com/products/nrf52840-mdk-usb-dongle)(or [w/Case](https://makerdiary.com/products/nrf52840-mdk-usb-dongle-w-case) option)
- A computer running macOS, Linux, or Windows 7 or newer

## Building the sample

Before you start building, remember to [set up the environment](../../setup.md) first.

Use the following steps to build the [BLE Observer] sample on the command line.

1. Open a terminal window.

2. Go to `my-workspace/ncs-playground` directory created in the [Setting up the environment](../../setup.md#get-the-code) section.

    ``` bash linenums="1"
    cd my-workspace/ncs-playground
    ```

3. Build the sample using the `west` command, specifying the board (following the `-b` option) as `dongle_nrf52840`:

    === "Default"

        ``` bash linenums="1"
        west build -p always -b dongle_nrf52840 samples/ble/observer
        ```
    
    === "Extended Scanning"

        ``` bash linenums="1"
        west build -p always -b dongle_nrf52840 samples/ble/observer -- -DOVERLAY_CONFIG=overlay-extended.conf
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
2. Open up a serial terminal, specifying the correct serial port that your computer uses to communicate with the dongle:

    === "macOS/Linux"

        Open up a terminal and run:

        ``` bash linenums="1"
        screen <serial-port-name> 115200
        ```

    === "Windows"

        1. Start [PuTTY].
        2. Configure the correct serial port and click __Open__:

            ![](../../../../assets/images/putty-settings.png)

3. Observe the output of the terminal. You should see the output, similar to what is shown in the following:

    === "Default"

        ``` { .bash .no-copy }
        Starting Observer Demo
        Started scanning...
        Device found: 49:38:F7:6C:CB:E0 (random) (RSSI -86), type 0, AD data len 31
        Device found: 50:96:57:16:C0:DF (random) (RSSI -85), type 0, AD data len 29
        Device found: CC:72:86:07:B4:7F (public) (RSSI -90), type 0, AD data len 19
        Device found: CC:72:86:08:3F:F1 (public) (RSSI -83), type 0, AD data len 19
        Device found: 5D:38:F1:C7:C5:BB (random) (RSSI -90), type 0, AD data len 31
        ...
        ```
    
    === "Extended Scanning"

        ``` { .bash .no-copy }
        Starting Observer Demo
        Started scanning...
        Device found: CC:72:86:08:3F:F1 (public) (RSSI -82), type 0, AD data len 19
        [DEVICE]: CC:72:86:08:3F:F1 (public), AD evt type 0, Tx Pwr: 127, RSSI -82 Data status: 0, AD data len: 19 Name:  C:1 S:1 D:0 SR:0 E:0 Pri PHY: LE 1M, Sec PHY: No packets, Interval: 0x0000 (0 ms), SID: 255
        Device found: 76:B5:1F:C0:CF:0D (random) (RSSI -84), type 0, AD data len 26
        [DEVICE]: 76:B5:1F:C0:CF:0D (random), AD evt type 0, Tx Pwr: 127, RSSI -84 Data status: 0, AD data len: 26 Name:  C:1 S:1 D:0 SR:0 E:0 Pri PHY: LE 1M, Sec PHY: No packets, Interval: 0x0000 (0 ms), SID: 255
        Device found: CC:72:86:1D:4F:31 (public) (RSSI -71), type 0, AD data len 19
        [DEVICE]: CC:72:86:1D:4F:31 (public), AD evt type 0, Tx Pwr: 127, RSSI -71 Data status: 0, AD data len: 19 Name:  C:1 S:1 D:0 SR:0 E:0 Pri PHY: LE 1M, Sec PHY: No packets, Interval: 0x0000 (0 ms), SID: 255
        ...
        ```

[BLE Observer]: https://github.com/makerdiary/ncs-playground/tree/main/samples/ble/observer
[PuTTY]: https://apps.microsoft.com/store/detail/putty/XPFNZKSKLBP7RJ