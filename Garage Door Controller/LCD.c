

	

 #include "stm32f10x.h"
 #include "lab1.h"
 #include "LCD.h"

// CLOCK AND TIMING FUNCTIONS
/*
* Name:         void clockInit()
* Paramaters:   none
* Description: This function will initialize the device internal
               clock to 24 Mhz
*/
void LCD_INIT(void)
{
	//Enable peripheral clocks for various ports and subsystems
	//Bit 4: Port C Bit3: Port B Bit 2: Port A
	RCC->APB2ENR |=  RCC_APB2ENR_IOPAEN | RCC_APB2ENR_IOPBEN | RCC_APB2ENR_IOPCEN;		
	
	// Write a 0xB ( 1011b ) into the configuration and mode bits for PA9 (GPIO)
	GPIOB->CRL |= GPIO_CRL_MODE0 | GPIO_CRL_MODE1 | GPIO_CRL_MODE5; 
	GPIOB->CRL &= ~(GPIO_CRL_CNF0 | GPIO_CRL_CNF1 | GPIO_CRL_CNF5);
	
	GPIOC->CRL |= GPIO_CRL_MODE0 | GPIO_CRL_MODE1 | GPIO_CRL_MODE2 | GPIO_CRL_MODE3 
	| GPIO_CRL_MODE4 | GPIO_CRL_MODE5 | GPIO_CRL_MODE6 | GPIO_CRL_MODE7;
	
	GPIOC->CRL &= ~(GPIO_CRL_CNF0 | GPIO_CRL_CNF1 | GPIO_CRL_CNF2 | GPIO_CRL_CNF3 
	| GPIO_CRL_CNF4 | GPIO_CRL_CNF5 | GPIO_CRL_CNF6 | GPIO_CRL_CNF7);
	
	delay(90000);
	CMD2LCD(LCD_8B2L);
	CMD2LCD(LCD_8B2L);
	CMD2LCD(LCD_8B2L);
	CMD2LCD(LCD_8B2L);
	CMD2LCD(LCD_DCB);
	CMD2LCD(LCD_CLR);
	CMD2LCD(LCD_MCR);
}

/*
* Name: commandToLCD
* Type: PUBLIC
* Parameters: a single byte of command information for the LCD controller
* Returns: nothing
* Description: This function generates control timing and data signals to send one command byte to the LCD
*/
void CMD2LCD(uint8_t data)
{
	GPIOB->BSRR = LCD_CM_ENA; //RS low, E high
	// GPIOC->ODR = data; //BAD: may affect upper bits on port C
	GPIOC->ODR &= 0xFF00; //GOOD: clears the low bits without affecting high bits
	GPIOC->ODR |= data; //GOOD: only affects lowest 8 bits of Port C
	delay(8000);
	
	GPIOB->BSRR = LCD_CM_DIS; //RS low, E low
	delay(80000);
}

void DAT2LCD(uint8_t data)
{
	GPIOB->BSRR = LCD_DM_ENA; //RS high, E high
	// GPIOC->ODR = data; //BAD: may affect upper bits on port C
	GPIOC->ODR &= 0xFF00; //GOOD: clears the low bits without affecting high bits
	GPIOC->ODR |= data; //GOOD: only affects lowest 8 bits of Port C
	delay(8000);
	
	GPIOB->BSRR = LCD_DM_DIS; //RS low, E low
	delay(80000);
}

void STR2LCD()
{
	char switch1, switch2, switch3, switch4;
	char name[14] = "CHRISTIAN JOHN";
	char stu[9] = "200360001";
	char space = ' ';
  int i = 0;
	uint32_t switches = (((GPIOA->IDR & (GPIO_IDR_IDR6 | GPIO_IDR_IDR7)) >> 6) | ((GPIOC->IDR & (GPIO_IDR_IDR10 | GPIO_IDR_IDR11)) >> 8) 
			| ((GPIOB->IDR & (GPIO_IDR_IDR8 | GPIO_IDR_IDR9)) >> 4) | ((GPIOC->IDR & GPIO_IDR_IDR12) >> 6) | ((GPIOA->IDR & GPIO_IDR_IDR5) << 2));

	for (i = 0;i < 14; i++)
	{
		DAT2LCD(name[i]);
	}
	CMD2LCD(LCD_LN2);
	for (i = 0;i < 9; i++)
	{
		DAT2LCD(stu[i]);
	}
	
	if((switches & 0X00000001) == 0)
	{switch1 = '1';} else {switch1 ='0';}
	if((switches & 0X00000002) == 0)
	{switch2 = '1';} else {switch2 ='0';}
	if((switches & 0X00000004) == 0)
	{switch3 = '1';} else {switch3 ='0';}
	if((switches & 0X00000008) == 0)
	{switch4 = '1';} else {switch4 ='0';}

	DAT2LCD(space);
	DAT2LCD(space);
	DAT2LCD(space);
	DAT2LCD(switch1);
	DAT2LCD(switch2);
	DAT2LCD(switch3);
	DAT2LCD(switch4);
}


void string2LCD(char value[])
{
	int j;
	int lenght = strlen(value);
	for (j = 0;j < lenght; j++)
	{
		DAT2LCD(value[j]);
	}
}


