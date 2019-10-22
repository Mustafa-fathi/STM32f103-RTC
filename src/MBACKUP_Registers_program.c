#include "LSTD_TYPES.h"
#include "MBACKUP_Registers_private.h"
#include "MBACKUP_Registers_interface.h"




void MBACKUP_Set_Data(u16 data)
{
	MBACKUP_REGISTER ->BKP_DR1 = data;
	
}


u16 MBACKUP_Get_Data(void)
{
	return MBACKUP_REGISTER->BKP_DR1;

}
