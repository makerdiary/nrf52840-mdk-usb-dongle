# Common sniffing actions

The nRF Sniffer for Bluetooth LE can help you explore and debug Bluetooth Low Energy communication in a number of typical scenarios.

## Sniffing advertisements from all nearby devices

Use the nRF Sniffer for Bluetooth LE to see advertisements from all nearby devices.

1. [Run the nRF Sniffer] (if not already running).
2. Ensure that __All advertising devices__ is selected in the device list.

## Sniffing advertisement packets involving a single Peripheral

Use the nRF Sniffer for Bluetooth LE to see advertisement packets, scan requests, and scan responses to and from a single device.

1. [Run the nRF Sniffer] (if not already running).
2. Select your device from the device list.

## Sniffing a connection involving a single Peripheral

Use the nRF Sniffer for Bluetooth LE to sniff a connection between a specific Peripheral and a Central.

1. [Run the nRF Sniffer] (if not already running).
2. Select your device from the device list.
3. Connect the Central to the Peripheral.

## Sniffing the pairing procedure of a connection

Use the nRF Sniffer for Bluetooth to sniff an encrypted connection between paired devices by sniffing the pairing procedure.

!!! Note
    If the board running the nRF Sniffer firmware is reset, stored bond information is lost.

1. [Run the nRF Sniffer] (if not already running).
2. Select your device from the device list.
3. Enter the credentials for pairing. The procedure depends on the type of encryption.

    - For connections that use legacy pairing with Just Works:
    
        1. Initiate pairing between the devices if it does not happen automatically.
        
        No further action is required.

    - For connections that use legacy pairing with a passkey:
    
        1. Initiate pairing between the devices if it does not happen automatically.
        2. Select __Legacy Passkey__ as input key and type the 6-digit passkey that is displayed on either the Central or the Peripheral into the input field in Wireshark.
        3. Press ++enter++.
        4. Enter the passkey into the other device.

    - For connections that use legacy pairing with OOB:
    
        1. Before the devices initiate pairing, select __Legacy OOB data__ as input key and type the OOB key in big-endian, hexadecimal format with a leading `0x` into the input field in Wireshark.
        2. Press ++enter++.
        3. Connect the Central to the Peripheral.
        4. Initiate pairing between the devices if it does not happen automatically.

    - For connections that use LE Secure Connections in debug mode:
    
        1. Enable Secure Connections debug mode on one or both of the devices.
        2. Initiate pairing between the devices if it does not happen automatically.

        In debug mode, the connection uses the debug keys specified in the [Bluetooth Core Specification]. The nRF Sniffer uses the same keys to decrypt the encrypted packets.

    - For connections that use LE Secure Connections with a private key:

        1. Before the devices initiate pairing, select __SC Private Key__ as input key and type the 32-byte DiffieHellman private key of your device in big-endian, hexadecimal format with a leading `0x` into the input field in Wireshark.
        2. Initiate pairing between the devices if it does not happen automatically.

## Sniffing a connection between bonded devices

Use the nRF Sniffer for Bluetooth to sniff an encrypted connection between bonded devices. If the nRF Sniffer has previously successfully sniffed the pairing procedure, it remembers the LTK needed to decrypt the connection. Otherwise, you must provide the LTK.

1. [Run the nRF Sniffer] (if not already running).
2. Select your device from the device list.
3. Enter the _LTK_ for the bond.

    - For connections that have an existing legacy bond, select __Legacy LTK__ as input key and type the legacy LTK key in big-endian, hexadecimal format with a leading `0x` into the input field in Wireshark.

    - For connections that have an existing LE Secure Connections bond, select __SC LTK__ as input key and type the LE Secure Connections _LTK_ key in big-endian, hexadecimal format with a leading `0x` into the input field in Wireshark.

4. Initiate encryption between the devices (pairing is not performed when a bond exists).

## Sniffing advertisement packets involving a privacyenabled Peripheral

Use the nRF Sniffer for Bluetooth LE to see advertisement packets, scan requests, and scan responses to and from a single privacy-enabled device. If the nRF Sniffer has previously successfully sniffed the pairing procedure, it remembers the IRK needed to resolve the identity of the device. Otherwise, you must provide the IRK.

1. [Run the nRF Sniffer] (if not already running).
2. Enter the IRK for the device. In Wireshark, select __IRK__ as the input key and type the IRK in big-endian, hexadecimal format with a leading `0x` into the input field.
3. Select your device or __Follow IRK__ from the device list.

## Sniffing advertisement packets involving a Periodic Advertiser

Use the nRF Sniffer for Bluetooth LE to see periodic advertise data from a Periodic Advertiser. If the advertiser has periodic advertising sync information, the sniffer follows the periodic advertising train.

1. [Run the nRF Sniffer] (if not already running).
2. Select your device from the device list.

[Run the nRF Sniffer]: ./running-sniffer.md
[Bluetooth Core Specification]: https://www.bluetooth.com/specifications/bluetooth-core-specification/
