
 #include "stm32f10x.h"
 #include "Motor.h"
 #include "IO.h"
 #include "sensor.h"
 

 uint16_t left_sensor(void)
 {
 if((GPIOB->IDR & GPIO_IDR_IDR12) == 0)
 { return 0xFFFF;}
 else
 { return 0x0000;}
 }

 uint16_t right_sensor(void)
 {
 if((GPIOB->IDR & GPIO_IDR_IDR13) == 0)
 { return 0xFFFF; }
 else
 { return 0x0000; }
 }
