#ifndef MRTC_INTERFACE_H
#define MRTC_INTERFACE_H

#define MRTC_OVERFLOW_INTERRUPT 1
#define MRTC_SECOND_INTERRUPT   2
#define MRTC_ALARM_INTERRUPT   4
#define MRTC_NVIC_INTERRUPT_ENABLE 3


void MRTC_Enable_Interrupt(u8 );
void MRTC_Disable_Interrupt(u8);
u8 MRTC_Get_RTC_Synch_State(void);
u8 MRTC_Get_RTC_Operation_State(void);
void MRTC_Set_Configuration_Flag(void);
void MRTC_Reset_Configuration_Flag(void);
void MRTC_Set_Prescaler(u16 prescaler_value);
void MRTC_Set_Counter(u32 data);
u8   MRTC_Get_Second_Interrupt_Flag(void);
void MRTC_Second_Interrupt_Clear(void);
void MRTC_SetCallBack(void(*ptr)(void));


#endif
