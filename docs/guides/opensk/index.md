# OpenSK FIDO2 Authenticator

## Introduction

[OpenSK] released by Google is a fully open-source implementation for security keys written in [Rust] that supports both FIDO U2F and [FIDO2] standards.

OpenSK is based on the FIDO2 specifications, which combine the World Wide Web Consortium’s (W3C) [Web Authentication (WebAuthn) specification] and FIDO Alliance’s corresponding [Client-to-Authenticator Protocol (CTAP)].

The nRF52840 MDK USB Dongle is supported by OpenSK. Taking advantage of the UF2 Bootloader, you can easily program the OpenSK firmware by just copying the `.uf2`-format image to the flash drive.

## Get Involved
We think the best way to learn is by doing. The following sections take you through the basics of OpenSK and show you how to build your own OpenSK firmware.

- [Getting Started with OpenSK]
- [Building your own OpenSK firmware]

## Reference

- [About FIDO2](https://fidoalliance.org/fido2/)
- [Google's OpenSK Repository](https://github.com/google/OpenSK)
- [OpenSK Firmware Releases](https://github.com/makerdiary/OpenSK-firmware/releases)

[OpenSK]: https://github.com/google/OpenSK
[Rust]: https://www.rust-lang.org/
[FIDO2]: https://fidoalliance.org/fido2/
[Web Authentication (WebAuthn) specification]: https://fidoalliance.org/fido2/fido2-web-authentication-webauthn/
[Client-to-Authenticator Protocol (CTAP)]: https://fidoalliance.org/specifications/download/
[Getting Started with OpenSK]: ./getting-started.md
[Building your own OpenSK firmware]: ./building.md