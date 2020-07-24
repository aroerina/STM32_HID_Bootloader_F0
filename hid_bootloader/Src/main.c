/*
* STM32 HID Bootloader - USB HID bootloader for STM32F0xx
* Copyright (c) 2018 Bruno Freitas - bruno@brunofreitas.com
*
* This program is free software: you can redistribute it and/or modify
* it under the terms of the GNU General Public License as published by
* the Free Software Foundation, either version 3 of the License, or
* (at your option) any later version.
*
* This program is distributed in the hope that it will be useful,
* but WITHOUT ANY WARRANTY; without even the implied warranty of
* MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
* GNU General Public License for more details.
*
* You should have received a copy of the GNU General Public License
* along with this program.  If not, see <http://www.gnu.org/licenses/>.
*
* Modified 20 April 2018
*	by Vassilis Serasidis <info@serasidis.gr>
*	This HID bootloader works with STM32F103 + STM32duino + Arduino IDE <http://www.stm32duino.com/>
*
* Modified January 2019
*	by Michel Stempin <michel.stempin@wanadoo.fr>
*	Cleanup and optimizations
*
* Modified July 2020
*	by Yoshio Nomura <@aroerina2 on twitter>
*	Ported for STM32F0xx series
*/

#include <stm32f0xx.h>
#include <stdbool.h>
#include "usb.h"
#include "config.h"
#include "hid.h"

/* Initial stack pointer index in vector table*/
#define INITIAL_MSP			0

/* Reset handler index in vector table*/
#define RESET_HANDLER			1

#define MAGIC_WORD				0xDEADBEEF

/* Simple function pointer type to call user program */
typedef void (*funct_ptr)(void);

/* The bootloader entry point function prototype */
void Reset_Handler(void);

/* Minimal initial Flash-based vector table */
uint32_t *VectorTable[] __attribute__((section(".isr_vector"))) = {

	/* Initial stack pointer (MSP) */
	(uint32_t *) SRAM_END,

	/* Initial program counter (PC): Reset handler */
	(uint32_t *) Reset_Handler
};

/* Bootloader and UserApp shared memory */
uint32_t shared_mem __attribute__((section (".SharedSection")));

static bool check_user_code(uint32_t user_address)
{
	uint32_t sp = *(volatile uint32_t *) user_address;

	/* Check if the stack pointer in the vector table points
	   somewhere in SRAM */
	return ((sp & 0x2FFE0000) == SRAM_BASE) ? true : false;
}

static void set_sysclock_to_48_mhz(void)
{
	/* Enable Prefetch Buffer & set Flash access to 1 wait states */
	SET_BIT(FLASH->ACR, FLASH_ACR_PRFTBE | FLASH_ACR_LATENCY);

	SET_BIT(RCC->CR2,RCC_CR2_HSI48ON);

	/* Wait until HSI48 is ready */
	while (READ_BIT(RCC->CR2, RCC_CR2_HSI48RDY) == 0) {
		;
	}

	/* Select HSI48 as system clock source */
	SET_BIT(RCC->CFGR, RCC_CFGR_SW_HSI48);

	/* Wait until HSI48 is used as system clock source */
	while (READ_BIT(RCC->CFGR, RCC_CFGR_SWS_HSI48) == 0) {
		;
	}
}

void Reset_Handler(void)
{
	/* Setup the system clock (System clock source and Flash settings)
	 */
	set_sysclock_to_48_mhz();

	UploadStarted = false;
	UploadFinished = false;
	funct_ptr UserProgram = (funct_ptr) *(volatile uint32_t *) (USER_PROGRAM + 0x04);

	/* If:
	 *  - no User Code is uploaded to the MCU
	 *  - Shared memory value matched magic word
	 * then enter HID bootloader...
	 */
	if (check_user_code(USER_PROGRAM) == false || shared_mem == MAGIC_WORD) {

		USB_Shutdown();
		USB_Init();

		while(1){
			USB_Handler();
		}

	}

	/* Setup the stack pointer to the user-defined one */
	__set_MSP((*(volatile uint32_t *) USER_PROGRAM));

	/* Jump to the user firmware entry point */
	UserProgram();

	/* Never reached */
	for (;;) {
		;
	}
}
