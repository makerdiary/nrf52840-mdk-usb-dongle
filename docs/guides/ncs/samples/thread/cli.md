# Thread CLI

The Thread CLI sample demonstrates how to send commands to a Thread device using the OpenThread Command Line Interface (CLI). The CLI is integrated into the Zephyr shell.

!!! Tip "Sniffing packets from a Thread network" 
    You can use [nRF Sniffer for 802.15.4](../../../nrf802154-sniffer/index.md) to capture and analyze packets exchanged on a Thread network.

## Requirements

Before you start, check that you have the required hardware and software:

- 2x [nRF52840 MDK USB Dongle](https://makerdiary.com/products/nrf52840-mdk-usb-dongle)(or [w/Case](https://makerdiary.com/products/nrf52840-mdk-usb-dongle-w-case) option)
- A computer running macOS, Linux, or Windows 7 or newer

## Building the sample

Before you start building, remember to [set up the environment](../../setup.md) first.

Use the following steps to build the [Thread CLI] sample on the command line.

1. Open a terminal window.

2. Go to `my-workspace/ncs-playground` directory created in the [Setting up the environment](../../setup.md#get-the-code) section.

    ``` bash linenums="1"
    cd my-workspace/ncs-playground
    ```

3. Build the sample using the `west` command, specifying the board (following the `-b` option) as `dongle_nrf52840`:

    === "Default"

        ``` bash linenums="1"
        west build -p always -b dongle_nrf52840 samples/openthread/cli
        ```

    === "Low power mode"

        ``` bash linenums="1"
        west build -p always -b dongle_nrf52840 samples/openthread/cli -- -DOVERLAY_CONFIG=overlay-low_power.conf -DDTC_OVERLAY_FILE=low_power.overlay
        ```

    === "Multiprotocol"

        ``` bash linenums="1"
        west build -p always -b dongle_nrf52840 samples/openthread/cli -- -DOVERLAY_CONFIG=overlay-multiprotocol.conf
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

3. Configure the required Thread network parameters with the `ot channel`, `ot panid`, and `ot networkkey` commands. Make sure to use the same parameters for all nodes that you add to the network. The following example uses the default OpenThread parameters:

    ``` { .bash .no-copy linenums="1" }
    uart:~$ ot channel 11
    Done
    uart:~$ ot panid 0xabcd
    Done
    uart:~$ ot networkkey 00112233445566778899aabbccddeeff
    Done
    ```

4. Enable the Thread network with the `ot ifconfig up` and `ot thread start` commands:

    ``` { .bash .no-copy linenums="7" }
    uart:~$ ot ifconfig up
    Done
    uart:~$ ot thread start
    Done
    ```

5. Invoke some of the OpenThread commands:

    1. Test the state of the Thread network with the `ot state` command. For example:

        ``` { .bash .no-copy linenums="11"}
        uart:~$ ot state
        leader
        Done
        ```

    2. Get the Thread network name with the `ot networkname` command. For example:

        ``` { .bash .no-copy linenums="14"}
        uart:~$ ot networkname
        OpenThread
        Done
        ```        

    3. Get the IP addresses of the current Thread network with the `ot ipaddr` command. For example:

        ``` { .bash .no-copy linenums="17"}
        uart:~$ ot ipaddr
        fdde:ad00:beef:0:0:ff:fe00:fc00
        fdde:ad00:beef:0:0:ff:fe00:1000
        fdde:ad00:beef:0:a5b3:5dbd:97b2:474b
        fe80:0:0:0:3cae:981b:5d24:3f00
        Done
        ``` 

6. Test communication between the dongles with the following command:

    ``` { .bash .no-copy }
    ot ping ip_address_of_the_first_dongle
    ```

    For example:

    ``` { .bash .no-copy linenums="1" }
    uart:~$ ot ping fdde:ad00:beef:0:a5b3:5dbd:97b2:474b
    16 bytes from fdde:ad00:beef:0:a5b3:5dbd:97b2:474b: icmp_seq=1 hlim=64 time=24ms
    1 packets transmitted, 1 packets received. Packet loss = 0.0%. Round-trip min/avg/max = 24/24.0/24 ms.
    Done
    ```

[Thread CLI]: https://github.com/makerdiary/ncs-playground/tree/main/samples/openthread/cli
[PuTTY]: https://apps.microsoft.com/store/detail/putty/XPFNZKSKLBP7RJ

