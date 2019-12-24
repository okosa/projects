 #include "stm32f10x.h"
 #include "pwm.h"
 #include "motor.h"
#include "remote.h"

/**
* Name:        void pwm_clock(void)   
* Paramaters:     none
* Description:    This function initializes the timer for input capture
* Preconditions:  N/A
* Postconditions:
*/
void Tim_Init()
{

 RCC->APB2ENR |=RCC_APB2ENR_TIM1EN;
 RCC->APB2ENR|=RCC_APB2ENR_IOPAEN;

 GPIOA->CRH &= 0xFFFFFFF4; //Input digital

 TIM1->CR1 |= TIM_CR1_CEN; //counter enabled
 TIM1->CR2 |= TIM_CR2_TI1S; //TI1 selection
 TIM1->PSC = 23;
 TIM1->ARR = 65535;
 TIM1->CCMR1 |=TIM_CCMR1_CC1S_0; // Select the active input for TIMx_CCR1
 TIM1->CCER |= TIM_CCER_CC1P ; // Select the active polarity for TI1FP1
 TIM1->CCMR1 |=TIM_CCMR1_CC2S_1; //Select the active input forTIMx_CCR2:
 TIM1->CCER &= ~TIM_CCER_CC2P ; //Select the active polarity for TI1FP2
 TIM1->SMCR = 0x0050; // Select the valid trigger
 TIM1->SMCR |= TIM_SMCR_SMS_2 ; //Configure the slave mode controller in reset mode:

 TIM1->CCER |= TIM_CCER_CC1E |TIM_CCER_CC2E ; // Enable the captures:
 }

 
 /**
* Name:        void pwm_clock(void)   
* Paramaters:     none
* Description:    This function reads the width of the pulse
* Preconditions:  N/A
* Postconditions:
*/
 uint16_t width_read()
 {
	 if ((TIM1->SR & TIM_SR_CC2IF) == TIM_SR_CC2IF)
	 {
	 return TIM1->CCR2;
	 }
	 else 
		 return 0;
 }

 
 /**
* Name:        void pwm_clock(void)   
* Paramaters:     none
* Description:    This function reads the period of the pulse
* Preconditions:  N/A
* Postconditions:
*/
 uint16_t period_read()
 {
	 if ((TIM1->SR & TIM_SR_CC1IF) == TIM_SR_CC1IF)
	 {
	 return TIM1->CCR1;
	 }
	 else 
		 return 0;
	 }

/**
* Name:        void pwm_clock(void)   
* Paramaters:     none
* Description:    This function decodes the code that corresponds to the signal genertaed from the remote
* Preconditions:  N/A
* Postconditions:
*/
 uint32_t code_decode()
 {
	 uint16_t width;
	 uint16_t period;
	 uint32_t bit_code = 0x0;
	 int bit=0;
	 int bit_count=0;
	 

	 while (bit_count<32)
	 {
		 if ((TIM1->SR & TIM_SR_UIF)==TIM_SR_UIF)
		 {
			 TIM1->SR &= ~TIM_SR_UIF;
			 width=width_read();
			 period=period_read();

		 if((width!=0) ||(period !=0))
		 {
			 if ((width > 500)&&(width < 700))				//500 and 700 weere gotten from the oscilloscope
			 {
				 if ((period > 800) && (period < 1300))   //800 and 1300 were gotten from the oscilloscope
				 {
					 bit = 0;
					 bit_count++;
				 }
				 else if ((period > 1800) && (period < 2300))
				 {
					 bit = 1;
					 bit_count++;
				 }
				 bit_code = (bit_code << 1)| bit;
			 }
		 }
		 }
	 }
	 if (bit_count == 32)
	 {
		return bit_code;
	 }
	 else 
	{
		return 0;
	}
	 }

 




