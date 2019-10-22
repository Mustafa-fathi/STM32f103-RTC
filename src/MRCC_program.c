#include "LSTD_TYPES.h"
#include "MRCC_private.h"
#include "MRCC_interface.h"

void MRCC_Initialize(void)
{
	MRCC -> CR   = 0x00010000;
		MRCC -> CFGR = 0x00000001;
}

void MRCC_EnableClock(u8 Bus, u32 Peripheral)
{
	switch (Bus)
	{
		case BUS_AHB  : MRCC -> AHBENR |= Peripheral; break;

		case BUS_ABP1 : MRCC -> APB1ENR|= Peripheral; break;

		case BUS_ABP2 : MRCC -> APB2ENR|= Peripheral; break;
	}
}

void MRCC_DisableClock(u8 Bus, u32 Peripheral)
{
	switch (Bus)
	{
		case BUS_AHB  : MRCC -> AHBENR &= ~Peripheral; break;

		case BUS_ABP1 : MRCC -> APB1ENR&= ~Peripheral; break;

		case BUS_ABP2 : MRCC -> APB2ENR&= ~Peripheral; break;
	}
}
void MRCC_Reset_Backup_Domain_Registers(u8 flag)
{

	if (flag==1)
	{
	   MRCC ->BDCR |=(1<<16);
	}

	else
	{
		 MRCC ->BDCR &=~(1<<16);
	}

}


void MRCC_Enable_Low_Speed_External_Clock(void)
{
	MRCC ->BDCR |=(1<<0);
}

void MRCC_Enable_RTC_clock(void)
{
	MRCC -> BDCR |=(1<<15);
}

u8 MRCC_LSE_Ready(void)
{
	return (MRCC->BDCR & (1<<1));

}

/*
 * function Description:-
 * ----------------------
 * this function used to select the clock source of RTC
 *
 * */
void MRCC_Clock_Source(u8 clock)
{
	switch (clock)
	{
	   case  PERIPHERAL_RTC_LSE : MRCC->BDCR |=(1<<8);
	                              MRCC->BDCR &=~(1<<9);  break;

	   case PERIPHERAL_RTC_LSI :  MRCC->BDCR &=~(1<<8);
                                  MRCC->BDCR |=(1<<9);  break;

	   case PERIPHERAL_RTC_HSE :  MRCC->BDCR |=(1<<8);
                                  MRCC->BDCR |=(1<<9);  break;

	}

}


