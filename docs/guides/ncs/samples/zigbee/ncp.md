# Zigbee NCP

## Overview

The Zigbee NCP sample demonstrates the usage of Zigbee’s [Network Co-Processor (NCP)] architecture.

Together with the source code from [ZBOSS NCP Host], you can use this sample to create a complete and functional Zigbee device. For example, as shown in the [Testing](#testing) section, you can program nRF52840 MDK USB Dongle with the NCP sample and bundle it with the simple gateway application on the NCP host processor.

You can then use this sample together with the [Zigbee Light bulb] to set up a basic Zigbee network.

!!! Tip "Sniffing packets from a Zigbee network" 
    You can use [nRF Sniffer for 802.15.4](../../../nrf802154-sniffer/index.md) to capture and analyze packets exchanged on a Zigbee network.


## Requirements

Before you start, check that you have the required hardware and software:

- 2x [nRF52840 MDK USB Dongle](https://makerdiary.com/products/nrf52840-mdk-usb-dongle)(or [w/Case](https://makerdiary.com/products/nrf52840-mdk-usb-dongle-w-case) option)
- A computer running 64-bit Ubuntu 18.04 Linux

## Building the sample

Before you start building, remember to [set up the environment](../../setup.md) first.

Use the following steps to build the [Zigbee NCP] sample on the command line.

1. Open a terminal window.

2. Go to `my-workspace/ncs-playground` directory created in the [Setting up the environment](../../setup.md#get-the-code) section.

    ``` bash linenums="1"
    cd my-workspace/ncs-playground
    ```

3. Build the sample using the `west` command, specifying the board (following the `-b` option) as `dongle_nrf52840`:

    ``` bash linenums="1"
    west build -p always -b dongle_nrf52840 samples/zigbee/ncp
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

After flashing the Zigbee NCP firmware, complete the following steps to test it:

1. Download and extract the [ZBOSS NCP Host package].

    !!! Note 
        If you are using a Linux distribution different than the 64-bit Ubuntu 18.04, make sure to rebuild the package libraries and applications. Follow the instructions in the [Rebuilding the ZBOSS libraries for host] section in the [NCP Host documentation].

2. Plug the dongle that runs the Zigbee NCP firmware into the USB port of your computer.
3. Get the dongle's serial port names. You will get two serial ports: one used for communication with the NCP Host and one used to print ZBOSS stack logs.
4. Turn on the dongle that runs the [Zigbee Light bulb] sample.
5. To start the simple gateway application, run the following command with `serial_port_name` replaced with the serial port name used for communication with the NCP sample:

    ``` bash linenums="1"
    NCP_SLAVE_PTY=*serial_port_name* ./application/simple_gw/simple_gw
    ```

6. The simple gateway device forms the Zigbee network and opens the network for 180 seconds for new devices to join. When the light bulb joins the network, the __RGB LED__ on the light bulb device turns __Green__ to indicate that it is connected to the simple gateway. The gateway then starts discovering the On/Off cluster. When it is found, the simple gateway configures bindings and reporting for the device. It then starts sending On/Off toggle commands with a 15-second interval that toggle the __Red LED__ on the light bulb on and off.


[Network Co-Processor (NCP)]: https://developer.nordicsemi.com/nRF_Connect_SDK/doc/latest/nrf/protocols/zigbee/architectures.html#ug-zigbee-platform-design-ncp-details
[ZBOSS NCP Host]: https://developer.nordicsemi.com/nRF_Connect_SDK/doc/latest/nrf/protocols/zigbee/tools.html#ug-zigbee-tools-ncp-host
[ZBOSS NCP Host package]: https://developer.nordicsemi.com/Zigbee/ncp_sdk_for_host/ncp_host_v2.2.0.zip
[Zigbee Light bulb]: https://github.com/makerdiary/ncs-playground/tree/main/samples/zigbee/light_bulb
[Zigbee NCP]: https://github.com/makerdiary/ncs-playground/tree/main/samples/zigbee/ncp
[Rebuilding the ZBOSS libraries for host]: https://developer.nordicsemi.com/nRF_Connect_SDK/doc/zboss/3.11.2.0/zboss_ncp_host.html#rebuilding_libs
[NCP Host documentation]: https://developer.nordicsemi.com/nRF_Connect_SDK/doc/zboss/3.11.2.0/zboss_ncp_host_intro.html