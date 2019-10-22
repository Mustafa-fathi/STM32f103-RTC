#ifndef MDIO_PRIVATE_H
#define MDIO_PRIVATE_H

typedef struct
{
	volatile u32 CRL;
	volatile u32 CRH;
	volatile u32 IDR;
	volatile u32 ODR;
	volatile u32 BSRR;
	volatile u32 BRR;
	volatile u32 LCKR;
}GPIO_type;

#define GPIOA  ((volatile GPIO_type*) 0x40010800)
#define GPIOB  ((volatile GPIO_type*) 0x40010C00)
#define GPIOC  ((volatile GPIO_type*) 0x40011000)

#endif
