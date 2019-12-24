

#include "a2d.h"
#include "registers.h"

/**
* Name:           initA2D()
* Paramaters:     none
* Description:    ADC initialization
* Preconditions:  n/a
* Postconditions: n/a
*/

void initA2D(){
	
	*regRCC_APB2ENR |= RCC_APB2ENR_IOPAEN | RCC_APB2ENR_ADC1EN;
	*regGPIOC_CRL &= ~GPIO_CRL_MODE0;
	*regGPIOC_CRL |= GPIO_CRL_CNF0_1;	
		
	*regADC1_SMPR1 |= ADC_SMPR1_SMP10_2 | ADC_SMPR1_SMP10_0; 

	*regADC1_SQR3 |= ADC_SQR3_SQ1_1 | ADC_SQR3_SQ1_3;	

	*regADC1_CR1 |= ADC_CR1_EOCIE |ADC_CR1_SCAN;	
		
	*regADC1_CR2 |= ADC_CR2_ADON | ADC_CR2_EXTTRIG | ADC_CR2_EXTSEL | ADC_CR2_SWSTART | ADC_CR2_RSTCAL;
	while ((*regADC1_CR2 & ADC_CR2_RSTCAL) == ADC_CR2_RSTCAL){}	

	*regADC1_CR2 |= 	ADC_CR2_CAL;
	while ((*regADC1_CR2 & ADC_CR2_CAL) == ADC_CR2_CAL){}		

		


	*regADC1_CR2 |= ADC_CR2_ADON | ADC_CR2_SWSTART;
	
}



/**
* Name:           uint16_t ReadA2d(int ch)
* Paramaters:     none
* Description:    returns ADC register data
* Preconditions:  n/a
* Postconditions: n/a
*/

uint16_t ReadA2d()
{
//ADC1->SQR3 = ch;
 *regADC1_CR2 |= ADC_CR2_ADON;	
 while((*regADC1_SR & ADC_SR_EOC) != ADC_SR_EOC)
 {}
	 return (*regADC1_DR);

}













