

	
	

/******************************************************************************
 * Name:    lab1_lib.c
 * Description: STM32 peripherals initialization and functions
 * Version: V1.00
 * Author: Dave Duguid / Trevor Douglas
 *
 * This software is supplied "AS IS" without warranties of any kind.
 *
 *
 *----------------------------------------------------------------------------
 * History:
 *          V1.00 Initial Version
 *          V1.1 reformatted (kjn)
 *****************************************************************************/
 #include "stm32f10x.h"
 #include "lab1.h"
 #include "IO.h" 


// CLOCK AND TIMING FUNCTIONS

/*
* Name:         void clockInit()
* Paramaters:   none
* Description: This function will initialize the device internal
               clock to 24 Mhz
*/
void portClockInit(void)
{
	 //Enable peripheral clocks for various ports and subsystems
    //Bit 4: Port C Bit3: Port B Bit 2: Port A
    RCC->APB2ENR |=  RCC_APB2ENR_IOPAEN | RCC_APB2ENR_IOPBEN | RCC_APB2ENR_IOPCEN;
}

void portSetup(void)
{
	// Write a 0xB ( 1011b ) into the configuration and mode bits for PA9 (GPIO)
    GPIOA->CRH |= GPIO_CRH_MODE9 | GPIO_CRH_MODE10 | GPIO_CRH_MODE11 | GPIO_CRH_MODE12; 
    GPIOA->CRH &= ~(GPIO_CRH_CNF9 | GPIO_CRH_CNF10 | GPIO_CRH_CNF11 | GPIO_CRH_CNF12);
	
	/*// FOR INPUTS
		GPIOC->CRH &= ~GPIO_CRH_MODE10 & ~GPIO_CRH_MODE11 & ~GPIO_CRH_MODE12;
		GPIOC->CRH |= ~GPIO_CRH_CNF10_0 | GPIO_CRH_CNF10_1 | ~GPIO_CRH_CNF11_0 | GPIO_CRH_CNF11_1 | ~GPIO_CRH_CNF12_0 | GPIO_CRH_CNF12_1; 
	
		GPIOB->CRH &= ~GPIO_CRH_MODE8 & ~GPIO_CRH_MODE9;
		GPIOB->CRH |= ~GPIO_CRH_CNF8_0 | GPIO_CRH_CNF8_1 | ~GPIO_CRH_CNF9_0 | GPIO_CRH_CNF9_1;
	
		GPIOA->CRL &=  ~GPIO_CRL_MODE5 & ~GPIO_CRL_MODE6 & ~GPIO_CRL_MODE7;
	  GPIOA->CRL |= ~GPIO_CRL_CNF5_0 | GPIO_CRL_CNF5_1 | ~GPIO_CRL_CNF6_0 | GPIO_CRL_CNF6_1 | ~GPIO_CRL_CNF7_0 | GPIO_CRL_CNF7_1; */
}

uint32_t switches(void){
	return (((GPIOA->IDR & (GPIO_IDR_IDR6 | GPIO_IDR_IDR7)) >> 6) | ((GPIOC->IDR & (GPIO_IDR_IDR10 | GPIO_IDR_IDR11)) >> 8) 
				| ((GPIOB->IDR & (GPIO_IDR_IDR8 | GPIO_IDR_IDR9)) >> 4) | ((GPIOC->IDR & GPIO_IDR_IDR12) >> 6) | ((GPIOA->IDR & GPIO_IDR_IDR5) << 2));
}

void led_display(void)
{
	int i = 1200000;
	
	uint32_t BOB = switches();

	if((BOB & 0X00000001) == 0)
	{
			GPIOA->BSRR = LED1_ON;
	}
	else if((BOB & 0X00000002) == 0)
	{
			GPIOA->BSRR = LED2_ON;
	}
	else if((BOB & 0X00000004) == 0)
	{
			GPIOA->BSRR = LED3_ON;
	}
	else if((BOB & 0X00000008) == 0)
	{
			GPIOA->BSRR = LED4_ON;
	}
	else
	{
			GPIOA->BSRR = LED1_OFF | LED2_OFF | LED3_OFF | LED4_OFF;
	}
	
	if((BOB & 0X00000010) == 0)
	{
			GPIOA->BSRR = LED1_ON;
			delay(i);
			GPIOA->BSRR = LED1_OFF;
			delay(i);
	}
	else if((BOB & 0X00000020) == 0)
	{
			GPIOA->BSRR = LED2_ON;
			delay(i);
			GPIOA->BSRR = LED2_OFF;
			delay(i);
	}
	else if((BOB & 0X00000040) == 0)
	{
			GPIOA->BSRR = LED3_ON;
			delay(i);
			GPIOA->BSRR = LED3_OFF;
			delay(i);
	}
	else if((BOB & 0X00000080) == 0)
	{
			GPIOA->BSRR = LED4_ON;
			delay(i);
			GPIOA->BSRR = LED4_OFF;
			delay(i);
	}
	else
	{
			GPIOA->BSRR = LED1_OFF | LED2_OFF | LED3_OFF | LED4_OFF;
	}
}




