#ifndef __HW_GPIO_H__
#define __HW_GPIO_H__

#include "stdint.h"
#include "common_macros.h"


/*************************************************************************
                          DEFINATIONS
**************************************************************************/													

#define    NUM_OF_PORTS                     6
#define    NUM_OF_PINS_PER_PORTS            8

#define    PORTA_ID                         0
#define    PORTB_ID                         1
#define    PORTC_ID                         2
#define    PORTD_ID                         3
#define    PORTE_ID                         4
#define    PORTF_ID                         5

 
#define    PIN0_ID                          0
#define    PIN1_ID                          1
#define    PIN2_ID                          2
#define    PIN3_ID                          3
#define    PIN4_ID                          4
#define    PIN5_ID                          5
#define    PIN6_ID                          6
#define    PIN7_ID                          7

#define    LOGIC_HIGH                      (1)
#define    LOGIC_LOW                       (0)

/*************************************************************************
                         TYPE DECELARTIONS
**************************************************************************/
typedef enum{
	PIN_INPUT,PIN_OUTPUT
}GPIO_PinDirectionType;

typedef enum{
	PORT_INPUT,PORT_OUTPUT = 0xff
}GPIO_PortDirectionType;

typedef enum{
	PIN_NO_RESISTOR,PIN_PULLUP_RESISTOR,PIN_PULLDOWN_RESISTOR
}GPIO_PinResistorType;

typedef enum{
	PORT_NO_RESISTOR,PORT_PULLUP_RESISTOR,PORT_PULLDOWN_RESISTOR
}GPIO_PortResistorType;


/***************************************************************************
                         FUNCTION PROTOTYPES
****************************************************************************/


void GPIO_setupPinDirection(uint32_t port_num,uint8_t pin_num,GPIO_PinDirectionType direction,GPIO_PinResistorType resistor);
/* THIS FUNCTION SETUP THE DIRECTION OF PIN IN THE PORT   */


void GPIO_writePin(uint32_t port_num,uint8_t pin_num,uint8_t value);
/* THIS FUNCTION WRITES THE VALUE ON THE CHOOSEN PIN      */

void GPIO_togglePin(uint32_t port_num,uint8_t pin_num);
/* THIS FUNCTION TOGGLES THE VALUE ON THE CHOOSEN PIN      */

uint8_t GPIO_readPin(uint32_t port_num,uint8_t pin_num);
/* THIS FUNCTUON READS THE PIN AND RETURN VALUE IN IT     */

void GPIO_setupPortDirection(uint32_t port_num,GPIO_PortDirectionType);
/*  SETUP PORT DIRECTION TO BE INPUT OR OUTPUT             */

void GPIO_writePort(uint32_t port_num ,uint8_t value);
/*   WRITE THE REQUIRED VALUE ON THE PORT                  */

void GPIO_togglePort(uint32_t port_num );
/*   TOGGLE THE VALUE OF THE PORT                          */

uint32_t GPIO_readPort(uint32_t port_num);
/*   RETURN THE VALUE IN THE PORT                           */

void GPIOF_EnableInt(void);
	



#endif