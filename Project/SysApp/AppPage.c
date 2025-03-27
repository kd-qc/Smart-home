/*********************************************************************************
  *Copyright(C),2020-2021, SIRI
  *FileName:  AppPage.c
  *Author:  SIRI
  *Version: v1.0.1.202211215
  *Date:  20221/12/15
  *Description:  
  *Others:  
  *Function List:  
  ||主要函数列表，每条记录应包含函数名及功能简要说明||
     1.…………
     2.…………
  *History:  
  |修改历史记录列表，每条修改记录应包含修改日期、修改者及修改内容简介||
     1.Date:
       Author:
       Modification:
     2.…………
**********************************************************************************/
	
#include "./SysApp/AppParam.h"
#include "./SysApp/AppPage.h"


//外部引用
/*extern------------------------------*/
extern void RestoreFactory( void );
extern SysParam_t SysParamHandle;

sLcdDispDelay_t gs_lcdDispDelayHandle = 
{
	.tim = { 0 , 0},
	.x = { 0 , 0},
	.y = { 0 , 0},
	.page_id = Page_Default,
	.p_SysParamHandle = &SysParamHandle,
};

/*--------------------------------------------------------------------------------*/
/*
  *Function:  app_PageMain_Event_Handle
  * Description：  //页面-主页时间处理
  *Input:  p_SysParamHandle, 系统参数句柄
  *Output:  //输出参数的说明
  *Return:  //函数返回值的说明
  *Others:  //其他说明
**/
void app_LcdDispChX( u8 index )
{
	LCD_Display_Words( 1, index+1, "*");
}
/*--------------------------------------------------------------------------------*/
/*
  *Function:  app_LcdDispChNum
  * Description：  //页面-主页时间处理
  *Input:  p_SysParamHandle, 系统参数句柄
  *Output:  //输出参数的说明
  *Return:  //函数返回值的说明
  *Others:  //其他说明
**/
void app_LcdDispChNum( u8 index, u8 num)
{
	u8 str[2];
	str[0] = '0' + num;
	str[1] = '\0';
	LCD_Display_Words( 1, index+1, str );
}

/*--------------------------------------------------------------------------------*/
/*
  *Function:  app_PageMain_Event_Handle
  * Description：  //页面-主页时间处理
  *Input:  p_SysParamHandle, 系统参数句柄
  *Output:  //输出参数的说明
  *Return:  //函数返回值的说明
  *Others:  //其他说明
**/
void app_LcdDispChNull( u8 row, u8 index )
{
	LCD_Display_Words(row, index+1, " ");
}
/*--------------------------------------------------------------------------------*/
/*
  *Function:  app_LcdClearChNull
  * Description：  //页面-主页时间处理
  *Input:  p_SysParamHandle, 系统参数句柄
  *Output:  //输出参数的说明
  *Return:  //函数返回值的说明
  *Others:  //其他说明
**/
void app_LcdClearChNull( u8 index )
{
	LCD_Display_Words(index, 0, "                ");
}

/*--------------------------------------------------------------------------------*/
/*
  *Function:  app_LcdClearChNull
  * Description：  //页面-主页时间处理
  *Input:  p_SysParamHandle, 系统参数句柄
  *Output:  //输出参数的说明
  *Return:  //函数返回值的说明
  *Others:  //其他说明
**/
void app_LcdDispDelayHandle( void )
{
	u8 index; 
	for (index=0; index<2; index++)
	{
		if (gs_lcdDispDelayHandle.tim[index] > 0)
		{
			gs_lcdDispDelayHandle.tim[index]--;
			if (gs_lcdDispDelayHandle.tim[index] == 0)
			{
				app_LcdClearChNull( gs_lcdDispDelayHandle.x[index] );
				if (gs_lcdDispDelayHandle.page_id != Page_Default)
				{
					app_DispPage(gs_lcdDispDelayHandle.p_SysParamHandle, gs_lcdDispDelayHandle.page_id);
				}
			}
		}
	}
	
}

/*--------------------------------------------------------------------------------*/
/*
  *Function:  app_LcdClearChNull
  * Description：  //页面-主页时间处理
  *Input:  p_SysParamHandle, 系统参数句柄
  *Output:  //输出参数的说明
  *Return:  //函数返回值的说明
  *Others:  //其他说明
**/
void app_LcdDispStrDelay( u8 x, u8 y, u8 *str, u32 delay_time, enumPageID_t page_id )
{	
	if (str != NULL)
	{
		LCD_Display_Words(x, y, str);
	}
	gs_lcdDispDelayHandle.page_id = page_id;
	if (gs_lcdDispDelayHandle.tim[0] == 0)
	{
		gs_lcdDispDelayHandle.x[0] = x;
		gs_lcdDispDelayHandle.tim[0] = delay_time;
	}
	else
	{
		gs_lcdDispDelayHandle.x[1] = x;
		gs_lcdDispDelayHandle.tim[1] = delay_time;
	}
}


/*--------------------------------------------------------------------------------*/
/*
  *Function:  app_DispPage
  * Description：  //页面-主页时间处理
  *Input:  p_SysParamHandle, 系统参数句柄
  *Output:  //输出参数的说明
  *Return:  //函数返回值的说明
  *Others:  //其他说明
**/
void app_DispPage( SysParam_t *p_SysParamHandle, enumPageID_t page_id)
{
	gs_lcdDispDelayHandle.tim[0] = 0;
	gs_lcdDispDelayHandle.tim[1] = 0;

	p_SysParamHandle->PageID = page_id;
	
	/* 数字缓存清零 */
	p_SysParamHandle->u8CodeNumIndex = 0;

	/* 指纹模块状态设置 */
	if (page_id == Page_Main)
	{
		p_SysParamHandle->p_as608handle->eWM = FpWork_Press;
		p_SysParamHandle->p_as608handle->esStatus = FpStatus_Check;
	}
	else
	{
		p_SysParamHandle->p_as608handle->eWM = FpWork_None;
	}
	
	/* 更新LCD事件标志 */
	SetBit(p_SysParamHandle->u8EventReg, LCD_PAGE_EVENT_BIT);
}


/*--------------------------------------------------------------------------------*/
/*
  *Function:  app_PageMain_Event_Handle
  * Description：  //页面-主页时间处理
  *Input:  p_SysParamHandle, 系统参数句柄
  *Output:  //输出参数的说明
  *Return:  //函数返回值的说明
  *Others:  //其他说明
**/
void app_PageMain_Event_Handle( SysParam_t *p_SysParamHandle )
{
	enumKeyCode_t key_code = (enumKeyCode_t)p_SysParamHandle->u8KeyCode;
	switch (key_code)
	{
		case KeyCode_Back:
			/* 数字输入，清除 */
			if (p_SysParamHandle->u8CodeNumIndex > 0)
			{
				p_SysParamHandle->u8CodeNumIndex--;
				/* lcd 去除 '*' */
				app_LcdDispChNull(1, p_SysParamHandle->u8CodeNumIndex);
			}
			break;
			
		case KeyCode_Enter:
		/* 数字输入，清除 */
			if (1 == p_SysParamHandle->u8CodeNumIndex)
			{
				if (p_SysParamHandle->InputCodes[0] == KeyCode_Num9)
				{
					app_DispPage(p_SysParamHandle, Page_Admin_Login);
				}
				else if (p_SysParamHandle->InputCodes[0] == KeyCode_Num8)
				{
					app_DispPage(p_SysParamHandle, Page_AdminRestoreFactory);
				}
			}
			else
			{
				/* 延时显示1s */
				app_LcdDispStrDelay(2, 3, "无效", 1500, Page_Default);
				/* 蜂鸣器报警 */
				longBeep( );
			}
			break;
			
		case KeyCode_Ch10:/* 符号“+” */
		case KeyCode_Ch11:/* 符号“-” */
		case KeyCode_Ch12:/* 符号“*” */
		case KeyCode_Ch13:/* 符号“#” */
			break;
		
		case KeyCode_Num0:
		case KeyCode_Num1:
		case KeyCode_Num2:
 		case KeyCode_Num3:
 		case KeyCode_Num4:
 		case KeyCode_Num5:
 		case KeyCode_Num6:
 		case KeyCode_Num7:
 		case KeyCode_Num8:
 		case KeyCode_Num9:
	 		/* 密码存入缓存 */
			p_SysParamHandle->InputCodes[p_SysParamHandle->u8CodeNumIndex] = key_code-KeyCode_Num0;
			/* 显示 字符 '*' */
			app_LcdDispChX(p_SysParamHandle->u8CodeNumIndex);
			/* 查看位数是否匹配 */
			if (p_SysParamHandle->u8CodeNumIndex == UNLOCK_PASSWORD_LEN-1)
			{
				p_SysParamHandle->u8CodeNumIndex = 0;
				/* 密码位数匹配 */
				if (!User_MemCmp(p_SysParamHandle->InputCodes, p_SysParamHandle->p_eeprom_data->UnLockPassword, UNLOCK_PASSWORD_LEN))
				{
					/* 密码匹配成功 */
					app_LcdDispStrDelay(1, 2, NULL, 1500, Page_Default);	
					app_LcdDispStrDelay(2, 2, "密码正确", 1500, Page_Default);	
					/* 开启继电器解锁 */
					Switch_On( );
				}
				else
				{
					/* 密码匹配失败 */
					app_LcdDispStrDelay(1, 2, NULL, 1500, Page_Default);	
					app_LcdDispStrDelay(2, 2, "密码错误", 1500, Page_Default);
					/* 蜂鸣器报警 */
					longBeep( );
				}
				delay_ms(1500);
			}
			else
			{
				p_SysParamHandle->u8CodeNumIndex++;
			}
 			break;

 		default:
 			break;
	}
}

/*--------------------------------------------------------------------------------*/
/*
  *Function:  app_PageAdminLogin_Event_Handle
  * Description：  //页面-主页时间处理
  *Input:  p_SysParamHandle, 系统参数句柄
  *Output:  //输出参数的说明
  *Return:  //函数返回值的说明
  *Others:  //其他说明
**/
void app_PageAdminLogin_Event_Handle( SysParam_t *p_SysParamHandle )
{
	enumKeyCode_t key_code = (enumKeyCode_t)p_SysParamHandle->u8KeyCode;
	switch (key_code)
	{
		case KeyCode_Back:
			/* 数字输入，清除 */
			if (p_SysParamHandle->u8CodeNumIndex > 0)
			{
				p_SysParamHandle->u8CodeNumIndex--;
				/* lcd 去除 '*' */
				app_LcdDispChNull(1, p_SysParamHandle->u8CodeNumIndex);
			}
			else
			{
				app_DispPage(p_SysParamHandle, Page_Main);
			}
			break;
			
		case KeyCode_Enter:
			break;
			
		case KeyCode_Ch10:/* 符号“+” */
		case KeyCode_Ch11:/* 符号“-” */
		case KeyCode_Ch12:/* 符号“*” */
		case KeyCode_Ch13:/* 符号“#” */
			break;
		
		case KeyCode_Num0:
		case KeyCode_Num1:
		case KeyCode_Num2:
 		case KeyCode_Num3:
 		case KeyCode_Num4:
 		case KeyCode_Num5:
 		case KeyCode_Num6:
 		case KeyCode_Num7:
 		case KeyCode_Num8:
 		case KeyCode_Num9:
 			/* 密码存入缓存 */
			p_SysParamHandle->InputCodes[p_SysParamHandle->u8CodeNumIndex] = key_code;
			/* 显示 字符 '*' */
			app_LcdDispChX(p_SysParamHandle->u8CodeNumIndex);
			/* 查看位数是否匹配 */
			if (p_SysParamHandle->u8CodeNumIndex == ADMIN_PASSWORD_LEN-1)
			{
				p_SysParamHandle->u8CodeNumIndex = 0;
				/* 密码位数匹配 */
				if (!User_MemCmp(p_SysParamHandle->InputCodes, p_SysParamHandle->p_eeprom_data->AdminPassword, ADMIN_PASSWORD_LEN))
				{
					/* 密码匹配成功 */
					app_DispPage(p_SysParamHandle, Page_Admin);
				}
				else
				{
					app_LcdDispStrDelay(1, 2, NULL, 1500, Page_Default);
					app_LcdDispStrDelay(2, 2, "密码错误", 1500, Page_Default);
					/* 蜂鸣器报警 */
					longBeep( );
				}
			}
			else
			{
				p_SysParamHandle->u8CodeNumIndex++;
			}
 			break;

 		default:
 			break;
	}
}

/*--------------------------------------------------------------------------------*/
/*
  *Function:  app_PageAdminLogin_Event_Handle
  * Description：  //页面-主页时间处理
  *Input:  p_SysParamHandle, 系统参数句柄
  *Output:  //输出参数的说明
  *Return:  //函数返回值的说明
  *Others:  //其他说明
**/
void app_PageAdmin_Event_Handle( SysParam_t *p_SysParamHandle )
{
	enumKeyCode_t key_code = (enumKeyCode_t)p_SysParamHandle->u8KeyCode;
	switch (key_code)
	{
		case KeyCode_Back:
			/* 切换页面 */
			app_DispPage(p_SysParamHandle, Page_Admin_Login);
			break;
			
		case KeyCode_Enter:
			/* 一位 */ 
			if (p_SysParamHandle->u2AdminMngI == 0)
			{
				/* 切换页面 */
				app_DispPage(p_SysParamHandle, Page_AdminPasswordManage);
			}
			else if (p_SysParamHandle->u2AdminMngI == 1)
			{
				/* 切换页面 */
				app_DispPage(p_SysParamHandle, Page_AdminFingerprintManage);
			}
			else if (p_SysParamHandle->u2AdminMngI == 2)
			{
				/* 切换页面 */
				app_DispPage(p_SysParamHandle, Page_AdminRFIDManage);
			} 
			else
			{
				/* 切换页面 */
				app_DispPage(p_SysParamHandle, Page_AdminWifiConfig);
			}
			break;
			
		case KeyCode_Ch10:/* 符号“+” */
			if (p_SysParamHandle->u2AdminMngI < 2)
			{
				LCD_Display_Words( p_SysParamHandle->u2AdminMngI , 0, " ");
				LCD_Display_Words( ++p_SysParamHandle->u2AdminMngI , 0, "*");
			}
			else if (p_SysParamHandle->u2AdminMngI == 2)
			{
				/*!< 切换下页面 */
				app_LcdClearChNull( 0 );
				app_LcdClearChNull( 1 );
				app_LcdClearChNull( 2 );
				
				LCD_Display_Words(0, 0, "    WIFI配网");
				
				++p_SysParamHandle->u2AdminMngI;
				LCD_Display_Words( 0, 0, "*");
			}
			/* 密码匹配失败 */
			break;
		
		case KeyCode_Ch11:/* 符号“-” */
			if (p_SysParamHandle->u2AdminMngI == 3)
			{
				/*!< 切换上页面 */
				app_LcdClearChNull( 0 );

				LCD_Display_Words(0, 0, "    密码管理");
				LCD_Display_Words(1, 0, "    指纹管理");
				LCD_Display_Words(2, 0, "    ID卡管理");
				
				LCD_Display_Words( --p_SysParamHandle->u2AdminMngI , 0, "*");
			}
			else if (p_SysParamHandle->u2AdminMngI > 0)
			{
				LCD_Display_Words( p_SysParamHandle->u2AdminMngI , 0, " ");
				LCD_Display_Words( --p_SysParamHandle->u2AdminMngI , 0, "*");
			}
			break;
			
		case KeyCode_Ch12:/* 符号“*” */
		case KeyCode_Ch13:/* 符号“#” */
			break;
		
		case KeyCode_Num0:
		case KeyCode_Num1:
		case KeyCode_Num2:
 		case KeyCode_Num3:
 		case KeyCode_Num4:
 		case KeyCode_Num5:
 		case KeyCode_Num6:
 		case KeyCode_Num7:
 		case KeyCode_Num8:
 		case KeyCode_Num9:
 			break;

 		default:
 			break;
	}
}

/*--------------------------------------------------------------------------------*/
/*
  *Function:  app_PagePasswordManage_Event_Handle
  * Description：  //页面-主页时间处理
  *Input:  p_SysParamHandle, 系统参数句柄
  *Output:  //输出参数的说明
  *Return:  //函数返回值的说明
  *Others:  //其他说明
**/
void app_PagePasswordManage_Event_Handle( SysParam_t *p_SysParamHandle )
{
	enumKeyCode_t key_code = (enumKeyCode_t)p_SysParamHandle->u8KeyCode;
	switch (key_code)
	{
		case KeyCode_Back:
			/* 切换页面 */
			app_DispPage(p_SysParamHandle, Page_Admin);
			break;
			
		case KeyCode_Enter:
			/* 一位 */ 
			(p_SysParamHandle->u2AdminPwMngI == 0) ? \
 			app_DispPage(p_SysParamHandle, Page_UnlockPassword) : \
 			app_DispPage(p_SysParamHandle, Page_AdminPassword);
			break;
			
		case KeyCode_Ch10:/* 符号“+” */
			if (p_SysParamHandle->u2AdminPwMngI < 1)
			{
				LCD_Display_Words( p_SysParamHandle->u2AdminPwMngI + 1, 0, " " );
				LCD_Display_Words( ++p_SysParamHandle->u2AdminPwMngI + 1, 0, "*" );
			}
			/* 密码匹配失败 */
			break;
		
		case KeyCode_Ch11:/* 符号“-” */
			if (p_SysParamHandle->u2AdminPwMngI > 0)
			{
				LCD_Display_Words( p_SysParamHandle->u2AdminPwMngI + 1, 0, " ");
				LCD_Display_Words( --p_SysParamHandle->u2AdminPwMngI + 1, 0, "*");
			}
			break;
			
		case KeyCode_Ch12:/* 符号“*” */
		case KeyCode_Ch13:/* 符号“#” */
			break;
		
		case KeyCode_Num0:
		case KeyCode_Num1:
		case KeyCode_Num2:
 		case KeyCode_Num3:
 		case KeyCode_Num4:
 		case KeyCode_Num5:
 		case KeyCode_Num6:
 		case KeyCode_Num7:
 		case KeyCode_Num8:
 		case KeyCode_Num9:
 			break;

 		default:
 			break;
	}
}

/*--------------------------------------------------------------------------------*/
/*
  *Function:  app_PagePasswordManage_Event_Handle
  * Description：  //页面-主页时间处理
  *Input:  p_SysParamHandle, 系统参数句柄
  *Output:  //输出参数的说明
  *Return:  //函数返回值的说明
  *Others:  //其他说明
**/
void app_PageFP_and_PageRF_Manage_Event_Handle( SysParam_t *p_SysParamHandle )
{
	enumKeyCode_t key_code = (enumKeyCode_t)p_SysParamHandle->u8KeyCode;
	switch (key_code)
	{
		case KeyCode_Back:
			/* 切换页面 */
			app_DispPage(p_SysParamHandle, Page_Admin);
			break;
			
		case KeyCode_Enter:
			if (p_SysParamHandle->PageID == Page_AdminFingerprintManage)
			{
				/* 一位 */ 
				(p_SysParamHandle->u2FigrPrtMngI == 0) ? \
	 			app_DispPage(p_SysParamHandle, Page_AdminFingerprintInput) : \
	 			app_DispPage(p_SysParamHandle, Page_AdminFingerprintDelete);
			}
			else
			{
				/* 一位 */ 
				(p_SysParamHandle->u2RFIDMngI == 0) ? \
	 			app_DispPage(p_SysParamHandle, Page_AdminRFIDInput) : \
	 			app_DispPage(p_SysParamHandle, Page_AdminRFIDDelete);
			}
			break;
			
		case KeyCode_Ch10:/* 符号“+” */
			if (p_SysParamHandle->PageID == Page_AdminFingerprintManage)
			{
				if (p_SysParamHandle->u2FigrPrtMngI < 1)
				{
					LCD_Display_Words( p_SysParamHandle->u2FigrPrtMngI + 1, 0, " " );
					LCD_Display_Words( ++p_SysParamHandle->u2FigrPrtMngI + 1, 0, "*" );
				}
			}
			else
			{
				if (p_SysParamHandle->u2RFIDMngI < 1)
				{
					LCD_Display_Words( p_SysParamHandle->u2RFIDMngI + 1, 0, " " );
					LCD_Display_Words( ++p_SysParamHandle->u2RFIDMngI + 1, 0, "*" );
				}
			}
			break;
		
		case KeyCode_Ch11:/* 符号“-” */
			if (p_SysParamHandle->PageID == Page_AdminFingerprintManage)
			{
				if (p_SysParamHandle->u2FigrPrtMngI > 0)
				{
					LCD_Display_Words( p_SysParamHandle->u2FigrPrtMngI + 1, 0, " " );
					LCD_Display_Words( --p_SysParamHandle->u2FigrPrtMngI + 1, 0, "*" );
				}
			}
			else
			{
				if (p_SysParamHandle->u2RFIDMngI > 0)
				{
					LCD_Display_Words( p_SysParamHandle->u2RFIDMngI + 1, 0, " " );
					LCD_Display_Words( --p_SysParamHandle->u2RFIDMngI + 1, 0, "*" );
				}
			}
			break;
			
		case KeyCode_Ch12:/* 符号“*” */
		case KeyCode_Ch13:/* 符号“#” */
			break;
		
		case KeyCode_Num0:
		case KeyCode_Num1:
		case KeyCode_Num2:
 		case KeyCode_Num3:
 		case KeyCode_Num4:
 		case KeyCode_Num5:
 		case KeyCode_Num6:
 		case KeyCode_Num7:
 		case KeyCode_Num8:
 		case KeyCode_Num9:
 			break;

 		default:
 			break;
	}
}

/*--------------------------------------------------------------------------------*/
/*
  *Function:  app_PageAdminPw_and_UnlockPw_Event_Handle
  * Description：  //页面-主页时间处理
  *Input:  p_SysParamHandle, 系统参数句柄
  *Output:  //输出参数的说明
  *Return:  //函数返回值的说明
  *Others:  //其他说明
**/
void app_PageAdminPw_and_UnlockPw_Event_Handle( SysParam_t *p_SysParamHandle )
{
	enumKeyCode_t key_code = (enumKeyCode_t)p_SysParamHandle->u8KeyCode;
	/* 定义密码长度 */
	u8 code_len = 0;
	switch (key_code)
	{
		case KeyCode_Back:
			/* 数字输入，清除 */
			if (p_SysParamHandle->u8CodeNumIndex > 0 && p_SysParamHandle->u8CodeNumIndex < ADMIN_PASSWORD_LEN)
			{
				p_SysParamHandle->u8CodeNumIndex--;
				/* lcd 去除 'num' */
				app_LcdDispChNull(1, p_SysParamHandle->u8CodeNumIndex);
			}
			else
			{
				app_DispPage(p_SysParamHandle, Page_AdminPasswordManage);
			}
			break;
			
		case KeyCode_Enter:
			
			break;
			
		case KeyCode_Ch10:/* 符号“+” */
			break;
		
		case KeyCode_Ch11:/* 符号“-” */
			break;
			
		case KeyCode_Ch12:/* 符号“*” */
		case KeyCode_Ch13:/* 符号“#” */
			break;
		
		case KeyCode_Num0:
		case KeyCode_Num1:
		case KeyCode_Num2:
 		case KeyCode_Num3:
 		case KeyCode_Num4:
 		case KeyCode_Num5:
 		case KeyCode_Num6:
 		case KeyCode_Num7:
 		case KeyCode_Num8:
 		case KeyCode_Num9:
 			(p_SysParamHandle->PageID == Page_AdminPassword) ? \
 			(code_len = ADMIN_PASSWORD_LEN) : \
 			(code_len = UNLOCK_PASSWORD_LEN);
			/* 查看位数是否匹配 */
			if (p_SysParamHandle->u8CodeNumIndex < code_len)
			{
	 			/* 密码存入缓存 */
				p_SysParamHandle->InputCodes[p_SysParamHandle->u8CodeNumIndex] = key_code-KeyCode_Num0;
				/* 显示 数字     */
				app_LcdDispChNum(p_SysParamHandle->u8CodeNumIndex, key_code-KeyCode_Num0 );
				/* index ++ */
				p_SysParamHandle->u8CodeNumIndex++;
				
				if (p_SysParamHandle->u8CodeNumIndex == code_len)
				{
					/* 密码匹配成功 */
					LCD_Display_Words( 2, 1, "请确认密码" );
					app_LcdDispStrDelay(1, 2, NULL, 500, Page_Default);
				}
			}
			else
			{
				/* 第二次输入 */
				if (key_code-KeyCode_Num0 != p_SysParamHandle->InputCodes[p_SysParamHandle->u8CodeNumIndex - code_len] )
				{
					/* 蜂鸣器报警 */
					longBeep( );
					app_LcdDispStrDelay(2, 1, "输入不一致", 1500, Page_Default);
					app_LcdDispStrDelay(1, 2, NULL, 1500, Page_Default);
					/* 重头输入 */
					p_SysParamHandle->u8CodeNumIndex = 0;
				}
				else
				{
					/* 显示 数字     */
					app_LcdDispChNum(p_SysParamHandle->u8CodeNumIndex- code_len, key_code-KeyCode_Num0 );
					/* 检测是否输入完成 */
					if (++p_SysParamHandle->u8CodeNumIndex == code_len * 2)
					{
						app_LcdDispStrDelay(2, 1, "密码设定成功", 1500, Page_AdminPasswordManage);
						(p_SysParamHandle->PageID == Page_AdminPassword) ? \
			 			User_MemCpy(p_SysParamHandle->p_eeprom_data->AdminPassword, p_SysParamHandle->InputCodes, code_len): \
						User_MemCpy(p_SysParamHandle->p_eeprom_data->UnLockPassword, p_SysParamHandle->InputCodes, code_len);
						/* 保存至EEPROM */
						(p_SysParamHandle->PageID == Page_AdminPassword) ? \
			 			AT24CXX_Write(ADMIN_PASSWORD_EEPROM_ADDR, p_SysParamHandle->p_eeprom_data->AdminPassword, code_len) : \
			 			AT24CXX_Write(UNLOCK_PASSWORD_EEPROM_ADDR, p_SysParamHandle->p_eeprom_data->UnLockPassword, code_len);
						
					}
				}
			}
 			break;

 		default:
 			break;
	}
}


/*--------------------------------------------------------------------------------*/
/*
  *Function:  app_PageAdminRFandFP_Event_Handle
  * Description：  //页面-主页时间处理
  *Input:  p_SysParamHandle, 系统参数句柄
  *Output:  //输出参数的说明
  *Return:  //函数返回值的说明
  *Others:  //其他说明
**/
void app_PageAdminFPandRF_Input_Event_Handle( SysParam_t *p_SysParamHandle )
{
	enumKeyCode_t key_code = (enumKeyCode_t)p_SysParamHandle->u8KeyCode;
	switch (key_code)
	{
		case KeyCode_Back:
			(p_SysParamHandle->PageID == Page_AdminFingerprintInput) ? \
			app_DispPage(p_SysParamHandle, Page_AdminFingerprintManage) : \
			app_DispPage(p_SysParamHandle, Page_AdminRFIDManage);
			break;
			
		case KeyCode_Enter:
			if (p_SysParamHandle->u8CodeNumIndex == 1)
			{
				p_SysParamHandle->u8CodeNumIndex++;
				app_LcdClearChNull(1);
				app_LcdClearChNull(2);
				if (p_SysParamHandle->PageID == Page_AdminFingerprintInput)
				{
					LCD_Display_Words(2, 2, "请录入指纹");
					p_SysParamHandle->p_as608handle->esStatus = FpStatus_Add;
					p_SysParamHandle->p_as608handle->eWM = FpWork_Press;
					p_SysParamHandle->p_as608handle->inputId = p_SysParamHandle->u8FingerPrint_ID;
				}
				else 
				{
					LCD_Display_Words(2, 2, "请刷ID卡");
				}
			}
			break;
			
		case KeyCode_Ch10:/* 符号“+” */
		case KeyCode_Ch11:/* 符号“-” */
		case KeyCode_Ch12:/* 符号“*” */
		case KeyCode_Ch13:/* 符号“#” */
			break;
		
		case KeyCode_Num0:
			break;
		case KeyCode_Num1:
		case KeyCode_Num2:
 		case KeyCode_Num3:
 		case KeyCode_Num4:
 		case KeyCode_Num5:
 		case KeyCode_Num6:
 		case KeyCode_Num7:
 		case KeyCode_Num8:
 		case KeyCode_Num9:
 			p_SysParamHandle->u8CodeNumIndex = 1;
			/* 显示 字符 '*' */
			u8 str[3];
			str[0] = ' ';
 			str[1] = '0' + key_code - KeyCode_Num0;
 			str[2] = '\0';
			LCD_Display_Words( 3, 3, str );
			/* 句柄保存id */
			(p_SysParamHandle->PageID == Page_AdminFingerprintInput) ? \
			(p_SysParamHandle->u8FingerPrint_ID = key_code) : \
			(p_SysParamHandle->u4RFCard_ID = key_code);
			
 			break;

 		default:
 			break;
	}
}

/*--------------------------------------------------------------------------------*/
/*
  *Function:  app_PageAdminFPandRF_Delete_Event_Handle
  * Description：  //页面-主页时间处理
  *Input:  p_SysParamHandle, 系统参数句柄
  *Output:  //输出参数的说明
  *Return:  //函数返回值的说明
  *Others:  //其他说明
**/
void app_PageAdminFPandRF_Delete_Event_Handle( SysParam_t *p_SysParamHandle )
{
	enumKeyCode_t key_code = (enumKeyCode_t)p_SysParamHandle->u8KeyCode;
	u8 id_str[3] = {'0', '\0', '\0'};
	switch (key_code)
	{
		case KeyCode_Back:
			(p_SysParamHandle->PageID == Page_AdminFingerprintDelete) ? \
			app_DispPage(p_SysParamHandle, Page_AdminFingerprintManage) : \
			app_DispPage(p_SysParamHandle, Page_AdminRFIDManage);
			break;
			
		case KeyCode_Enter:
			
			if (p_SysParamHandle->u8CodeNumIndex == 1)
			{
				/* 显示 字符 '*' */
				app_LcdClearChNull( 1 );
				/* 密码匹配失败 */
				app_LcdClearChNull( 2 );
				if (p_SysParamHandle->PageID == Page_AdminFingerprintDelete)
				{
					id_str[0] = '0' + p_SysParamHandle->u8FingerPrint_ID;
					LCD_Display_Words(1, 0, "    ID: ");
					LCD_Display_Words(1, 3, id_str);
					if (0x00 == PS_DeletChar(p_SysParamHandle->u8FingerPrint_ID, 1))//删除单个指纹
					{
						app_LcdDispStrDelay(1, 0, NULL, 1500, Page_AdminFingerprintManage);					
						app_LcdDispStrDelay(2, 0, "    删除成功   ", 1500, Page_AdminFingerprintManage);
					}
					else
					{
						app_LcdDispStrDelay(2, 0, "    删除失败   ", 1500, Page_AdminFingerprintManage);
					}
				}
				else
				{
					id_str[0] = '0' + p_SysParamHandle->u4RFCard_ID;
					LCD_Display_Words(1, 0, "    ID卡: ");
					LCD_Display_Words(1, 5, id_str);
					app_LcdDispStrDelay(1, 0, NULL, 1500, Page_AdminRFIDManage);					
					app_LcdDispStrDelay(2, 0, "    删除成功   ", 1500, Page_AdminRFIDManage);
					

					User_MemSet((u8 *)&p_SysParamHandle->p_eeprom_data->IDCardSN[p_SysParamHandle->u4RFCard_ID-1][0], \
								0x00, IDCARE_SN_LEN);
					AT24CXX_Write(IDCARE_SN_EEPROM_ADDR+p_SysParamHandle->u4RFCard_ID-1, \
								  (u8 *)&p_SysParamHandle->p_eeprom_data->IDCardSN[p_SysParamHandle->u4RFCard_ID-1][0], \
								  IDCARE_SN_LEN);
				}
				
			}
			break;
			
		case KeyCode_Ch10:/* 符号“+” */
		case KeyCode_Ch11:/* 符号“-” */
		case KeyCode_Ch12:/* 符号“*” */
		case KeyCode_Ch13:/* 符号“#” */
			break;
		
		case KeyCode_Num0:
			break;
		case KeyCode_Num1:
		case KeyCode_Num2:
 		case KeyCode_Num3:
 		case KeyCode_Num4:
 		case KeyCode_Num5:
 		case KeyCode_Num6:
 		case KeyCode_Num7:
 		case KeyCode_Num8:
 		case KeyCode_Num9:
 			p_SysParamHandle->u8CodeNumIndex = 1;
 			/* 显示 字符 '*' */
			id_str[0] = ' ';
 			id_str[1] = '0' + key_code - KeyCode_Num0;
 			id_str[2] = '\0';
			LCD_Display_Words( 3, 3, id_str );
			/* 句柄保存id */
			(p_SysParamHandle->PageID == Page_AdminFingerprintDelete) ? \
			(p_SysParamHandle->u8FingerPrint_ID = key_code) : \
			(p_SysParamHandle->u4RFCard_ID = key_code);
			
 			break;
			
 		default:
 			break;
	}
}

/*--------------------------------------------------------------------------------*/
/*
  *Function:  app_PageAdminRFandFP_Event_Handle
  * Description：  //页面-主页时间处理
  *Input:  p_SysParamHandle, 系统参数句柄
  *Output:  //输出参数的说明
  *Return:  //函数返回值的说明
  *Others:  //其他说明
**/
void app_PageAdminRF_Input_Event_Handle( SysParam_t *p_SysParamHandle )
{
	enumKeyCode_t key_code = (enumKeyCode_t)p_SysParamHandle->u8KeyCode;
	switch (key_code)
	{
		case KeyCode_Back:
			app_DispPage(p_SysParamHandle, Page_AdminRFIDManage);
			break;
			
		case KeyCode_Enter:
			if (p_SysParamHandle->u8CodeNumIndex == 1)
			{
				p_SysParamHandle->u8CodeNumIndex++;
				app_LcdClearChNull(1);
				app_LcdClearChNull(2);
				
				LCD_Display_Words(2, 2, "请刷ID卡");
			}
			break;
			
		case KeyCode_Ch10:/* 符号“+” */
		case KeyCode_Ch11:/* 符号“-” */
		case KeyCode_Ch12:/* 符号“*” */
		case KeyCode_Ch13:/* 符号“#” */
			break;
		
		case KeyCode_Num0:
			break;
		case KeyCode_Num1:
		case KeyCode_Num2:
 		case KeyCode_Num3:
 		case KeyCode_Num4:
 		case KeyCode_Num5:
 		case KeyCode_Num6:
 		case KeyCode_Num7:
 		case KeyCode_Num8:
 		case KeyCode_Num9:
 			p_SysParamHandle->u8CodeNumIndex = 1;
			/* 显示 字符 '*' */
			u8 str[3];
			str[0] = ' ';
 			str[1] = '0' + key_code - KeyCode_Num0;
 			str[2] = '\0';
			LCD_Display_Words( 3, 3, str );
			/* 句柄保存id */
			p_SysParamHandle->u4RFCard_ID = key_code;
			
 			break;

 		default:
 			break;
	}
}


/*--------------------------------------------------------------------------------*/
/*
  *Function:  app_PageAdminRF_Delete_Event_Handle
  * Description：  //页面-主页时间处理
  *Input:  p_SysParamHandle, 系统参数句柄
  *Output:  //输出参数的说明
  *Return:  //函数返回值的说明
  *Others:  //其他说明
**/
void app_PageAdminRF_Delete_Event_Handle( SysParam_t *p_SysParamHandle )
{
	enumKeyCode_t key_code = (enumKeyCode_t)p_SysParamHandle->u8KeyCode;
	u8 id_str[3] = {'0', '\0', '\0'};
	switch (key_code)
	{
		case KeyCode_Back:
			app_DispPage(p_SysParamHandle, Page_AdminRFIDManage);
			break;
			
		case KeyCode_Enter:
			
			if (p_SysParamHandle->u8CodeNumIndex == 1)
			{
				/* 显示 字符 '*' */
				app_LcdClearChNull( 1 );
				/* 密码匹配失败 */
				app_LcdClearChNull( 2 );
				id_str[0] = '0' + p_SysParamHandle->u4RFCard_ID;
				LCD_Display_Words(1, 0, "    ID卡: ");
				LCD_Display_Words(1, 5, id_str);
				app_LcdDispStrDelay(1, 0, NULL, 1500, Page_AdminRFIDManage);					
				app_LcdDispStrDelay(2, 0, "    删除成功   ", 1500, Page_AdminRFIDManage);
				

				User_MemSet((u8 *)&p_SysParamHandle->p_eeprom_data->IDCardSN[p_SysParamHandle->u4RFCard_ID-1][0], \
							0x00, IDCARE_SN_LEN);
				AT24CXX_Write(IDCARE_SN_EEPROM_ADDR+p_SysParamHandle->u4RFCard_ID-1, \
							  (u8 *)&p_SysParamHandle->p_eeprom_data->IDCardSN[p_SysParamHandle->u4RFCard_ID-1][0], \
							  IDCARE_SN_LEN);
			}
			break;
			
		case KeyCode_Ch10:/* 符号“+” */
		case KeyCode_Ch11:/* 符号“-” */
		case KeyCode_Ch12:/* 符号“*” */
		case KeyCode_Ch13:/* 符号“#” */
			break;
		
		case KeyCode_Num0:
			break;
		case KeyCode_Num1:
		case KeyCode_Num2:
 		case KeyCode_Num3:
 		case KeyCode_Num4:
 		case KeyCode_Num5:
 		case KeyCode_Num6:
 		case KeyCode_Num7:
 		case KeyCode_Num8:
 		case KeyCode_Num9:
 			p_SysParamHandle->u8CodeNumIndex = 1;
 			/* 显示 字符 '*' */
			id_str[0] = ' ';
 			id_str[1] = '0' + key_code - KeyCode_Num0;
 			id_str[2] = '\0';
			LCD_Display_Words( 3, 3, id_str );
			/* 句柄保存id */
			p_SysParamHandle->u4RFCard_ID = key_code;
			
 			break;
			
 		default:
 			break;
	}
}

/*--------------------------------------------------------------------------------*/
/*
  *Function:  app_PageAdminFP_Input_Event_Handle
  * Description：  //页面-主页时间处理
  *Input:  p_SysParamHandle, 系统参数句柄
  *Output:  //输出参数的说明
  *Return:  //函数返回值的说明
  *Others:  //其他说明
**/
void app_PageAdminFP_Input_Event_Handle( SysParam_t *p_SysParamHandle )
{
	enumKeyCode_t key_code = (enumKeyCode_t)p_SysParamHandle->u8KeyCode;
 	u8 str[5] = { 0 };
	switch (key_code)
	{
		case KeyCode_Back:
			/* 数字输入，清除 */
			if (p_SysParamHandle->u8CodeNumIndex > 0)
			{
				p_SysParamHandle->u8CodeNumIndex--;
				p_SysParamHandle->u8FingerPrint_ID /= 10;
				/* lcd 去除 '*' */
				int2str(p_SysParamHandle->u8FingerPrint_ID, str);				
				LCD_Display_Words( 3, 3, "  " );
 				LCD_Display_Words( 3, 3, str );
			}
			else
			{
				app_DispPage(p_SysParamHandle, Page_AdminFingerprintManage);
			}
			break;
			
		case KeyCode_Enter:
			if (p_SysParamHandle->u8CodeNumIndex > 0)
			{
				p_SysParamHandle->u8CodeNumIndex = 0;
				app_LcdClearChNull(1);
				app_LcdClearChNull(2);
				LCD_Display_Words(2, 2, "请录入指纹");
				p_SysParamHandle->p_as608handle->esStatus = FpStatus_Add;
				p_SysParamHandle->p_as608handle->eWM = FpWork_Press;
				p_SysParamHandle->p_as608handle->inputId = p_SysParamHandle->u8FingerPrint_ID;
				//索引清零
				p_SysParamHandle->u8FingerPrint_ID = 0;
			}
			break;
			
		case KeyCode_Ch10:/* 符号“+” */
		case KeyCode_Ch11:/* 符号“-” */
		case KeyCode_Ch12:/* 符号“*” */
		case KeyCode_Ch13:/* 符号“#” */
			break;
		
		case KeyCode_Num0:
		case KeyCode_Num1:
		case KeyCode_Num2:
 		case KeyCode_Num3:
 		case KeyCode_Num4:
 		case KeyCode_Num5:
 		case KeyCode_Num6:
 		case KeyCode_Num7:
 		case KeyCode_Num8:
 		case KeyCode_Num9:
 			if (p_SysParamHandle->u8CodeNumIndex < 2)
 			{
 				p_SysParamHandle->u8CodeNumIndex++;
 				p_SysParamHandle->u8FingerPrint_ID *= 10;
 				p_SysParamHandle->u8FingerPrint_ID += key_code;
 				int2str(p_SysParamHandle->u8FingerPrint_ID, str);
 				LCD_Display_Words( 3, 3, str );
 			}
 			break;

 		default:
 			break;
	}
}

/*--------------------------------------------------------------------------------*/
/*
  *Function:  app_PageAdminFP_Delete_Event_Handle
  * Description：  //页面-主页时间处理
  *Input:  p_SysParamHandle, 系统参数句柄
  *Output:  //输出参数的说明
  *Return:  //函数返回值的说明
  *Others:  //其他说明
**/
void app_PageAdminFP_Delete_Event_Handle( SysParam_t *p_SysParamHandle )
{
	enumKeyCode_t key_code = (enumKeyCode_t)p_SysParamHandle->u8KeyCode;
	u8 str[5] = { 0 };
	switch (key_code)
	{
		case KeyCode_Back:
			/* 数字输入，清除 */
			if (p_SysParamHandle->u8CodeNumIndex > 0)
			{
				p_SysParamHandle->u8CodeNumIndex--;
				p_SysParamHandle->u8FingerPrint_ID /= 10;
				/* lcd 去除 '*' */
				int2str(p_SysParamHandle->u8FingerPrint_ID, str);
				LCD_Display_Words( 3, 3, "  " );
 				LCD_Display_Words( 3, 3, str );
			}
			else
			{
				app_DispPage(p_SysParamHandle, Page_AdminFingerprintManage);
			}
			break;
			
		case KeyCode_Enter:
			
			if (p_SysParamHandle->u8CodeNumIndex > 0)
			{
				/* 显示 字符 '*' */
				app_LcdClearChNull( 1 );
				/* 密码匹配失败 */
				app_LcdClearChNull( 2 );
				
				int2str(p_SysParamHandle->u8FingerPrint_ID, str);
				LCD_Display_Words(1, 0, "    ID: ");
				LCD_Display_Words(1, 5, str);
				if (0x00 == PS_DeletChar(p_SysParamHandle->u8FingerPrint_ID, 1))//删除单个指纹
				{
					app_LcdDispStrDelay(1, 0, NULL, 1500, Page_AdminFingerprintManage);					
					app_LcdDispStrDelay(2, 0, "    删除成功   ", 1500, Page_AdminFingerprintManage);
				}
				else
				{
					app_LcdDispStrDelay(2, 0, "    删除失败   ", 1500, Page_AdminFingerprintManage);
				}

				p_SysParamHandle->u8FingerPrint_ID = 0;
				
			}
			break;
			
		case KeyCode_Ch10:/* 符号“+” */
		case KeyCode_Ch11:/* 符号“-” */
		case KeyCode_Ch12:/* 符号“*” */
		case KeyCode_Ch13:/* 符号“#” */
			break;
		
		case KeyCode_Num0:
		case KeyCode_Num1:
		case KeyCode_Num2:
 		case KeyCode_Num3:
 		case KeyCode_Num4:
 		case KeyCode_Num5:
 		case KeyCode_Num6:
 		case KeyCode_Num7:
 		case KeyCode_Num8:
 		case KeyCode_Num9:
 			if (p_SysParamHandle->u8CodeNumIndex < 2)
 			{
 				p_SysParamHandle->u8CodeNumIndex++;
 				p_SysParamHandle->u8FingerPrint_ID *= 10;
 				p_SysParamHandle->u8FingerPrint_ID += key_code;
 				int2str(p_SysParamHandle->u8FingerPrint_ID, str);
 				LCD_Display_Words( 3, 3, str );
 			}
 			break;
 			
 		default:
 			break;
	}
}

/*--------------------------------------------------------------------------------*/
/*
  *Function:  app_PageWifiConfig_Event_Handle
  * Description：  //页面-主页时间处理
  *Input:  p_SysParamHandle, 系统参数句柄
  *Output:  //输出参数的说明
  *Return:  //函数返回值的说明
  *Others:  //其他说明
**/
void app_PageWifiConfig_Event_Handle( SysParam_t *p_SysParamHandle )
{
	enumKeyCode_t key_code = (enumKeyCode_t)p_SysParamHandle->u8KeyCode;
	switch (key_code)
	{
		case KeyCode_Back:
			/* 切换页面 */
			app_DispPage(p_SysParamHandle, Page_Admin);
			break;
			
		case KeyCode_Enter:
		
			/* 一位 */ 
			if (p_SysParamHandle->u1WifiConfigI == 0)
			{
				gizwitsSetMode(WIFI_SOFTAP_MODE);
			}
			else
			{
				gizwitsSetMode(WIFI_AIRLINK_MODE);
			}
			
			app_LcdDispStrDelay(2, 2, "设置成功", 1500, Page_Admin);
			break;
			
		case KeyCode_Ch10:/* 符号“+” */
			if (p_SysParamHandle->u1WifiConfigI < 1)
			{
				LCD_Display_Words( p_SysParamHandle->u1WifiConfigI+1, 0, " ");
				LCD_Display_Words( ++p_SysParamHandle->u1WifiConfigI+1, 0, "*");
			}
			/* 密码匹配失败 */
			break;
		
		case KeyCode_Ch11:/* 符号“-” */
			if (p_SysParamHandle->u2AdminMngI > 0)
			{
				LCD_Display_Words( p_SysParamHandle->u1WifiConfigI+1, 0, " ");
				LCD_Display_Words( --p_SysParamHandle->u1WifiConfigI+1, 0, "*");

			}
			break;
			
		case KeyCode_Ch12:/* 符号“*” */
		case KeyCode_Ch13:/* 符号“#” */
			break;
		
		case KeyCode_Num0:
		case KeyCode_Num1:
		case KeyCode_Num2:
 		case KeyCode_Num3:
 		case KeyCode_Num4:
 		case KeyCode_Num5:
 		case KeyCode_Num6:
 		case KeyCode_Num7:
 		case KeyCode_Num8:
 		case KeyCode_Num9:
 			break;

 		default:
 			break;
	}
}

/*--------------------------------------------------------------------------------*/
/*
  *Function:  app_PageAdminLogin_Event_Handle
  * Description：  //页面-主页时间处理
  *Input:  p_SysParamHandle, 系统参数句柄
  *Output:  //输出参数的说明
  *Return:  //函数返回值的说明
  *Others:  //其他说明
**/
void app_PageRestoreFactory_Event_Handle( SysParam_t *p_SysParamHandle )
{
	enumKeyCode_t key_code = (enumKeyCode_t)p_SysParamHandle->u8KeyCode;
	switch (key_code)
	{
		case KeyCode_Back:
			/* 数字输入，清除 */
			if (p_SysParamHandle->u8CodeNumIndex > 0)
			{
				p_SysParamHandle->u8CodeNumIndex--;
				/* lcd 去除 '*' */
				app_LcdDispChNull(1, p_SysParamHandle->u8CodeNumIndex);
			}
			else
			{
				app_DispPage(p_SysParamHandle, Page_Main);
			}
			break;
			
		case KeyCode_Enter:
			break;
			
		case KeyCode_Ch10:/* 符号“+” */
		case KeyCode_Ch11:/* 符号“-” */
		case KeyCode_Ch12:/* 符号“*” */
			break;
		case KeyCode_Ch13:/* 符号“#” */
		case KeyCode_Num0:
		case KeyCode_Num1:
		case KeyCode_Num2:
 		case KeyCode_Num3:
 		case KeyCode_Num4:
 		case KeyCode_Num5:
 		case KeyCode_Num6:
 		case KeyCode_Num7:
 		case KeyCode_Num8:
 		case KeyCode_Num9:
 			/* 密码存入缓存 */
			p_SysParamHandle->InputCodes[p_SysParamHandle->u8CodeNumIndex] = key_code ;
			/* 显示 字符 '*' */
			app_LcdDispChX(p_SysParamHandle->u8CodeNumIndex);
			/* 查看位数是否匹配 */
			if (p_SysParamHandle->u8CodeNumIndex == ADMIN_PASSWORD_LEN-1)
			{
				p_SysParamHandle->u8CodeNumIndex = 0;
				for (u8 i=0; i<ADMIN_PASSWORD_LEN; i++)
				{
					/* 密码位数匹配 */
					if (p_SysParamHandle->InputCodes[i] == KeyCode_Ch13)
					{
						continue;
					}
					else
					{
						/* 密码匹配失败 */
						app_LcdDispStrDelay(1, 2, NULL, 1500, Page_Default);
						app_LcdDispStrDelay(2, 2, "密码错误", 1500, Page_Default);
						/* 蜂鸣器报警 */
						longBeep( );
						return;
					}
				}
				/* 密码匹配成功--恢复出厂 */
				RestoreFactory( );
			}
			else
			{
				p_SysParamHandle->u8CodeNumIndex++;
			}
 			break;

 		default:
 			break;
	}
}

/*--------------------------------------------------------------------------------*/
/*
  *Function:  app_DispPageHandle
  * Description：  //页面-主页时间处理
  *Input:  p_SysParamHandle, 系统参数句柄
  *Output:  //输出参数的说明
  *Return:  //函数返回值的说明
  *Others:  //其他说明
**/
void app_PageEvent_Handle( SysParam_t *p_SysParamHandle )
{
	enumPageID_t page_id = p_SysParamHandle->PageID;
	if (IsSetBit(p_SysParamHandle->u8EventReg, LCD_PAGE_EVENT_BIT))
	{
		ResetBit(p_SysParamHandle->u8EventReg, LCD_PAGE_EVENT_BIT);
		/* 清空页面 */
		LCD_Clear();
		switch (page_id)
		{
			case Page_Main:
				LCD_Display_Words(0, 1, "智能门禁系统");
				LCD_Display_Words(3, 5, "Enter");
				break;
				
			case Page_Admin_Login:
				LCD_Display_Words(0, 0, "请输入管理员密码");
				LCD_Display_Words(3, 0, "Back");	
				break;

			case Page_AdminPasswordManage:
				LCD_Display_Words(0, 0, "****密码管理****");
				LCD_Display_Words(1, 0, "  修改解锁密码");
				LCD_Display_Words(2, 0, "  修改管理密码");
				LCD_Display_Words(3, 0, "Back       Enter");

				
				LCD_Display_Words(p_SysParamHandle->u2AdminPwMngI + 1, 0, "*");
				break;

			case Page_UnlockPassword:
				LCD_Display_Words(0, 0, "请输入新解锁密码");
				LCD_Display_Words(3, 0, "Back");
				break;

			case Page_AdminPassword:
				LCD_Display_Words(0, 0, "请输入新管理密码");
				LCD_Display_Words(3, 0, "Back");
				break;

			case Page_Admin:
				if (p_SysParamHandle->u2AdminMngI == 3)
				{
					LCD_Display_Words(0, 0, "    WIFI配网");
					LCD_Display_Words(0, 0, "*");
				}
				else
				{
					LCD_Display_Words(0, 0, "    密码管理");
					LCD_Display_Words(1, 0, "    指纹管理");
					LCD_Display_Words(2, 0, "    ID卡管理");
					
					LCD_Display_Words(p_SysParamHandle->u2AdminMngI, 0, "*");
				}
			
				LCD_Display_Words(3, 0, "Back       Enter");
				break;
		#if 0
			case Page_AdminFingerprintManage:
				LCD_Display_Words(0, 0, "****指纹管理****");
				LCD_Display_Words(1, 0, "    添加指纹");
				LCD_Display_Words(2, 0, "    删除指纹");
				LCD_Display_Words(3, 0, "Back       Enter");
				
				LCD_Display_Words(p_SysParamHandle->u2FigrPrtMngI + 1, 0, "*");
				break;

			case Page_AdminFingerprintInput:
				LCD_Display_Words(0, 0, "****指纹录入****");
				LCD_Display_Words(1, 0, "按数字选择指纹ID");
				LCD_Display_Words(2, 0, "  ID范围:1-99");
				LCD_Display_Words(3, 0, "Back       Enter");
				break;

			case Page_AdminFingerprintDelete:
				LCD_Display_Words(0, 0, "****指纹删除****");
				LCD_Display_Words(1, 0, "按数字选择指纹ID");
				LCD_Display_Words(2, 0, "  ID范围:1-99");
				LCD_Display_Words(3, 0, "Back       Enter");
				break;
		#endif
			case Page_AdminRFIDManage:
				LCD_Display_Words(0, 0, "****ID卡管理****");
				LCD_Display_Words(1, 0, "    添加ID卡");
				LCD_Display_Words(2, 0, "    删除ID卡");
				LCD_Display_Words(3, 0, "Back       Enter");

				LCD_Display_Words(p_SysParamHandle->u2RFIDMngI + 1, 0, "*");
				break;
			
			case Page_AdminRFIDInput:
				LCD_Display_Words(0, 0, "****ID卡添加****");
				LCD_Display_Words(1, 0, "按数字选择卡ID");
				LCD_Display_Words(2, 0, "  ID范围:1-9");
				LCD_Display_Words(3, 0, "Back       Enter");	

				break;

			case Page_AdminRFIDDelete:
				LCD_Display_Words(0, 0, "****ID卡删除****");
				LCD_Display_Words(1, 0, "按数字选择卡ID");
				LCD_Display_Words(2, 0, "  ID范围:1-9");
				LCD_Display_Words(3, 0, "Back       Enter");	
				break;

			case Page_AdminWifiConfig:
				LCD_Display_Words(0, 0, "****WIFI配网****");
				LCD_Display_Words(1, 2, "热点配网");
				LCD_Display_Words(2, 2, "一键配网");
				LCD_Display_Words(3, 0, "Back       Enter");

				LCD_Display_Words(p_SysParamHandle->u1WifiConfigI + 1, 0, "*");
				break;
				
			case Page_AdminRestoreFactory:
				LCD_Display_Words(0, 0, "  输入重置密码  ");
				LCD_Display_Words(3, 0, "Back  恢复出厂");	
				break;
				
			case Page_Default:	
			default:
				break;
		}
	}	
}

/*--------------------------------------------------------------------------------*/
/*
  *Function:  app_KeyEvent_Handle
  * Description：  //页面-主页时间处理
  *Input:  p_SysParamHandle, 系统参数句柄
  *Output:  //输出参数的说明
  *Return:  //函数返回值的说明
  *Others:  //其他说明
**/
void app_KeyEvent_Handle( SysParam_t * p_SysParamHandle )
{
	if (IsSetBit(p_SysParamHandle->u8EventReg, KEY_EVENT_BIT))
	{
		ResetBit(p_SysParamHandle->u8EventReg, KEY_EVENT_BIT);
		/* 根据页面 ID 调用事件处理函数 */
		switch (p_SysParamHandle->PageID)
		{
			case Page_Main:
				app_PageMain_Event_Handle( p_SysParamHandle );
				break;
				
			case Page_Admin_Login:
				app_PageAdminLogin_Event_Handle( p_SysParamHandle );
				break;

			case Page_Admin:
				app_PageAdmin_Event_Handle( p_SysParamHandle );
				break;

			case Page_AdminPasswordManage:
				app_PagePasswordManage_Event_Handle( p_SysParamHandle );
				break;

			case Page_UnlockPassword: 
			case Page_AdminPassword:
				app_PageAdminPw_and_UnlockPw_Event_Handle( p_SysParamHandle );
				break;
			
			case Page_AdminFingerprintManage:
			case Page_AdminRFIDManage:
				app_PageFP_and_PageRF_Manage_Event_Handle( p_SysParamHandle );
				break;

			case Page_AdminFingerprintInput:
				app_PageAdminFP_Input_Event_Handle( p_SysParamHandle );
				break;
				
			case Page_AdminRFIDInput:  
				app_PageAdminRF_Input_Event_Handle( p_SysParamHandle );
				break;

			case Page_AdminFingerprintDelete:
				app_PageAdminFP_Delete_Event_Handle( p_SysParamHandle );
				break;
				
			case Page_AdminRFIDDelete:
				app_PageAdminRF_Delete_Event_Handle( p_SysParamHandle );
				break;  

			case Page_AdminWifiConfig:
				app_PageWifiConfig_Event_Handle( p_SysParamHandle );
				break;  

			case Page_AdminRestoreFactory:
				app_PageRestoreFactory_Event_Handle( p_SysParamHandle );
				break; 
				
			case Page_Default:	
			default: 
				break;
		}
	}
}

/*--------------------------------------------------------------------------------*/
/*
  *Function:  app_IDCardEvent_Handle
  * Description：  //页面-主页时间处理
  *Input:  p_SysParamHandle, 系统参数句柄
  *Output:  //输出参数的说明
  *Return:  //函数返回值的说明
  *Others:  //其他说明
**/
void app_IDCardEvent_Handle( SysParam_t * p_SysParamHandle )
{
	RC522Handle_t	*p_rc522handle = p_SysParamHandle->p_rc522handle;
	u8 u8Index;
	u8 id_str[2] = {'0', '\0'};
	if (IsSetBit(p_SysParamHandle->u8EventReg, RFID_EVENT_BIT))
	{
		ResetBit(p_SysParamHandle->u8EventReg, RFID_EVENT_BIT);
		/* 根据页面 ID 调用事件处理函数 */
		switch (p_SysParamHandle->PageID)
		{
			case Page_Main:
				for (u8Index=0; u8Index<IDCARD_NUM; u8Index++)
				{
					if ( !User_MemCmp(p_rc522handle->SN, &p_SysParamHandle->p_eeprom_data->IDCardSN[u8Index][0], IDCARE_SN_LEN) )
					{
						LCD_Display_Words(1, 2, "ID卡: ");	
						id_str[0] += (u8Index+1);
						LCD_Display_Words(1, 5, id_str);	
						app_LcdDispStrDelay(1, 2, NULL, 1500, Page_Default);
						app_LcdDispStrDelay(2, 2, "成功解锁", 1500, Page_Default);
						/* 开启继电器解锁 */
						Switch_On( );
						
						break;
					}
				}
				//if (u8Index == p_SysParamHandle->p_eeprom_data->nID)
				if (u8Index == IDCARD_NUM)
				{
					app_LcdDispStrDelay(2, 2, "刷卡错误", 1500, Page_Default);
					/* 蜂鸣器报警 */
					longBeep( );
				}
				break;
				
			case Page_AdminRFIDInput:
				if (p_SysParamHandle->u4RFCard_ID != 0 		/* 检测id是否已输入 */
				&& p_SysParamHandle->u8CodeNumIndex == 2)	/* enter按键已按下 */
				{
					/* 本地缓存 */
					User_MemCpy(&p_SysParamHandle->p_eeprom_data->IDCardSN[p_SysParamHandle->u4RFCard_ID-1][0], \
								p_SysParamHandle->p_rc522handle->SN, IDCARE_SN_LEN);

					/* 保存至EEPROM */
					AT24CXX_Write(IDCARE_SN_EEPROM_ADDR+(p_SysParamHandle->u4RFCard_ID-1)*IDCARE_SN_LEN, \
								 &p_SysParamHandle->p_eeprom_data->IDCardSN[p_SysParamHandle->u4RFCard_ID-1][0], \
								 IDCARE_SN_LEN);
					app_LcdDispStrDelay(2, 2, "录入成功", 1500, Page_AdminRFIDManage);
				}
				break;
				
			default: 
				break;
		}
	}
}

/*--------------------------------------------------------------------------------*/
/*
  *Function:  app_FingerPrintEvent_Handle
  * Description：  //页面-主页时间处理
  *Input:  p_SysParamHandle, 系统参数句柄
  *Output:  //输出参数的说明
  *Return:  //函数返回值的说明
  *Others:  //其他说明
**/
void app_FingerPrintEvent_Handle( SysParam_t * p_SysParamHandle )
{
	AS608Handle_t	*p_as608handle = p_SysParamHandle->p_as608handle;
	u8 str[20] = {0};
	if (IsSetBit(p_SysParamHandle->u8EventReg, FP_EVENT_BIT))
	{
		ResetBit(p_SysParamHandle->u8EventReg, FP_EVENT_BIT);
		/* 根据页面 ID 调用事件处理函数 */
		switch (p_SysParamHandle->PageID)
		{
			case Page_Main:
				if ( p_SysParamHandle->u8pf_check_result == FpResult_CheckOK)
				{
					int2str(p_as608handle->pserch_result->ID, str);//把指纹ID转成字符类型方便显示
					LCD_Display_Words(2, 0, "     ID:");
					LCD_Display_Words(2, 4, str);
					
					app_LcdDispStrDelay(1, 2, "成功解锁", 1500, Page_Default);
					app_LcdDispStrDelay(2, 0, NULL, 1500, Page_Default);
					/* 开启继电器解锁 */
					Switch_On( );
				}
				else
				{
					app_LcdDispStrDelay(2, 2, "指纹错误", 1500, Page_Default);
					/* 蜂鸣器报警 */
					longBeep( );
				}
				break;
				
			case Page_AdminFingerprintInput:
				if ( p_SysParamHandle->u8pf_check_result == FpResult_CheckOK )		/* enter按键已按下 */
				{
					app_LcdDispStrDelay(1, 2, "录入成功", 1500, Page_AdminFingerprintManage);
				}
				break;
				
			default: 
				break;
		}
	}
}

/*--------------------------------------------------------------------------------*/
/*
  *Function:  app_GizwitsDataEvent_Handle
  * Description：  //页面-主页时间处理
  *Input:  p_SysParamHandle, 系统参数句柄
  *Output:  //输出参数的说明
  *Return:  //函数返回值的说明
  *Others:  //其他说明
**/
void app_GizwitsDataEvent_Handle( SysParam_t * p_SysParamHandle )
{
	dataPoint_t	*p_dataPoint = p_SysParamHandle->p_DataPoint;
	if (IsSetBit(p_SysParamHandle->u8EventReg, Gizwits_EVENT_BIT))
	{
		ResetBit(p_SysParamHandle->u8EventReg, Gizwits_EVENT_BIT);
		/* 根据页面 ID 调用事件处理函数 */
		switch (p_SysParamHandle->PageID)
		{
			case Page_Main:
				if ( p_dataPoint->valueunlock == 1)
				{
					app_LcdDispStrDelay(2, 1, "远程解锁成功", 1500, Page_Default);
					/* 开启继电器解锁 */
					Switch_On( );
					/* app按键延时恢复 */
					delay_ms(1500);
					p_dataPoint->valueunlock = 0;
				}
				break;
				
			default: 
				if ( p_dataPoint->valueunlock == 1)
				{
					p_dataPoint->valueunlock = 0;
				}
				break;
		}
	}
}

/*--------------------------------------------------------------------------------*/

/****************************************** end file ********************************************/

