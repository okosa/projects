


#include <stdint.h>
#include "stm32f10x.h"
#include "lab1.h"

//Bit masks for leds on STM32VLDiscovery board PC8 and PC9 using GPIOC_BSRR
// Green LED is on bit 9 of port C, Blue LED is on bit 8.
 #define GREEN_ON	0X00000200 //
 #define GREEN_OFF	0x02000000 //
 #define BLUE_ON	0x00000100 //
 #define BLUE_OFF	0x01000000 //
 
 #define LED1_OFF	0X00000200 //
 #define LED1_ON	0x02000000 //
 #define LED2_OFF	0x00000400 //
 #define LED2_ON	0x04000000 //
 #define LED3_OFF	0X00000800 //
 #define LED3_ON	0x08000000 //
 #define LED4_OFF	0x00001000 //
 #define LED4_ON	0x10000000 //

	// Initialize the Cortex M3 port clock using the RCC registers
	void portClockInit(void);
	// Port Setup
	void portSetup(void);
	void led_display(void);
	uint32_t switches(void);


