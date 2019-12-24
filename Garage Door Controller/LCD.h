
#include <stdint.h>

 //Functions available for public use
 
 //Commands for Hitachi 44780 compatible LCD controllers
#define LCD_8B2L 0x38 // ; Enable 8 bit data, 2 display lines
#define LCD_DCB 0x0F // ; Enable Display, Cursor, Blink
#define LCD_MCR 0x06 // ; Set Move Cursor Right
#define LCD_CLR 0x01 // ; Home and clear LCD
#define LCD_LN1 0x80 // ;Set DDRAM to start of line 1
#define LCD_LN2 0xC0 // ; Set DDRAM to start of line 

	// Control signal manipulation for LCDs on 352/384/387 board
	// PB0:RS PB1:ENA PB5:R/W*
#define LCD_CM_ENA 0x00210002 //
#define LCD_CM_DIS 0x00230000 //
#define LCD_DM_ENA 0x00200003 //
#define LCD_DM_DIS 0x00220001 //

	// Initialize the Cortex M3 port clock using the RCC registers
	void LCD_INIT(void);
	void CMD2LCD(uint8_t data);
	void DAT2LCD(uint8_t data);
	void STR2LCD(void);
	void string2LCD(char value[]);


