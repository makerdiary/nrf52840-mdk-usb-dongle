/*
 * Copyright (c) 2012-2014 Wind River Systems, Inc.
 * Copyright (c) 2016-2025, Makerdiary
 *
 * SPDX-License-Identifier: Apache-2.0
 */

 #include <stdio.h>
 #include <zephyr/kernel.h>
 
 int main(void)
 {
	 while (1)
	 {
		 printk("[%" PRIu32 "] Hello World! %s\n", k_uptime_seconds(), CONFIG_BOARD_TARGET);
		 k_msleep(1000);
	 }
 
	 return 0;
 }
