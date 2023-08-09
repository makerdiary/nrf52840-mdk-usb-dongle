# Zigbee Shell

## Overview

This Zigbee Shell sample demonstrates a Zigbee router (with the possibility of being a coordinator) that uses the Zigbee shell library for interaction.

You can use this sample for several purposes, including:

- Initial configuration of the network - forming a network as coordinator, adding devices to the network with the install codes, setting the extended PAN ID.
- Benchmarking - measuring time needed for a message to travel from one node to another.

## Requirements

Before you start, check that you have the required hardware and software:

- 2x [nRF52840 MDK USB Dongle](https://makerdiary.com/products/nrf52840-mdk-usb-dongle)(or [w/Case](https://makerdiary.com/products/nrf52840-mdk-usb-dongle-w-case) option)
- A computer running macOS, Linux, or Windows 7 or newer

## Building the sample

Before you start building, remember to [set up the environment](../../setup.md) first.

Use the following steps to build the [Zigbee Shell] sample on the command line.

1. Open a terminal window.

2. Go to `my-workspace/ncs-playground` directory created in the [Setting up the environment](../../setup.md#get-the-code) section.

    ``` bash linenums="1"
    cd my-workspace/ncs-playground
    ```

3. Build each sample using the `west` command, specifying the board (following the `-b` option) as `dongel_nrf52840`:

    ``` bash linenums="1"
    west build -p always -b dongle_nrf52840 samples/zigbee/shell
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

After flashing the Zigbee Shell firmware, complete the following steps to test it:

1. Plug the first shell device into the USB port of your computer.

2. Open up a serial terminal, specifying the correct serial port that your computer uses to communicate with the first shell device:

    === "macOS/Linux"

        Open up a terminal and run:

        ``` bash linenums="1"
        screen <serial-port-name> 115200
        ```

    === "Windows"

        1. Start [PuTTY].
        2. Configure the correct serial port and click __Open__:

            ![](../../../../assets/images/putty-settings.png)

3. To set the first shell device to work as coordinator, run the following shell command:

    ``` bash linenums="1"
    bdb role zc
    ```

    This shell device is now the shell coordinator node.

4. Run the following command on this shell coordinator node to start a new Zigbee network:

    ``` bash linenums="1"
    bdb start
    ```

5. Run the following command on the second shell device:

    ``` bash linenums="1"
    bdb start
    ```

    This shell device joins the network.

6. To acquired short address of the second shell device, run the following command:

    ``` bash linenums="1"
    zdo short
    ```

    You should see the output, similar to the following:

    ``` {.bash .no-copy linenums="1" }
    uart:~$ zdo short
    50b4
    Done
    ```

7. To check the communication between the nodes, issue a ping request on the coordinator with the acquired short address value and the payload size:

    ``` { .bash .no-copy linenume="1" }
    zcl ping zdo_short_address payload_size
    ```

    For example:

    ``` bash linenums="1"
    zcl ping 0x50b4 10
    ```

    The ping time response is returned when the ping is successful, followed by the additional information from the endpoint logger. For example:

    ``` { .bash .no-copy linenume="1" }
    uart:~$ zcl ping 0x50b4 10
    Ping time: 17 ms
    Done
    [00:08:20.789,245] <inf> zigbee.eprxzcl: Received ZCL command (0): src_addr=0x50b4(short) src_ep=64 dst_ep=64 cluster_id=0xbeef profile_id=0x0104 cmd_dir=0 common_cmd=0 cmd_id=0x01 cmd_seq=0 disable_def_resp=1 manuf_code=void payload=[cdcdcdcdcdcdcdcdcdcd] (0)
    ```

    !!! Tip
        To disable the logs from Zigbee endpoint logger:

        ``` bash linenums="1"
        log disable zigbee.eprxzcl
        ```

        To enable logs from Zigbee endpoint logger and set its logging to the info level (`inf`)

        ``` bash linenums="1"
        log enable inf zigbee.eprxzcl
        ```

[Zigbee Shell]: https://github.com/makerdiary/ncs-playground/tree/main/samples/zigbee/shell
[PuTTY]: https://apps.microsoft.com/store/detail/putty/XPFNZKSKLBP7RJ
