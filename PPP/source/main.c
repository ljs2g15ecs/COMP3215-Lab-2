/*
 * main.c
 *
 *  Created on: 26 Nov 2017
 *      Author: lewis
 */

/*
 * Copyright (c) 2016, NXP Semiconductor, Inc.
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without modification,
 * are permitted provided that the following conditions are met:
 *
 * o Redistributions of source code must retain the above copyright notice, this list
 *   of conditions and the following disclaimer.
 *
 * o Redistributions in binary form must reproduce the above copyright notice, this
 *   list of conditions and the following disclaimer in the documentation and/or
 *   other materials provided with the distribution.
 *
 * o Neither the name of NXP Semiconductor, Inc. nor the names of its
 *   contributors may be used to endorse or promote products derived from this
 *   software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND
 * ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
 * WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
 * DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE FOR
 * ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
 * (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
 * LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON
 * ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
 * SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */

/**
 * @file    PPP.c
 * @brief   Application entry point.
 */
#include <stdio.h>
#include "board.h"
#include "pin_mux.h"
#include "clock_config.h"
#include "MKW41Z4.h"
#include "fsl_debug_console.h"

/* TODO: insert other include files here. */
#include "fsl_lpuart.h"
#include "fsl_gpio.h"
#include "PPP.h"

/* TODO: insert other definitions and declarations here. */

uint8_t data;
uint8_t newData;
uint8_t ONLINE[] = "\r\nONLINE\r\n";

GPIO_Type		*led_gpio[]	=	{	GPIOA,	GPIOA,	GPIOC,	GPIOB	};
uint32_t		led_pins[]	=	{	18,		19,		1,		0		};

void	LPUART0_IRQHandler(void)
{
	/* If new data arrived. */
	///*
	if ((kLPUART_RxDataRegFullFlag)&LPUART_GetStatusFlags(LPUART0))
	{
		/*
		data = LPUART_ReadByte(LPUART0);
		newData = 1;
		//*/

		//
		data = LPUART_ReadByte(LPUART0);
		if(data == 0x7E)		newData = 2;
		else if(data == 0x20)	newData = 3;
		else					newData = 1;
		//
	}
	//*/
	//pppReceiveHandler();
}
/*
 * @brief   Application entry point.
 */
int main(void) {

	/* Init board hardware. */
    BOARD_InitBootPins();
    BOARD_InitBootClocks();

    lpuart_config_t config;
	LPUART_GetDefaultConfig(&config);
	config.baudRate_Bps = BOARD_DEBUG_UART_BAUDRATE;
	config.enableTx = true;
	config.enableRx = true;
	LPUART_Init(LPUART0, &config, CLOCK_GetFreq(kCLOCK_CoreSysClk));
	CLOCK_SetLpuartClock(0x1U);

	LPUART_EnableInterrupts(LPUART0, kLPUART_RxDataRegFullInterruptEnable);
	EnableIRQ(LPUART0_IRQn);

	static const 	gpio_pin_config_t led_conf =
	{
		kGPIO_DigitalOutput,		//	OUTPUT
		1,							//	HIGH INITIAL VALUE
	};

	/* Force the counter to be placed into memory. */
	volatile uint8_t i = 0;
	for(i=0; i<4; i++)				GPIO_PinInit(led_gpio[i], led_pins[i], &led_conf);

    /* Enter an infinite loop, just incrementing a counter. */
    for(i=0;;i++)
    {

    	switch(newData)
    	{
    		case 0:
    			break;
    		case 1:
				LPUART_WriteByte(LPUART0, data);
				newData = 0;
				break;
    		case 2:
    			LPUART_WriteBlocking(LPUART0, ONLINE, sizeof(ONLINE));
    			newData = 0;
    			break;
    		case 3:
    			GPIO_TogglePinsOutput(GPIOB, (1 << led_pins[3]));
    			newData = 0;
    			break;
    		default:
    			break;
    	}
    	//
    }

	/*
	pppInitStruct();
	while(1)
	{
		waitForPcConnectString(); // wait for PC to send a connect message
		while( connectedPpp() ) {
			waitForPppFrame(); // process PPP frames until we receive a disconnect command
		}
	}
	//*/
    return 0;
}

