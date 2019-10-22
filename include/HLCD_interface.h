/*
 * HLCD_interface.h
 *
 *  Created on: Jul 26, 2019
 *      Author: Hampota
 */

#ifndef HLCD_INTERFACE_H_
#define HLCD_INTERFACE_H_


#define HLCD_DATA_PORT         MDIO_PORTA
#define HLCD_CONTROL_PORT      MDIO_PORTB
#define HLCD_ENABLE_PIN             0
#define HLCD_READ_WRITE_PIN         1
#define HLCD_REGISTER_SELECT        6

void HLCD_init(void);

void Delay(u32 volatile time);

void HLCD_Set_Enable(void);
void HLCD_Clear_Enable(void);

void HLCD_Set_Write(void);
void HLCD_Set_Read(void);


void HLCD_Charachter_Mode(void);
void HLCD_Command_Mode(void);

void HLCD_Print_Charachter(u8 ch);
void HLCD_Print_Instruction(u8 ch);

void HLCD_Print_String(u8 arr[]);

void HLCD_Print_Number(u32 num);
void HLCD_Set_Position(u8 row , u8 colomn);

#endif /* HLCD_INTERFACE_H_ */
