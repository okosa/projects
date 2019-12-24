/*
    FreeRTOS V7.2.0 - Copyright (C) 2012 Real Time Engineers Ltd.


    ***************************************************************************
     *                                                                       *
     *    FreeRTOS tutorial books are available in pdf and paperback.        *
     *    Complete, revised, and edited pdf reference manuals are also       *
     *    available.                                                         *
     *                                                                       *
     *    Purchasing FreeRTOS documentation will not only help you, by       *
     *    ensuring you get running as quickly as possible and with an        *
     *    in-depth knowledge of how to use FreeRTOS, it will also help       *
     *    the FreeRTOS project to continue with its mission of providing     *
     *    professional grade, cross platform, de facto standard solutions    *
     *    for microcontrollers - completely free of charge!                  *
     *                                                                       *
     *    >>> See http://www.FreeRTOS.org/Documentation for details. <<<     *
     *                                                                       *
     *    Thank you for using FreeRTOS, and thank you for your support!      *
     *                                                                       *
    ***************************************************************************


    This file is part of the FreeRTOS distribution.

    FreeRTOS is free software; you can redistribute it and/or modify it under
    the terms of the GNU General Public License (version 2) as published by the
    Free Software Foundation AND MODIFIED BY the FreeRTOS exception.
    >>>NOTE<<< The modification to the GPL is included to allow you to
    distribute a combined work that includes FreeRTOS without being obliged to
    provide the source code for proprietary components outside of the FreeRTOS
    kernel.  FreeRTOS is distributed in the hope that it will be useful, but
    WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY
    or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU General Public License for
    more details. You should have received a copy of the GNU General Public
    License and the FreeRTOS license exception along with FreeRTOS; if not it
    can be viewed here: http://www.freertos.org/a00114.html and also obtained
    by writing to Richard Barry, contact details for whom are available on the
    FreeRTOS WEB site.

    1 tab == 4 spaces!
    
    ***************************************************************************
     *                                                                       *
     *    Having a problem?  Start by reading the FAQ "My application does   *
     *    not run, what could be wrong?                                      *
     *                                                                       *
     *    http://www.FreeRTOS.org/FAQHelp.html                               *
     *                                                                       *
    ***************************************************************************

    
    http://www.FreeRTOS.org - Documentation, training, latest information, 
    license and contact details.
    
    http://www.FreeRTOS.org/plus - A selection of FreeRTOS ecosystem products,
    including FreeRTOS+Trace - an indispensable productivity tool.

    Real Time Engineers ltd license FreeRTOS to High Integrity Systems, who sell 
    the code with commercial support, indemnification, and middleware, under 
    the OpenRTOS brand: http://www.OpenRTOS.com.  High Integrity Systems also
    provide a safety engineered and independently SIL3 certified version under 
    the SafeRTOS brand: http://www.SafeRTOS.com.
*/

/*
 * This is a very simple demo that demonstrates task and queue usages only in
 * a simple and minimal FreeRTOS configuration.  Details of other FreeRTOS 
 * features (API functions, tracing features, diagnostic hook functions, memory
 * management, etc.) can be found on the FreeRTOS web site 
 * (http://www.FreeRTOS.org) and in the FreeRTOS book.
 *
 * Details of this demo (what it does, how it should behave, etc.) can be found
 * in the accompanying PDF application note.
 *
*/

/* Kernel includes. */
#include "FreeRTOS.h"
#include "task.h"
#include "queue.h"
#include "timers.h"
#include "serial.h"
#include "CLI.h"
#include "pwm.h"
#include "a2d.h"


/* Standard include. */
#include <stdio.h>
#include <stdint.h>

/* Priorities at which the tasks are created. */
#define mainSERVO_PRIORITY                  ( tskIDLE_PRIORITY + 2 )
#define mainCLIADC_PRIORITY                  ( tskIDLE_PRIORITY + 2 )
#define mainCONTROLLER_PRIORITY              ( tskIDLE_PRIORITY + 3 )

/* The rate at which data is sent to the queue, specified in milliseconds. */
#define mainQUEUE_SEND_FREQUENCY_MS         ( 10 / portTICK_RATE_MS )

/* The number of items the queue can hold.  This is 1 as the receive task
will remove items as they are added, meaning the send task should always find
the queue empty. */
#define mainQUEUE_LENGTH                    ( 1 )

/* The ITM port is used to direct the printf() output to the serial window in 
the Keil simulator IDE. */
#define mainITM_Port8(n)    (*((volatile unsigned char *)(0xE0000000+4*n)))
#define mainITM_Port32(n)   (*((volatile unsigned long *)(0xE0000000+4*n)))
#define mainDEMCR           (*((volatile unsigned long *)(0xE000EDFC)))
#define mainTRCENA          0x01000000

/*-----------------------------------------------------------*/

/*
 * The tasks as described in the accompanying PDF application note.
 */
static void adctask( void *pvParameters ); 
static void clitask( void *pvParameters );
static void ctrltask( void *pvParameters );			//Control task
static void servotask( void *pvParameters );		// servo motor task



/*-----------------------------------------------------------*/

/* The queue used by both tasks. */
static xQueueHandle xQueuectrl = NULL;
static xQueueHandle xQueuepwm = NULL;

/* Define an enumerated type used to identify the source of the data.*/
typedef enum
{

    ADC_msg,

    CLI_msg

} DataSource_t;

/* Define the structure type that will be passed on the queue. */
typedef struct

{

    uint16_t ucValue;

    DataSource_t eDataSource;

} Data_t;


/* One array position is used for each task created by this demo.  The 
variables in this array are set and cleared by the trace macros within
FreeRTOS, and displayed on the logic analyzer window within the Keil IDE -
the result of which being that the logic analyzer shows which task is
running when. */
unsigned long ulTaskNumber[ configEXPECTED_NO_RUNNING_TASKS ];

/*-----------------------------------------------------------*/

//look up table with IR sensor values for each height starting from 5cm to 65cm with increments of 5cm
static const uint16_t voltLUT[13] = {1760, 3148,3082,2623 , 2172, 1913, 1213, 1001, 946, 825, 724, 695, 608};


int main(void)
{
	

	 serial_open(); 			//open usart serial communication
	 	
	 timer_init();					//configure timer for PWM
	 initA2D();								


    /* Create the queue. */
    xQueuectrl = xQueueCreate( mainQUEUE_LENGTH, sizeof( unsigned long ) );
	  xQueuepwm = xQueueCreate( mainQUEUE_LENGTH, sizeof( unsigned long ) );
    
    
		writeToCLI("\n\r");
		writeToCLI("Ball Levitation Plant! FreeRTOS implementation");
		writeToCLI("\n\r");
		writeToCLI("Enter distance set points between 0 and 60cm (increments of 5cm)");
	  writeToCLI("\n\r");

    if(( xQueuectrl != NULL ) || ( xQueuepwm != NULL ))
    {
        /* Start the two tasks as described in the accompanying application
        note. */


        xTaskCreate( clitask, ( signed char * ) "CLI",
                 configMINIMAL_STACK_SIZE, NULL,
                 mainCLIADC_PRIORITY, NULL );
        xTaskCreate( adctask, ( signed char * ) "ADC",
                 configMINIMAL_STACK_SIZE, NULL,
                 mainCLIADC_PRIORITY, NULL );
				xTaskCreate( servotask, ( signed char * ) "Servo",
                 configMINIMAL_STACK_SIZE, NULL,
                 mainSERVO_PRIORITY, NULL );
				xTaskCreate( ctrltask, ( signed char * ) "Controller",
                 configMINIMAL_STACK_SIZE, NULL,
                 mainCONTROLLER_PRIORITY, NULL );
								 
        /* Start the tasks running. */
        vTaskStartScheduler();
    }

    /* If all is well we will never reach here as the scheduler will now be
    running.  If we do reach here then it is likely that there was insufficient
    heap available for the idle task to be created. */
    for( ;; )
        ;
}
/*-----------------------------------------------------------
This task gets the sensor reading and sends it to the queue

*/


static void adctask( void *pvParameters )
{
	
	portTickType xNextWakeTime;
	Data_t ulValueToSend;
	char volt[12];
	
    /* Initialise xNextWakeTime - this only needs to be done once. */
    xNextWakeTime = xTaskGetTickCount();

    for( ;; )
    {
        /* Place this task in the blocked state until it is time to run again.
        The block time is specified in ticks, the constant used converts ticks
        to ms.  While in the Blocked state this task will not consume any CPU
        time. */
        vTaskDelayUntil( &xNextWakeTime, mainQUEUE_SEND_FREQUENCY_MS );
        ulValueToSend.eDataSource = ADC_msg;
			  ulValueToSend.ucValue = ReadA2d();
			  sprintf(volt, "%d", ulValueToSend.ucValue);     

//			
        /* Send to the queue - causing the queue receive task to unblock and
        print out a message.  0 is used as the block time so the sending 
        operation will not block - it shouldn't need to block as the queue 
        should always be empty at this point in the code. */
        xQueueSend( xQueuectrl, &ulValueToSend, 0 );
    }
}

/*-----------------------------------------------------------
This task gets the user's height and sends the corresponding sensor value at that height to the Queue.
*/

static void clitask( void *pvParameters )
{
	const int command_max =4;
	char command[command_max];	
	portTickType xNextWakeTime;
	int value;
	uint16_t volt;
	Data_t ulValueToSend;
	

    /* Initialise xNextWakeTime - this only needs to be done once. */
    xNextWakeTime = xTaskGetTickCount();

    for( ;; )
    {
        /* Place this task in the blocked state until it is time to run again.
        The block time is specified in ticks, the constant used converts ticks
        to ms.  While in the Blocked state this task will not consume any CPU
        time. */
        vTaskDelayUntil( &xNextWakeTime, mainQUEUE_SEND_FREQUENCY_MS );
    
				
				writeToCLI("COM0>");
				clearCommandBuffer(command);
				getCommand(command);
        sscanf(command, "%d", &value);
			  value = value/5;
			  volt = voltLUT[value];
        ulValueToSend.ucValue = volt;
			  ulValueToSend.eDataSource = CLI_msg;
			
			
        /* Send to the queue - causing the queue receive task to unblock and
        print out a message.  0 is used as the block time so the sending 
        operation will not block - it shouldn't need to block as the queue 
        should always be empty at this point in the code. */
        xQueueSend( xQueuectrl, &ulValueToSend, 0 );
    }
}

/*-----------------------------------------------------------
This task receives the IR sensor value and the user's height sensor value. If the sensor value is 1760, 
the ball keeps rising until it passes the user's setpoint and drops below the user's setpoint before rising again. 
This way the ball is constantly correcting itself


*/

static void ctrltask (void *pvParameters )
{
  Data_t ulReceivedValue;	
	
	uint16_t adc_val, cli_val, pwmctrl;
	


    for( ;; )
    {
        /* Wait until something arrives in the queue - this task will block
        indefinitely provided INCLUDE_vTaskSuspend is set to 1 in
        FreeRTOSConfig.h. */
        xQueueReceive( xQueuectrl, &ulReceivedValue, portMAX_DELAY );

        /*  To get here something must have been received from the queue, but
        is it the expected value?  If it is, print out a pass message, if no,
        print out a fail message. */
        if( ulReceivedValue.eDataSource == ADC_msg )
        {
           adc_val = ulReceivedValue.ucValue;
			
        }
        if  ( ulReceivedValue.eDataSource == CLI_msg )
        {
					  cli_val = ulReceivedValue.ucValue;
					

       }
				
//played around with the servo to get these "magic numbers". need to change them for different servo
			 
			 if(adc_val == 1760) 																		//if ball is at 0cm
			 {
					pwmctrl = 2450;																			//open the servo so ball rises
				 	xQueueSend( xQueuepwm, &pwmctrl, 0 );
			 }
			
			else if ( (cli_val != 0) && (adc_val < cli_val))				//if user's height is above the ball
				{ 
					    
				     
				    pwmctrl = 2400;																		//close the servo to drop the ball
						xQueueSend( xQueuepwm, &pwmctrl, 0 );
					
				}
				else if ( (cli_val != 0) && (adc_val > cli_val))			//if user's height is below the ball
				{
					 
					pwmctrl = 2450;																			//open the servo so ball rises
						xQueueSend( xQueuepwm, &pwmctrl, 0 );
					
					
    }
}
		}
/*-----------------------------------------------------------
		changes the dutycycke of the pwm
		*/


static void servotask (void *pvParameters )
{

	uint16_t ulReceivedValue;	

    for( ;; )
    {
        /* Wait until something arrives in the queue - this task will block
        indefinitely provided INCLUDE_vTaskSuspend is set to 1 in
        FreeRTOSConfig.h. */
        xQueueReceive( xQueuepwm, &ulReceivedValue, portMAX_DELAY );
        changeDC(ulReceivedValue);
     
  
    }
}


