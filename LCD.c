#include "lcd.h"



void LCD_Init(void)
{
	GPIO_setupPortDirection(PORTB_ID,PORT_OUTPUT); // Setup PortB as output
	LCD_sendCommand(TWO_LINE_LCD_Four_BIT_MODE);  
	LCD_sendCommand(INCREMENT_CURSOR);          
	LCD_sendCommand(CLEAR_COMMAND);					
	LCD_sendCommand(LCD_ON);          
	LCD_sendCommand(SET_CURSOR_LOCATION);   
	LCD_sendCommand(CURSOR_OFF);
  delayMs(50);	
}

void LCD_writeBits(uint8_t data, uint8_t control)
{
	data &= 0xF0;                       
	control &= 0x0F;                    
	LCD = data | control;         
	LCD = data | control | EN;    
	delayUs(1);													
	LCD = data | control;					
	LCD = 0;                      
}


void LCD_sendCommand(uint8_t command)
{
	LCD_writeBits(command & 0xF0 , 0);    
	LCD_writeBits((command & 0x0F )<< 4 , 0);			 
	delayMs(2);       
	
}

void LCD_displayCharacter(uint8_t data)
{
	LCD_writeBits(data & 0xF0 , RS);   
	LCD_writeBits((data & 0x0F )<< 4 , RS);     
	delayUs(40);			
	
		
}

void LCD_displayString(const uint8_t *Str)
{
	uint8_t i = 0;
	while(Str[i] != '\0')
	{
		LCD_displayCharacter(Str[i]);
		i++;
	}
}

void LCD_goToRowColumn(uint8_t row,uint8_t col)
{
	uint8_t Address = 0;
	
	switch(row)
	{
		case 0:
				Address=col;
				break;
		case 1:
				Address=col+0x40;
				break;
		
	}					
	
	LCD_sendCommand(Address | SET_CURSOR_LOCATION); 
}


void LCD_clearScreen(void)
{
	LCD_sendCommand(CLEAR_COMMAND); //clear display 
}



void LCD_displayTime(int16_t Time_In_Secs)
{
	uint16_t Seconds = Time_In_Secs % 60;
	uint16_t Minutes = Time_In_Secs / 60;
	
	
	
	LCD_goToRowColumn(1,8);
	LCD_displayCharacter(':');
	
	if(Seconds <= 9 )
	 {
		 
		 LCD_goToRowColumn(1,9);
		 LCD_displayCharacter('0');
		 LCD_goToRowColumn(1,10);
		 LCD_PrintINT(Seconds);
		 
	 }
	 else
	  {
			
			LCD_goToRowColumn(1,9);
			LCD_PrintINT(Seconds);
			
	  }
		
		if(Minutes <= 9 )
	 {
		 
		 LCD_goToRowColumn(1,6);
		 LCD_displayCharacter('0');
		 LCD_goToRowColumn(1,7);
		 LCD_PrintINT(Minutes);
		 
	 }
	 else
	  {
			
			LCD_goToRowColumn(1,6);
			LCD_PrintINT(Minutes);
			
	  }
		
	}
  
  


void LCD_displayStringRowColumn(uint8_t row,uint8_t col,const uint8_t *Str)
{
	LCD_goToRowColumn(row,col); /* go to to the required LCD position */
	LCD_displayString(Str); /* display the string */
}


void LCD_PrintINT(uint32_t number)
{
  uint8_t toprint[4] = {0};
  sprintf(toprint, "%d", number);
  int i = 0;
  while(toprint[i] != '\0')
  {
    LCD_displayCharacter(toprint[i]);
    i++;
  }
}

void LCD_displayCharRowColumn(uint8_t row,uint8_t col, uint8_t data)
{
	LCD_goToRowColumn(row,col); /* go to to the required LCD position */
	LCD_displayCharacter(data); /* display the string */
}





