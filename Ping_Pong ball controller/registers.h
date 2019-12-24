#ifndef REGISTERS_H
#define REGISTERS_H


#include "util.h"

typedef uint32_t volatile * const Reg32;


#define PERIPH_BASE           ((uint32_t)0x40000000)

#define AHBPERIPH_BASE        (PERIPH_BASE + 0x20000)
#define RCC_BASE              (AHBPERIPH_BASE + 0x1000)
#define RCC_APB2ENR           (RCC_BASE + 0x18)
#define RCC_APB1ENR			  (RCC_BASE + 0x1C)
#define APB2PERIPH_BASE       (PERIPH_BASE + 0x10000)
#define GPIOC_BASES           (0x40011000)
#define GPIOC_CRL             (GPIOC_BASES + 0x00)
#define GPIOB_BASE            (APB2PERIPH_BASE + 0x0C00)
#define GPIOB_ODR             (GPIOB_BASE + 0x0C)
#define GPIOB_CRH             (GPIOB_BASE + 0x04)
#define GPIOB_CRL             (GPIOB_BASE + 0x00)
#define GPIOB_BSRR            (GPIOB_BASE  + 0x10)
#define GPIOB_BRR             (GPIOB_BASE  + 0x14)
#define GPIOA_BASE	  (APB2PERIPH_BASE + 0x0800)
//#define GPIOA_BASE	  ((uint32_t)0x40010800)
#define GPIOA_CRL	  (GPIOA_BASE + 0x00)
#define GPIOA_BRR	  (GPIOA_BASE + 0x14)
#define GPIOA_BSRR	  (GPIOA_BASE + 0x10)
//#define USART2_BASE	  (APB1PERIPH_BASE + 0x4400)
#define USART2_BASES        ((uint32_t)0x40004400)
#define USART2_BRR	  (USART2_BASES + 0x08)
#define USART2_SR	  (USART2_BASES + 0x00)
#define USART2_DR	  (USART2_BASES + 0x04)
#define USART2_CR1	  (USART2_BASES + 0x0C)
#define USART2_CR2	  (USART2_BASES + 0x10)
#define USART2_CR3	  (USART2_BASES + 0x14)
#define TIM4_BASES    ((uint32_t)0x40000800)
#define TIM4_CCER     (TIM4_BASES + 0x20)
#define TIM4_CR1 			(TIM4_BASES + 0x00)
#define TIM4_EGR			(TIM4_BASES + 0x14)
#define TIM4_PSC 			(TIM4_BASES + 0x28)
#define TIM4_ARR			(TIM4_BASES + 0x2C)
#define TIM4_CCR2 		(TIM4_BASES + 0x38)
#define TIM4_CCMR1  	(TIM4_BASES + 0x18)
#define ADC1_BASES			(0x40012400)
#define ADC1_SQR3			(ADC1_BASES + 0x34)
#define ADC1_SMPR1    (ADC1_BASES + 0x0C)
#define ADC1_CR1      (ADC1_BASES + 0x04)
#define ADC1_CR2      (ADC1_BASES + 0x08)
#define ADC1_DR      (ADC1_BASES + 0x4C)
#define ADC1_SR      (ADC1_BASES + 0x00)


extern Reg32 regRCC_APB1ENR;
extern Reg32 regRCC_APB2ENR;
extern Reg32 regGPIOC_CRL;
extern Reg32 regGPIOB_ODR; 
extern Reg32 regGPIOB_CRH;
extern Reg32 regGPIOB_BSRR; 
extern Reg32 regGPIOB_BRR;
extern Reg32 regGPIOB_CRL;
extern Reg32 regGPIOA_CRL;
extern Reg32 regGPIOA_BSRR; 
extern Reg32 regGPIOA_BSR;
extern Reg32 regUSART2_BRR; 
extern Reg32 regUSART2_SR;
extern Reg32 regUSART2_DR;
extern Reg32 regUSART2_CR1;
extern Reg32 regUSART2_CR2;
extern Reg32 regUSART2_CR3;
extern Reg32 regTIM4_CCER;
extern Reg32 regTIM4_CR1; 
extern Reg32 regTIM4_EGR; 
extern Reg32 regTIM4_PSC; 
extern Reg32 regTIM4_ARR; 
extern Reg32 regTIM4_CCR2; 
extern Reg32 regTIM4_CCMR1; 
extern Reg32 regADC1_SQR3;
extern Reg32 regADC1_SMPR1;
extern Reg32 regADC1_CR1;
extern Reg32 regADC1_CR2;
extern Reg32 regADC1_DR;
extern Reg32 regADC1_SR;

#endif      
