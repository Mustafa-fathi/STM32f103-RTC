#ifndef MRTC_PRIVATE_H
#define MRTC_PRIVATE_H


typedef struct{
	
	volatile u32 RTC_CRH;
	volatile u32 RTC_CRL;
	volatile u32 RTC_PRLH;
	volatile u32 RTC_PRLL;
	volatile u32 RTC_DIVH;
	volatile u32 RTC_DIVL;
	volatile u32 RTC_CNTH;
	volatile u32 RTC_CNTL;
	volatile u32 RTC_ALRH;
	volatile u32 RTC_ALRL;
	
	
	
	
	
}MRTC_type;



#define MRTC ((volatile MRTC_type *) 0x40002800)





#endif
