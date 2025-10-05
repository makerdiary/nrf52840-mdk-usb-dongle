# Copyright (c) 2016-2025 Makerdiary <https://makerdiary.com>
# SPDX-License-Identifier: Apache-2.0

board_runner_args(uf2 "--board-id=nRF52840-MDK-USB-Dongle")
board_runner_args(pyocd "--target=nrf52840" "--frequency=4000000")
include(${ZEPHYR_BASE}/boards/common/uf2.board.cmake)
include(${ZEPHYR_BASE}/boards/common/pyocd.board.cmake)
include(${ZEPHYR_BASE}/boards/common/openocd-nrf5.board.cmake)
