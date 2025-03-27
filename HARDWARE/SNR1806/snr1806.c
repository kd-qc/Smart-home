#include <string.h>
#include "stm32f10x.h"

#include "usart.h"
#include "user_common.h"
#include "SNR1806/snr1806.h"

#ifndef NULL
#define NULL 0
#endif

static u8 gRevDataBuf[30] = { 0 };

LD3322Handle_t gs_Ld3322Handle = 
{
	.bl_rev_cmd_flg = 0,
	.u16_cmd_num = 0,
	.u16_cmd_len = 0,
	.pu8_rev_cmd_buf = gRevDataBuf,
	.pCmdTable = NULL,
};

/**
 *name: ld3322_init
 *decription: 语音识别模块初始化
*/
void ld3322_init(void)
{
	uart2_init(9600);
}

/**
 *name: ld3322_init
 *decription: 语音识别模块初始化
*/
void Ld3322_RevOneFrameData( u8 *pDataBuf, u16 u16DataLen)
{
	User_MemCpy(gs_Ld3322Handle.pu8_rev_cmd_buf, pDataBuf, u16DataLen);
	gs_Ld3322Handle.bl_rev_cmd_flg = CMD_REV_OK;
	gs_Ld3322Handle.u16_cmd_len = u16DataLen;

	DEBUG_LOG("%s", gs_Ld3322Handle.pu8_rev_cmd_buf);
}


/**
 *name: RegisterLd3322
 *decription: 注册语音模块参数列表
*/
void RegisterLd3322(LD3322Handle_t *psLdHandle, CmdHandle_t *pInstructionList, u16 u16ListNum )
{
	psLdHandle->u16_cmd_num = u16ListNum;
	psLdHandle->pCmdTable = pInstructionList;
}

/**
 *name: drv_Ld3322_Handle
 *decription: 注册语音模块参数列表
*/
void drv_Ld3322_Handle( LD3322Handle_t *psLdHandle )
{
	uint16_t index;
	if (psLdHandle->bl_rev_cmd_flg == CMD_REV_OK)
	{
		psLdHandle->bl_rev_cmd_flg = CMD_REV_NO_OK;
		for (index=0; index<psLdHandle->u16_cmd_num; index++)
		{
			if (!strcmp(psLdHandle->pCmdTable[index].cmd_str, psLdHandle->pu8_rev_cmd_buf))
			{
				psLdHandle->pCmdTable[index].funCallback();
				
				DEBUG_LOG("Ld3322 check OK\n");

				break;
			}
		}
		if (index == psLdHandle->u16_cmd_num)
		{
			DEBUG_LOG("Ld3322 Erorr\n");
		}
		User_MemSet(psLdHandle->pu8_rev_cmd_buf, 0x0, 30);
	}
}

