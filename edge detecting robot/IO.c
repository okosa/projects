#include "stm32f10x.h"
 #include "Motor.h"
 #include "IO.h"
 #include "sensor.h"


 // CLOCK AND TIMING FUNCTIONS

 /*
 * Name: void clockInit()
 * Paramaters: none
 * Description: This function will initialize the device internal
 clock to 24 Mhz
 */

 void clockInit(void)
 {
 uint32_t temp = 0x00;
 //If you hover over the RCC you can go to the definition and then
 //see it is a structure of all the RCC registers. Then you can
 //simply assign a value.
 RCC->CFGR = 0x00050002; // Output PLL/2 as MCO,
 // PLLMUL X3, PREDIV1 is PLL input

 RCC->CR = 0x01010081; // Turn on PLL, HSE, HSI

 while (temp != 0x02000000) // Wait for the PLL to stabilize
 {
 temp = RCC->CR & 0x02000000; //Check to see if the PLL lock bit is set
 }
 }
 
 
 
 /*
 * Name: void portclockInit()
 * Paramaters: none
 * Description: This function will configure ports A, B and C
 */
 void portClockInit(void)
 {
 //Enable peripheral clocks for various ports and subsystems
 RCC->APB2ENR |= RCC_APB2ENR_IOPAEN | RCC_APB2ENR_IOPBEN | RCC_APB2ENR_IOPCEN;
 }
 
 /*
 * Name: void delay()
 * Paramaters: none
 * Description: This function will delay
 */
 void delay(uint32_t count)
{
 int i=0;
 for(i=0; i< count; ++i)
 {
 }
}
 
 
 