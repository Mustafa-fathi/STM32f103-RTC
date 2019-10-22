#ifndef MBACKUP_REGISTERS_PRIVATE_H
#define MBACKUP_REGISTERS_PRIVATE_H


typedef struct{
	
	
	volatile u32 reserved1;
	volatile u32 BKP_DR1;
	/*there are many registers but i dont need them */
	
}MBACKUP_REGISTERS_type;



#define MBACKUP_REGISTER ((volatile MBACKUP_REGISTERS_type *) 0x40006C00)




#endif
