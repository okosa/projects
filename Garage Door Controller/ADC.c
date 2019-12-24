

	
	
	

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
 #include "ADC.h" 
 #include "LCD.h"
// CLOCK AND TIMING FUNCTIONS

/*
* Name:         void ADC_INIT()
* Paramaters:   none
* Description: This function will initialize the ADC 
*/
void ADC_clockInit()
{
	 RCC->APB2ENR |=  RCC_APB2ENR_IOPAEN | RCC_APB2ENR_ADC1EN;
}
	
void ADC_config()
{
	  GPIOA->CRL &= ~(GPIO_CRL_MODE1 | GPIO_CRL_MODE2); 
    GPIOA->CRL &= ~(GPIO_CRL_CNF1 | GPIO_CRL_CNF2);
}
	
void ADC_INIT()
{
	ADC1->CR2 |= ADC_CR2_CAL | ADC_CR2_ADON;
	//ADC1->CR2 |= ~ADC_CR2_ALIGN;
	ADC1->SMPR2 |= ADC_SMPR2_SMP1 | ADC_SMPR2_SMP2;
	ADC1->SQR3 &= ~ADC_SQR3_SQ1;
}

uint16_t ADC_READ(uint32_t SQR3Value)
{
	uint16_t data;
	
	ADC1->SQR3 = SQR3Value;
	ADC1->CR2 |= ADC_CR2_ADON;
	
	while ((ADC1->SR & ADC_SR_EOC) != ADC_SR_EOC ) 
	{}
	data = (ADC1->DR & ADC_DR_DATA);
	
	return data;
}

void hex_val(uint16_t hexval)
{
 if (hexval < 0x0A){DAT2LCD(0x30 + hexval);}
 else {DAT2LCD(0x41 + (hexval - 0x0A));}
}

void show_hex(uint16_t hexval)
{
  DAT2LCD(0x30);
	DAT2LCD(0x78);
	DAT2LCD(0x30);
	DAT2LCD(0x30);
	DAT2LCD(0x30);
	DAT2LCD(0x30);
	hex_val((hexval & 0xF000)>> 12 );
	hex_val((hexval & 0xF00)>> 8 );
	hex_val((hexval & 0xF0)>> 4 );
	hex_val((hexval & 0xF));
}

int resolution(uint16_t data)
{
	return data*0.8;
}

void displayTemp(uint16_t temp)
{
	uint16_t tempDecimal = temp;
	tempDecimal = tempDecimal% 1000;
	DAT2LCD(0x30 + (tempDecimal/100));
	
	tempDecimal = tempDecimal% 100;
	DAT2LCD(0x30 + (tempDecimal/10));
	
	tempDecimal = tempDecimal % 10;
	DAT2LCD('.');
	DAT2LCD(0x30 + tempDecimal);
	DAT2LCD('C');
}

void displayVolt(uint16_t volt)
{
	uint16_t tempVolts = volt;
	tempVolts = tempVolts% 10000;
	DAT2LCD(0x30 + (tempVolts/1000));
	DAT2LCD('.');
	tempVolts = tempVolts% 1000;
	
	DAT2LCD(0x30 + (tempVolts/100));
	
	tempVolts = tempVolts % 100;
	
	DAT2LCD(0x30 + (tempVolts/10));
	DAT2LCD('V');
}


