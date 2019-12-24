
 #include "stm32f10x.h"
 #include "Motor.h"
 #include "IO.h"
 #include "sensor.h"
 #include "LCD.h"

 /*
 * Name: void clockInit()
 * Paramaters: none
 * Description: This function will initialize the device internal
 clock to 24 Mhz
 */

 void pwm_clock(void)
 {
	 RCC->APB1ENR |= RCC_APB1ENR_TIM4EN; //clock enable for tim15
	 RCC->APB2ENR |= RCC_APB2ENR_IOPAEN | RCC_APB2ENR_IOPBEN; //clock enable for port A anb B
	 RCC->APB2ENR |= RCC_APB2ENR_AFIOEN; // clock enable for afio

	 GPIOB->CRL |= GPIO_CRL_CNF6_1 | GPIO_CRL_MODE6; //left forward6
	 GPIOB->CRL &= ~GPIO_CRL_CNF6_0;

	 GPIOB->CRL |= GPIO_CRL_CNF7_1 | GPIO_CRL_MODE7; //right forward7
	 GPIOB->CRL &= ~GPIO_CRL_CNF7_0;

	 GPIOB->CRH |= GPIO_CRH_CNF8_1 | GPIO_CRH_MODE8; //right backward
	 GPIOB->CRH &= ~GPIO_CRH_CNF8_0;

	 GPIOB->CRH |= GPIO_CRH_CNF9_1 | GPIO_CRH_MODE9; //left backward
	 GPIOB->CRH &= ~GPIO_CRH_CNF9_0;

	 RCC->APB2ENR |= RCC_APB2ENR_IOPAEN | RCC_APB2ENR_IOPBEN | RCC_APB2ENR_IOPCEN;
 }

 
 /*
 * Name: void tim4pwm_init(void)
 * Paramaters: none
 * Description: This function will initialize the pwm
 
 */
 void tim4pwm_init(void)
 {
	 TIM4->CR1 |= TIM_CR1_CEN;
	 TIM4->CR2 |= TIM_CR2_OIS1;
	 TIM4->CR2 |= TIM_CR2_OIS2;
	 TIM4->CR2 |= TIM_CR2_OIS3;
	 TIM4->CR2 |= TIM_CR2_OIS4;
	 TIM4->EGR |= TIM_EGR_UG;

	 TIM4->CCMR1 |= TIM_CCMR1_OC1M_2 | TIM_CCMR1_OC1M_1 | TIM_CCMR1_OC1PE | TIM_CCMR1_OC1FE;
	 TIM4->CCMR1 |= TIM_CCMR1_OC2M_2 | TIM_CCMR1_OC2M_1 | TIM_CCMR1_OC2PE | TIM_CCMR1_OC2FE;
	 TIM4->CCMR2 |= TIM_CCMR2_OC3M_2 | TIM_CCMR2_OC3M_1 | TIM_CCMR2_OC3PE | TIM_CCMR2_OC3FE;
	 TIM4->CCMR2 |= TIM_CCMR2_OC4M_2 | TIM_CCMR2_OC4M_1 | TIM_CCMR2_OC4PE | TIM_CCMR2_OC4FE;

	 TIM4->CCER |= TIM_CCER_CC1E;
	 TIM4->CCER |= TIM_CCER_CC2E;
	 TIM4->CCER |= TIM_CCER_CC3E;
	 TIM4->CCER |= TIM_CCER_CC4E;
	 TIM4->PSC = 2399;
	 TIM4->ARR = 100;
	 TIM4->CCR1 = 50;
	 TIM4->CCR2 = 50;
	 TIM4->CCR3 = 50;
	 TIM4->CCR4 = 50;
	 TIM4->BDTR |= TIM_BDTR_MOE | TIM_BDTR_OSSI;
	 TIM4->CR1 |= TIM_CR1_ARPE | TIM_CR1_CEN;
 }

  /*
 * Name: void move_forward(void)
 * Paramaters: none
 * Description: This function will move the robot forward
 
 */
 void move_forward(void)
 {
	 TIM4->CCR1 = 50 ;
	 TIM4->CCR2 = 0;

	 TIM4->CCR3 = 50 ;
	 TIM4->CCR4 = 0;
 }

 
  /*
 * Name: void move_back(void)
 * Paramaters: none
 * Description: This function will move the robot backwardward
 
 */
 void move_back(void)
 {
	 TIM4->CCR1 = 0;
	 TIM4->CCR2 = 50;

	 TIM4->CCR3 = 0;

	 TIM4->CCR4 = 50;
 }

  /*
 * Name: void move_right(void)
 * Paramaters: none
 * Description: This function will move the robot right
 
 */
 void move_right(void)
 {
	 TIM4->CCR1 = 50;
	TIM4->CCR2 = 0;
	 TIM4->CCR3 = 25;
	 TIM4->CCR4 = 0;
 }
  /*
 * Name: void move_right(void)
 * Paramaters: none
 * Description: This function will move the robot left
 
 */

 void move_left(void)
 {
	 TIM4->CCR1 = 25;
	 TIM4->CCR2 = 0;

	 TIM4->CCR3 = 50;
	 TIM4->CCR4 = 0;
 }

 
  /*
 * Name: void move_right(void)
 * Paramaters: none
 * Description: This function will stop the robot
 
 */
 void stop(void)
 {
	 TIM4->CCR1 = 0;
	 TIM4->CCR2 = 0;

	 TIM4->CCR3 = 0;
	 TIM4->CCR4 = 0;
 }
 
 
