#include "systick.h"



void SysTick_Init (void) {
	SysTick ->CTRL = 0;               //Disable SysTick during setup
	SysTick ->LOAD = 0x00FFFFFF;      //Maximum reload value
	SysTick ->VAL = 0;                //any write to CURRENT clears it	     
  SET_BIT((SysTick ->CTRL),0U);     //enable SysTick with core clock
	SET_BIT((SysTick ->CTRL),2U);     //enable SysTick with core clock
}

void SysTick_Disable(void)
{
  CLEAR_BIT((SysTick ->CTRL),0U);
}


void SysTick_Wait (uint32_t delay){
	SysTick ->LOAD = delay - 1;      //Number of counts
	SysTick ->VAL = 0;               //Any value written to CURRENT clears
while (BIT_IS_CLEAR((SysTick->CTRL),16U)); //wait for flag          
}                                         

void SysTick_Wait1s(uint32_t delay) {
	volatile unsigned long i; 
	for (i=0; i<delay; i++){       
		SysTick_Wait(16000000); //wait 1 second
 }
}
	
void delayMs(uint32_t delay)
{  
	volatile unsigned long i; 
	for (i=0; i<delay; i++){       
		SysTick_Wait(16000); //delay for 1 melli second
	}	
		
}


void delayUs(uint32_t delay)             
{
	volatile unsigned long i; 
	for (i=0; i<delay; i++){       
		SysTick_Wait(16); //delay for 1 micro second
	}	
}

 
