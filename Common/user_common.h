#ifndef __USER_COMMON_H
#define __USER_COMMON_H
/* include --------------------------------------*/
#include "sys.h"
/* define --------------------------------------*/
#define IsSetBit( reg, bit)  	((reg & bit) == bit)
#define IsResetBit( reg, bit)  	(!(reg & bit))
#define SetBit( reg, bit)  		(reg |= bit)
#define ResetBit( reg, bit)  	(reg &= (~bit))


/* typedef --------------------------------------*/
extern u8 User_MemCmp(u8 * pMem1, u8 * pMem2, u16 len);
extern u8 User_MemCpy( u8 *pDesMem, u8 *pSrcMem, u16 len);
extern u8 User_MemSet( u8 *Mem, u8 data, u16 len);


#endif /* __USER_COMMON_H */

