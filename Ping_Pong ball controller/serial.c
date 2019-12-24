

#include "serial.h"
#include "registers.h"

/**
* Name:           void usart_init()
* Paramaters:     none
* Description:    This function configures USART2
* Preconditions:  stm32f10x.h is included in project
* Postconditions: 
*/
void serial_open()
{
	
*regRCC_APB1ENR |= RCC_APB1ENR_USART2EN;
*regRCC_APB2ENR  |=RCC_APB2ENR_IOPAEN|RCC_APB2ENR_AFIOEN;

*regGPIOA_CRL|=	GPIO_CRL_MODE2|GPIO_CRL_CNF2_1|GPIO_CRL_CNF3_0;
*regGPIOA_CRL &=	~GPIO_CRL_CNF2_0 & ~GPIO_CRL_MODE3;	

*regUSART2_CR1 |= USART_CR1_UE;
*regUSART2_BRR =((unsigned int)(72000000/(16*9600))) << 3;
*regUSART2_CR1|=USART_CR1_TE |USART_CR1_RE;
*regUSART2_CR1 &= ~USART_CR1_OVER8 & ~USART_CR1_M & ~USART_CR1_PCE;
*regUSART2_CR2 &= ~USART_CR2_STOP;	
	
}

void sendbyte(uint16_t data){
		while(( *regUSART2_SR & USART_SR_TXE)!= USART_SR_TXE)       //Wait for the TxE bit in USART2_SR to be 1
  { };
	*regUSART2_DR = data;
}

/**
* Name:           getbyte
* Paramaters:     None
* Description:    This function reads from serial interface
* Preconditions:  stm32f10x.h is included in project
* Postconditions: 
*/



char getbyte(void){
	while(( *regUSART2_SR & USART_SR_RXNE)!= USART_SR_RXNE)       
  { };
	return *regUSART2_DR ;
}
