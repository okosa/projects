 

#include "CLI.h"


/**
* Name:           void writeToCLI(const char data[])
* Paramaters:     none
* Description:    This function writes to the Terminal
* Preconditions:  N/A
* Postconditions: Outputs characters to the CLI
*/
void writeToCLI(const char data[])
{
int i;
	for (i=0; i < strlen(data); i++){
		sendbyte(data[i]);
	}

}

/**
* Name:           void getCommand(char command[])
* Paramaters:     none
* Description:    This function gets user input from terminal
* Preconditions:  N/A
* Postconditions: reads input into a character array
*/
void getCommand(char command[])
{
	int i=0;
	char input;
	while (input!= 0x0d){
	input = command[i] = getbyte();
		
		if ((input == 0x7f) || (input == 0x8))
			{ 
				if (i!=0)
					{
						sendbyte(0x8);
						i--;
						command[i] = 0x0;
						sendbyte(' ');
						writeToCLI("\u001b[1D");	
				
					}		
			}
	  else 
			{
				sendbyte(command[i]);
				i++;}
			} 

	writeToCLI("\n\r");
}


/**
* Name:           void getCommand(char command[])
* Paramaters:     none
* Description:    This function clears the command array
* Preconditions:  N/A
* Postconditions:
*/
void clearCommandBuffer(char command[])
{
	int i;
		for ( i = 0; i < strlen (command); i++)
			{command[i] = ' ';}

}

