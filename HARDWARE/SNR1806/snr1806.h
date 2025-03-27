#ifndef __LD3322_H
#define __LD3322_H


#define CMD_REV_OK		1
#define CMD_REV_NO_OK	!CMD_REV_OK

typedef void (*CmdCallbackFunc)(void);
typedef struct CmdHandle
{
	u8 *cmd_str;
	CmdCallbackFunc funCallback;
}CmdHandle_t;


typedef struct 
{
	u8 bl_rev_cmd_flg :1;
	u16 u16_cmd_num;
	u16 u16_cmd_len;
	u8 *pu8_rev_cmd_buf;
	CmdHandle_t *pCmdTable;
}LD3322Handle_t;
extern LD3322Handle_t gs_Ld3322Handle;
extern void ld3322_init( void );
extern void Ld3322_RevOneFrameData( u8 *pDataBuf, u16 u16DataLen);
extern void RegisterLd3322(LD3322Handle_t *psLdHandle, CmdHandle_t *pInstructionList, u16 u16ListNum );
extern void drv_Ld3322_Handle( LD3322Handle_t *psLdHandle );

#endif	/* __LD3322_H */

