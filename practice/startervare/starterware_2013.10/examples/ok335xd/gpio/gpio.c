/* 
 * \file   gpioLEDBlink.c
 *
 * \brief  This application uses a GPIO pin to control the blinking of
 *         an LED present on the baseboard.
 */

/*
* Copyright (C) 2010 Texas Instruments Incorporated - http://www.ti.com/ 
*/
/* 
*  Redistribution and use in source and binary forms, with or without 
*  modification, are permitted provided that the following conditions 
*  are met:
*
*    Redistributions of source code must retain the above copyright 
*    notice, this list of conditions and the following disclaimer.
*
*    Redistributions in binary form must reproduce the above copyright
*    notice, this list of conditions and the following disclaimer in the 
*    documentation and/or other materials provided with the   
*    distribution.
*
*    Neither the name of Texas Instruments Incorporated nor the names of
*    its contributors may be used to endorse or promote products derived
*    from this software without specific prior written permission.
*
*  THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS 
*  "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT 
*  LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
*  A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT 
*  OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, 
*  SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT 
*  LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
*  DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
*  THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT 
*  (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE 
*  OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
*
*/


#include "soc_AM335x.h"
#include "evmskAM335x.h"
#include "gpio_v2.h"


/*****************************************************************************
**                INTERNAL MACRO DEFINITIONS
*****************************************************************************/
#define GPIO_INSTANCE_ADDRESS           (SOC_GPIO_1_REGS)
#define GPIO_INSTANCE_PIN_NUMBER(i)        (i + 16)

/*****************************************************************************
**                INTERNAL FUNCTION PROTOTYPES
*****************************************************************************/
static void Delay(unsigned int count);

/*****************************************************************************
**                INTERNAL FUNCTION DEFINITIONS
*****************************************************************************/
/*
** The main function. Application starts here.
*/
int main()
{
	unsigned int  i = 0;

    unsigned int count=0;
   	UARTPuts("UART START GPIO!!!!!!\n", -1);
    /* Enabling functional clocks for GPIO1 instance. */
    GPIO1ModuleClkConfig();

    /* Selecting GPIO1[16] pin for use. */
    GPIO1Pin16PinMuxSetup();
	
	/* Selecting GPIO1[17] pin for use. */
    GPIO1Pin17PinMuxSetup();

	/* Selecting GPIO1[18] pin for use. */
    GPIO1Pin18PinMuxSetup();
	
	/* Selecting GPIO1[19] pin for use. */
    GPIO1Pin19PinMuxSetup();
	
    /* Enabling the GPIO module. */
    GPIOModuleEnable(GPIO_INSTANCE_ADDRESS);

    /* Resetting the GPIO module. */
    GPIOModuleReset(GPIO_INSTANCE_ADDRESS);
	for(i = 0;i < 4;i++)
	{
    	/* Setting the GPIO pin as an output pin. */
    	GPIODirModeSet(GPIO_INSTANCE_ADDRESS,GPIO_INSTANCE_PIN_NUMBER(i),GPIO_DIR_OUTPUT);
	}
  	UARTPuts("StarterWareGPIO \r\n", -1);//modified by wcl

    while(1)
    {
        
		for(i = 0;i < 4;i++)
		{
		/* Driving a logic HIGH on the GPIO pin. */
        GPIOPinWrite(GPIO_INSTANCE_ADDRESS,
                     GPIO_INSTANCE_PIN_NUMBER(i),
                     GPIO_PIN_HIGH);
		}

   		Delay(5000000);
    
		for(i = 0;i < 4;i++)
		{
        /* Driving a logic LOW on the GPIO pin. */
        GPIOPinWrite(GPIO_INSTANCE_ADDRESS,
                     GPIO_INSTANCE_PIN_NUMBER(i),
                     GPIO_PIN_LOW);
		}
    	Delay(5000000);   
    	UARTPuts(" led \r\n", -1);//modified by wcl
    }

} 

/*
** A function which is used to generate a delay.
*/
static void Delay(volatile unsigned int count)
{
    while(count--);
}


/******************************* End of file *********************************/
