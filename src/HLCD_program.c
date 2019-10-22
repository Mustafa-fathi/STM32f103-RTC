/*
 * HLCD.c
 *
 *  Created on: Jul 26, 2019
 *      Author: Hampota
 */

#include "LSTD_TYPES.h"
#include "HLCD_interface.h"
#include "MDIO_interface.h"


void Delay(u32 volatile time)
{
		u32 volatile num1=900;
    u32 volatile time1 = num1*time;
    while(time1)
    {
        time1--;
    }
}

void HLCD_Set_Enable(void)
{

	MDIO_set_pin(HLCD_CONTROL_PORT , HLCD_ENABLE_PIN);

}

void HLCD_Clear_Enable(void)
{

	MDIO_clr_pin(HLCD_CONTROL_PORT , HLCD_ENABLE_PIN);

}


void HLCD_Set_Write(void)
{
   /*Set Read/Write to LOW to enable writing on LCD*/
	MDIO_clr_pin(HLCD_CONTROL_PORT , HLCD_READ_WRITE_PIN);

}


void HLCD_Set_Read(void)
{
	/*Set Read/Write to HIGH to enable READING on LCD*/
		MDIO_set_pin(HLCD_CONTROL_PORT , HLCD_READ_WRITE_PIN);
}



void HLCD_Charachter_Mode(void)
{
  /*because we need to write DATA on LCD we should Set LCD_Register_Select*/
	MDIO_set_pin(HLCD_CONTROL_PORT , HLCD_REGISTER_SELECT);
}

void HLCD_Command_Mode(void)
{

	/*because we need to write COMMAND on LCD we should Reset LCD_Register_Select*/
		MDIO_clr_pin(HLCD_CONTROL_PORT , HLCD_REGISTER_SELECT);
}


/*to send a character to LCD you should:-
 * 1- Set LCD_Read_Write to LOW to enable writing on LCD.
 * 2- Set LCD Register_select to write on it 'Character Mode'.
 * 3- Set LCD_Enable.
 * 4- Send the character.
 * 5- Set Delay.
 * 6- Clear Enable.
 *  */

void HLCD_Print_Charachter(u8 ch)
{
	MDIO_assgin_value(HLCD_DATA_PORT , ch);
	HLCD_Set_Write();
	HLCD_Charachter_Mode();
	HLCD_Set_Enable();
	Delay(1);
    HLCD_Clear_Enable();
	Delay(1);


}



void HLCD_Print_Instruction(u8 ch)
{

	MDIO_assgin_value(HLCD_DATA_PORT , ch);
	HLCD_Set_Write();
	HLCD_Command_Mode();
    HLCD_Set_Enable();
    Delay(1);
	HLCD_Clear_Enable();
	Delay(1);


}


void HLCD_Print_String(u8 arr[])
{
	u8 counter=0;
	while (arr[counter] != '\0')
	{
		HLCD_Print_Charachter(arr[counter]);
		counter++;

	}



}


void HLCD_Print_Number(u32 num)
{
	if (num ==0)
	{
		HLCD_Print_Charachter('0');

	}


	else
	{
		u32 reserved=1;
		while (num!=0)
		{
			reserved = (reserved *10)+(num %10);
			num=num/10;
		}


		while (reserved !=1)
		{
			HLCD_Print_Charachter((reserved % 10 )+48);
			reserved /=10;
		}

	}



}
void HLCD_Set_Position(u8 row , u8 colomn)
{

 if (row == 0)
 {
	 HLCD_Print_Instruction(128+colomn);
 }

 else if (row ==1)
 {
	 HLCD_Print_Instruction(128+64+colomn);
 }

}
void HLCD_init(void)
{

	/*we make PORTA (A0:A7) as LCD_DATA_Output
	 *
	 * we make PORTB (B0:B2) as LCD_Control (LCD_Enable) , (LCD_R/W) , (LCD_Register_Select)
	 * */
	MDIO_Initialize();

	Delay(50);

	/*according to QAPASS LCD Datasheet*/
		/* we made the interface of this LCD is 8-bit.
		 * number of lines is 2 lines.
		 * font size is 5*11.
		 * */
		HLCD_Print_Instruction(0b00111000);

		/*turn LCD on .
		 * set cursor off.
		 * */
		HLCD_Print_Instruction(0b00001100);

		/*
		 *
		 * display clear
		 * */

		HLCD_Print_Instruction(0b00000001);







}






