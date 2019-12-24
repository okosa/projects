
 #include "stm32f10x.h"
 #include "pwm.h"
 
/**
* Name:        void clock(void)   
* Paramaters:     none
* Description:    This function configures ports A, B, C and sets system clocks for TIM4 & AFIO.
									The GPIO pins are hooked up to the sparkfun motor drive pins 
* Preconditions:  N/A 
* Postconditions:
*/
void clock(void)
{
	
	RCC->APB1ENR |=  RCC_APB1ENR_TIM4EN; //clock enable for tim4
	RCC->APB2ENR |=  RCC_APB2ENR_IOPAEN; //clock enable for port A
	RCC->APB2ENR |=  RCC_APB2ENR_IOPCEN; // CLOCK ENABLE FOR PORT C
	RCC->APB2ENR |=  RCC_APB2ENR_IOPBEN; // CLOCK ENABLE FOR PORT B
	RCC->APB2ENR |= RCC_APB2ENR_AFIOEN; // clock enable for afio
	

	
	GPIOB->CRL &= ~GPIO_CRL_MODE6 & ~GPIO_CRL_CNF6;
	  GPIOB->CRL |= GPIO_CRL_CNF6_1 | GPIO_CRL_MODE6; //PWM

	
		GPIOA->CRH |= GPIO_CRH_MODE9 | GPIO_CRH_MODE10; 
    GPIOA->CRH &= ~GPIO_CRH_CNF9 & ~GPIO_CRH_CNF10 ; // AIN2 and STBY
	
	GPIOA->CRL |= GPIO_CRL_MODE5;
  GPIOA->CRL &= ~GPIO_CRL_CNF5; //AIN1
	
	GPIOA->CRL |= GPIO_CRL_MODE6;
    GPIOA->CRL &= ~GPIO_CRL_CNF6; //BIN1
	
	GPIOA->CRH |= GPIO_CRH_MODE11;    //BIN2
    GPIOA->CRH &= ~GPIO_CRH_CNF11;
	
}

/**
* Name:           void pwm_init(void)
* Paramaters:     none
* Description:    initializes the pwm
* Preconditions:  N/A
* Postconditions:
*/
void pwm_init(void)
{
	TIM4->CR1 |= TIM_CR1_CEN;
	TIM4->CR2 |= TIM_CR2_OIS1;
	TIM4->EGR |= TIM_EGR_UG;
	
	TIM4->CCMR1 |= TIM_CCMR1_OC1M_2 | TIM_CCMR1_OC1M_1 | TIM_CCMR1_OC1PE | TIM_CCMR1_OC1FE;
	
	TIM4->CCER |= TIM_CCER_CC1E;
	TIM4->PSC = 1399;
	TIM4->ARR = 100;
	TIM4->CCR1 = 1;
	TIM4->BDTR |= TIM_BDTR_MOE | TIM_BDTR_OSSI;
	TIM4->CR1 |= TIM_CR1_ARPE | TIM_CR1_CEN;
}


	




	
	


