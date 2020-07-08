; GPIO Test program - 

;;; Directives
            PRESERVE8
            THUMB       

        		 
;;; Equates

INITIAL_MSP	EQU		0x20001000	; Initial Main Stack Pointer Value


;PORT A GPIO - Base Addr: 0x40010800
GPIOA_CRL	EQU		0x40010800	; (0x00) Port Configuration Register for Px7 -> Px0
GPIOA_CRH	EQU		0x40010804	; (0x04) Port Configuration Register for Px15 -> Px8
GPIOA_IDR	EQU		0x40010808	; (0x08) Port Input Data Register
GPIOA_ODR	EQU		0x4001080C	; (0x0C) Port Output Data Register
GPIOA_BSRR	EQU		0x40010810	; (0x10) Port Bit Set/Reset Register
GPIOA_BRR	EQU		0x40010814	; (0x14) Port Bit Reset Register
GPIOA_LCKR	EQU		0x40010818	; (0x18) Port Configuration Lock Register

;PORT B GPIO - Base Addr: 0x40010C00
GPIOB_CRL	EQU		0x40010C00	; (0x00) Port Configuration Register for Px7 -> Px0
GPIOB_CRH	EQU		0x40010C04	; (0x04) Port Configuration Register for Px15 -> Px8
GPIOB_IDR	EQU		0x40010C08	; (0x08) Port Input Data Register
GPIOB_ODR	EQU		0x40010C0C	; (0x0C) Port Output Data Register
GPIOB_BSRR	EQU		0x40010C10	; (0x10) Port Bit Set/Reset Register
GPIOB_BRR	EQU		0x40010C14	; (0x14) Port Bit Reset Register
GPIOB_LCKR	EQU		0x40010C18	; (0x18) Port Configuration Lock Register

;The onboard LEDS are on port C bits 8 and 9
;PORT C GPIO - Base Addr: 0x40011000
GPIOC_CRL	EQU		0x40011000	; (0x00) Port Configuration Register for Px7 -> Px0
GPIOC_CRH	EQU		0x40011004	; (0x04) Port Configuration Register for Px15 -> Px8
GPIOC_IDR	EQU		0x40011008	; (0x08) Port Input Data Register
GPIOC_ODR	EQU		0x4001100C	; (0x0C) Port Output Data Register
GPIOC_BSRR	EQU		0x40011010	; (0x10) Port Bit Set/Reset Register
GPIOC_BRR	EQU		0x40011014	; (0x14) Port Bit Reset Register
GPIOC_LCKR	EQU		0x40011018	; (0x18) Port Configuration Lock Register

;Registers for configuring and enabling the clocks
;RCC Registers - Base Addr: 0x40021000
RCC_CR		EQU		0x40021000	; Clock Control Register
RCC_CFGR	EQU		0x40021004	; Clock Configuration Register
RCC_CIR		EQU		0x40021008	; Clock Interrupt Register
RCC_APB2RSTR	EQU	0x4002100C	; APB2 Peripheral Reset Register
RCC_APB1RSTR	EQU	0x40021010	; APB1 Peripheral Reset Register
RCC_AHBENR	EQU		0x40021014	; AHB Peripheral Clock Enable Register

RCC_APB2ENR	EQU		0x40021018	; APB2 Peripheral Clock Enable Register  -- Used

RCC_APB1ENR	EQU		0x4002101C	; APB1 Peripheral Clock Enable Register
RCC_BDCR	EQU		0x40021020	; Backup Domain Control Register
RCC_CSR		EQU		0x40021024	; Control/Status Register
RCC_CFGR2	EQU		0x4002102C	; Clock Configuration Register 2

; Times for delay routines
        
DELAYTIME	EQU		1000000; (200 ms/24MHz PLL)
SECOND_DELAY EQU 	5000000
FIRST_MOLE_SPEED_DELAY EQU 2000000
; Vector Table Mapped to Address 0 at Reset
            AREA    RESET, Data, READONLY
            EXPORT  __Vectors

__Vectors	DCD		INITIAL_MSP			; stack pointer value when stack is empty
        	DCD		Reset_Handler		; reset vector
			
            AREA    MYCODE, CODE, READONLY
			EXPORT	Reset_Handler
			ENTRY
			
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;;; UC1 and UC2 (Reset_Handler)
;;; Require:
;;; R3: loaded with a DELAYTIME value
;;; R6: loaded with a SECOND_DELAY value
;;; R4: loaded with a value of zero
;;; 4 LEDS
;;;	The Reset_handler provides the intially LED lighting by turning the LEDS on in a pattern
;;; and keeps them on in a loop (Blink_Leds)
;;;
Reset_Handler		PROC
	
	;port and Led initialization
	BL GPIO_ClockInit
	BL GPIO_init
		
		
	
	BL Turn_Off_Leds; Function to Turn OFF all LEDs before the game begins
    LDR R3, =DELAYTIME
	LDR R6, = SECOND_DELAY
    LDR R4, =0x0 
	
;loop to keep the LEDs blinking
Blink_Leds
    BL R_On; Branch to turn the Red Led on     
    BL B_On; Branch to turn the Black Led on   
    BL Bl_On; Branch to turn the Blue Led on    
    BL G_On; Branch to turn the Green Led on	
    LDR R4, =0x0    
    BL UC2_Delay; The wait the happens before the game starts    
	BL Check_Input; a function call to check when a button has been pressed
    BL Turn_Off_Leds
    LDR R4, =0x0    
    BL UC2_Delay;   
   
    B Blink_Leds
    ENDP

;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;;; UC1 and UC2 (Waiting for Players)
;;; Notes:
;;; these are subroutines specifically designed to turn on the LEDs
;;; from the Reset_Handler

R_On
    LDR R0, =GPIOA_ODR
    LDR R1, [R0]
    LDR R2, =0xFFFFFDFF
    AND R1, R1, R2; 1101 1111 1111
    STR R1, [R0]
    BX LR

B_On
    LDR R0, =GPIOA_ODR
    LDR R1, [R0]
    LDR R2, =0xFFFFFBFF
    AND R1, R1, R2; 1011 1111 1111
    STR R1, [R0]
    BX LR
	
Bl_On
    LDR R0, =GPIOA_ODR
    LDR R1, [R0]
    LDR R2, =0xFFFFF7FF
    AND R1, R1, R2; 0111 1111 1111
    STR R1, [R0]
    BX LR

G_On
    LDR R0, =GPIOA_ODR
    LDR R1, [R0]
    LDR R2, =0xFFFFEFFF
    AND R1, R1, R2; 1110 1111 1111 1111
    STR R1, [R0]
    BX LR
	
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;;; UC1 and UC2 (Waiting for Players)
;;; Notes:
;;; this a subroutine that turn off all the LEDS when called

Turn_Off_Leds
    LDR R0, =GPIOA_ODR
    LDR R1, [R0]
    LDR R2, =0x00001E00
    ORR R1, R1, R2; 0001 1110 0000 0000
    STR R1, [R0]	
    BX LR	
	
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;;; UC1 and UC2 (Waiting for Players)
;;; Notes:
;;; a check_input function that verifies when a switch has been pressed

Check_Input
	push {lr}
	BL red_button_check
	
	BL black_button_check
	
	BL blue_button_check
	
	BL green_button_check
	pop {lr}
	BX LR

;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;;; UC1 and UC2 
;;; Notes:
;;; these are subroutines that handle checks for individual button presses
;;; and calls a Random Number Generator function to start the game play

red_button_check	
	ldr r0,=GPIOB_IDR
	ldr r1,[r0]
	lsr r1,#8
	and r1,#1
	cmp r1,#0
	BEQ Random_No_Gen
	BX LR
	
	
black_button_check
	ldr r0,=GPIOB_IDR
	ldr r1,[r0]
	lsr r1,#9
	and r1,#1
	cmp r1,#0
	BEQ Random_No_Gen
	BX LR
	
blue_button_check
	ldr r0,=GPIOC_IDR
	ldr r1,[r0]
	lsr r1,#12
	and r1,#1
	cmp r1,#0
	BEQ Random_No_Gen
	BX LR
	
green_button_check
	ldr r0,=GPIOA_IDR
	ldr r1,[r0]
	lsr r1,#5
	and r1,#1
	cmp r1,#0
	BEQ Random_No_Gen
	BX LR
	
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;;; UC3 (Normal Game play)
;;; Require:
;;; R11: loaded with a "1664525" value for the random number function
;;; R12: loaded with a "1013904223" value for the random number function
;;; R8: constantly intialized a value of 0 when the Random_No_Gen is called
;;; R7: loaded with an address where the value of R5 is stored
;;; 
;;; Notes:
;;;	This function creates an initial "PrelimWait" time before the actual game starts
;;; This function then generates a random number then turns on the equivalent LED
;;;	
	ALIGN
Random_No_Gen PROC	
	MOV R8, #0
	MOV32 R5, #0xf00f9889 ; seed number only occurs once
	LDR R7, = 0x20001008
	STR R5,  [R7]
	
ran_no_gen
;;generating random number
	BL Turn_Off_Leds
	BL PrelimWait
	LDR R11, =  1664525
	LDR R12, = 1013904223
	LDR R5, [R7]
	MUL R5, R5, R11
	ADD R5, R5, R12
	
	STR R5, [R7]
	
	LSR R5, R5, #30 ; shifting right ton obtain 2 bits used for the comparison

	CMP R5, #0
	BEQ Black_On
	
	CMP R5, #1
	BEQ Green_On
	
	CMP R5, #2
	BEQ Red_On
	
	CMP R5, #3
	BEQ Blue_On
	
	ENDP
		
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;;; UC3 (Normal Game play)
;;; these are specific subroutines made to turn on LEDs
;;; check for user input as well as no user input 
;;;	and the corresponding instruction set based on these parameters

Red_On
    LDR R0, =GPIOA_ODR
    LDR R1, [R0]
    LDR R2, =0xFFFFFDFF
    AND R1, R1, R2; 1101 1111 1111
    STR R1, [R0]
	BL ReactTime
	BL blue_button_gamecheck
	BL black_button_gamecheck
	BL green_button_gamecheck
	BL red_button_gamecheck_success
	BNE fail
	bl ran_no_gen
	
	
Black_On
    LDR R0, =GPIOA_ODR
    LDR R1, [R0]
    LDR R2, =0xFFFFFBFF
    AND R1, R1, R2; 1011 1111 1111
    STR R1, [R0]
	BL ReactTime
	BL red_button_gamecheck
	BL blue_button_gamecheck
	BL green_button_gamecheck
	BL black_button_gamecheck_success
	BNE fail
	bl ran_no_gen
	
Blue_On
    LDR R0, =GPIOA_ODR
    LDR R1, [R0]
    LDR R2, =0xFFFFF7FF
    AND R1, R1, R2; 0111 1111 1111
    STR R1, [R0]
	BL ReactTime
	BL red_button_gamecheck
	BL green_button_gamecheck
	BL black_button_gamecheck
	BL blue_button_gamecheck_success
	BNE fail	
	bl ran_no_gen


Green_On
    LDR R0, =GPIOA_ODR
    LDR R1, [R0]
    LDR R2, =0xFFFFEFFF
    AND R1, R1, R2; 1110 1111 1111 1111
    STR R1, [R0]
	BL ReactTime
	BL red_button_gamecheck
	BL blue_button_gamecheck
	BL black_button_gamecheck
	BL green_button_gamecheck_success
	BNE fail
	bl ran_no_gen	
	
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;;; UC3 (Normal Game play)
;;; this is a delay routine that handles the time the user waits before game start

	ALIGN
PrelimWait PROC 
	MOV R4, #0	
Wait	
    ADD R4, R4, #0x1
    CMP R6, R4
    BNE Wait
    BX LR
    ENDP
		
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;;; UC3 (Normal Game play)
;;; this is a delay routine that handles the time the user has to "whack the mole"

	ALIGN		
ReactTime PROC 
	MOV R4, #0
	LDR R6, = FIRST_MOLE_SPEED_DELAY
mole_Delay	
    ADD R4, R4, #0x1
    CMP R6, R4
    BNE mole_Delay
    BX LR
    ENDP	

;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;;; UC2 
;;; this is a delay routine that help with the intial LED light blinking at the Reset_HAndler stage

	ALIGN
UC2_Delay PROC 
	MOV R4, #0
Delay	
    ADD R4, R4, #0x1
    CMP R3, R4
    BNE Delay
    BX LR
    ENDP
		
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;;; UC5 (End Failure)
;;; This is a subroutine that falshes the lights in a pattern when player fails
;;; displays the level they where on in binary form when the failed
;;; then branches back to the link register, which is the default state

fail
	BL R_On; Branch to turn the Red Led on     
    BL B_On; Branch to turn the Black Led on   
    BL Bl_On; Branch to turn the Blue Led on    
    BL G_On; Branch to turn the Green Led on	
    LDR R4, =0x0    
    BL UC2_Delay; The wait the happens before the game starts    
	BL Check_Input	
    BL Turn_Off_Leds
    LDR R4, =0x0    
    BL UC2_Delay;       

	AND R0, R8, #1
	CMP R0, #0
	BEQ first
	BL G_On
first 

	LSR R8, #1
	AND R0, R8, #1
	CMP R0, #0
	BEQ second
	BL Bl_On
second
	LSR R8, #1
	AND R0, R8, #1
	CMP R0, #0
	BEQ third
	BL B_On
third
	LSR R8, #1
	AND R0, R8, #1
	CMP R0, #0
	BEQ fourth
	BL R_On
fourth
	BL PrelimWait
	BL Reset_Handler
	

;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;;; UC3 (Normal Game Play.)
;;; these are subroutines that checks when a user has input the correct
;;; or incorrect button during gameplay
;;; if the successful button presses go to the next level or "Next_cycle"

red_button_gamecheck
	ldr r0,=GPIOB_IDR
	ldr r1,[r0]
	lsr r1,#8
	and r1,#1
	cmp r1,#0
	BEQ fail
	BX LR

blue_button_gamecheck
	ldr r0,=GPIOC_IDR
	ldr r1,[r0]
	lsr r1,#12
	and r1,#1
	cmp r1,#0
	BEQ fail
	bx lr
	
green_button_gamecheck
	ldr r0,=GPIOA_IDR
	ldr r1,[r0]
	lsr r1,#5
	and r1,#1
	cmp r1,#0
	BEQ fail
	BX LR
	
black_button_gamecheck
	ldr r0,=GPIOB_IDR
	ldr r1,[r0]
	lsr r1,#9
	and r1,#1
	cmp r1,#0
	BEQ fail
	bx lr
	
green_button_gamecheck_success
	ldr r0,=GPIOA_IDR
	ldr r1,[r0]
	lsr r1,#5
	and r1,#1
	cmp r1,#0
	BEQ next_level
	BX LR
red_button_gamecheck_success
	ldr r0,=GPIOB_IDR
	ldr r1,[r0]
	lsr r1,#8
	and r1,#1
	cmp r1,#0
	BEQ next_level
	BX LR

blue_button_gamecheck_success
	ldr r0,=GPIOC_IDR
	ldr r1,[r0]
	lsr r1,#12
	and r1,#1
	cmp r1,#0
	BEQ next_level
	bx lr	

black_button_gamecheck_success
	ldr r0,=GPIOB_IDR
	ldr r1,[r0]
	lsr r1,#9
	and r1,#1
	cmp r1,#0
	BEQ next_level
	bx lr
	
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;;; these are subroutines that are used to turn off corresponding LED
R_Off
    LDR R0, =GPIOA_ODR
    LDR R1, [R0]
    LDR R2, =0x200
    ORR R1, R1, R2; 0010 0000 0000
    STR R1, [R0]
    BX LR

B_Off
    LDR R0, =GPIOA_ODR
    LDR R1, [R0]
    LDR R2, =0x400
    ORR R1, R1, R2; 0100 0000 0000
    STR R1, [R0]
    BX LR
	
Bl_Off
    LDR R0, =GPIOA_ODR
    LDR R1, [R0]
    LDR R2, =0x800
    ORR R1, R1, R2; 1000 0000 0000
    STR R1, [R0]
    BX LR	
	
G_Off
    LDR R0, =GPIOA_ODR
    LDR R1, [R0]
    LDR R2, =0x1000
    ORR R1, R1, R2; 0001 0000 0000 0000
    STR R1, [R0]
    BX LR
	
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;;; UC4 (End Success.)
;;; This is a subroutine that falshes the lights in a pattern when player wins
;;; then branches back to the link register, which is the default state
success
	BL R_On	
	BL G_On	
	
	BL UC2_Delay
	
	BL B_On	
	BL Bl_On
	
	BL UC2_Delay
	
	
	BL Bl_Off
	BL B_Off
	
	BL UC2_Delay
	
	BL G_Off	
	BL R_Off
	
	BL UC2_Delay	
	BL Reset_Handler
	
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;;; UC3 (Normal Game Play..)
;;; This is a subroutine that handles NumCycles
;;; this subroutine decreases the players reaction time
;;; and counts the level they are on
next_level
	LDR R9, = 150000
	MUL R11, R8, R9 
	SUB R6, R6, R11
	ADD R8, R8, #1
	CMP R8, #15
	BEQ success
	BL ran_no_gen
	
;;;;;;;;Subroutines ;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;	
;This routine will enable the clock for the Ports that you need	
	ALIGN
GPIO_ClockInit PROC

	; Students to write.  Registers   .. RCC_APB2ENR
	; ENEL 384 Pushbuttons: SW2(Red): P,B8 SW3(Black): PB9, SW4(Blue): PC12 *****NEW for 2015**** SW5(Green): PA5
	; ENEL 384 board LEDs: D1 - PA9, D2 - PA10, D3 - PA11, D4 - PA12
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;;RCC_APB2ENR is enable the CLOCK
;find the register map for RCC_APB2ENR
;enable port a , port b, and port c

	ldr r0,=RCC_APB2ENR
	ldr r1,[r0]					
	ldr r4,=0x1c			;for active port a,b,c: 0001 1100
	orr r1,r1,r4
	str r1,[r0]
	
	BX LR
	ENDP
		
	
	
;This routine enables the GPIO for the LED's.  By default the I/O lines are input so we only need to configure for ouptut.
	ALIGN
GPIO_init  PROC
	
; ENEL 384 board LEDs: D1 - PA9, D2 - PA10, D3 - PA11, D4 - PA12
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;for enable GPIOA_CRH P112 memory map;The reset value:ox4444 4444
;CNF:General purpose 00  MODE:ourput 50MHz 11
;make PIN 9,10,11,12 --0011
	
	; enabling leds
	LDR R0, =GPIOA_CRH
	ldr r1,=0x44433334
	str r1,[r0]

    BX LR
	ENDP
		




	ALIGN
	END
