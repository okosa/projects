#include <stdint.h>
 
 /////////////////////////////////////////////////REMOTE CODES///////////////////////////////////////////////////////////
 #define power_button 0X10EFD827
 #define a_button 0X10EFF807
 #define b_button 0X10EF7887
 #define c_button 0X10EF58A7
 #define up_button 0X10EFA05F
 #define left_button 0X10EF10EF
 #define center_button 0X10EF20DF
 #define right_button 0X10EF807F
 #define down_button 0X10EF00FF


 void Tim_Init(void);  
 uint16_t width_read(void);
 uint16_t period_read(void);
 uint32_t code_decode(void);
 
 
 