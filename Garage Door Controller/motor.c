 #include "stm32f10x.h"
 #include "pwm.h"

/**
* Name:  void motorOPEN(void)
* Paramaters:     none
* Description:    This function closes the DVD drive/ turns the motor in one direction
* Preconditions:  N/A
* Postconditions:
*/
  void motorOPEN(void)
{
	GPIOA->BSRR = 0x00000400;  // Set pin 10 (stby) to 1
  	GPIOA->BSRR = 0x00000020;  // Set PA5 (AIN1) to 1

	GPIOA->BSRR = (1 << 23);  // CLear PA9 (AIN2) to 0  
	
	
	TIM4->CCR1 = 90;  //PWM 0                                                                                                                                                                        
		
		
	}
		
	/**
* Name:  void motorOPEN(void)
* Paramaters:     none
* Description:    This function opens the DVD drive/ turns the motor in the opposite direction to motor open. 
									It has the same definition as motorOPEN, but the wriring is different. For code readability, I
									did not use the same function to open and close the garage door.
* Preconditions:  N/A
* Postconditions:
*/
void motorCLOSE(void)
{
	GPIOA->BSRR = 0x00000400;  // Set pin 10 (stby) to 1
	GPIOA->BSRR = 0x00000040;  // Set PA6 (BIN1) to 1

	GPIOA->BSRR = (1 << 21);  // CLear PA11 (BIN2) to 0  
	
	
	TIM4->CCR1 = 90;  //PWM 0                                                                                                                                                                        
		
		
	}
		
	
	
	