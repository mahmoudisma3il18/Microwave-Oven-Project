#include  "gpio.h"
#include  "common_macros.h"
#include  "TM4C123.h"

/******************************************************************************
******************************************************************************/

void GPIO_setupPinDirection(uint32_t port_num,uint8_t pin_num,GPIO_PinDirectionType direction,GPIO_PinResistorType resistor)
{
	
	   
	
	if( (port_num >= NUM_OF_PORTS) || (pin_num >= NUM_OF_PINS_PER_PORTS))
	{
		// Do nothing if number of pin or port is incorect 
	}
	else
	{
		
		switch(port_num)
		{
			case PORTA_ID :
				SYSCTL->RCGCGPIO  |= 0x01; // Enable clock for PORTA
			  GPIOA->LOCK =     0x4C4F434B;  ////It enables write access to GPIOCR register.
			  GPIOA->DEN        |=(1<<pin_num); 
			
			switch(resistor)
			{
				case PIN_NO_RESISTOR :
					break;
				
				case PIN_PULLUP_RESISTOR:
					GPIOA->CR = 0X01;
				  SET_BIT((GPIOA->PUR),pin_num);
				  break;
				
				
			}
				if ( direction == PIN_OUTPUT )
					SET_BIT((GPIOA->DIR),pin_num);
				else
					CLEAR_BIT((GPIOA->DIR),pin_num);
				break;
				
			case PORTB_ID :
				SYSCTL->RCGCGPIO  |= 0x02; // Enable clock for PORTB
			  GPIOB->LOCK =     0x4C4F434B;  ////It enables write access to GPIOCR register.
			  GPIOB->DEN        |=(1<<pin_num); 
			
       switch(resistor)
			{
				case PIN_NO_RESISTOR :
					break;
				
				case PIN_PULLUP_RESISTOR:
					GPIOB->CR = 0X01;
				  SET_BIT((GPIOB->PUR),pin_num);
				  break;
				
				case PIN_PULLDOWN_RESISTOR :
					GPIOA->CR = 0X01;
				  SET_BIT((GPIOB->PDR),pin_num);
				  break;
			}			
				if ( direction == PIN_OUTPUT )
					SET_BIT((GPIOB->DIR),pin_num);
				else
					CLEAR_BIT((GPIOB->DIR),pin_num);
				break;
				
			case PORTC_ID :
        SYSCTL->RCGCGPIO  |= 0x04; // Enable clock for PORTC
		   	GPIOC->LOCK =     0x4C4F434B;  ////It enables write access to GPIOCR register.
			  GPIOC->DEN        |=(1<<pin_num); 
			 switch(resistor)
			{
				case PIN_NO_RESISTOR :
					break;
				
				case PIN_PULLUP_RESISTOR:
					GPIOC->CR = 0X01;
				  SET_BIT((GPIOC->PUR),pin_num);
				  break;
				
				
			}
				if ( direction == PIN_OUTPUT )
					SET_BIT((GPIOC->DIR),pin_num);
				else
					CLEAR_BIT((GPIOC->DIR),pin_num);
				break;	
				
			case PORTD_ID :
        SYSCTL->RCGCGPIO  |= 0x08; // Enable clock for PORTD
			  GPIOD->LOCK =     0x4C4F434B;  ////It enables write access to GPIOCR register.
			  GPIOD->DEN        |=(1<<pin_num);
       switch(resistor)
			{
				case PIN_NO_RESISTOR :
					break;
				
				case PIN_PULLUP_RESISTOR:
					GPIOD->CR = 0X01;
				  SET_BIT((GPIOD->PUR),pin_num);
				  break;
				
				
			}			
				if ( direction == PIN_OUTPUT )
					SET_BIT((GPIOD->DIR),pin_num);
				else
					CLEAR_BIT((GPIOD->DIR),pin_num);
				break;		
				
			case PORTE_ID :
        SYSCTL->RCGCGPIO  |= 0x10; // Enable clock for PORTE
			  GPIOE->LOCK =     0x4C4F434B;  ////It enables write access to GPIOCR register.
			  GPIOE->DEN        |=(1<<pin_num);  
			 switch(resistor)
			{
				case PIN_NO_RESISTOR :
					break;
				
				case PIN_PULLUP_RESISTOR:
					GPIOE->CR = 0X01;
				  SET_BIT((GPIOE->PUR),pin_num);
				  break;
				
				
			}
				if ( direction == PIN_OUTPUT )
					SET_BIT((GPIOE->DIR),pin_num);
				else
					CLEAR_BIT((GPIOE->DIR),pin_num);
				break;		
				
			case PORTF_ID :
        SYSCTL->RCGCGPIO  |= 0x20; // Enable clock for PORTF
			  GPIOF->LOCK =     0x4C4F434B;  ////It enables write access to GPIOCR register.
			  GPIOF->CR = 0X01;  
			  GPIOF->LOCK = 0;            /* lock commit register */
      
				if ( direction == PIN_OUTPUT )
					SET_BIT((GPIOF->DIR),pin_num);
				else
					CLEAR_BIT((GPIOF->DIR),pin_num);
				
				GPIOF->DEN        |=(1<<pin_num);
				
				 switch(resistor)
			{
				case PIN_NO_RESISTOR :
					break;
				
				case PIN_PULLUP_RESISTOR:
					
				  SET_BIT((GPIOF->PUR),pin_num);
				  break;
				
				case PIN_PULLDOWN_RESISTOR :
					
				  SET_BIT((GPIOF->PDR),pin_num);
				  break;
			}			
         break;			

					
		}
	}
}

/****************************************************************************
****************************************************************************/

void GPIO_writePin(uint32_t port_num,uint8_t pin_num,uint8_t value)
{
	
	
	if( (port_num >= NUM_OF_PORTS) || (pin_num >= NUM_OF_PINS_PER_PORTS))
	{
		// Do nothing if number of pin or port is incorect 
	}
	else
	{
		
		switch(port_num)
		{
			case PORTA_ID :
				if ( value == LOGIC_HIGH )
					SET_BIT((GPIOA->DATA),pin_num);
				else
					CLEAR_BIT((GPIOA->DATA),pin_num);
				break;
				
			case PORTB_ID :
				if ( value == LOGIC_HIGH )
					SET_BIT((GPIOB->DATA),pin_num);
				else
					CLEAR_BIT((GPIOB->DATA),pin_num);
				break;
				
			case PORTC_ID :
				if ( value == LOGIC_HIGH )
					SET_BIT((GPIOC->DATA),pin_num);
				else
					CLEAR_BIT((GPIOC->DATA),pin_num);
				break;	
				
			case PORTD_ID :
				if ( value == LOGIC_HIGH )
					SET_BIT((GPIOD->DATA),pin_num);
				else
					CLEAR_BIT((GPIOD->DATA),pin_num);
				break;		
				
			case PORTE_ID :
				if ( value == LOGIC_HIGH )
					SET_BIT((GPIOE->DATA),pin_num);
				else
					CLEAR_BIT((GPIOE->DATA),pin_num);
				break;		
				
			case PORTF_ID :
				if ( value == LOGIC_HIGH )
					SET_BIT((GPIOF->DATA),pin_num);
				else
					CLEAR_BIT((GPIOF->DATA),pin_num);
				break;		

					
		}
	}
	
}

/*****************************************************************************
*****************************************************************************/

void GPIO_togglePin(uint32_t port_num,uint8_t pin_num)
{
	
	
	if( (port_num >= NUM_OF_PORTS) || (pin_num >= NUM_OF_PINS_PER_PORTS))
	{
		// Do nothing if number of pin or port is incorect 
	}
	else
	{
		
		switch(port_num)
		{
			case PORTA_ID :
				TOGGLE_BIT((GPIOA->DATA),pin_num);
				break;
				
			case PORTB_ID :
				TOGGLE_BIT((GPIOB->DATA),pin_num);
				break;
				
			case PORTC_ID :
				TOGGLE_BIT((GPIOC->DATA),pin_num);
				break;	
				
			case PORTD_ID :
				TOGGLE_BIT((GPIOD->DATA),pin_num);
				break;		
				
			case PORTE_ID :
				TOGGLE_BIT((GPIOE->DATA),pin_num);
				break;		
				
			case PORTF_ID :
				TOGGLE_BIT((GPIOF->DATA),pin_num);
				break;		
				
		}
	}
	
}

/**************************************************************************
**************************************************************************/

uint8_t GPIO_readPin(uint32_t port_num,uint8_t pin_num)
{
	
	uint8_t pin_value = LOGIC_LOW;
	
	if( (port_num >= NUM_OF_PORTS) || (pin_num >= NUM_OF_PINS_PER_PORTS))
	{
		// Do nothing if number of pin or port is incorect 
	}
	else
	{
		
		switch(port_num)
		{
			case PORTA_ID :
				if BIT_IS_SET((GPIOA->DATA),pin_num)
					pin_value = LOGIC_HIGH;
				else
					pin_value = LOGIC_LOW;
				break;
				
			case PORTB_ID :
				if BIT_IS_SET((GPIOB->DATA),pin_num)
					pin_value = LOGIC_HIGH;
				else
					pin_value = LOGIC_LOW;
				break;	
				
			case PORTC_ID :
				if BIT_IS_SET((GPIOC->DATA),pin_num)
					pin_value = LOGIC_HIGH;
				else
					pin_value = LOGIC_LOW;
				break;	
				
			case PORTD_ID :
				if BIT_IS_SET((GPIOD->DATA),pin_num)
					pin_value = LOGIC_HIGH;
				else
					pin_value = LOGIC_LOW;
				break;	
				
			case PORTE_ID :
				if BIT_IS_SET((GPIOE->DATA),pin_num)
					pin_value = LOGIC_HIGH;
				else
					pin_value = LOGIC_LOW;
				break;	
				
			case PORTF_ID :
				if BIT_IS_SET((GPIOF->DATA),pin_num)
					pin_value = LOGIC_HIGH;
				else
					pin_value = LOGIC_LOW;
				break;	
				
			
					
		}
	}
	
	return pin_value;
}

/************************************************************************************
************************************************************************************/

void GPIO_setupPortDirection(uint32_t port_num,GPIO_PortDirectionType direction)
{
	if( port_num >= NUM_OF_PORTS)
	{
		// Do nothing if number of pin or port is incorect 
	}
	else
	{
		
		switch(port_num)
		{
			case PORTA_ID :
				SYSCTL->RCGCGPIO  |= 0x01; // Enable clock for PORTA
			  GPIOA->LOCK =     0x4C4F434B;  ////It enables write access to GPIOCR register.
			  GPIOA->DEN        |= 0xff;  
				GPIOA->DIR        = direction;
				break;
				
			case PORTB_ID :
				SYSCTL->RCGCGPIO  |= 0x02; // Enable clock for PORTB
			  GPIOB->LOCK =     0x4C4F434B;  ////It enables write access to GPIOCR register.
			  GPIOB->DEN        |= 0xff;  
				GPIOB->DIR        = direction;
				break;
				
			case PORTC_ID :
        SYSCTL->RCGCGPIO  |= 0x04; // Enable clock for PORTC
		   	GPIOC->LOCK =     0x4C4F434B;  ////It enables write access to GPIOCR register.
			  GPIOC->DEN        |= 0xff;  
				GPIOC->DIR        = direction;
				break;	
				
			case PORTD_ID :
        SYSCTL->RCGCGPIO  |= 0x08; // Enable clock for PORTD
			  GPIOD->LOCK =     0x4C4F434B;  ////It enables write access to GPIOCR register.
			  GPIOD->DEN        |= 0xff; 
				GPIOD->DIR        = direction;
				break;		
				
			case PORTE_ID :
        SYSCTL->RCGCGPIO  |= 0x10; // Enable clock for PORTE
			  GPIOE->LOCK =     0x4C4F434B;  ////It enables write access to GPIOCR register.
			  GPIOE->DEN        |= 0xff;  
				GPIOE->DIR        = direction;
			  break;
				
			case PORTF_ID :
        SYSCTL->RCGCGPIO  |= 0x20; // Enable clock for PORTF
			  GPIOF->LOCK =     0x4C4F434B;  ////It enables write access to GPIOCR register.
			  GPIOF->DEN        |= 0xff;  
				GPIOF->DIR        = direction;
				break;		

					
		}
	}
}

/*******************************************************************************************
*******************************************************************************************/

void GPIO_writePort(uint32_t port_num,uint8_t value)
{
	if( port_num >= NUM_OF_PORTS )
	{
		// Do nothing if number of pin or port is incorect 
	}
	else
	{
		
		switch(port_num)
		{
			case PORTA_ID :
				GPIOA->DATA = value;
				break;
				
			case PORTB_ID :
				GPIOB->DATA = value;
				break;
				
			case PORTC_ID :
				GPIOC->DATA = value;
				break;	
				
			case PORTD_ID :
				GPIOD->DATA = value;
				break;		
				
			case PORTE_ID :
				GPIOE->DATA = value;
				break;		
				
			case PORTF_ID :
				GPIOF->DATA = value;
				break;		

					
		}
	}
}

/*************************************************************************************************
**************************************************************************************************/

void GPIO_togglePort(uint32_t port_num)
{
	if( port_num >= NUM_OF_PORTS )
	{
		// Do nothing if number of pin or port is incorect 
	}
	else
	{
		
		switch(port_num)
		{
			case PORTA_ID :
				GPIOA->DATA ^= 0xff;
				break;
				
			case PORTB_ID :
				GPIOB->DATA ^= 0xff;
				break;
				
			case PORTC_ID :
				GPIOC->DATA ^= 0xff;
				break;	
				
			case PORTD_ID :
				GPIOD->DATA ^= 0xff;
				break;		
				
			case PORTE_ID :
				GPIOE->DATA ^= 0xff;
				break;		
				
			case PORTF_ID :
				GPIOF->DATA ^= 0xff;
				break;		

					
		}
	}
}

/**************************************************************************************************
**************************************************************************************************/

uint32_t GPIO_readPort(uint32_t port_num)
{
	uint32_t port_value = LOGIC_LOW;
	
	if(port_num >= NUM_OF_PORTS)
	{
		// DO NO THING
	}
	else
	{
		switch(port_num)
		{
			case PORTA_ID : 
				port_value = GPIOA->DATA;
			  break;
			
			case PORTB_ID :
				port_value = GPIOB->DATA;
			  break;
			
			case PORTC_ID :
				port_value = GPIOC->DATA;
			  break;
			
			case PORTD_ID :
				port_value = GPIOD->DATA;
			  break;
			
			case PORTE_ID : 
				port_value = GPIOE->DATA;
			  break;
			
			case PORTF_ID :
				port_value = GPIOF->DATA;
			  break;
		}
	}
	
	return port_value;
}


void GPIOF_EnableInt(void) {
	
	   /* configure PORTF4, 0 for falling edge trigger interrupt */
    GPIOF->IS  &= ~(1<<4)|~(1<<0)|~(1<<2);        /* make bit 4, 0 edge sensitive */
    GPIOF->IBE &=~(1<<4)|~(1<<0);         /* trigger is controlled by IEV */
	  GPIOF->IBE |= (1<<2);
    GPIOF->IEV &= ~(1<<4)|~(1<<0);        /* falling edge trigger */
	
	
    GPIOF->ICR |= (1<<4)|(1<<0)|(1<<2);          /* clear any prior interrupt */
    GPIOF->IM  |= (1<<4)|(1<<0)|(1<<2);          /* unmask interrupt */
    
    /* enable interrupt in NVIC and set priority to 3 */
    NVIC->IP[30] = 3 << 5;     /* set interrupt priority to 3 */
    NVIC->ISER[0] |= (1<<30);  /* enable IRQ30 (D30 of ISER[0]) */
	
}