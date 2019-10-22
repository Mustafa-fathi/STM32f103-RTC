#include "LSTD_TYPES.h"

#include "MNVK_private.h"
#include "MNVK_interface.h"


void MNVK_EnableInt(u8 ID )
{
	if (ID > 0 && ID <= 31 )
	{
		MNVK -> ISER[0] =(1<<ID);
	}
	else if (ID < 31 && ID <= 59 )
	{
		ID =ID -32;
		MNVK -> ISER[1] =(1<<ID);
	}
	else {}
}
void MNVK_DisableInt(u8 ID )
{
	if (ID > 0 && ID <= 31 )
	{
		MNVK -> ICER[0]=(1<<ID);
	}
	else if (ID > 31 && ID <= 59 )
	{
		ID =ID -32;
		MNVK -> ICER[1]=(1<<ID);
	}
	else {}
}

void MNVK_Set_Pending_Flag(u8 ID )
{
	if (ID > 0 && ID <= 31 )
	{
		MNVK -> ISPR[0]=(1<<ID);
	}
	else if (ID > 31 && ID <= 59 )
	{
		ID =ID -32;
		MNVK -> ISPR[1]=(1<<ID);
	}
	else {}
}


void MNVK_Clr_Pending_Flag(u8 ID )
{
	if (ID > 0 && ID <= 31 )
	{
		MNVK -> ICPR[0]=(1<<ID);
	}
	else if (ID > 31 && ID <= 59 )
	{
		ID =ID -32;
		MNVK -> ICPR[1]=(1<<ID);
	}
	else {}
}


//////////////////
void MNVK_SetPiriority(void)
{
	AIRCR=0x05FA0700;  //block nested interrupts
}



