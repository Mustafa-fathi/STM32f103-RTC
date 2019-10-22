#ifndef _MPOWER_CONTROL_PRIVATE_H
#define _MPOWER_CONTROL_PRIVATE_H


typedef struct {
	
	volatile u32 PWR_CR;
	volatile u32 PWR_CSR;
	
	
}MPOWER_CONTROL_type;



#define MPOWER_CONTROL  ((volatile MPOWER_CONTROL_type*) 0x40007000)



#endif