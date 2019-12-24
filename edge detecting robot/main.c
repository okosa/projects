
 #include "stm32f10x.h"
  #include "LCD.h"
 #include "motor.h"
 #include "IO.h"
 #include "sensor.h"


 int main (void) {

 clockInit();
 pwm_clock();
 tim4pwm_init();
 

 while(1)
{
	 int i = 12000000;
	 int u = 1200000;
	 if((GPIOC->IDR & GPIO_IDR_IDR12) == 0) //if blue button is pushed, start moving forward
	 {
	
	 delay(u);
	 move_forward();

 }
 else if ((GPIOA->IDR & GPIO_IDR_IDR15) == 0 )
 {
	 move_back();
	 delay(i);
	 move_left();
 }
 else if((left_sensor() == 0x0000))
 {
	 
	 move_back();
	 delay(u);
	 move_right();
 }
 else if((right_sensor() == 0x0000))
 {
 
	 move_back();
	 delay(u);
	 move_left();
 }
 else if ((GPIOA->IDR & GPIO_IDR_IDR5) == 0) //if green button is pushed, stop
 {
	 stop();
	
 }
 }
}
