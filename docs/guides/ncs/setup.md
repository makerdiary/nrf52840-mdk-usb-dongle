# Setting up the environment

To start working with the nRF Connect SDK, you should set up your development environment. nRF Connect SDK is based on the Zephyr RTOS, which means most of the requirements for Zephyr are also suitable for the nRF Connect SDK. The only requirement that is not covered by the [installation steps in Zephyr](https://docs.zephyrproject.org/latest/develop/getting_started/index.html) is the [GN] tool. This tool is needed only for [Matter] applications.

This guide shows you how to set up a command-line nRF Connect SDK development environment on Ubuntu, macOS, or Windows manually. For automatic installation, please refer to the [Installing automatically](https://developer.nordicsemi.com/nRF_Connect_SDK/doc/latest/nrf/gs_assistant.html) page.

## Select and Update OS

Install available updates for your operating system:

=== "Windows"

    Select __Start__ > __Settings__ > __Update & Security__ > __Windows Update__. Click __Check for updates__ and install any that are available.

=== "macOS"

    On macOS Mojave or later, select __System Preferences...__ > __Software Update__. Click __Update Now__ if necessary.

    On other versions, see [this Apple support topic](https://support.apple.com/en-us/HT201541).

=== "Ubuntu"

    This guide covers Ubuntu version 18.04 LTS and later.

    ``` bash linenums="1"
    sudo apt update
    ```

    ``` bash linenums="2"
    sudo apt upgrade
    ```

## Install dependencies

Next, you’ll install some host dependencies using your package manager.

The current minimum required version for the main dependencies are:

| Tool                  | Min. Version |
|-----------------------|--------------|
| [CMake]               | 3.20.0       |
| [Python]              | 3.8          |
| [Devicetree compiler] | 1.4.6        |

=== "Windows"

    We use [Chocolatey] to install dependencies here. If Chocolatey isn’t an option, you can install dependencies from their respective websites and ensure the command line tools added in your __`PATH`__ environment variable.


    1. [Install chocolatey](https://chocolatey.org/install).

    2. Open a `cmd.exe` window as Administrator. To do so, press the Windows key ++win++ , type `cmd.exe`, right-click the result, and choose __Run as Administrator__.

    3. Disable global confirmation to avoid having to confirm the installation of individual programs:

        ``` bash linenums="1"
        choco feature enable -n allowGlobalConfirmation
        ```

    4. Use `choco` to install the required dependencies:

        ``` bash linenums="1"
        choco install cmake --installargs 'ADD_CMAKE_TO_PATH=System'
        ```

        ``` bash linenums="2"
        choco install ninja gperf python git dtc-msys2 wget unzip
        ```

    5. Close the window and open a new `cmd.exe` window __as a regular user__ to continue.

    !!! Tip
        To check the list of installed packages and their versions, run the following command:

        ``` bash linenums="1"
        choco list -lo
        ```

=== "macOS"

    1. Install [Homebrew]:

        ``` bash linenums="1"
        /bin/bash -c "$(curl -fsSL https://raw.githubusercontent.com/Homebrew/install/HEAD/install.sh)"
        ```

    2. Use `brew` to install the required dependencies:

        ``` bash linenums="1"
        brew install cmake ninja gperf python3 ccache qemu dtc wget libmagic
        ```
    
    !!! Tip
        To check the versions of these dependencies installed, run the following command:

        ``` bash linenums="1"
        brew list --versions
        ```

=== "Ubuntu"

    1. If using an Ubuntu version older than 22.04, it is necessary to add extra repositories to meet the minimum required versions for the main dependencies listed above. In that case, download, inspect and execute the Kitware archive script to add the Kitware APT repository to your sources list. A detailed explanation of `kitware-archive.sh` can be found here [kitware third-party apt repository](https://apt.kitware.com/):

        ``` bash linenums="1"
        wget https://apt.kitware.com/kitware-archive.sh
        ```

        ``` bash linenums="2"
        sudo bash kitware-archive.sh
        ```
    
    2. Use `apt` to install the required dependencies:

        ``` bash linenums="1"
        sudo apt install --no-install-recommends git cmake ninja-build gperf \
        ccache dfu-util device-tree-compiler wget \
        python3-dev python3-pip python3-setuptools python3-tk python3-wheel xz-utils file \
        make gcc gcc-multilib g++-multilib libsdl2-dev libmagic1
        ```
    
    3. Verify the versions of the main dependencies installed on your system by entering:

        ``` bash linenums="1"
        cmake --version
        ```

        ``` bash linenums="2"
        python3 --version
        ```

        ``` bash linenums="3"
        dtc --version
        ```

??? Note "Install GN tool for Matter"

    If you want to build [Matter] applications, additionally install the [GN] meta-build system. This system generates the Ninja files that the nRF Connect SDK uses.

    === "Windows"

        To install the GN tool, complete the following steps:

        1. Download the latest version of the GN binary archive for Windows from the [GN website](https://gn.googlesource.com/gn/#getting-a-binary).

        2. Extract the `zip` archive.

        3. Ensure that the GN tool is added to your __`PATH`__ environment variable.
    
    === "macOS"

        To install the GN tool, complete the following steps:

        1. Create the directory for the GN tool:

            ``` bash linenums="1"
            mkdir ${HOME}/gn && cd ${HOME}/gn
            ```

        2. Download the GN binary archive and extract it by using the following commands:

            === "Apple Silicon (M1 & M2)"

                ``` bash linenums="1"
                wget -O gn.zip https://chrome-infra-packages.appspot.com/dl/gn/gn/mac-arm64/+/latest
                ```

                ``` bash linenums="2"
                unzip gn.zip
                ```

                ``` bash linenums="3"
                rm gn.zip
                ```

            === "64-bit AMD (Intel)"

                ``` bash linenums="1"
                wget -O gn.zip https://chrome-infra-packages.appspot.com/dl/gn/gn/mac-amd64/+/latest
                ```

                ``` bash linenums="2"
                unzip gn.zip
                ```

                ``` bash linenums="3"
                rm gn.zip
                ```

        3. Add the location of the GN tool to the system __`PATH`__. For example, if you are using `bash`, run the following commands:

            1. Create the `.bash_profile` file if you do not have it already:

                ``` bash linenums="1"
                touch ${HOME}/.bash_profile
                ```

            2. Add the location of the GN tool to `.bash_profile`:

                ``` bash linenums="1"
                echo 'export PATH=${HOME}/gn:"$PATH"' >> ${HOME}/.bash_profile
                ```

                ``` bash linenums="2"
                source ${HOME}/.bash_profile
                ```

    === "Linux"

        To install the GN tool, complete the following steps:

        1. Create the directory for the GN tool:

            ``` bash linenums="1"
            mkdir ${HOME}/gn && cd ${HOME}/gn
            ```

        2. Download the GN binary archive and extract it by using the following commands:

            ``` bash linenums="1"
            wget -O gn.zip https://chrome-infra-packages.appspot.com/dl/gn/gn/linux-amd64/+/latest
            ```

            ``` bash linenums="2"
            unzip gn.zip
            ```

            ``` bash linenums="3"
            rm gn.zip
            ```

        3. Add the location of the GN tool to the system __`PATH`__. For example, if you are using `bash`, run the following commands:

            ``` bash linenums="1"
            echo 'export PATH=${HOME}/gn:"$PATH"' >> ${HOME}/.bashrc
            ```

            ``` bash linenums="2"
            source ${HOME}/.bashrc
            ```

## Install west

To manage the combination of repositories and versions, the nRF Connect SDK uses Zephyr’s [west].

To install west, reopen the command prompt window as an administrator to ensure that Python is initialized, and complete the following step:

=== "Windows"

    Enter the following command in a command-line window:

    ``` bash linenums="1"
    pip3 install west
    ```

    !!! Note
        Ensure the west location is added to the path in environmental variables.

=== "macOS"

    Enter the following command in a terminal window:

    ``` bash linenums="1"
    pip3 install west
    ```

=== "Ubuntu"

    Enter the following command in a terminal window:

    ``` bash linenums="1"
    pip3 install --user west
    ```

    ``` bash linenums="2"
    echo 'export PATH=~/.local/bin:"$PATH"' >> ~/.bashrc
    ```

    ``` bash linenums="3"
    source ~/.bashrc
    ```

## Get the code

To help you quickly build and run the samples on nRF52840 MDK USB Dongle, we maintain a public repository named [ncs-playground] which consists of nRF Connect SDK manifest repositories, additional hardware drivers and tested samples, etc.

To clone the repositories, complete the following steps:

1. Initialize the workspace folder (`my-workspace`) where all the required repositories will be cloned:

    ``` bash linenums="1"
    west init -m https://github.com/makerdiary/ncs-playground --mr main my-workspace
    ```

    !!! Tip
        You can initialize west with the revision of [ncs-playground] that you want to check out. For example, to check out the `v2.4.0` release, enter the following command:

        ``` bash linenums="1"
        west init -m https://github.com/makerdiary/ncs-playground --mr v2.4.0 my-workspace
        ```

2. Enter the following commands to clone the project repositories:

    ``` bash linenums="1"
    cd my-workspace
    ```

    ``` bash linenums="2"
    west update
    ```

    After all the repositories updated, your workspace folder now looks similar to this:

    ``` bash linenums="1"
    my-workspace
    |___ .west
    |___ bootloader
    |___ ncs-playground
    |___ modules
    |___ nrf
    |___ nrfxlib
    |___ zephyr
    |___ ...

    ``` 

3. Export a [Zephyr CMake package](https://docs.zephyrproject.org/latest/build/zephyr_cmake_package.html#cmake-pkg). This allows CMake to automatically load the boilerplate code required for building nRF Connect SDK applications:

    ``` bash linenums="1"
    west zephyr-export
    ```

## Install additional Python dependencies

The nRF Connect SDK requires additional Python packages to be installed. Use the following commands to install the requirements for each repository.

=== "Windows"

    Enter the following command in a command-line window in the `my-workspace` folder:

    ``` bash linenums="1"
    pip3 install -r zephyr/scripts/requirements.txt
    ```

    ``` bash linenums="2"
    pip3 install -r nrf/scripts/requirements.txt
    ```

    ``` bash linenums="3"
    pip3 install -r bootloader/mcuboot/scripts/requirements.txt
    ```

=== "macOS"

    Enter the following command in a terminal in the `my-workspace` folder:

    ``` bash linenums="1"
    pip3 install -r zephyr/scripts/requirements.txt
    ```

    ``` bash linenums="2"
    pip3 install -r nrf/scripts/requirements.txt
    ```

    ``` bash linenums="3"
    pip3 install -r bootloader/mcuboot/scripts/requirements.txt
    ```

=== "Ubuntu"

    Enter the following command in a terminal in the `my-workspace` folder:

    ``` bash linenums="1"
    pip3 install --user -r zephyr/scripts/requirements.txt
    ```

    ``` bash linenums="2"
    pip3 install --user -r nrf/scripts/requirements.txt
    ```

    ``` bash linenums="3"
    pip3 install --user -r bootloader/mcuboot/scripts/requirements.txt
    ```

## Install Zephyr SDK

The [Zephyr Software Development Kit (SDK)] contains toolchains for each of Zephyr’s supported architectures, which include a compiler, assembler, linker and other programs required to build Zephyr applications.

It also contains additional host tools, such as custom QEMU and OpenOCD builds that are used to emulate, flash and debug Zephyr applications.

=== "Windows"

    1. Open a `cmd.exe` window by pressing the Windows key typing `cmd.exe`.
    2. Download the [Zephyr SDK bundle]:

        ``` bash linenums="1"
        cd %HOMEPATH%
        ```

        ``` bash linenums="2"
        wget https://github.com/zephyrproject-rtos/sdk-ng/releases/download/v0.16.1/zephyr-sdk-0.16.1_windows-x86_64.7z
        ```

    3. Extract the Zephyr SDK bundle archive:

        ``` bash linenums="1"
        7z x zephyr-sdk-0.16.1_windows-x86_64.7z
        ```
    
        !!! Note
            It is recommended to extract the Zephyr SDK bundle at one of the following locations:

            - `%HOMEPATH%`
            - `%PROGRAMFILES%`

            The Zephyr SDK bundle archive contains the `zephyr-sdk-0.16.1` directory and, when extracted under `%HOMEPATH%`, the resulting installation path will be `%HOMEPATH%\zephyr-sdk-0.16.1`.

    4. Run the Zephyr SDK bundle setup script:

        ``` bash linenums="1"
        cd zephyr-sdk-0.16.1
        ```

        ``` bash linenums="2"
        setup.cmd
        ```

        !!! Note
            You only need to run the setup script once after extracting the Zephyr SDK bundle.
            
            You must rerun the setup script if you relocate the Zephyr SDK bundle directory after the initial setup.

=== "macOS"

    1. Download and verify the [Zephyr SDK bundle]:

        ``` bash linenums="1"
        cd ~
        ```

        ``` bash linenums="2"
        wget https://github.com/zephyrproject-rtos/sdk-ng/releases/download/v0.16.1/zephyr-sdk-0.16.1_macos-x86_64.tar.xz
        ```

        ``` bash linenums="3"
        wget -O - https://github.com/zephyrproject-rtos/sdk-ng/releases/download/v0.16.1/sha256.sum | shasum --check --ignore-missing
        ```

        If your host architecture is 64-bit ARM (Apple Silicon, also known as M1), replace `x86_64` with `aarch64` in order to download the 64-bit ARM macOS SDK.

    2. Extract the Zephyr SDK bundle archive:

        ``` bash linenums="1"
        tar xvf zephyr-sdk-0.16.1_macos-x86_64.tar.xz
        ```

        !!! Note
            It is recommended to extract the Zephyr SDK bundle at one of the following locations:

            - `$HOME`
            - `$HOME/.local`
            - `$HOME/.local/opt`
            - `$HOME/bin`
            - `/opt`
            - `/usr/local`

            The Zephyr SDK bundle archive contains the `zephyr-sdk-0.16.1` directory and, when extracted under `$HOME`, the resulting installation path will be `$HOME/zephyr-sdk-0.16.1`.

    3. Run the Zephyr SDK bundle setup script:

        ``` bash linenums="1"
        cd zephyr-sdk-0.16.1
        ```

        ``` bash linenums="2"
        ./setup.sh
        ```

        !!! Note
            You only need to run the setup script once after extracting the Zephyr SDK bundle.

            You must rerun the setup script if you relocate the Zephyr SDK bundle directory after the initial setup.

=== "Ubuntu"

    1. Download and verify the [Zephyr SDK bundle]:

        ``` bash linenums="1"
        cd ~
        ```

        ``` bash linenums="2"
        wget https://github.com/zephyrproject-rtos/sdk-ng/releases/download/v0.16.1/zephyr-sdk-0.16.1_linux-x86_64.tar.xz
        ```

        ``` bash linenums="3"
        wget -O - https://github.com/zephyrproject-rtos/sdk-ng/releases/download/v0.16.1/sha256.sum | shasum --check --ignore-missing
        ```

        If your host architecture is 64-bit ARM (for example, Raspberry Pi), replace `x86_64` with `aarch64` in order to download the 64-bit ARM Linux SDK.


    2. Extract the Zephyr SDK bundle archive:

        ``` bash linenums="1"
        tar xvf zephyr-sdk-0.16.1_linux-x86_64.tar.xz
        ```

        !!! Note
            It is recommended to extract the Zephyr SDK bundle at one of the following locations:

            - `$HOME`
            - `$HOME/.local`
            - `$HOME/.local/opt`
            - `$HOME/bin`
            - `/opt`
            - `/usr/local`

            The Zephyr SDK bundle archive contains the `zephyr-sdk-0.16.1` directory and, when extracted under `$HOME`, the resulting installation path will be `$HOME/zephyr-sdk-0.16.1`.

    3. Run the Zephyr SDK bundle setup script:

        ``` bash linenums="1"
        cd zephyr-sdk-0.16.1
        ```

        ``` bash linenums="2"
        ./setup.sh
        ```

        !!! Note
            You only need to run the setup script once after extracting the Zephyr SDK bundle.
            
            You must rerun the setup script if you relocate the Zephyr SDK bundle directory after the initial setup.

    4. Install [udev] rules, which allow you to flash most Zephyr boards as a regular user:

        ``` bash linenums="1"
        sudo cp ~/zephyr-sdk-0.16.1/sysroots/x86_64-pokysdk-linux/usr/share/openocd/contrib/60-openocd.rules /etc/udev/rules.d
        ```

        ``` bash linenums="2"
        sudo udevadm control --reload
        ```

[GN]: https://gn.googlesource.com/gn/
[Matter]: https://csa-iot.org/all-solutions/matter/
[CMake]: https://cmake.org/
[Python]: https://www.python.org/
[Devicetree compiler]: https://www.devicetree.org/
[Chocolatey]:https://chocolatey.org/
[Homebrew]: https://brew.sh/
[west]: https://docs.zephyrproject.org/latest/develop/west/index.html
[ncs-playground]: https://github.com/makerdiary/ncs-playground
[Zephyr Software Development Kit (SDK)]: https://docs.zephyrproject.org/latest/develop/toolchains/zephyr_sdk.html#toolchain-zephyr-sdk
[Zephyr SDK bundle]: https://github.com/zephyrproject-rtos/sdk-ng/releases/tag/v0.16.1
[udev]: https://en.wikipedia.org/wiki/Udev