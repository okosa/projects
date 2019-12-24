



/******************************************************************************
 * Name:    ADC_lib.h
 * Description: STM32 peripherals initialization
 * Version: V1.00
 *
 * This software is supplied "AS IS" without warranties of any kind.
 *
 *
 *----------------------------------------------------------------------------
 * History:
 *          V1.00 Initial Version
 *          V1.1 reformatted (kjn)
 *****************************************************************************/
#include <stdint.h>

void ADC_clockInit();
void ADC_config();
void ADC_INIT();
void hex_val(uint16_t hexval);
void show_hex(uint16_t hexval);
uint16_t ADC_READ(uint32_t SQR3Value);
int resolution(uint16_t data);
void displayTemp(uint16_t temp);
void displayVolt(uint16_t volt);

