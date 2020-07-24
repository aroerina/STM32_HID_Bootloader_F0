#ifndef __CONFIG_H
#define __CONFIG_H

// USB product id =0x1209
#define		PRODUCT_ID_H		0x12
#define		PRODUCT_ID_L		0x09
// USB vendor  id =0xBEBA
#define		VENDOR_ID_H			0xBE
#define		VENDOR_ID_L			0xBA

/* Flash memory base address */
#define 	FLASH_BASE_ADDRESS	0x08000000

/* *
 * PAGE_SIZE : Flash Page size
 *  Low and MEDIUM Density STM32F0xx devices have 1 kB Flash page
 *  High Density StM32F0xx devices have 2 kB Flash page
 *
 * PAGEMIN : This should be the last page taken by the bootloader
 *  (2 * 1024) or (1 * 2048) In any case, the bootloader size is 2048 bytes
 */

#define 	BOOTLOADER_SIZE		2048
#define		PAGE_SIZE			2048
#define		MIN_PAGE		(BOOTLOADER_SIZE/PAGE_SIZE)

/* SRAM size */
#define SRAM_SIZE			(16 * 1024)

/* SRAM end (bottom of stack) */
#define SRAM_END			(SRAM_BASE + SRAM_SIZE)

/* HID Bootloader takes 2 kb flash. */
#define USER_PROGRAM			(FLASH_BASE + BOOTLOADER_SIZE)

#endif
