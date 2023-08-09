# ADC

## Overview

This sample demonstrates how to use the ADC driver API. It reads ADC samples from one or more channels and prints the readings on the console. If voltage of the used reference can be obtained, the raw readings are converted to millivolts.

## Requirements

Before you start, check that you have the required hardware and software:

- 1x [nRF52840 MDK USB Dongle](https://makerdiary.com/products/nrf52840-mdk-usb-dongle)(or [w/Case](https://makerdiary.com/products/nrf52840-mdk-usb-dongle-w-case) option)
- A computer running macOS, Linux, or Windows 7 or newer

## Building the sample

Before you start building, remember to [set up the environment](../setup.md) first.

Use the following steps to build the [ADC] sample on the command line.

1. Open a terminal window.

2. Go to `my-workspace/ncs-playground` directory created in the [Setting up the environment](../setup.md#get-the-code) section.

    ``` bash linenums="1"
    cd my-workspace/ncs-playground
    ```

3. Build the sample using the `west` command, specifying the board (following the `-b` option) as `dongle_nrf52840`:

    ``` bash linenums="1"
    west build -p always -b dongle_nrf52840 samples/adc
    ```

    !!! Tip
        The `-p always` option forces a pristine build, and is recommended for new users. Users may also use the `-p auto` option, which will use heuristics to determine if a pristine build is required, such as when building another sample.

4. After running the `west build` command, the build files can be found in `build/zephyr`. 

## Flashing the firmware

The sample is designed to work with the UF2 Bootloader, so that you can easily flash the sample [using the UF2 Bootloader](../../../programming/uf2boot.md). The firmware can be found in `build/zephyr` with the name `zephyr.uf2`.

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

            ![](../../../assets/images/putty-settings.png)

3. Observe the output of the terminal. You should see the output, similar to what is shown in the following:

    ``` { .bash .no-copy linenums="1" }
    ADC reading[1]:
    - adc@40007000, channel 0: 548 = 321 mV
    - adc@40007000, channel 1: 15279 = 3357 mV
    ADC reading[2]:
    - adc@40007000, channel 0: 547 = 320 mV
    - adc@40007000, channel 1: 15272 = 3355 mV
    ADC reading[3]:
    - adc@40007000, channel 0: 554 = 324 mV
    - adc@40007000, channel 1: 15270 = 3355 mV
    ...
    ```

[ADC]: https://github.com/makerdiary/ncs-playground/tree/main/samples/adc
[PuTTY]: https://apps.microsoft.com/store/detail/putty/XPFNZKSKLBP7RJ