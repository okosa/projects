
	


 #include "stm32f10x.h"
 #include "interrupt.h"

void interruptSetup(void)
{
	RCC->APB2ENR |=  RCC_APB2ENR_IOPCEN;
	
	GPIOC->CRH |= GPIO_CRH_MODE8 | GPIO_CRH_MODE9; 
	GPIOC->CRH &= ~(GPIO_CRH_CNF8 | GPIO_CRH_CNF9);
}

void systick(void)
{
	SysTick->CTRL = 0x00;
	SysTick->VAL = 0x00;
	SysTick->LOAD = 0x016E3600;
	SysTick->CTRL = 0x07;
}

void interruptInit(void)
{
	//ENABLE AFIO CLOCK 
	RCC->APB2ENR |= RCC_APB2ENR_AFIOEN;
	//CHOOSE PORT A
	AFIO->EXTICR[0] &= ~AFIO_EXTICR1_EXTI0;
	//UNMASK PA8
	EXTI->IMR |= EXTI_IMR_MR8;
	//SELECT FALLING EDGE
	EXTI->FTSR |= EXTI_FTSR_TR0;
	//UNMASK EXTI0
	NVIC->ISER[0] |= NVIC_ISER_SETENA_6;
}



