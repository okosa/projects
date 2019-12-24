
#include "lab1.h" 
#include "stm32f10x.h"
#include "pwm.h"
#include "motor.h"
 #include "remote.h"
#include <stdio.h>


int main (void) 
{ 
	uint32_t remote_code;
	clockInit();     //initialize device internal clock to 24Mhz
	clock();         // set up system clocks      
	pwm_init();
	Tim_Init();

 remote_code = 0;
 remote_code = code_decode();

	while (1) 
	{ 
		
		if ((GPIOB->IDR & GPIO_IDR_IDR8) ==0 )
		{
			motorOPEN();  //opens the garage door
		
		}
		
		 if ((GPIOB->IDR & GPIO_IDR_IDR5) ==0 )
			{
				motorOPEN();  //opens the garage door	
			}
		
		else	if ((GPIOB->IDR & GPIO_IDR_IDR9) ==0)
		{
				motorCLOSE();  //close the garage door
		} 
			
		else	if ((GPIOB->IDR & GPIO_IDR_IDR7) ==0)
		{
					motorCLOSE();  //close the garage door
		}


		
		
		if (remote_code == left_button)
			{
				motorOPEN() ;
			}	
			
		else if (remote_code == right_button) 
					{
						motorCLOSE() ;
					}





	}
}



