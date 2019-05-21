# Building and Running the OpenThread examples

This section describes how to build the OpenThread library and example applications.

## Clone the repository

Clone the `nrf52840-mdk-usb-dongle` repository from GitHub:

``` sh
git clone --recursive https://github.com/makerdiary/nrf52840-mdk-usb-dongle.git
```

Or if you have already cloned the project, you may update the submodule:

``` sh
git submodule update --init
```

## Build the OpenThread libraries

Before building the OpenThread examples, you first need to build the OpenThread libraries.

1. Open terminal and change directory to:

	``` sh
	cd ./nrf52840-mdk-usb-dongle/deps/openthread
	```

2. To install the dependencies, run:

	``` sh
	./bootstrap
	```

3. Always clean the repo of previous builds first by running `make clean`:

	``` sh
	make -f examples/Makefile-nrf52840 clean
	```

4. Run the following command. This allows you to communicate with the nRF52840 chip over USB:

	``` sh
	make -f examples/Makefile-nrf52840 BORDER_AGENT=1 BORDER_ROUTER=1 COAP=1 COMMISSIONER=1 DNS_CLIENT=1 JOINER=1 LINK_RAW=1 MAC_FILTER=1 MTD_NETDIAG=1 SERVICE=1 UDP_FORWARD=1 ECDSA=1 SNTP_CLIENT=1 COAPS=1 USB=1
	```

## Build the OpenThread CLI
Now it's ready to build the OpenThread CLI example. The example is located in `nrf52840-mdk-usb-dongle/examples/openthread/cli`. 

Navigate to the directory with the OpenThread Full Thread Device (FTD) CLI Makefile:

``` sh
cd ./nrf52840-mdk-usb-dongle/examples/openthread/cli/ftd/armgcc
```

Run `make` to build the example:

``` sh
make
```

## Build the OpenThread NCP
The example is located in `nrf52840-mdk-usb-dongle/examples/openthread/ncp`. 

Navigate to the directory with the OpenThread Full Thread Device (FTD) NCP Makefile:

``` sh
cd ./nrf52840-mdk-usb-dongle/examples/openthread/ncp/ftd/armgcc
```

Run `make` to build the example:

``` sh
make
```


