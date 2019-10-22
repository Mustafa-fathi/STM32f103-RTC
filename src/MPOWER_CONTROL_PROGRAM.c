#include "LSTD_TYPES.h"
#include "MPOWER_CONTROL_PRIVATE.h"
#include "MPOWER_CONTROL_INTERFACE.h"




void MPOWER_EnableBackupWriteProtection(void)
{
	
	
	MPOWER_CONTROL->PWR_CR &=~(1<<8);
}

void MPOWER_DisableBackupWriteProtection(void)
{
	
	
	MPOWER_CONTROL->PWR_CR |=(1<<8);
}



