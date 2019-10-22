#ifndef _MNVK_PRIVATE_H
#define _MNVK_PRIVATE_H



typedef struct
{
	volatile u32 ISER [32] ;
	volatile u32 ICER [32] ;
	volatile u32 ISPR [32] ;
	volatile u32 ICPR [32] ;
	volatile u32 IABR [32] ;
	//volatile u32 IPR  [32] ;
	//volatile u32 STIR [32] ;

}NVK_Type;

#define MNVK   ((volatile NVK_Type*) 0xE000E100)



#define AIRCR *((volatile u32*) 0xE000E014)

#endif
