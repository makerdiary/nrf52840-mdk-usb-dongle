PROJECT_NAME     := thread_cli_ftd_nrf52840_mdk_usb_dongle
TARGETS          := nrf52840_xxaa
OUTPUT_DIRECTORY := _build
FW_VERSION_MAJOR := 1
FW_VERSION_MINOR := 4
FW_VERSION_PATCH := 0
FW_VERSION       := $(FW_VERSION_MAJOR).$(FW_VERSION_MINOR).$(FW_VERSION_PATCH)

MDK_ROOT := ../../../..
SDK_ROOT := $(MDK_ROOT)/nrf_sdks/nRF5_SDK_for_Thread_and_Zigbee_v4.1.0_32ce5f8
PROJ_DIR := ..

$(OUTPUT_DIRECTORY)/nrf52840_xxaa.out: \
	LINKER_SCRIPT  := thread_cli_ftd_usb_gcc_nrf52.ld

# Source files common to all targets
SRC_FILES += \
	$(SDK_ROOT)/modules/nrfx/mdk/gcc_startup_nrf52840.S \
	$(SDK_ROOT)/components/boards/boards.c \
	$(SDK_ROOT)/components/libraries/log/src/nrf_log_backend_rtt.c \
	$(SDK_ROOT)/components/libraries/log/src/nrf_log_backend_serial.c \
	$(SDK_ROOT)/components/libraries/log/src/nrf_log_default_backends.c \
	$(SDK_ROOT)/components/libraries/log/src/nrf_log_frontend.c \
	$(SDK_ROOT)/components/libraries/log/src/nrf_log_str_formatter.c \
	$(SDK_ROOT)/components/libraries/button/app_button.c \
	$(SDK_ROOT)/components/libraries/util/app_error.c \
	$(SDK_ROOT)/components/libraries/util/app_error_handler_gcc.c \
	$(SDK_ROOT)/components/libraries/util/app_error_weak.c \
	$(SDK_ROOT)/components/libraries/scheduler/app_scheduler.c \
	$(SDK_ROOT)/components/libraries/timer/app_timer2.c \
	$(SDK_ROOT)/components/libraries/usbd/app_usbd.c \
	$(SDK_ROOT)/components/libraries/usbd/class/cdc/acm/app_usbd_cdc_acm.c \
	$(SDK_ROOT)/components/libraries/usbd/app_usbd_core.c \
	$(SDK_ROOT)/components/libraries/usbd/app_usbd_serial_num.c \
	$(SDK_ROOT)/components/libraries/usbd/app_usbd_string_desc.c \
	$(SDK_ROOT)/components/libraries/util/app_util_platform.c \
	$(SDK_ROOT)/components/libraries/assert/assert.c \
	$(SDK_ROOT)/components/libraries/timer/drv_rtc.c \
	$(SDK_ROOT)/components/libraries/mem_manager/mem_manager.c \
	$(SDK_ROOT)/components/libraries/util/nrf_assert.c \
	$(SDK_ROOT)/components/libraries/atomic_fifo/nrf_atfifo.c \
	$(SDK_ROOT)/components/libraries/atomic/nrf_atomic.c \
	$(SDK_ROOT)/components/libraries/balloc/nrf_balloc.c \
	$(SDK_ROOT)/external/fprintf/nrf_fprintf.c \
	$(SDK_ROOT)/external/fprintf/nrf_fprintf_format.c \
	$(SDK_ROOT)/components/libraries/memobj/nrf_memobj.c \
	$(SDK_ROOT)/components/libraries/pwr_mgmt/nrf_pwr_mgmt.c \
	$(SDK_ROOT)/components/libraries/ringbuf/nrf_ringbuf.c \
	$(SDK_ROOT)/components/libraries/experimental_section_vars/nrf_section_iter.c \
	$(SDK_ROOT)/components/libraries/sortlist/nrf_sortlist.c \
	$(SDK_ROOT)/components/libraries/strerror/nrf_strerror.c \
	$(SDK_ROOT)/integration/nrfx/legacy/nrf_drv_clock.c \
	$(SDK_ROOT)/integration/nrfx/legacy/nrf_drv_power.c \
	$(SDK_ROOT)/components/drivers_nrf/nrf_soc_nosd/nrf_nvic.c \
	$(SDK_ROOT)/modules/nrfx/hal/nrf_nvmc.c \
	$(SDK_ROOT)/components/drivers_nrf/nrf_soc_nosd/nrf_soc.c \
	$(SDK_ROOT)/modules/nrfx/soc/nrfx_atomic.c \
	$(SDK_ROOT)/modules/nrfx/drivers/src/nrfx_clock.c \
	$(SDK_ROOT)/modules/nrfx/drivers/src/nrfx_gpiote.c \
	$(SDK_ROOT)/modules/nrfx/drivers/src/nrfx_nvmc.c \
	$(SDK_ROOT)/modules/nrfx/drivers/src/nrfx_power.c \
	$(SDK_ROOT)/modules/nrfx/drivers/src/nrfx_systick.c \
	$(SDK_ROOT)/modules/nrfx/drivers/src/nrfx_usbd.c \
	$(SDK_ROOT)/components/libraries/bsp/bsp.c \
	$(SDK_ROOT)/components/libraries/bsp/bsp_thread.c \
	$(SDK_ROOT)/external/paho/mqtt-sn/mqttsn_packet/MQTTSNConnectClient.c \
	$(SDK_ROOT)/external/paho/mqtt-sn/mqttsn_packet/MQTTSNConnectServer.c \
	$(SDK_ROOT)/external/paho/mqtt-sn/mqttsn_packet/MQTTSNDeserializePublish.c \
	$(SDK_ROOT)/external/paho/mqtt-sn/mqttsn_packet/MQTTSNPacket.c \
	$(SDK_ROOT)/external/paho/mqtt-sn/mqttsn_packet/MQTTSNSearchClient.c \
	$(SDK_ROOT)/external/paho/mqtt-sn/mqttsn_packet/MQTTSNSearchServer.c \
	$(SDK_ROOT)/external/paho/mqtt-sn/mqttsn_packet/MQTTSNSerializePublish.c \
	$(SDK_ROOT)/external/paho/mqtt-sn/mqttsn_packet/MQTTSNSubscribeClient.c \
	$(SDK_ROOT)/external/paho/mqtt-sn/mqttsn_packet/MQTTSNSubscribeServer.c \
	$(SDK_ROOT)/external/paho/mqtt-sn/mqttsn_packet/MQTTSNUnsubscribeClient.c \
	$(SDK_ROOT)/external/paho/mqtt-sn/mqttsn_packet/MQTTSNUnsubscribeServer.c \
	$(SDK_ROOT)/modules/nrfx/soc/nrfx_atomic.c \
	$(SDK_ROOT)/modules/nrfx/drivers/src/nrfx_timer.c \
	$(SDK_ROOT)/modules/nrfx/drivers/src/nrfx_saadc.c \
	$(SDK_ROOT)/modules/nrfx/drivers/src/nrfx_ppi.c \
	$(SDK_ROOT)/integration/nrfx/legacy/nrf_drv_ppi.c \
	$(PROJ_DIR)/../main.c \
	$(SDK_ROOT)/external/segger_rtt/SEGGER_RTT.c \
	$(SDK_ROOT)/external/segger_rtt/SEGGER_RTT_Syscalls_GCC.c \
	$(SDK_ROOT)/external/segger_rtt/SEGGER_RTT_printf.c \
	$(SDK_ROOT)/modules/nrfx/mdk/system_nrf52840.c \
	$(SDK_ROOT)/external/utf_converter/utf.c \
	$(SDK_ROOT)/components/thread/utils/thread_utils.c \
	$(SDK_ROOT)/components/thread/mqtt_sn/mqtt_sn_client/mqttsn_client.c \
	$(SDK_ROOT)/components/thread/mqtt_sn/mqtt_sn_client/mqttsn_gateway_discovery.c \
	$(SDK_ROOT)/components/thread/mqtt_sn/mqtt_sn_client/mqttsn_packet_fifo.c \
	$(SDK_ROOT)/components/thread/mqtt_sn/mqtt_sn_client/mqttsn_packet_receiver.c \
	$(SDK_ROOT)/components/thread/mqtt_sn/mqtt_sn_client/mqttsn_packet_sender.c \
	$(SDK_ROOT)/components/thread/mqtt_sn/mqtt_sn_client/mqttsn_platform.c \
	$(SDK_ROOT)/components/thread/mqtt_sn/mqtt_sn_client/mqttsn_transport_ot.c \

# Include folders common to all targets
INC_FOLDERS += \
	$(SDK_ROOT)/external/openthread/project/config \
	$(SDK_ROOT)/external/utf_converter \
	$(SDK_ROOT)/external/nrf_security/config \
	$(SDK_ROOT)/components/libraries/usbd/class/cdc/acm \
	$(SDK_ROOT)/integration/nrfx \
	$(PROJ_DIR) \
	$(SDK_ROOT)/external/openthread/project/nrf52840 \
	$(SDK_ROOT)/external/nrf_security/include \
	$(SDK_ROOT)/components/thread/utils \
	$(SDK_ROOT)/components/libraries/log/src \
	$(SDK_ROOT)/components/libraries/scheduler \
	$(MDK_ROOT)/config \
	$(PROJ_DIR)/config \
	$(SDK_ROOT)/components/libraries/experimental_section_vars \
	$(SDK_ROOT)/components/libraries/atomic_fifo \
	$(SDK_ROOT)/external/nRF-IEEE-802.15.4-radio-driver/src/fem \
	$(SDK_ROOT)/components/softdevice/mbr/headers \
	$(SDK_ROOT)/modules/nrfx/mdk \
	$(SDK_ROOT)/external/paho/mqtt-sn/mqttsn_packet \
	$(SDK_ROOT)/components/thread/mqtt_sn/mqtt_sn_client \
	$(SDK_ROOT)/external/nrf_security/nrf_cc310_plat/include \
	$(SDK_ROOT)/components/libraries/strerror \
	$(SDK_ROOT)/integration/nrfx/legacy \
	$(SDK_ROOT)/components/boards \
	$(SDK_ROOT)/components/drivers_nrf/nrf_soc_nosd \
	$(SDK_ROOT)/components/libraries/usbd/class/cdc \
	$(SDK_ROOT)/components/libraries/button \
	$(SDK_ROOT)/components/libraries/log \
	$(SDK_ROOT)/modules/nrfx/hal \
	$(SDK_ROOT)/components/libraries/mem_manager \
	$(SDK_ROOT)/components/libraries/bsp \
	$(SDK_ROOT)/components/libraries/sortlist \
	$(SDK_ROOT)/modules/nrfx/drivers/include \
	$(SDK_ROOT)/components/libraries/ringbuf \
	$(SDK_ROOT)/external/fprintf \
	$(SDK_ROOT)/components/libraries/balloc \
	$(SDK_ROOT)/components/libraries/util \
	$(SDK_ROOT)/modules/nrfx \
	$(SDK_ROOT)/external/openthread/include \
	$(SDK_ROOT)/components \
	$(SDK_ROOT)/external/segger_rtt \
	$(SDK_ROOT)/components/libraries/memobj \
	$(SDK_ROOT)/external/nRF-IEEE-802.15.4-radio-driver/src/fem/three_pin_gpio \
	$(SDK_ROOT)/components/libraries/usbd \
	$(SDK_ROOT)/components/libraries/atomic \
	$(SDK_ROOT)/components/libraries/delay \
	$(SDK_ROOT)/components/toolchain/cmsis/include \
	$(SDK_ROOT)/external/nrf_security/mbedtls_plat_config \
	$(SDK_ROOT)/components/libraries/mutex \
	$(SDK_ROOT)/components/libraries/pwr_mgmt \
	$(SDK_ROOT)/components/libraries/timer \

# Libraries common to all targets
LIB_FILES += \
	$(SDK_ROOT)/external/openthread/lib/nrf52840/gcc/libopenthread-cli-ftd.a \
	$(SDK_ROOT)/external/openthread/lib/nrf52840/gcc/libopenthread-ftd.a \
	$(SDK_ROOT)/external/openthread/lib/nrf52840/gcc/libopenthread-nrf52840-transport-usb.a \
	$(SDK_ROOT)/external/openthread/lib/nrf52840/gcc/libopenthread-platform-utils.a \
	$(SDK_ROOT)/external/nrf_security/lib/libmbedcrypto_glue.a \
	$(SDK_ROOT)/external/nrf_security/lib/libmbedcrypto_glue_cc310.a \
	$(SDK_ROOT)/external/nrf_security/lib/libmbedcrypto_glue_vanilla.a \
	$(SDK_ROOT)/external/nrf_security/lib/libmbedcrypto_vanilla_backend.a \
	$(SDK_ROOT)/external/nrf_security/lib/libmbedtls_tls_vanilla.a \
	$(SDK_ROOT)/external/nrf_security/lib/libmbedtls_x509_vanilla.a \
	$(SDK_ROOT)/external/nrf_security/lib/libnrf_cc310_platform_0.9.2.a \
	$(SDK_ROOT)/external/openthread/lib/nrf52840/gcc/libopenthread-nrf52840-sdk.a \
	$(SDK_ROOT)/external/nrf_security/lib/libmbedcrypto_cc310_backend.a \
	$(SDK_ROOT)/external/nrf_security/lib/libmbedcrypto_glue.a \
	$(SDK_ROOT)/external/nrf_security/lib/libmbedcrypto_glue_cc310.a \
	$(SDK_ROOT)/external/nrf_security/lib/libmbedcrypto_glue_vanilla.a \
	$(SDK_ROOT)/external/nrf_security/lib/libmbedtls_base_vanilla.a \
	$(SDK_ROOT)/external/openthread/lib/nrf52840/gcc/libnordicsemi-nrf52840-radio-driver.a \
	$(SDK_ROOT)/external/nrf_security/lib/libmbedcrypto_cc310_backend.a \
	$(SDK_ROOT)/external/nrf_security/lib/libmbedcrypto_vanilla_backend.a \
	$(SDK_ROOT)/external/openthread/lib/nrf52840/gcc/libopenthread-nrf52840-transport-usb.a \
	$(SDK_ROOT)/external/openthread/lib/nrf52840/gcc/libopenthread-platform-utils.a \
	$(SDK_ROOT)/external/nrf_security/lib/libmbedtls_base_vanilla.a \
	$(SDK_ROOT)/external/nrf_security/lib/libmbedtls_tls_vanilla.a \
	$(SDK_ROOT)/external/nrf_security/lib/libmbedtls_x509_vanilla.a \
	$(SDK_ROOT)/external/nrf_security/lib/libnrf_cc310_platform_0.9.2.a \
	$(SDK_ROOT)/external/openthread/lib/nrf52840/gcc/libopenthread-ftd.a \

# Optimization flags
OPT = -O3 -g3
# Uncomment the line below to enable link time optimization
#OPT += -flto

# C flags common to all targets
CFLAGS += $(OPT)
CFLAGS += -DAPP_TIMER_V2
CFLAGS += -DAPP_TIMER_V2_RTC1_ENABLED
CFLAGS += -DBOARD_CUSTOM
CFLAGS += -DNRF52840_MDK_USB_DONGLE
#CFLAGS += -DCONFIG_GPIO_AS_PINRESET
CFLAGS += -DENABLE_FEM
CFLAGS += -DFLOAT_ABI_HARD
CFLAGS += -DMBEDTLS_CONFIG_FILE=\"nrf-config.h\"
CFLAGS += -DMBEDTLS_USER_CONFIG_FILE=\"nrf52840-mbedtls-config.h\"
CFLAGS += -DMBR_PRESENT
CFLAGS += -DNRF52840_XXAA
CFLAGS += -DOPENTHREAD_CONFIG_ENABLE_BUILTIN_MBEDTLS=0
CFLAGS += -DOPENTHREAD_CONFIG_FILE=\"openthread-config-wrap.h\"
CFLAGS += -DOPENTHREAD_FTD=1
CFLAGS += -DUSBD_POWER_DETECTION=1
CFLAGS += -mcpu=cortex-m4
CFLAGS += -mthumb -mabi=aapcs
CFLAGS += -Wall -Werror
CFLAGS += -mfloat-abi=hard -mfpu=fpv4-sp-d16
# keep every function in a separate section, this allows linker to discard unused ones
CFLAGS += -ffunction-sections -fdata-sections -fno-strict-aliasing
CFLAGS += -fno-builtin -fshort-enums

# C++ flags common to all targets
CXXFLAGS += $(OPT)
# Assembler flags common to all targets
ASMFLAGS += -g3
ASMFLAGS += -mcpu=cortex-m4
ASMFLAGS += -mthumb -mabi=aapcs
ASMFLAGS += -mfloat-abi=hard -mfpu=fpv4-sp-d16
ASMFLAGS += -DAPP_TIMER_V2
ASMFLAGS += -DAPP_TIMER_V2_RTC1_ENABLED
ASMFLAGS += -DBOARD_CUSTOM
ASMFLAGS += -DNRF52840_MDK_USB_DONGLE
#ASMFLAGS += -DCONFIG_GPIO_AS_PINRESET
ASMFLAGS += -DENABLE_FEM
ASMFLAGS += -DFLOAT_ABI_HARD
ASMFLAGS += -DMBR_PRESENT
ASMFLAGS += -DNRF52840_XXAA
ASMFLAGS += -DOPENTHREAD_FTD=1
ASMFLAGS += -DUSBD_POWER_DETECTION=1

# Linker flags
LDFLAGS += $(OPT)
LDFLAGS += -mthumb -mabi=aapcs -L$(SDK_ROOT)/modules/nrfx/mdk -T$(LINKER_SCRIPT)
LDFLAGS += -mcpu=cortex-m4
LDFLAGS += -mfloat-abi=hard -mfpu=fpv4-sp-d16
# let linker dump unused sections
LDFLAGS += -Wl,--gc-sections
# use newlib in nano version
LDFLAGS += --specs=nano.specs

nrf52840_xxaa: CFLAGS += -D__HEAP_SIZE=0
nrf52840_xxaa: CFLAGS += -D__STACK_SIZE=8192
nrf52840_xxaa: ASMFLAGS += -D__HEAP_SIZE=0
nrf52840_xxaa: ASMFLAGS += -D__STACK_SIZE=8192

# Add standard libraries at the very end of the linker input, after all objects
# that may need symbols provided by these libraries.
LIB_FILES += -lc -lnosys -lm -lstdc++


.PHONY: default help

# Default target - first one defined
default: nrf52840_xxaa

# Print all targets that can be built
help:
	@echo following targets are available:
	@echo		nrf52840_xxaa
	@echo		flash_mbr
	@echo		sdk_config - starting external tool for editing sdk_config.h
	@echo		flash      - flashing binary

TEMPLATE_PATH := $(SDK_ROOT)/components/toolchain/gcc


include $(TEMPLATE_PATH)/Makefile.common

$(foreach target, $(TARGETS), $(call define_target, $(target)))

.PHONY: flash erase pkg copy

# Flash the program
flash: default
	@echo Flashing: $(OUTPUT_DIRECTORY)/nrf52840_xxaa.hex
	pyocd flash -t nrf52840 $(OUTPUT_DIRECTORY)/nrf52840_xxaa.hex

erase:
	pyocd erase -t nrf52840 --chip

# Generate DFU package
pkg: default
	@echo Generating DFU package using nrfutil...
	nrfutil pkg generate --hw-version 52 --sd-req 0 --application-version ${FW_VERSION_MAJOR}${FW_VERSION_MINOR}${FW_VERSION_PATCH} --application $(OUTPUT_DIRECTORY)/nrf52840_xxaa.hex $(OUTPUT_DIRECTORY)/nrf52840_xxaa.zip

# Copy firmware and package
copy: pkg
	@echo Copying firmware and package...
	cp $(OUTPUT_DIRECTORY)/nrf52840_xxaa.hex $(PROJ_DIR)/hex/$(PROJECT_NAME)_v$(FW_VERSION).hex
	cp $(OUTPUT_DIRECTORY)/nrf52840_xxaa.zip $(PROJ_DIR)/hex/$(PROJECT_NAME)_v$(FW_VERSION).zip

SDK_CONFIG_FILE := $(PROJ_DIR)/config/sdk_config.h
CMSIS_CONFIG_TOOL := $(SDK_ROOT)/external_tools/cmsisconfig/CMSIS_Configuration_Wizard.jar
sdk_config:
	java -jar $(CMSIS_CONFIG_TOOL) $(SDK_CONFIG_FILE)
