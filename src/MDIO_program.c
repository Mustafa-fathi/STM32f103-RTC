#include "LSTD_TYPES.h"
#include "MDIO_interface.h"
#include "MDIO_private.h"


void MDIO_Initialize(void)
{
	/*for LCD_pins:-
	 * ------------
	 * make PORTA (A0:A7) as LCD_data as output
	 * make PORTB (B0,B1,B6) for (LCD_Enable) , (LCD_R/W) , (LCD_Register_Select) as output
	 *
	 * */
		GPIOA ->CRL = 0x33333333 ;
		GPIOB ->CRL = 0x03000433 ;
}

void MDIO_SetPinValue (u8 Port, u8 PinNum, u8 Value)
{
	switch (Port)
	{
		case MDIO_PORTA : if (Value == MDIO_HIGH)
						GPIOA -> ODR |= (1<<PinNum);
					    else
						GPIOA -> ODR &= ~(1<<PinNum);
					    break;
		case MDIO_PORTB:
					if (Value == MDIO_HIGH)
						GPIOB -> ODR |= (1<<PinNum);
					else
						GPIOB -> ODR &= ~(1<<PinNum);
					break;
		case MDIO_PORTC:
					if (Value == MDIO_HIGH)
						GPIOC -> ODR |= (1<<PinNum);
					else
						GPIOC -> ODR &= ~(1<<PinNum);
					break;
	}
}

void MDIO_set_pin(u8 port  , u8 pin )
{
         switch(port)
		  {
		  case MDIO_PORTA : GPIOA -> BSRR = (1<< pin);        break;
		   
		  case MDIO_PORTB : GPIOB -> BSRR = (1<<pin );		  break;

		  case MDIO_PORTC : GPIOC -> BSRR = (1<<pin );         break; 
		  
		  
		  
		  }


}

void MDIO_clr_pin (u8 port , u8 pin )
{
 switch(port)
		  {
		  case MDIO_PORTA : GPIOA -> BRR = (1<< pin);        break;
		   
		  case MDIO_PORTB : GPIOB -> BRR = (1<<pin );		  break;

		  case MDIO_PORTC : GPIOC -> BRR = (1<<pin );          break; 
		  
		  
		  
		  }



}

void MDIO_assgin_value (u8 port , u16 value )
{
switch(port)
		  {
		  case MDIO_PORTA : GPIOA -> ODR =  value ;     break;
		   
		  case MDIO_PORTB : GPIOB -> ODR = value ; 		  break;

		  case MDIO_PORTC : GPIOC -> ODR = value ;          break;
		  
		  
		  
		  }


}












