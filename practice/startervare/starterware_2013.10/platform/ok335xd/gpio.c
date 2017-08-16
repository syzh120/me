/**
 * \file   pio.c
 *
 * \brief  This file contains functions which performs the platform specific
 *         configurations of GPIO.
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


#include "hw_control_AM335x.h"
#include "evmskAM335x.h"
#include "soc_AM335x.h"
#include "hw_cm_wkup.h"
#include "hw_cm_per.h"
#include "hw_types.h"
#include "gpio_v2.h"

/**
 * \brief  This function does the Pin Multiplexing and selects GPIO0[2]
 *         for use. By GPIO0[2], we mean 2nd pin of GPIO0 instance.
 *
 * \param  None
 *
 * \return none
 */


unsigned int GPIO1Pin16PinMuxSetup(void)
{
	    HWREG(SOC_CONTROL_REGS + CONTROL_CONF_GPMC_A(0)) = (CONTROL_CONF_GPMC_A0_CONF_GPMC_A0_PUDEN |
															CONTROL_CONF_GPMC_A0_CONF_GPMC_A0_RXACTIVE | 
															CONTROL_CONF_MUXMODE(7));
	    
	  
}
unsigned int GPIO1Pin17PinMuxSetup(void)
{
	    HWREG(SOC_CONTROL_REGS + CONTROL_CONF_GPMC_A(1)) = (CONTROL_CONF_GPMC_A1_CONF_GPMC_A1_PUDEN |
															CONTROL_CONF_GPMC_A1_CONF_GPMC_A1_RXACTIVE | 
															CONTROL_CONF_MUXMODE(7));
	    
	  
}
unsigned int GPIO1Pin18PinMuxSetup(void)
{
	    HWREG(SOC_CONTROL_REGS + CONTROL_CONF_GPMC_A(2)) = (CONTROL_CONF_GPMC_A2_CONF_GPMC_A2_PUDEN |
															CONTROL_CONF_GPMC_A2_CONF_GPMC_A2_RXACTIVE | 
															CONTROL_CONF_MUXMODE(7));
	    
	  
}
unsigned int GPIO1Pin19PinMuxSetup(void)
{
	    HWREG(SOC_CONTROL_REGS + CONTROL_CONF_GPMC_A(3)) = (CONTROL_CONF_GPMC_A3_CONF_GPMC_A3_PUDEN |
															CONTROL_CONF_GPMC_A3_CONF_GPMC_A3_RXACTIVE | 
															CONTROL_CONF_MUXMODE(7));
	    
	  
}




void GPIO0Pin2PinMuxSetup(void)
{
    HWREG(SOC_CONTROL_REGS + CONTROL_CONF_SPI0_SCLK) = 
                   ((CONTROL_CONF_SPI0_SCLK_CONF_SPI0_SCLK_RXACTIVE |
		     CONTROL_CONF_SPI0_SCLK_CONF_SPI0_SCLK_PUDEN    |
		     CONTROL_CONF_MUXMODE(7)) & 
                     (~CONTROL_CONF_SPI0_SCLK_CONF_SPI0_SCLK_PUTYPESEL));
}

/**
 * \brief  This function does the Pin Multiplexing and selects GPIO1[2]
 *         for use. By GPIO1[2], we mean 2nd pin of GPIO1 instance.
 *
 * \param  None
 *
 * \return none
 */
void GPIO1Pin2PinMuxSetup(void)
{
    HWREG(SOC_CONTROL_REGS + CONTROL_CONF_GPMC_AD(2)) = 
		    ((CONTROL_CONF_GPMC_AD_CONF_GPMC_AD_RXACTIVE |
		      CONTROL_CONF_GPMC_AD_CONF_GPMC_AD_PUDEN    |
		      CONTROL_CONF_MUXMODE(7)) & 
                      (~CONTROL_CONF_GPMC_AD_CONF_GPMC_AD_PUTYPESEL));
}

/**
 * \brief  This function does the Pin Multiplexing and selects GPIO pin
 *         GPIO1[30] for use. GPIO1[30] means 30th pin of GPIO1 instance.
 *         This pin can be used to enable backlight.
 *
 * \param  None
 *
 */
void GPIO1Pin29PinMuxSetup(void)
{
    HWREG(SOC_CONTROL_REGS + CONTROL_CONF_GPMC_CSN(0)) =
         (CONTROL_CONF_GPMC_CSN0_CONF_GPMC_CSN0_PUTYPESEL |
         CONTROL_CONF_MUXMODE(7));
}

/**
 * \brief  This function does the Pin Multiplexing and selects GPIO pin
 *         GPIO1[4] for use. GPIO1[4] means 4th pin of GPIO1 instance.
 *         This pin can be used to toggle User Led 4.
 *
 * \param  None
 *
 */
void GPIO1Pin4PinMuxSetup(void)
{
    HWREG(SOC_CONTROL_REGS + CONTROL_CONF_GPMC_AD(4)) = 
         (CONTROL_CONF_GPMC_AD4_CONF_GPMC_AD4_RXACTIVE |
          CONTROL_CONF_MUXMODE(7));

}

/**
 * \brief  This function does the Pin Multiplexing for the GPIO pin GPIO0[7]
 *         i.e. 7th pin of GPIO0 instance and selects it for use.
 *
 * \param  None
 *
 * \return TRUE/FALSE
 *
 */

unsigned int GPIO0Pin7PinMuxSetup(void)
{
    unsigned int profile = 0;
    unsigned int status = FALSE;



	 HWREG(SOC_CONTROL_REGS + CONTROL_CONF_ECAP0_IN_PWM0_OUT) =	
                (CONTROL_CONF_ECAP0_IN_PWM0_OUT_CONF_ECAP0_IN_PWM0_OUT_RXACTIVE |
                 CONTROL_CONF_MUXMODE(7));
     status = TRUE;
#if 0
    profile = EVMProfileGet(); 

    switch(profile)
    {
        /* Fall through for cases 0, 1, and 2. */
        case 0:
        case 1:
        case 2:
        case 7:
            HWREG(SOC_CONTROL_REGS + CONTROL_CONF_ECAP0_IN_PWM0_OUT) =	
                (CONTROL_CONF_ECAP0_IN_PWM0_OUT_CONF_ECAP0_IN_PWM0_OUT_RXACTIVE |
                 CONTROL_CONF_MUXMODE(7));
            status = TRUE;
        break;

        /* Fall through for cases 3, 4, 5 and 6. */
        case 3:
        case 4:
        case 5:
        case 6:
        default:
        break;
    }
#endif
    return status;
}



/*
** This function enables the functional clocks for GPIO0 instance.
*/
void GPIO0ModuleClkConfig(void)
{
    /* Writing to MODULEMODE field of CM_WKUP_GPIO0_CLKCTRL register. */
    HWREG(SOC_CM_WKUP_REGS + CM_WKUP_GPIO0_CLKCTRL) |=
        CM_WKUP_GPIO0_CLKCTRL_MODULEMODE_ENABLE;

    /* Waiting for MODULEMODE field to reflect the written value. */
    while(CM_WKUP_GPIO0_CLKCTRL_MODULEMODE_ENABLE !=
          (HWREG(SOC_CM_WKUP_REGS + CM_WKUP_GPIO0_CLKCTRL) &
           CM_WKUP_GPIO0_CLKCTRL_MODULEMODE));

    /*
    ** Writing to OPTFCLKEN_GPIO0_GDBCLK field of CM_WKUP_GPIO0_CLKCTRL
    ** register.
    */
    HWREG(SOC_CM_WKUP_REGS + CM_WKUP_GPIO0_CLKCTRL) |=
        CM_WKUP_GPIO0_CLKCTRL_OPTFCLKEN_GPIO0_GDBCLK;

    /* Waiting for OPTFCLKEN_GPIO0_GDBCLK field to reflect the written value. */
    while(CM_WKUP_GPIO0_CLKCTRL_OPTFCLKEN_GPIO0_GDBCLK !=
          (HWREG(SOC_CM_WKUP_REGS + CM_WKUP_GPIO0_CLKCTRL) &
           CM_WKUP_GPIO0_CLKCTRL_OPTFCLKEN_GPIO0_GDBCLK));

    /* Writing to IDLEST field in CM_WKUP_GPIO0_CLKCTRL register. */
    while((CM_WKUP_GPIO0_CLKCTRL_IDLEST_FUNC <<
           CM_WKUP_GPIO0_CLKCTRL_IDLEST_SHIFT) !=
          (HWREG(SOC_CM_WKUP_REGS + CM_WKUP_GPIO0_CLKCTRL) &
           CM_WKUP_GPIO0_CLKCTRL_IDLEST));

    /*
    ** Waiting for CLKACTIVITY_GPIO0_GDBCLK field in CM_WKUP_GPIO0_CLKCTRL
    ** register to attain desired value.
    */
    while(CM_WKUP_CLKSTCTRL_CLKACTIVITY_GPIO0_GDBCLK !=
          (HWREG(SOC_CM_WKUP_REGS + CM_WKUP_CLKSTCTRL) &
           CM_WKUP_CLKSTCTRL_CLKACTIVITY_GPIO0_GDBCLK));
}

/*
** This function enables the functional clocks for GPIO1 instance.
*/
void GPIO1ModuleClkConfig(void)
{
    /* Writing to MODULEMODE field of CM_PER_GPIO1_CLKCTRL register. */
    HWREG(SOC_CM_PER_REGS + CM_PER_GPIO1_CLKCTRL) |=
          CM_PER_GPIO1_CLKCTRL_MODULEMODE_ENABLE;

    /* Waiting for MODULEMODE field to reflect the written value. */
    while(CM_PER_GPIO1_CLKCTRL_MODULEMODE_ENABLE !=
          (HWREG(SOC_CM_PER_REGS + CM_PER_GPIO1_CLKCTRL) &
           CM_PER_GPIO1_CLKCTRL_MODULEMODE));
    /*
    ** Writing to OPTFCLKEN_GPIO_1_GDBCLK bit in CM_PER_GPIO1_CLKCTRL
    ** register.
    */
    HWREG(SOC_CM_PER_REGS + CM_PER_GPIO1_CLKCTRL) |=
          CM_PER_GPIO1_CLKCTRL_OPTFCLKEN_GPIO_1_GDBCLK;

    /*
    ** Waiting for OPTFCLKEN_GPIO_1_GDBCLK bit to reflect the desired
    ** value.
    */
    while(CM_PER_GPIO1_CLKCTRL_OPTFCLKEN_GPIO_1_GDBCLK !=
          (HWREG(SOC_CM_PER_REGS + CM_PER_GPIO1_CLKCTRL) &
           CM_PER_GPIO1_CLKCTRL_OPTFCLKEN_GPIO_1_GDBCLK));

    /*
    ** Waiting for IDLEST field in CM_PER_GPIO1_CLKCTRL register to attain the
    ** desired value.
    */
    while((CM_PER_GPIO1_CLKCTRL_IDLEST_FUNC <<
           CM_PER_GPIO1_CLKCTRL_IDLEST_SHIFT) !=
           (HWREG(SOC_CM_PER_REGS + CM_PER_GPIO1_CLKCTRL) &
            CM_PER_GPIO1_CLKCTRL_IDLEST));

    /*
    ** Waiting for CLKACTIVITY_GPIO_1_GDBCLK bit in CM_PER_L4LS_CLKSTCTRL
    ** register to attain desired value.
    */
    while(CM_PER_L4LS_CLKSTCTRL_CLKACTIVITY_GPIO_1_GDBCLK !=
          (HWREG(SOC_CM_PER_REGS + CM_PER_L4LS_CLKSTCTRL) &
           CM_PER_L4LS_CLKSTCTRL_CLKACTIVITY_GPIO_1_GDBCLK));
}

/* Enable module clock to 3rd instance of GPIO */
void GPIO3ModuleClkConfig(void)
{
    /* Writing to MODULEMODE field of CM_PER_GPIO3_CLKCTRL register. */
    HWREG(SOC_CM_PER_REGS + CM_PER_GPIO3_CLKCTRL) =
          CM_PER_GPIO3_CLKCTRL_MODULEMODE_ENABLE;

    /* Waiting for MODULEMODE field to reflect the written value. */
    while(CM_PER_GPIO3_CLKCTRL_MODULEMODE_ENABLE !=
         (HWREG(SOC_CM_PER_REGS + CM_PER_GPIO3_CLKCTRL) &
          CM_PER_GPIO3_CLKCTRL_MODULEMODE));

    /*
    ** Writing to OPTFCLKEN_GPIO_3_GDBCLK bit in CM_PER_GPIO3_CLKCTRL
    ** register.
    */
    HWREG(SOC_CM_PER_REGS + CM_PER_GPIO3_CLKCTRL) |=
          CM_PER_GPIO3_CLKCTRL_OPTFCLKEN_GPIO_3_GDBCLK;

    /*
    ** Waiting for OPTFCLKEN_GPIO_3_GDBCLK bit to reflect the desired
    ** value.
    */
    while(CM_PER_GPIO3_CLKCTRL_OPTFCLKEN_GPIO_3_GDBCLK !=
          (HWREG(SOC_CM_PER_REGS + CM_PER_GPIO3_CLKCTRL) &
           CM_PER_GPIO3_CLKCTRL_OPTFCLKEN_GPIO_3_GDBCLK));

}

/*
** This function enables GPIO1 pins
*/
unsigned int GPIO1PinMuxSetup(unsigned int pinNo)
{
    HWREG(SOC_CONTROL_REGS + CONTROL_CONF_GPMC_AD(pinNo)) =
        (CONTROL_CONF_GPMC_AD_CONF_GPMC_AD_SLEWCTRL |     /* Slew rate slow */
        CONTROL_CONF_GPMC_AD_CONF_GPMC_AD_RXACTIVE |    /* Receiver enabled */
        (CONTROL_CONF_GPMC_AD_CONF_GPMC_AD_PUDEN & (~CONTROL_CONF_GPMC_AD_CONF_GPMC_AD_PUDEN)) | /* PU_PD enabled */
        (CONTROL_CONF_GPMC_AD_CONF_GPMC_AD_PUTYPESEL & (~CONTROL_CONF_GPMC_AD_CONF_GPMC_AD_PUTYPESEL)) | /* PD */
        (CONTROL_CONF_MUXMODE(7))    /* Select mode 7 */
        );
     return TRUE;
}

/**
 * \brief  This function does the pin multiplexing for any GPIO Pin.
 *
 * \param  offsetAddr   This is the offset address of the Pad Control Register
 *                      corresponding to the GPIO pin. These addresses are
 *                      offsets with respect to the base address of the
 *                      Control Module.
 * \param  padConfValue This is the value to be written to the Pad Control
 *                      register whose offset address is given by 'offsetAddr'.
 *
 * The 'offsetAddr' and 'padConfValue' can be obtained from macros defined
 * in the file 'include/armv7a/am335x/pin_mux.h'.\n
 *
 * \return  None.
 */
void GpioPinMuxSetup(unsigned int offsetAddr, unsigned int padConfValue)
{
    HWREG(SOC_CONTROL_REGS + offsetAddr) = (padConfValue);
}

/****************************** End of file *********************************/