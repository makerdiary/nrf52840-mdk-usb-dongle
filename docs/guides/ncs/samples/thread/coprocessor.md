# Thread Co-processor

## Overview

The Thread Co-processor sample demonstrates how to implement [OpenThread’s Co-processor designs] inside the Zephyr environment. The sample uses the [Radio co-processor (RCP)] architecture.

The sample is based on [Zephyr’s OpenThread Co-Processor] sample. However, it customizes Zephyr’s sample to fulfill the nRF Connect SDK requirements (for example, by increasing the stack size dedicated for the user application), and also extends it with features such as:

- Increased Mbed TLS heap size.
- Lowered main stack size to increase user application space.
- No obsolete configuration options.
- Vendor hooks for co-processor architecture allowing users to extend handled properties by their own, customized functionalities.
- Thread 1.2 features.

!!! Tip "Sniffing packets from a Thread network" 
    You can use [nRF Sniffer for 802.15.4](../../../nrf802154-sniffer/index.md) to capture and analyze packets exchanged on a Thread network.

## Requirements

Before you start, check that you have the required hardware and software:

- 1x nRF52840 MDK USB Dongle](https://makerdiary.com/products/nrf52840-mdk-usb-dongle)(or [w/Case](https://makerdiary.com/products/nrf52840-mdk-usb-dongle-w-case) option)
- A computer running macOS, Linux, or Windows 7 or newer
- [Python] v3.6 or later

## Building the sample

Before you start building, remember to [set up the environment](../../setup.md) first.

Use the following steps to build the [Thread Co-processor] sample on the command line.

1. Open a terminal window.

2. Go to `my-workspace/ncs-playground` directory created in the [Setting up the environment](../../setup.md#get-the-code) section.

    ``` bash linenums="1"
    cd my-workspace/ncs-playground
    ```

3. Build the sample using the `west` command, specifying the board (following the `-b` option) as `dongle_nrf52840`:

    === "Default"

        ``` bash linenums="1"
        west build -p always -b dongle_nrf52840 samples/openthread/coprocessor
        ```

    === "Vendor hooks support"

        ``` bash linenums="1"
        west build -p always -b dongle_nrf52840 samples/openthread/coprocessor -- -DOVERLAY_CONFIG=overlay-vendor_hook.conf
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
2. Get the board’s serial port name (for example, `/dev/cu.usbmodem14201`).
3. Build the OpenThread POSIX applications by performing the following steps:

    1. Enter the `openthread` directory:

        ``` bash linenums="1"
        cd modules/lib/openthread
        ```
    
    2. Install the OpenThread dependencies:

        ``` bash linenums="2"
        ./script/bootstrap
        ```

    3. Build the `ot-daemon` and `ot-ctl` applications with support for Thread v1.2:

        ``` bash linenums="3"
        ./script/cmake-build posix -DOT_THREAD_VERSION=1.2 -DOT_DAEMON=ON
        ```

    You can find the generated applications in `./build/posix/src/posix/`.

4. Open up a terminal window, and start `ot-daemon` with the `--verbose` flag so you can see log output and confirm that it is running:

    ``` bash linenums="1"
    sudo ./build/posix/src/posix/ot-daemon 'spinel+hdlc+uart:///dev/cu.usbmodem14201?uart-baudrate=115200' --verbose
    ```

    When successful, `ot-daemon` in verbose mode generates output similar to the following:

    ``` { .bash .no-copy linenums="2" }
    Feb 10 16:51:15  ./build/posix/src/posix/ot-daemon[56466] <Info>: Running OPENTHREAD/632b63089; POSIX; Feb 10 2023 16:31:19
    Feb 10 16:51:15  ./build/posix/src/posix/ot-daemon[56466] <Info>: Thread version: 3
    Feb 10 16:51:15  ./build/posix/src/posix/ot-daemon[56466] <Info>: Thread interface: utun4
    Feb 10 16:51:15  ./build/posix/src/posix/ot-daemon[56466] <Info>: RCP version: OPENTHREAD/632b63089; Zephyr; Feb 10 2023 16:50:38
    ```

5. Open up a second terminal window and use `ot-ctl` to communicate with the RCP node, specifying the Thread interface `utun4` shown in `ot-daemon` log output:

    ``` bash linenums="1"
    sudo ./build/posix/src/posix/ot-ctl -I utun4
    ```

6. From this point, you can follow the [Testing instructions in the CLI] sample by removing the `ot` prefix for each command. For example:

    ``` { .bash .no-copy linenums="1" }
    > state
    state
    disabled
    Done
    > channel
    channel
    11
    Done
    > panid 0xabcd
    panid 0xabcd
    Done
    ...
    ```

[Python]: https://www.python.org/downloads/
[OpenThread’s Co-processor designs]: https://developer.nordicsemi.com/nRF_Connect_SDK/doc/latest/nrf/ug_thread_architectures.html#thread-architectures-designs-cp
[Radio co-processor (RCP)]: https://developer.nordicsemi.com/nRF_Connect_SDK/doc/latest/nrf/ug_thread_architectures.html#thread-architectures-designs-cp-rcp
[Zephyr’s OpenThread Co-Processor]: https://developer.nordicsemi.com/nRF_Connect_SDK/doc/latest/zephyr/samples/net/openthread/coprocessor/README.html#coprocessor-sample
[Thread Co-processor]: https://github.com/makerdiary/ncs-playground/tree/main/samples/openthread/coprocessor
[Testing instructions in the CLI]: ./cli.md#testing
