#include "PWM.h"
#include "registers.h"
#include "stm32f10x.h"


void timer_init(void){
	
			*regRCC_APB1ENR |=  RCC_APB1ENR_TIM4EN; //clock enable for tim4
		*regRCC_APB2ENR |=  RCC_APB2ENR_IOPBEN |RCC_APB2ENR_AFIOEN;  // CLOCK ENABLE FOR PORT B and  clock enable for afio
			*regGPIOB_CRL |=GPIO_CRL_MODE7|GPIO_CRL_CNF7_1;
	*regGPIOB_CRL   &=	~GPIO_CRL_CNF7_0;

 
	*regTIM4_CR1 |= TIM_CR1_CEN;
	*regTIM4_EGR |= TIM_EGR_UG;
*regTIM4_CCMR1 |= TIM_CCMR1_OC2M_1 |TIM_CCMR1_OC2M_2 | TIM_CCMR1_OC2PE |TIM_CCMR1_OC2FE; 
 *regTIM4_CCER |=  TIM_CCER_CC2E;
 
	*regTIM4_PSC = 72;
	*regTIM4_ARR = 20000;
	*regTIM4_CCR2 = 0;
	

	

	*regTIM4_EGR |= TIM_EGR_UG;
}
	

void changeDC(int num){
	*regTIM4_CCR2 = num;
 *regGPIOB_ODR ^= GPIO_ODR_ODR8;
}
