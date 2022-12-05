#include "gpio.h"
#include "LCD.h"
#include "systick.h"
#include "keypad.h"

static volatile uint8_t SW2_FLAG ;
static volatile uint8_t SW1_FLAG ;
static volatile uint8_t CLEAR_FLAG ; 
static volatile uint8_t CASED_FLAG ;
static volatile uint8_t DOOR_FLAG = 0;


void Display_Time(int16_t CookingTimeInSecs);
void GPIOF_Handler(void);
void ToggleLedBuzzer(void);


int main( void ) {
	
	SysTick_Init();
	LCD_Init();
	KEYPAD_Init();
	

  GPIO_setupPinDirection(PORTF_ID,PIN4_ID,PIN_INPUT,PIN_PULLUP_RESISTOR);
  GPIO_setupPinDirection(PORTF_ID,PIN0_ID,PIN_INPUT,PIN_PULLUP_RESISTOR);
	GPIO_setupPinDirection(PORTF_ID,PIN2_ID,PIN_INPUT,PIN_PULLUP_RESISTOR);
	GPIO_setupPinDirection(PORTA_ID,PIN6_ID,PIN_OUTPUT,PIN_NO_RESISTOR);// BUZZER
	GPIO_setupPinDirection(PORTA_ID,PIN7_ID,PIN_OUTPUT,PIN_NO_RESISTOR);// LED

	
	 
  GPIOF_EnableInt();

	uint8_t COOKING_CASE  = '0';
	uint8_t EnteredCookingWeight = '0';
	uint8_t CookingTimeCaseD [] = {"0000"};
	int16_t CookingTimeInSecs = 0 ;
	
	

	
	
	while(1)
	{
		
		COOKING_CASE = KEYPAD_Getkey();
				
		switch(COOKING_CASE) {
			
			case 'A' :
				LCD_displayStringRowColumn(0,4,"POP CORN");
			  CookingTimeInSecs = 60 ;
			  LCD_displayTime(CookingTimeInSecs);
			  while((SW2_FLAG == 0) && (CLEAR_FLAG !=3)) ;
			  Display_Time(CookingTimeInSecs);
						break ;		
						
				ERROR_CASE_B:						
			case 'B' :
				LCD_displayStringRowColumn(0,2,"BEEF WEIGHT?");
			  EnteredCookingWeight = KEYPAD_Getkey();
			  if((EnteredCookingWeight <='9') && (EnteredCookingWeight>='1')) {
					
						LCD_clearScreen();
						LCD_displayCharacter(EnteredCookingWeight);
						LCD_displayString(" kilos");
						SysTick_Wait1s(2);
						LCD_clearScreen();
						CookingTimeInSecs = (EnteredCookingWeight - '0') * 30;
						LCD_displayTime(CookingTimeInSecs);
						while(SW2_FLAG == 0);
			      Display_Time(CookingTimeInSecs);		
					}
					
				else {
					
					LCD_clearScreen();
					LCD_displayStringRowColumn(0,7,"ERR");
					SysTick_Wait1s(2);
					goto ERROR_CASE_B;
					
				}
					break;
				
				
				ERROR_CASE_C:	
			case 'C' :
				LCD_displayStringRowColumn(0,0,"Chicken WEIGHT?");
			  EnteredCookingWeight = KEYPAD_Getkey();
			  if((EnteredCookingWeight <='9') && (EnteredCookingWeight>='1')) {
					
						LCD_clearScreen();
						LCD_displayCharacter(EnteredCookingWeight);
						LCD_displayString(" kilos");
						SysTick_Wait1s(2);
						LCD_clearScreen();
						CookingTimeInSecs = (EnteredCookingWeight - '0') * 12;
						LCD_displayTime(CookingTimeInSecs);
						while(SW2_FLAG == 0);
			      Display_Time(CookingTimeInSecs);
					}
					
				else{
					LCD_clearScreen();
					LCD_displayStringRowColumn(0,7,"ERR");
					SysTick_Wait1s(2);
					goto ERROR_CASE_C;
					
				}
					break;
				 
				ERROR_CASE_D:
				case 'D' :
			CASED_FLAG = 1;		
			LCD_displayStringRowColumn(0,1,"Cooking Time?");
			SysTick_Wait1s(2);
			LCD_clearScreen();	
				
			LCD_displayStringRowColumn(1,6,"00:00");	
			CookingTimeCaseD[0] = KEYPAD_Getkey();
			LCD_displayCharRowColumn(1,10,CookingTimeCaseD[0]);
				
			CookingTimeCaseD[1] = KEYPAD_Getkey();
			LCD_displayCharRowColumn(1,9,CookingTimeCaseD[0]);
			LCD_displayCharRowColumn(1,10,CookingTimeCaseD[1]);
			
			CookingTimeCaseD[2] = KEYPAD_Getkey();
			LCD_displayCharRowColumn(1,7,CookingTimeCaseD[0]);
			LCD_displayCharRowColumn(1,9,CookingTimeCaseD[1]);
			LCD_displayCharRowColumn(1,10,CookingTimeCaseD[2]);
		  
			CookingTimeCaseD[3] = KEYPAD_Getkey();
			LCD_displayCharRowColumn(1,6,CookingTimeCaseD[0]);
			LCD_displayCharRowColumn(1,7,CookingTimeCaseD[1]);
			LCD_displayCharRowColumn(1,9,CookingTimeCaseD[2]);
			LCD_displayCharRowColumn(1,10,CookingTimeCaseD[3]);
			
			
			    CookingTimeInSecs = ((CookingTimeCaseD[0] - '0') * 600) + ((CookingTimeCaseD[1] - '0') * 60) + ((CookingTimeCaseD[2] - '0') * 10) + ((CookingTimeCaseD[3] - '0'));
	     if((CookingTimeInSecs <= 1800) && (CookingTimeInSecs>0)) {   
					LCD_displayTime(CookingTimeInSecs);	
			    while(SW2_FLAG == 0) {
						if (CLEAR_FLAG == 1) {
							CLEAR_FLAG = 2;
							SW2_FLAG = 1 ;
							break;
						}
					}
			    Display_Time(CookingTimeInSecs);
			  }
			else {
					LCD_clearScreen();
					LCD_displayStringRowColumn(0,7,"ERR");
					SysTick_Wait1s(2);
					goto ERROR_CASE_D;
					
				}
			break;
      			
		}			
  }
}


void Display_Time(int16_t CookingTimeInSecs) {

		for(CookingTimeInSecs;CookingTimeInSecs >= 0;CookingTimeInSecs --){
							LCD_displayTime(CookingTimeInSecs);
							
			GPIO_writePin(PORTA_ID,PIN7_ID,LOGIC_HIGH);
			if((CLEAR_FLAG != 1) && ((CLEAR_FLAG / 2 ) == 1))
								break;  
      if((CASED_FLAG == 1) && (SW1_FLAG == 1))
                break;				                                                                                             
      while( (SW1_FLAG == 1) || (DOOR_FLAG == 1) ) {
							 LCD_displayTime(CookingTimeInSecs); 
				       GPIO_togglePin(PORTA_ID,PIN7_ID);
				       delayMs(500);
			}
			SysTick_Wait1s(1);
													                                   
						}
		if(CookingTimeInSecs == -1) {
			ToggleLedBuzzer();
		}
		LCD_clearScreen();
		GPIO_writePin(PORTA_ID,PIN7_ID,LOGIC_LOW);				
		SW2_FLAG = 0;
		SW1_FLAG = 0;
    CLEAR_FLAG = 0; 
		CASED_FLAG = 0;
    						
						
}

void ToggleLedBuzzer(void) {
	
      GPIO_writePin(PORTA_ID,PIN6_ID,LOGIC_HIGH);
			GPIO_writePin(PORTA_ID,PIN7_ID,LOGIC_HIGH);
			SysTick_Wait1s(1);
			GPIO_writePin(PORTA_ID,PIN6_ID,LOGIC_LOW);
			GPIO_writePin(PORTA_ID,PIN7_ID,LOGIC_LOW);
			delayMs(300);
			GPIO_writePin(PORTA_ID,PIN6_ID,LOGIC_HIGH);
			GPIO_writePin(PORTA_ID,PIN7_ID,LOGIC_HIGH);
			SysTick_Wait1s(1);
			GPIO_writePin(PORTA_ID,PIN6_ID,LOGIC_LOW);
			GPIO_writePin(PORTA_ID,PIN7_ID,LOGIC_LOW);
			delayMs(300);
			GPIO_writePin(PORTA_ID,PIN6_ID,LOGIC_HIGH);
			GPIO_writePin(PORTA_ID,PIN7_ID,LOGIC_HIGH);
			SysTick_Wait1s(1);
			GPIO_writePin(PORTA_ID,PIN6_ID,LOGIC_LOW);
			GPIO_writePin(PORTA_ID,PIN7_ID,LOGIC_LOW);
			delayMs(300);			
}


/* SW1 is connected to PF4 pin, SW2 is connected to PF0. */
/* Both of them trigger PORTF falling edge interrupt */
void GPIOF_Handler(void)
{	
  
 if (BIT_IS_SET((GPIOF->MIS),4)) { //sw
 
     delayMs(200);
     	 
      if (BIT_IS_SET((GPIOF->MIS),4)){ //Debouncing 
				if(SW1_FLAG == 0)
				   SW1_FLAG = 1;	
        else 
           SW1_FLAG = 0;
				
			  CLEAR_FLAG ++ ;
				
				
				GPIOF->ICR |= 0x10; /* clear the interrupt flag */	
       
			}
 } 
    else if (BIT_IS_SET((GPIOF->MIS),0)) /* check if interrupt causes by PF0/SW2 */
    {   
			delayMs(200);
			if (BIT_IS_SET((GPIOF->MIS),0)) { //Debouncing
				SW2_FLAG = 1;
        SW1_FLAG = 0;
			  CLEAR_FLAG = 0;
			
				
        GPIOF->ICR |= 0x01; /* clear the interrupt flag */
			}
		}
		
		 else if (BIT_IS_SET((GPIOF->MIS),2)) /* check if interrupt causes by PF2/SW3 */
    {   
			delayMs(200);
			if (BIT_IS_SET((GPIOF->MIS),2)) { //Debouncing
			
				if(DOOR_FLAG == 0)
				{
					DOOR_FLAG = 1;
					
				}
				else
					DOOR_FLAG = 0;
			
				
        GPIOF->ICR |= 0x04; /* clear the interrupt flag */
			}
		}
	
}

