## Install the nRF5 SDK

Download the SDK file [nRF5_SDK_v15.2.0_9412b96](https://www.nordicsemi.com/Software-and-Tools/Software/nRF5-SDK/Download#infotabs) from [www.nordicsemi.com](https://www.nordicsemi.com).

Extract the zip file to the `nrf52840-mdk-usb-dongle` repository. This should give you the following folder structure:

``` sh
./nrf52840-mdk-usb-dongle/
├── LICENSE
├── README.md
├── config
├── deps
│   └── openthread
├── docs
├── examples
├── firmware
├── mkdocs.yml
├── nrf_sdks
│   ├── README.md
│   └── nRF5_SDK_v15.2.0_9412b96
└── tools
```

To use the nRF5 SDK you first need to set the toolchain path in `makefile.windows` or `makefile.posix` depending on platform you are using. That is, the `.posix` should be edited if your are working on either Linux or macOS. These files are located in:

``` sh
<nRF5 SDK>/components/toolchain/gcc
```

Open the file in a text editor ([Sublime](https://www.sublimetext.com/) is recommended), and make sure that the `GNU_INSTALL_ROOT` variable is pointing to your GNU Arm Embedded Toolchain install directory.

``` sh
GNU_INSTALL_ROOT ?= $(HOME)/gcc-arm-none-eabi/gcc-arm-none-eabi-6-2017-q2-update/bin/
GNU_VERSION ?= 6.3.1
GNU_PREFIX ?= arm-none-eabi
```

## Install the nRF5 SDK for Thread and Zigbee

Download the SDK file [nRF5 SDK for Thread and Zigbee V3.0.0](https://www.nordicsemi.com/Software-and-Tools/Software/nRF5-SDK-for-Thread-and-Zigbee/Download#infotabs) from [www.nordicsemi.com](https://www.nordicsemi.com).

Extract the zip file to the `nrf52840-mdk-usb-dongle` repository. This should give you the following folder structure:

``` sh
./nrf52840-mdk-usb-dongle/
├── LICENSE
├── README.md
├── config
├── deps
│   └── openthread
├── docs
├── examples
├── firmware
├── mkdocs.yml
├── nrf_sdks
│   ├── README.md
│   ├── nRF5SDKforThreadandZigbeev300d310e71
│   └── nRF5_SDK_v15.2.0_9412b96
└── tools
```

To use the Thread SDK you first need to set the toolchain path in `makefile.windows` or `makefile.posix` depending on platform you are using. That is, the `.posix` should be edited if your are working on either Linux or macOS. These files are located in:

``` sh
<Thread SDK>/components/toolchain/gcc
```

Open the file in a text editor, and make sure that the `GNU_INSTALL_ROOT` variable is pointing to your GNU Arm Embedded Toolchain install directory.

``` sh
GNU_INSTALL_ROOT ?= $(HOME)/gcc-arm-none-eabi/gcc-arm-none-eabi-7-2018-q2-update/bin/
GNU_VERSION ?= 7.3.1
GNU_PREFIX ?= arm-none-eabi
```
