#ifndef MRCC_INTEFACE_H
#define MRCC_INTEFACE_H

#define BUS_AHB         5
#define BUS_ABP1        7
#define BUS_ABP2        29

#define PERIPHERAL_DMA1 1
#define PERIPHERAL_DMA2 2

#define PERIPHERAL_GPIOA 0x04
#define PERIPHERAL_GPIOB 0x08
#define PERIPHERAL_GPIOC 0x16

#define PERIPHERAL_TIMER1 0x800

#define PERIPHERAL_ADC1 0x200
#define PERIPHERAL_ADC2 0x400

#define PERIPHERAL_MRTC_POWER_ENABLE  0x10000000

#define PERIPHERAL_MRTC_BACKUP_ENABLE 0x08000000

#define PERIPHERAL_AFIO 0x1


#define PERIPHERAL_RTC_LSE 11
#define PERIPHERAL_RTC_LSI 22
#define PERIPHERAL_RTC_HSE 33

void MRCC_Initialize(void);
void MRCC_EnableClock(u8 Bus, u32 Peripheral);
void MRCC_DisableClock(u8 Bus, u32 Peripheral);
void MRCC_Reset_Backup_Domain_Registers (u8 flag);
void MRCC_Enable_Low_Speed_External_Clock(void);
u8 MRCC_LSE_Ready(void);
void MRCC_Clock_Source(u8 clock);
void MRCC_Enable_RTC_clock(void);
u32 MRTC_Get_Counter(void);







#endif
