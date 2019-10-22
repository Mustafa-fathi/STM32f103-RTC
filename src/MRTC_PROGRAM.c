#include "LSTD_TYPES.h"
#include "MRTC_INTERFACE.h"
#include "MRTC_PRIVATE.h"





void (*MRTC_CallBack)(void);

u8 MRTC_Get_RTC_Operation_State(void)
{
	if ((MRTC ->RTC_CRL & (1<<5) )== 0)
	{
		return 0;
	}
	else
	{
		return 1;
	}
}



u8 MRTC_Get_RTC_Synch_State(void)
{
	if ((MRTC ->RTC_CRL & (1<<3)) == 0)
	{
		return 0;
	}

	else
	{
		return 1;
	}

}


void MRTC_Enable_Interrupt(u8 interrupt_kind){

	switch (interrupt_kind)
	{
	case MRTC_OVERFLOW_INTERRUPT : MRTC->RTC_CRH |=(1<<2); break;
	case MRTC_SECOND_INTERRUPT   : MRTC->RTC_CRH |=(1<<0); break;
	case MRTC_ALARM_INTERRUPT   : MRTC->RTC_CRH |=(1<<1);  break;



	}



}


void MRTC_Disable_Interrupt(u8 interrupt_kind){

	switch (interrupt_kind)
	{
	case MRTC_OVERFLOW_INTERRUPT : MRTC->RTC_CRH &=~(1<<2); break;
	case MRTC_SECOND_INTERRUPT   : MRTC->RTC_CRH &=~(1<<0); break;
	case MRTC_ALARM_INTERRUPT    : MRTC->RTC_CRH &=~(1<<1);  break;



	}

}

void MRTC_Set_Configuration_Flag(void)
{
	MRTC->RTC_CRL |=(1<<4);
}

void MRTC_Reset_Configuration_Flag(void)
{
	MRTC->RTC_CRL &=~(1<<4);
}


void MRTC_Set_Prescaler(u16 prescaler_value)
{
	MRTC ->RTC_PRLL = prescaler_value;
}


/*this function used to assign the data like 'day-month-year seconds-minutes-hours' to RTC */
void MRTC_Set_Counter(u32 data)
{
	u16 g_data_low=(data & 0xffff);
	u16 g_data_High=((data>>16) & 0xffff);

	MRTC ->RTC_CNTL = (data & 0xffff);
	MRTC ->RTC_CNTH = ((data>>16) & 0xffff);


}


u32 MRTC_Get_Counter(void)
{
	u32 counts=0;
	counts = (MRTC->RTC_CNTH );
	counts <<= 16;
	counts +=(MRTC->RTC_CNTL);

	return counts;
}

u8 MRTC_Get_Second_Interrupt_Flag(void)
{
	u8 flag=MRTC ->RTC_CRL&(1<<0);
	if (flag == 0)
	{
		return 0;
	}

	else
	{
	return 1;
	}

}

void MRTC_Second_Interrupt_Clear(void)
{

	MRTC ->RTC_CRL &=~(1<<0);
}


void MRTC_SetCallBack(void(*ptr)(void))
{
	MRTC_CallBack = ptr;
}


