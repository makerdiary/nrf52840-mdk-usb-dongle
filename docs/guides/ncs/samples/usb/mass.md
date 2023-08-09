# USB Mass Storage

## Overview 

The USB Mass Storage sample demonstrates the use of a USB Mass Storage driver by the Zephyr project. This very simple driver enumerates a board with either RAM or FLASH into an USB disk.

## Requirements

Before you start, check that you have the required hardware and software:

- 1x [nRF52840 MDK USB Dongle](https://makerdiary.com/products/nrf52840-mdk-usb-dongle)(or [w/Case](https://makerdiary.com/products/nrf52840-mdk-usb-dongle-w-case) option)
- A computer running macOS, Linux, or Windows 7 or newer

## Building the sample

Before you start building, remember to [set up the environment](../../setup.md) first.

Use the following steps to build the [USB Mass Storage] sample on the command line.

1. Open a terminal window.

2. Go to `my-workspace/ncs-playground` directory created in the [Setting up the environment](../../setup.md#get-the-code) section.

    ``` bash linenums="1"
    cd my-workspace/ncs-playground
    ```

3. Build the sample using the `west` command, specifying the board (following the `-b` option) as `dongle_nrf52840`. There are multiple configurations can be chosen:

    === "RAM-disk"

        ``` bash linenums="1"
        west build -p always -b dongle_nrf52840 samples/usb/mass
        ```

    === "RAM-disk with FATFS"

        ``` bash linenums="1"
        west build -p always -b dongle_nrf52840 samples/usb/mass -- -DCONFIG_APP_MSC_STORAGE_RAM=y
        ```
    
    === "FLASH-disk with FATFS"

        ``` bash linenums="1"
        west build -p always -b dongle_nrf52840 samples/usb/mass -- -DCONFIG_APP_MSC_STORAGE_FLASH_FATFS=y
        ```

    === "FLASH-disk with LittleFS"

        ``` bash linenums="1"
        west build -p always -b dongle_nrf52840 samples/usb/mass -- -DCONFIG_APP_MSC_STORAGE_FLASH_LITTLEFS=y
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
2. The dongle will be detected as an USB disk.

!!! Tip "LittleFS Usage"

    While a FAT-based file system can be mounted by many systems automatically, mounting the littlefs file system on a Linux or FreeBSD system can be accomplished using the [littlefs-fuse] utility.

[USB Mass Storage]: https://github.com/makerdiary/ncs-playground/tree/main/samples/usb/mass
[littlefs-fuse]: https://github.com/littlefs-project/littlefs-fuse