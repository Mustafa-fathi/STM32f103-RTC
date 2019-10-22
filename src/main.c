/*
 * main.c
 *
 *  Created on: Jul 23, 2019
 *      Author: Hampota
 */
#include "LSTD_TYPES.h"
#include "MRCC_interface.h"
#include "MRTC_INTERFACE.h"
#include "MPOWER_CONTROL_INTERFACE.h"
#include "MBACKUP_Registers_interface.h"
#include "MDIO_interface.h"
#include "MNVK_interface.h"
#include "HLCD_interface.h"

const u8 month_table[12] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};

u8 cal_hour = 14;
u8 cal_date = 20;
u8 cal_month = 10;
u8 cal_minute = 55;
u8 cal_second = 10;

u16 cal_year = 2019;

u8 RTC_error;

u16 RTS_Access_Key= 0x2651;
void MRTC_Set_RTC(u32 year,u8 month, u8 date, u8 hour, u8 minute, u8 second);
u8 check_for_leap_year(u16 year);
void get_RTC(void);
u8 RTC_Init();
void Delay_ms(u32 time);

u32 g_counts;

/*this flag used to give permission to processor to read the RTC */
u8 update_time=1;

void main(void)
{

	   MRCC_Initialize();
		MRCC_EnableClock(BUS_ABP2 , PERIPHERAL_GPIOA);
		MRCC_EnableClock(BUS_ABP2 , PERIPHERAL_GPIOB);

		HLCD_init();
		HLCD_Set_Position(0,0);
		HLCD_Print_String((u8*)"--> welcome RTC <--");
		RTC_error=RTC_Init();



		if (RTC_error==1)
		{
			HLCD_Set_Position(1,1);
			HLCD_Print_String((u8*)"RTC_failed !");
			for (u8 i=0; i<100 ; i++);

		}



while(1)
{
	if (update_time ==1)
	{



	       get_RTC();
	   	HLCD_Print_Instruction(0b00000001);
	       HLCD_Set_Position(0,0);
	       HLCD_Print_Number(cal_date);
	       HLCD_Set_Position(0,3);
	       HLCD_Print_Charachter('/');
	       HLCD_Set_Position(0,4);
	       HLCD_Print_Number(cal_month);
	       HLCD_Set_Position(0,6);
	       HLCD_Print_Charachter('/');
	       HLCD_Set_Position(0,7);
	       HLCD_Print_Number(cal_year);

	       HLCD_Set_Position(1,0);
	       HLCD_Print_Number(cal_hour);
	       HLCD_Set_Position(1,3);
	       HLCD_Print_Charachter(':');
	       HLCD_Set_Position(1,4);
	       HLCD_Print_Number(cal_minute);
	       HLCD_Set_Position(1,7);
	       HLCD_Print_Charachter(':');
	       HLCD_Set_Position(1,8);
	       HLCD_Print_Number(cal_second);

	       update_time=0;
	}

	if (cal_second == 20)
	{
		cal_year = 2020;
		RTS_Access_Key ^= RTS_Access_Key ;
		RTC_Init();


	}
}

}

void Delay_ms(u32 volatile time)
{
		u32 volatile num1=900;
    u32 volatile time1 = num1*time;
    while(time1)
    {
        time1--;
    }
}

u8 RTC_Init(void)
{

	u16 time_out=0;
	/*
	 * we make this trick because stm can be reset and we dont need to make the initialization
	 * many times we just need to make it for one time
	 * so after the resetting of our stm , stm (RTC) will compare the key that stored on it's backup registers .
	 *
	 * */

	if (MBACKUP_Get_Data()!=RTS_Access_Key)
	{

		 volatile u8 not_ready=0;
	/*we already know that right after reset or power on, the backup domain and the RTC are both disabled.
	 * Furthermore the backup registers are kept in a write protected state to avoid any parasitic write.
	 * Thus we need to enable power and backup interfaces by setting PWREN and BKPEN bits in the reset and
	 * clock control APB1 interface enable register
	 * */
	MRCC_EnableClock(BUS_ABP1 , PERIPHERAL_MRTC_POWER_ENABLE);
	MRCC_EnableClock(BUS_ABP1 , PERIPHERAL_MRTC_BACKUP_ENABLE);


	/*/*we need to disable the backup register write protection using the DBP bit of PWR_CR
		 * When we configure the RTC for the first time, we must reset backup registers and
		 *  also important RTC registers like the RTC counter register to avoid any unwanted parasitic values
		 *
		 */
	MPOWER_DisableBackupWriteProtection();

	MRCC_Reset_Backup_Domain_Registers(1);
	MRCC_Reset_Backup_Domain_Registers(0);

	/*enable Low Speed External Clock */
	MRCC_Enable_Low_Speed_External_Clock();

	/*we will check if the LSE 'Low Speed Clock ' is enabled or not , so if not we will
	 * return 1 and then print initialization failed on LCD
	 * */

	not_ready=MRCC_LSE_Ready();
	while((not_ready==0 ) && (time_out<1800))
	{

		time_out++;
		Delay_ms(1);
		not_ready=MRCC_LSE_Ready();

	}

	if (time_out>=1800)
	{
		return 1 ; //this means that the clock is failed to setup
	}





	/*select LSE clock as RTC clock */
	MRCC_Clock_Source(PERIPHERAL_RTC_LSE);

	/*enable the selected clock for RTC module */
	MRCC_Enable_RTC_clock();

	/*wait until RTC registers is ready to write on it*/
	while(MRTC_Get_RTC_Operation_State() != 1);

	/*wait until RTC registers become synchronized to any updates on it */
	while(MRTC_Get_RTC_Synch_State() !=1);

	/*enable interrupt that fired when RTC reaches programmed value */
	MRTC_Enable_Interrupt(MRTC_SECOND_INTERRUPT);

	/*wait until RTC registers is ready to write on it*/
	while(MRTC_Get_RTC_Operation_State() !=1);


	/*take permissions to update RTC registers like prescaler or counter */
	MRTC_Set_Configuration_Flag();

	/*now after take the permission i can update the prescaler to get 1 second
	 * notice that as we configured before the clock freq is 32.768 kHz LSE clock
	 * so we will charge the prescaler with 32767 to obtain 1 sec
	 * */
	MRTC_Set_Prescaler(32767);


	/*now we can't change RTC basic registers
	 * because we already reset the flag that can give us
	 * the ability to modify RTC basic registers
	 *  */
	MRTC_Reset_Configuration_Flag();

	/*wait until RTC registers is ready to write on it*/
	while (MRTC_Get_RTC_Operation_State() !=1);

	/*we saved the RTC_Access_Key on Backup register so we can initialize the RTC just once , HOW ?
	 * when we compared the RTC_Acess_Key with Backup register at the first time we will notice
	 * that they are different so we will make RTC_Initialization , but the trick is we assign or store
	 * RTC_Access_Key in back-up register so after comparing the RTC_Access_Key with backup_register
	 * we will notice they are the same so the RTC_initialization will not be happen :) .
	 *
	 * */
	MBACKUP_Set_Data(RTS_Access_Key);

	MPOWER_DisableBackupWriteProtection();



	MRTC_Set_RTC(cal_year, cal_month, cal_date, cal_hour, cal_minute, cal_second);
	//MRTC_Set_RTC(2019,10,12,15,30, 35);

	}

	else
	{

		/*wait until RTC registers become synchronized to any updates on it */
			while(MRTC_Get_RTC_Synch_State() !=1);


			/*enable interrupt that fired when RTC update 1 second so we can show the whole date and time
			 *
			 * we enable the interrupt here because after resetting the interrupt is disabled according to
			 * data sheet page 489
			 * so in this case we enable the interrupt again after the reset
			 * */
			MRTC_Enable_Interrupt(MRTC_SECOND_INTERRUPT);


			/*wait until RTC registers is ready to write on it*/
			while (MRTC_Get_RTC_Operation_State() !=1);



	}

  //nvic interrupt
	MNVK_EnableInt(MRTC_NVIC_INTERRUPT_ENABLE);

	return 0;
}






void MRTC_Set_RTC(u32 year,u8 month, u8 date, u8 hour, u8 minute, u8 second)
{
	u16 i=0;
	u32 counts=0;


	/*we know that the RTC counter register is 32-bit and we setup the prescaler so RTC_counter
	 * will count every 1 second and because the register is 32-bit
	 * RTC can count until 100 year let assume the current year is 2019 so RTC can only
	 * work until 2099 after that the time will be not correct  */
	   if(year > 2099)
	    {
	        year = 2099;
	    }

	    if(year < 1970)
	    {
	        year = 1970;
	    }

	    for(i = 1970; i < year; i++)
	    {
	          if(check_for_leap_year(i) == 1)
	          {
	        	  /*leap year (in seconds) = ordinary year (in seconds) + day   (in seconds)
	        	   *leap year (in seconds) = 31563600      (in seconds) + 86400 (in seconds)
	        	   *leap year (in seconds) = 31622400
	        	   * */
	              counts += 31622400;
	          }

	          else
	          {
	        	  /*3153600 Seconds = 525600 Minutes = 8760 Hours = 365 day = 12 months =1 year
	        	   * then 1 year= 31563600 seconds
	        	   * http://convert-units.info/time/second/31536000
	        	   *
	        	   * */
	              counts += 31536000;
	          }
	    }

	    /*month -=1 , WHY ???
	     * because month_table's (array) index starts from 0
	     * also we start the looping from 0
	     *
	     * */
	    month -= 1;

	    for(i = 0; i < month; i++)
	    {
	    	  /*86400 seconds = 1 day
	    	   * let the month is February (28 day)
	    	   * and we need to convert it to seconds
	    	   * so we will multilple the number of days with number of seconds of 1 day
	    	   * to obtain the February month in seconds
	    	   * */
	          counts += (((u32 )month_table[i]) * 86400);
	    }

	    if(check_for_leap_year(cal_year) == 1)
	    {
	        counts += 86400;
	    }

	    counts += ((u32)(date - 1) * 86400);
	    counts += ((u32)hour * 3600);
	    counts += ((u32)minute * 60);
	    counts += second;

	    g_counts=counts;

	    MRCC_EnableClock(BUS_ABP1 , PERIPHERAL_MRTC_POWER_ENABLE);
	    MRCC_EnableClock(BUS_ABP1 , PERIPHERAL_MRTC_BACKUP_ENABLE);


	    MPOWER_DisableBackupWriteProtection();

	    /*take permissions to update RTC registers like prescaler or counter */
	    MRTC_Set_Configuration_Flag();

	    /*we stored the date and time in RTC*/
	    MRTC_Set_Counter(counts);

		/*now we can't change RTC basic registers */
		MRTC_Reset_Configuration_Flag();

	    while( MRTC_Get_RTC_Operation_State() !=1);


	    MPOWER_EnableBackupWriteProtection();



}


/* https://en.wikipedia.org/wiki/Leap_year
 * leap year is the year that contains one additional day
 *  */
u8 check_for_leap_year(u16 year)
{
    if(year % 4 == 0)
    {
        if(year % 100 == 0)
        {
            if(year % 400 == 0)
            {
                return 1;
            }

            else
            {
                return 0;
            }
        }

        else
        {
            return 1;
        }
    }

    else
    {
        return 0;
    }
}

/*
 * Reading time is just the opposite of setting it.
 * The RTC counter registers are read and the current count is stored in a variable.
 * From this variable, the code first find the number of days that has passed since epoch.
 * Based on this info, the code find current year and then current month,
 * taking leap years into account in both steps. Finally we get date and time parameters.
 * Reading time doesn’t need any special privilege as like in writing time parameters.
 * */

void get_RTC()
{

	/*this variable used to calc the number of years that the RTC counter register hold*/
     u16 years_number = 0;
     static u16 day_count;


     u32 temp = 0;
     u32 counts = 0;

     /*this variable will contain the date and time*/
     counts=MRTC_Get_Counter();

     /*86400 seconds = 1 day
      * let assume we passed year=2019 ,month=8 , day=7
      * and as we know counts contains all of this data in seconds
      * so we will convert this data to days so we can extract the month and the year
      * */
     temp = (counts / 86400);

     /*here we will extract the specified year (for example 2019)
      *as we said before the initial year is 1970 and we charge RTC_count register
      *with this value and any anther year will be added to 1970
      *let assume the current year is 1979 so the RTC_counts will contain 9 years
      *and because we need to print 1979 , we will count the number of years by subtracting 1 year
      *after each checking of leap year let assume
      *it's became 9 years
      *
      *
      *  */
     if(day_count != temp)
     {
         day_count = temp;
         years_number = 1970;  //1970 as an initial year

         /*1 year = 365 day */
         while(temp >= 365)
         {
             if(check_for_leap_year(years_number) == 1)
             {
            	 /*366 because leap year have one day plus */
                 if(temp >= 366)
                 {
                     temp -= 366;
                 }

                 else
                 {
                     break;
                 }
             }

             else
             {
                 temp -= 365;
             }

             years_number++;
         }



         cal_year = years_number;

         years_number = 0;
         /*here we will calc the number of months
          * 28 because the minimum month (February) is 28 day
          *  */
         while(temp >= 28)
         {
             if((years_number == 1) && (check_for_leap_year(cal_year) == 1))
             {
                 if(temp >= 29)
                 {
                     temp -= 29;
                 }

                 else
                 {
                     break;
                 }
             }

             else
             {
                 if(temp >= month_table[years_number])
                 {
                     temp -= ((u32)month_table[years_number]);
                 }

                 else
                 {
                     break;
                 }
             }

             years_number++;
         };

         cal_month = (years_number + 1);
        // cal_date = (temp + 1);
         cal_date = (temp );
     }

     /*temp will contains the number of hours,minutes,seconds in seconds */
     //1565593190
     //temp=25189.92
     temp = (counts % 86400);

     //hour = 11
     cal_hour = (temp / 3600);
     //minute=8.1166
     cal_minute = ((temp % 3600) / 60);
     //second=59
     cal_second = ((temp % 3600) % 60);
}





void RTC_IRQHandler(void)
{
 if(MRTC_Get_Second_Interrupt_Flag() == 1)
 {
	 MRTC_Second_Interrupt_Clear();
	 update_time=1;
 }

 /*wait until make sure that the last write on register is terminated*/
 while (MRTC_Get_RTC_Operation_State() != 1);
}



