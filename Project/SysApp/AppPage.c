/*********************************************************************************
  *Copyright(C),2020-2021, SIRI
  *FileName:  AppPage.c
  *Author:  SIRI
  *Version: v1.0.1.202211215
  *Date:  20221/12/15
  *Description:  
  *Others:  
  *Function List:  
  ||��Ҫ�����б�ÿ����¼Ӧ���������������ܼ�Ҫ˵��||
     1.��������
     2.��������
  *History:  
  |�޸���ʷ��¼�б�ÿ���޸ļ�¼Ӧ�����޸����ڡ��޸��߼��޸����ݼ��||
     1.Date:
       Author:
       Modification:
     2.��������
**********************************************************************************/
	
#include "./SysApp/AppParam.h"
#include "./SysApp/AppPage.h"


//�ⲿ����
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
  * Description��  //ҳ��-��ҳʱ�䴦��
  *Input:  p_SysParamHandle, ϵͳ�������
  *Output:  //���������˵��
  *Return:  //��������ֵ��˵��
  *Others:  //����˵��
**/
void app_LcdDispChX( u8 index )
{
	LCD_Display_Words( 1, index+1, "*");
}
/*--------------------------------------------------------------------------------*/
/*
  *Function:  app_LcdDispChNum
  * Description��  //ҳ��-��ҳʱ�䴦��
  *Input:  p_SysParamHandle, ϵͳ�������
  *Output:  //���������˵��
  *Return:  //��������ֵ��˵��
  *Others:  //����˵��
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
  * Description��  //ҳ��-��ҳʱ�䴦��
  *Input:  p_SysParamHandle, ϵͳ�������
  *Output:  //���������˵��
  *Return:  //��������ֵ��˵��
  *Others:  //����˵��
**/
void app_LcdDispChNull( u8 row, u8 index )
{
	LCD_Display_Words(row, index+1, " ");
}
/*--------------------------------------------------------------------------------*/
/*
  *Function:  app_LcdClearChNull
  * Description��  //ҳ��-��ҳʱ�䴦��
  *Input:  p_SysParamHandle, ϵͳ�������
  *Output:  //���������˵��
  *Return:  //��������ֵ��˵��
  *Others:  //����˵��
**/
void app_LcdClearChNull( u8 index )
{
	LCD_Display_Words(index, 0, "                ");
}

/*--------------------------------------------------------------------------------*/
/*
  *Function:  app_LcdClearChNull
  * Description��  //ҳ��-��ҳʱ�䴦��
  *Input:  p_SysParamHandle, ϵͳ�������
  *Output:  //���������˵��
  *Return:  //��������ֵ��˵��
  *Others:  //����˵��
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
  * Description��  //ҳ��-��ҳʱ�䴦��
  *Input:  p_SysParamHandle, ϵͳ�������
  *Output:  //���������˵��
  *Return:  //��������ֵ��˵��
  *Others:  //����˵��
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
  * Description��  //ҳ��-��ҳʱ�䴦��
  *Input:  p_SysParamHandle, ϵͳ�������
  *Output:  //���������˵��
  *Return:  //��������ֵ��˵��
  *Others:  //����˵��
**/
void app_DispPage( SysParam_t *p_SysParamHandle, enumPageID_t page_id)
{
	gs_lcdDispDelayHandle.tim[0] = 0;
	gs_lcdDispDelayHandle.tim[1] = 0;

	p_SysParamHandle->PageID = page_id;
	
	/* ���ֻ������� */
	p_SysParamHandle->u8CodeNumIndex = 0;

	/* ָ��ģ��״̬���� */
	if (page_id == Page_Main)
	{
		p_SysParamHandle->p_as608handle->eWM = FpWork_Press;
		p_SysParamHandle->p_as608handle->esStatus = FpStatus_Check;
	}
	else
	{
		p_SysParamHandle->p_as608handle->eWM = FpWork_None;
	}
	
	/* ����LCD�¼���־ */
	SetBit(p_SysParamHandle->u8EventReg, LCD_PAGE_EVENT_BIT);
}


/*--------------------------------------------------------------------------------*/
/*
  *Function:  app_PageMain_Event_Handle
  * Description��  //ҳ��-��ҳʱ�䴦��
  *Input:  p_SysParamHandle, ϵͳ�������
  *Output:  //���������˵��
  *Return:  //��������ֵ��˵��
  *Others:  //����˵��
**/
void app_PageMain_Event_Handle( SysParam_t *p_SysParamHandle )
{
	enumKeyCode_t key_code = (enumKeyCode_t)p_SysParamHandle->u8KeyCode;
	switch (key_code)
	{
		case KeyCode_Back:
			/* �������룬��� */
			if (p_SysParamHandle->u8CodeNumIndex > 0)
			{
				p_SysParamHandle->u8CodeNumIndex--;
				/* lcd ȥ�� '*' */
				app_LcdDispChNull(1, p_SysParamHandle->u8CodeNumIndex);
			}
			break;
			
		case KeyCode_Enter:
		/* �������룬��� */
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
				/* ��ʱ��ʾ1s */
				app_LcdDispStrDelay(2, 3, "��Ч", 1500, Page_Default);
				/* ���������� */
				longBeep( );
			}
			break;
			
		case KeyCode_Ch10:/* ���š�+�� */
		case KeyCode_Ch11:/* ���š�-�� */
		case KeyCode_Ch12:/* ���š�*�� */
		case KeyCode_Ch13:/* ���š�#�� */
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
	 		/* ������뻺�� */
			p_SysParamHandle->InputCodes[p_SysParamHandle->u8CodeNumIndex] = key_code-KeyCode_Num0;
			/* ��ʾ �ַ� '*' */
			app_LcdDispChX(p_SysParamHandle->u8CodeNumIndex);
			/* �鿴λ���Ƿ�ƥ�� */
			if (p_SysParamHandle->u8CodeNumIndex == UNLOCK_PASSWORD_LEN-1)
			{
				p_SysParamHandle->u8CodeNumIndex = 0;
				/* ����λ��ƥ�� */
				if (!User_MemCmp(p_SysParamHandle->InputCodes, p_SysParamHandle->p_eeprom_data->UnLockPassword, UNLOCK_PASSWORD_LEN))
				{
					/* ����ƥ��ɹ� */
					app_LcdDispStrDelay(1, 2, NULL, 1500, Page_Default);	
					app_LcdDispStrDelay(2, 2, "������ȷ", 1500, Page_Default);	
					/* �����̵������� */
					Switch_On( );
				}
				else
				{
					/* ����ƥ��ʧ�� */
					app_LcdDispStrDelay(1, 2, NULL, 1500, Page_Default);	
					app_LcdDispStrDelay(2, 2, "�������", 1500, Page_Default);
					/* ���������� */
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
  * Description��  //ҳ��-��ҳʱ�䴦��
  *Input:  p_SysParamHandle, ϵͳ�������
  *Output:  //���������˵��
  *Return:  //��������ֵ��˵��
  *Others:  //����˵��
**/
void app_PageAdminLogin_Event_Handle( SysParam_t *p_SysParamHandle )
{
	enumKeyCode_t key_code = (enumKeyCode_t)p_SysParamHandle->u8KeyCode;
	switch (key_code)
	{
		case KeyCode_Back:
			/* �������룬��� */
			if (p_SysParamHandle->u8CodeNumIndex > 0)
			{
				p_SysParamHandle->u8CodeNumIndex--;
				/* lcd ȥ�� '*' */
				app_LcdDispChNull(1, p_SysParamHandle->u8CodeNumIndex);
			}
			else
			{
				app_DispPage(p_SysParamHandle, Page_Main);
			}
			break;
			
		case KeyCode_Enter:
			break;
			
		case KeyCode_Ch10:/* ���š�+�� */
		case KeyCode_Ch11:/* ���š�-�� */
		case KeyCode_Ch12:/* ���š�*�� */
		case KeyCode_Ch13:/* ���š�#�� */
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
 			/* ������뻺�� */
			p_SysParamHandle->InputCodes[p_SysParamHandle->u8CodeNumIndex] = key_code;
			/* ��ʾ �ַ� '*' */
			app_LcdDispChX(p_SysParamHandle->u8CodeNumIndex);
			/* �鿴λ���Ƿ�ƥ�� */
			if (p_SysParamHandle->u8CodeNumIndex == ADMIN_PASSWORD_LEN-1)
			{
				p_SysParamHandle->u8CodeNumIndex = 0;
				/* ����λ��ƥ�� */
				if (!User_MemCmp(p_SysParamHandle->InputCodes, p_SysParamHandle->p_eeprom_data->AdminPassword, ADMIN_PASSWORD_LEN))
				{
					/* ����ƥ��ɹ� */
					app_DispPage(p_SysParamHandle, Page_Admin);
				}
				else
				{
					app_LcdDispStrDelay(1, 2, NULL, 1500, Page_Default);
					app_LcdDispStrDelay(2, 2, "�������", 1500, Page_Default);
					/* ���������� */
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
  * Description��  //ҳ��-��ҳʱ�䴦��
  *Input:  p_SysParamHandle, ϵͳ�������
  *Output:  //���������˵��
  *Return:  //��������ֵ��˵��
  *Others:  //����˵��
**/
void app_PageAdmin_Event_Handle( SysParam_t *p_SysParamHandle )
{
	enumKeyCode_t key_code = (enumKeyCode_t)p_SysParamHandle->u8KeyCode;
	switch (key_code)
	{
		case KeyCode_Back:
			/* �л�ҳ�� */
			app_DispPage(p_SysParamHandle, Page_Admin_Login);
			break;
			
		case KeyCode_Enter:
			/* һλ */ 
			if (p_SysParamHandle->u2AdminMngI == 0)
			{
				/* �л�ҳ�� */
				app_DispPage(p_SysParamHandle, Page_AdminPasswordManage);
			}
			else if (p_SysParamHandle->u2AdminMngI == 1)
			{
				/* �л�ҳ�� */
				app_DispPage(p_SysParamHandle, Page_AdminFingerprintManage);
			}
			else if (p_SysParamHandle->u2AdminMngI == 2)
			{
				/* �л�ҳ�� */
				app_DispPage(p_SysParamHandle, Page_AdminRFIDManage);
			} 
			else
			{
				/* �л�ҳ�� */
				app_DispPage(p_SysParamHandle, Page_AdminWifiConfig);
			}
			break;
			
		case KeyCode_Ch10:/* ���š�+�� */
			if (p_SysParamHandle->u2AdminMngI < 2)
			{
				LCD_Display_Words( p_SysParamHandle->u2AdminMngI , 0, " ");
				LCD_Display_Words( ++p_SysParamHandle->u2AdminMngI , 0, "*");
			}
			else if (p_SysParamHandle->u2AdminMngI == 2)
			{
				/*!< �л���ҳ�� */
				app_LcdClearChNull( 0 );
				app_LcdClearChNull( 1 );
				app_LcdClearChNull( 2 );
				
				LCD_Display_Words(0, 0, "    WIFI����");
				
				++p_SysParamHandle->u2AdminMngI;
				LCD_Display_Words( 0, 0, "*");
			}
			/* ����ƥ��ʧ�� */
			break;
		
		case KeyCode_Ch11:/* ���š�-�� */
			if (p_SysParamHandle->u2AdminMngI == 3)
			{
				/*!< �л���ҳ�� */
				app_LcdClearChNull( 0 );

				LCD_Display_Words(0, 0, "    �������");
				LCD_Display_Words(1, 0, "    ָ�ƹ���");
				LCD_Display_Words(2, 0, "    ID������");
				
				LCD_Display_Words( --p_SysParamHandle->u2AdminMngI , 0, "*");
			}
			else if (p_SysParamHandle->u2AdminMngI > 0)
			{
				LCD_Display_Words( p_SysParamHandle->u2AdminMngI , 0, " ");
				LCD_Display_Words( --p_SysParamHandle->u2AdminMngI , 0, "*");
			}
			break;
			
		case KeyCode_Ch12:/* ���š�*�� */
		case KeyCode_Ch13:/* ���š�#�� */
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
  * Description��  //ҳ��-��ҳʱ�䴦��
  *Input:  p_SysParamHandle, ϵͳ�������
  *Output:  //���������˵��
  *Return:  //��������ֵ��˵��
  *Others:  //����˵��
**/
void app_PagePasswordManage_Event_Handle( SysParam_t *p_SysParamHandle )
{
	enumKeyCode_t key_code = (enumKeyCode_t)p_SysParamHandle->u8KeyCode;
	switch (key_code)
	{
		case KeyCode_Back:
			/* �л�ҳ�� */
			app_DispPage(p_SysParamHandle, Page_Admin);
			break;
			
		case KeyCode_Enter:
			/* һλ */ 
			(p_SysParamHandle->u2AdminPwMngI == 0) ? \
 			app_DispPage(p_SysParamHandle, Page_UnlockPassword) : \
 			app_DispPage(p_SysParamHandle, Page_AdminPassword);
			break;
			
		case KeyCode_Ch10:/* ���š�+�� */
			if (p_SysParamHandle->u2AdminPwMngI < 1)
			{
				LCD_Display_Words( p_SysParamHandle->u2AdminPwMngI + 1, 0, " " );
				LCD_Display_Words( ++p_SysParamHandle->u2AdminPwMngI + 1, 0, "*" );
			}
			/* ����ƥ��ʧ�� */
			break;
		
		case KeyCode_Ch11:/* ���š�-�� */
			if (p_SysParamHandle->u2AdminPwMngI > 0)
			{
				LCD_Display_Words( p_SysParamHandle->u2AdminPwMngI + 1, 0, " ");
				LCD_Display_Words( --p_SysParamHandle->u2AdminPwMngI + 1, 0, "*");
			}
			break;
			
		case KeyCode_Ch12:/* ���š�*�� */
		case KeyCode_Ch13:/* ���š�#�� */
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
  * Description��  //ҳ��-��ҳʱ�䴦��
  *Input:  p_SysParamHandle, ϵͳ�������
  *Output:  //���������˵��
  *Return:  //��������ֵ��˵��
  *Others:  //����˵��
**/
void app_PageFP_and_PageRF_Manage_Event_Handle( SysParam_t *p_SysParamHandle )
{
	enumKeyCode_t key_code = (enumKeyCode_t)p_SysParamHandle->u8KeyCode;
	switch (key_code)
	{
		case KeyCode_Back:
			/* �л�ҳ�� */
			app_DispPage(p_SysParamHandle, Page_Admin);
			break;
			
		case KeyCode_Enter:
			if (p_SysParamHandle->PageID == Page_AdminFingerprintManage)
			{
				/* һλ */ 
				(p_SysParamHandle->u2FigrPrtMngI == 0) ? \
	 			app_DispPage(p_SysParamHandle, Page_AdminFingerprintInput) : \
	 			app_DispPage(p_SysParamHandle, Page_AdminFingerprintDelete);
			}
			else
			{
				/* һλ */ 
				(p_SysParamHandle->u2RFIDMngI == 0) ? \
	 			app_DispPage(p_SysParamHandle, Page_AdminRFIDInput) : \
	 			app_DispPage(p_SysParamHandle, Page_AdminRFIDDelete);
			}
			break;
			
		case KeyCode_Ch10:/* ���š�+�� */
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
		
		case KeyCode_Ch11:/* ���š�-�� */
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
			
		case KeyCode_Ch12:/* ���š�*�� */
		case KeyCode_Ch13:/* ���š�#�� */
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
  * Description��  //ҳ��-��ҳʱ�䴦��
  *Input:  p_SysParamHandle, ϵͳ�������
  *Output:  //���������˵��
  *Return:  //��������ֵ��˵��
  *Others:  //����˵��
**/
void app_PageAdminPw_and_UnlockPw_Event_Handle( SysParam_t *p_SysParamHandle )
{
	enumKeyCode_t key_code = (enumKeyCode_t)p_SysParamHandle->u8KeyCode;
	/* �������볤�� */
	u8 code_len = 0;
	switch (key_code)
	{
		case KeyCode_Back:
			/* �������룬��� */
			if (p_SysParamHandle->u8CodeNumIndex > 0 && p_SysParamHandle->u8CodeNumIndex < ADMIN_PASSWORD_LEN)
			{
				p_SysParamHandle->u8CodeNumIndex--;
				/* lcd ȥ�� 'num' */
				app_LcdDispChNull(1, p_SysParamHandle->u8CodeNumIndex);
			}
			else
			{
				app_DispPage(p_SysParamHandle, Page_AdminPasswordManage);
			}
			break;
			
		case KeyCode_Enter:
			
			break;
			
		case KeyCode_Ch10:/* ���š�+�� */
			break;
		
		case KeyCode_Ch11:/* ���š�-�� */
			break;
			
		case KeyCode_Ch12:/* ���š�*�� */
		case KeyCode_Ch13:/* ���š�#�� */
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
			/* �鿴λ���Ƿ�ƥ�� */
			if (p_SysParamHandle->u8CodeNumIndex < code_len)
			{
	 			/* ������뻺�� */
				p_SysParamHandle->InputCodes[p_SysParamHandle->u8CodeNumIndex] = key_code-KeyCode_Num0;
				/* ��ʾ ����     */
				app_LcdDispChNum(p_SysParamHandle->u8CodeNumIndex, key_code-KeyCode_Num0 );
				/* index ++ */
				p_SysParamHandle->u8CodeNumIndex++;
				
				if (p_SysParamHandle->u8CodeNumIndex == code_len)
				{
					/* ����ƥ��ɹ� */
					LCD_Display_Words( 2, 1, "��ȷ������" );
					app_LcdDispStrDelay(1, 2, NULL, 500, Page_Default);
				}
			}
			else
			{
				/* �ڶ������� */
				if (key_code-KeyCode_Num0 != p_SysParamHandle->InputCodes[p_SysParamHandle->u8CodeNumIndex - code_len] )
				{
					/* ���������� */
					longBeep( );
					app_LcdDispStrDelay(2, 1, "���벻һ��", 1500, Page_Default);
					app_LcdDispStrDelay(1, 2, NULL, 1500, Page_Default);
					/* ��ͷ���� */
					p_SysParamHandle->u8CodeNumIndex = 0;
				}
				else
				{
					/* ��ʾ ����     */
					app_LcdDispChNum(p_SysParamHandle->u8CodeNumIndex- code_len, key_code-KeyCode_Num0 );
					/* ����Ƿ�������� */
					if (++p_SysParamHandle->u8CodeNumIndex == code_len * 2)
					{
						app_LcdDispStrDelay(2, 1, "�����趨�ɹ�", 1500, Page_AdminPasswordManage);
						(p_SysParamHandle->PageID == Page_AdminPassword) ? \
			 			User_MemCpy(p_SysParamHandle->p_eeprom_data->AdminPassword, p_SysParamHandle->InputCodes, code_len): \
						User_MemCpy(p_SysParamHandle->p_eeprom_data->UnLockPassword, p_SysParamHandle->InputCodes, code_len);
						/* ������EEPROM */
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
  * Description��  //ҳ��-��ҳʱ�䴦��
  *Input:  p_SysParamHandle, ϵͳ�������
  *Output:  //���������˵��
  *Return:  //��������ֵ��˵��
  *Others:  //����˵��
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
					LCD_Display_Words(2, 2, "��¼��ָ��");
					p_SysParamHandle->p_as608handle->esStatus = FpStatus_Add;
					p_SysParamHandle->p_as608handle->eWM = FpWork_Press;
					p_SysParamHandle->p_as608handle->inputId = p_SysParamHandle->u8FingerPrint_ID;
				}
				else 
				{
					LCD_Display_Words(2, 2, "��ˢID��");
				}
			}
			break;
			
		case KeyCode_Ch10:/* ���š�+�� */
		case KeyCode_Ch11:/* ���š�-�� */
		case KeyCode_Ch12:/* ���š�*�� */
		case KeyCode_Ch13:/* ���š�#�� */
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
			/* ��ʾ �ַ� '*' */
			u8 str[3];
			str[0] = ' ';
 			str[1] = '0' + key_code - KeyCode_Num0;
 			str[2] = '\0';
			LCD_Display_Words( 3, 3, str );
			/* �������id */
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
  * Description��  //ҳ��-��ҳʱ�䴦��
  *Input:  p_SysParamHandle, ϵͳ�������
  *Output:  //���������˵��
  *Return:  //��������ֵ��˵��
  *Others:  //����˵��
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
				/* ��ʾ �ַ� '*' */
				app_LcdClearChNull( 1 );
				/* ����ƥ��ʧ�� */
				app_LcdClearChNull( 2 );
				if (p_SysParamHandle->PageID == Page_AdminFingerprintDelete)
				{
					id_str[0] = '0' + p_SysParamHandle->u8FingerPrint_ID;
					LCD_Display_Words(1, 0, "    ID: ");
					LCD_Display_Words(1, 3, id_str);
					if (0x00 == PS_DeletChar(p_SysParamHandle->u8FingerPrint_ID, 1))//ɾ������ָ��
					{
						app_LcdDispStrDelay(1, 0, NULL, 1500, Page_AdminFingerprintManage);					
						app_LcdDispStrDelay(2, 0, "    ɾ���ɹ�   ", 1500, Page_AdminFingerprintManage);
					}
					else
					{
						app_LcdDispStrDelay(2, 0, "    ɾ��ʧ��   ", 1500, Page_AdminFingerprintManage);
					}
				}
				else
				{
					id_str[0] = '0' + p_SysParamHandle->u4RFCard_ID;
					LCD_Display_Words(1, 0, "    ID��: ");
					LCD_Display_Words(1, 5, id_str);
					app_LcdDispStrDelay(1, 0, NULL, 1500, Page_AdminRFIDManage);					
					app_LcdDispStrDelay(2, 0, "    ɾ���ɹ�   ", 1500, Page_AdminRFIDManage);
					

					User_MemSet((u8 *)&p_SysParamHandle->p_eeprom_data->IDCardSN[p_SysParamHandle->u4RFCard_ID-1][0], \
								0x00, IDCARE_SN_LEN);
					AT24CXX_Write(IDCARE_SN_EEPROM_ADDR+p_SysParamHandle->u4RFCard_ID-1, \
								  (u8 *)&p_SysParamHandle->p_eeprom_data->IDCardSN[p_SysParamHandle->u4RFCard_ID-1][0], \
								  IDCARE_SN_LEN);
				}
				
			}
			break;
			
		case KeyCode_Ch10:/* ���š�+�� */
		case KeyCode_Ch11:/* ���š�-�� */
		case KeyCode_Ch12:/* ���š�*�� */
		case KeyCode_Ch13:/* ���š�#�� */
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
 			/* ��ʾ �ַ� '*' */
			id_str[0] = ' ';
 			id_str[1] = '0' + key_code - KeyCode_Num0;
 			id_str[2] = '\0';
			LCD_Display_Words( 3, 3, id_str );
			/* �������id */
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
  * Description��  //ҳ��-��ҳʱ�䴦��
  *Input:  p_SysParamHandle, ϵͳ�������
  *Output:  //���������˵��
  *Return:  //��������ֵ��˵��
  *Others:  //����˵��
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
				
				LCD_Display_Words(2, 2, "��ˢID��");
			}
			break;
			
		case KeyCode_Ch10:/* ���š�+�� */
		case KeyCode_Ch11:/* ���š�-�� */
		case KeyCode_Ch12:/* ���š�*�� */
		case KeyCode_Ch13:/* ���š�#�� */
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
			/* ��ʾ �ַ� '*' */
			u8 str[3];
			str[0] = ' ';
 			str[1] = '0' + key_code - KeyCode_Num0;
 			str[2] = '\0';
			LCD_Display_Words( 3, 3, str );
			/* �������id */
			p_SysParamHandle->u4RFCard_ID = key_code;
			
 			break;

 		default:
 			break;
	}
}


/*--------------------------------------------------------------------------------*/
/*
  *Function:  app_PageAdminRF_Delete_Event_Handle
  * Description��  //ҳ��-��ҳʱ�䴦��
  *Input:  p_SysParamHandle, ϵͳ�������
  *Output:  //���������˵��
  *Return:  //��������ֵ��˵��
  *Others:  //����˵��
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
				/* ��ʾ �ַ� '*' */
				app_LcdClearChNull( 1 );
				/* ����ƥ��ʧ�� */
				app_LcdClearChNull( 2 );
				id_str[0] = '0' + p_SysParamHandle->u4RFCard_ID;
				LCD_Display_Words(1, 0, "    ID��: ");
				LCD_Display_Words(1, 5, id_str);
				app_LcdDispStrDelay(1, 0, NULL, 1500, Page_AdminRFIDManage);					
				app_LcdDispStrDelay(2, 0, "    ɾ���ɹ�   ", 1500, Page_AdminRFIDManage);
				

				User_MemSet((u8 *)&p_SysParamHandle->p_eeprom_data->IDCardSN[p_SysParamHandle->u4RFCard_ID-1][0], \
							0x00, IDCARE_SN_LEN);
				AT24CXX_Write(IDCARE_SN_EEPROM_ADDR+p_SysParamHandle->u4RFCard_ID-1, \
							  (u8 *)&p_SysParamHandle->p_eeprom_data->IDCardSN[p_SysParamHandle->u4RFCard_ID-1][0], \
							  IDCARE_SN_LEN);
			}
			break;
			
		case KeyCode_Ch10:/* ���š�+�� */
		case KeyCode_Ch11:/* ���š�-�� */
		case KeyCode_Ch12:/* ���š�*�� */
		case KeyCode_Ch13:/* ���š�#�� */
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
 			/* ��ʾ �ַ� '*' */
			id_str[0] = ' ';
 			id_str[1] = '0' + key_code - KeyCode_Num0;
 			id_str[2] = '\0';
			LCD_Display_Words( 3, 3, id_str );
			/* �������id */
			p_SysParamHandle->u4RFCard_ID = key_code;
			
 			break;
			
 		default:
 			break;
	}
}

/*--------------------------------------------------------------------------------*/
/*
  *Function:  app_PageAdminFP_Input_Event_Handle
  * Description��  //ҳ��-��ҳʱ�䴦��
  *Input:  p_SysParamHandle, ϵͳ�������
  *Output:  //���������˵��
  *Return:  //��������ֵ��˵��
  *Others:  //����˵��
**/
void app_PageAdminFP_Input_Event_Handle( SysParam_t *p_SysParamHandle )
{
	enumKeyCode_t key_code = (enumKeyCode_t)p_SysParamHandle->u8KeyCode;
 	u8 str[5] = { 0 };
	switch (key_code)
	{
		case KeyCode_Back:
			/* �������룬��� */
			if (p_SysParamHandle->u8CodeNumIndex > 0)
			{
				p_SysParamHandle->u8CodeNumIndex--;
				p_SysParamHandle->u8FingerPrint_ID /= 10;
				/* lcd ȥ�� '*' */
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
				LCD_Display_Words(2, 2, "��¼��ָ��");
				p_SysParamHandle->p_as608handle->esStatus = FpStatus_Add;
				p_SysParamHandle->p_as608handle->eWM = FpWork_Press;
				p_SysParamHandle->p_as608handle->inputId = p_SysParamHandle->u8FingerPrint_ID;
				//��������
				p_SysParamHandle->u8FingerPrint_ID = 0;
			}
			break;
			
		case KeyCode_Ch10:/* ���š�+�� */
		case KeyCode_Ch11:/* ���š�-�� */
		case KeyCode_Ch12:/* ���š�*�� */
		case KeyCode_Ch13:/* ���š�#�� */
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
  * Description��  //ҳ��-��ҳʱ�䴦��
  *Input:  p_SysParamHandle, ϵͳ�������
  *Output:  //���������˵��
  *Return:  //��������ֵ��˵��
  *Others:  //����˵��
**/
void app_PageAdminFP_Delete_Event_Handle( SysParam_t *p_SysParamHandle )
{
	enumKeyCode_t key_code = (enumKeyCode_t)p_SysParamHandle->u8KeyCode;
	u8 str[5] = { 0 };
	switch (key_code)
	{
		case KeyCode_Back:
			/* �������룬��� */
			if (p_SysParamHandle->u8CodeNumIndex > 0)
			{
				p_SysParamHandle->u8CodeNumIndex--;
				p_SysParamHandle->u8FingerPrint_ID /= 10;
				/* lcd ȥ�� '*' */
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
				/* ��ʾ �ַ� '*' */
				app_LcdClearChNull( 1 );
				/* ����ƥ��ʧ�� */
				app_LcdClearChNull( 2 );
				
				int2str(p_SysParamHandle->u8FingerPrint_ID, str);
				LCD_Display_Words(1, 0, "    ID: ");
				LCD_Display_Words(1, 5, str);
				if (0x00 == PS_DeletChar(p_SysParamHandle->u8FingerPrint_ID, 1))//ɾ������ָ��
				{
					app_LcdDispStrDelay(1, 0, NULL, 1500, Page_AdminFingerprintManage);					
					app_LcdDispStrDelay(2, 0, "    ɾ���ɹ�   ", 1500, Page_AdminFingerprintManage);
				}
				else
				{
					app_LcdDispStrDelay(2, 0, "    ɾ��ʧ��   ", 1500, Page_AdminFingerprintManage);
				}

				p_SysParamHandle->u8FingerPrint_ID = 0;
				
			}
			break;
			
		case KeyCode_Ch10:/* ���š�+�� */
		case KeyCode_Ch11:/* ���š�-�� */
		case KeyCode_Ch12:/* ���š�*�� */
		case KeyCode_Ch13:/* ���š�#�� */
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
  * Description��  //ҳ��-��ҳʱ�䴦��
  *Input:  p_SysParamHandle, ϵͳ�������
  *Output:  //���������˵��
  *Return:  //��������ֵ��˵��
  *Others:  //����˵��
**/
void app_PageWifiConfig_Event_Handle( SysParam_t *p_SysParamHandle )
{
	enumKeyCode_t key_code = (enumKeyCode_t)p_SysParamHandle->u8KeyCode;
	switch (key_code)
	{
		case KeyCode_Back:
			/* �л�ҳ�� */
			app_DispPage(p_SysParamHandle, Page_Admin);
			break;
			
		case KeyCode_Enter:
		
			/* һλ */ 
			if (p_SysParamHandle->u1WifiConfigI == 0)
			{
				gizwitsSetMode(WIFI_SOFTAP_MODE);
			}
			else
			{
				gizwitsSetMode(WIFI_AIRLINK_MODE);
			}
			
			app_LcdDispStrDelay(2, 2, "���óɹ�", 1500, Page_Admin);
			break;
			
		case KeyCode_Ch10:/* ���š�+�� */
			if (p_SysParamHandle->u1WifiConfigI < 1)
			{
				LCD_Display_Words( p_SysParamHandle->u1WifiConfigI+1, 0, " ");
				LCD_Display_Words( ++p_SysParamHandle->u1WifiConfigI+1, 0, "*");
			}
			/* ����ƥ��ʧ�� */
			break;
		
		case KeyCode_Ch11:/* ���š�-�� */
			if (p_SysParamHandle->u2AdminMngI > 0)
			{
				LCD_Display_Words( p_SysParamHandle->u1WifiConfigI+1, 0, " ");
				LCD_Display_Words( --p_SysParamHandle->u1WifiConfigI+1, 0, "*");

			}
			break;
			
		case KeyCode_Ch12:/* ���š�*�� */
		case KeyCode_Ch13:/* ���š�#�� */
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
  * Description��  //ҳ��-��ҳʱ�䴦��
  *Input:  p_SysParamHandle, ϵͳ�������
  *Output:  //���������˵��
  *Return:  //��������ֵ��˵��
  *Others:  //����˵��
**/
void app_PageRestoreFactory_Event_Handle( SysParam_t *p_SysParamHandle )
{
	enumKeyCode_t key_code = (enumKeyCode_t)p_SysParamHandle->u8KeyCode;
	switch (key_code)
	{
		case KeyCode_Back:
			/* �������룬��� */
			if (p_SysParamHandle->u8CodeNumIndex > 0)
			{
				p_SysParamHandle->u8CodeNumIndex--;
				/* lcd ȥ�� '*' */
				app_LcdDispChNull(1, p_SysParamHandle->u8CodeNumIndex);
			}
			else
			{
				app_DispPage(p_SysParamHandle, Page_Main);
			}
			break;
			
		case KeyCode_Enter:
			break;
			
		case KeyCode_Ch10:/* ���š�+�� */
		case KeyCode_Ch11:/* ���š�-�� */
		case KeyCode_Ch12:/* ���š�*�� */
			break;
		case KeyCode_Ch13:/* ���š�#�� */
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
 			/* ������뻺�� */
			p_SysParamHandle->InputCodes[p_SysParamHandle->u8CodeNumIndex] = key_code ;
			/* ��ʾ �ַ� '*' */
			app_LcdDispChX(p_SysParamHandle->u8CodeNumIndex);
			/* �鿴λ���Ƿ�ƥ�� */
			if (p_SysParamHandle->u8CodeNumIndex == ADMIN_PASSWORD_LEN-1)
			{
				p_SysParamHandle->u8CodeNumIndex = 0;
				for (u8 i=0; i<ADMIN_PASSWORD_LEN; i++)
				{
					/* ����λ��ƥ�� */
					if (p_SysParamHandle->InputCodes[i] == KeyCode_Ch13)
					{
						continue;
					}
					else
					{
						/* ����ƥ��ʧ�� */
						app_LcdDispStrDelay(1, 2, NULL, 1500, Page_Default);
						app_LcdDispStrDelay(2, 2, "�������", 1500, Page_Default);
						/* ���������� */
						longBeep( );
						return;
					}
				}
				/* ����ƥ��ɹ�--�ָ����� */
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
  * Description��  //ҳ��-��ҳʱ�䴦��
  *Input:  p_SysParamHandle, ϵͳ�������
  *Output:  //���������˵��
  *Return:  //��������ֵ��˵��
  *Others:  //����˵��
**/
void app_PageEvent_Handle( SysParam_t *p_SysParamHandle )
{
	enumPageID_t page_id = p_SysParamHandle->PageID;
	if (IsSetBit(p_SysParamHandle->u8EventReg, LCD_PAGE_EVENT_BIT))
	{
		ResetBit(p_SysParamHandle->u8EventReg, LCD_PAGE_EVENT_BIT);
		/* ���ҳ�� */
		LCD_Clear();
		switch (page_id)
		{
			case Page_Main:
				LCD_Display_Words(0, 1, "�����Ž�ϵͳ");
				LCD_Display_Words(3, 5, "Enter");
				break;
				
			case Page_Admin_Login:
				LCD_Display_Words(0, 0, "���������Ա����");
				LCD_Display_Words(3, 0, "Back");	
				break;

			case Page_AdminPasswordManage:
				LCD_Display_Words(0, 0, "****�������****");
				LCD_Display_Words(1, 0, "  �޸Ľ�������");
				LCD_Display_Words(2, 0, "  �޸Ĺ�������");
				LCD_Display_Words(3, 0, "Back       Enter");

				
				LCD_Display_Words(p_SysParamHandle->u2AdminPwMngI + 1, 0, "*");
				break;

			case Page_UnlockPassword:
				LCD_Display_Words(0, 0, "�������½�������");
				LCD_Display_Words(3, 0, "Back");
				break;

			case Page_AdminPassword:
				LCD_Display_Words(0, 0, "�������¹�������");
				LCD_Display_Words(3, 0, "Back");
				break;

			case Page_Admin:
				if (p_SysParamHandle->u2AdminMngI == 3)
				{
					LCD_Display_Words(0, 0, "    WIFI����");
					LCD_Display_Words(0, 0, "*");
				}
				else
				{
					LCD_Display_Words(0, 0, "    �������");
					LCD_Display_Words(1, 0, "    ָ�ƹ���");
					LCD_Display_Words(2, 0, "    ID������");
					
					LCD_Display_Words(p_SysParamHandle->u2AdminMngI, 0, "*");
				}
			
				LCD_Display_Words(3, 0, "Back       Enter");
				break;
		#if 0
			case Page_AdminFingerprintManage:
				LCD_Display_Words(0, 0, "****ָ�ƹ���****");
				LCD_Display_Words(1, 0, "    ���ָ��");
				LCD_Display_Words(2, 0, "    ɾ��ָ��");
				LCD_Display_Words(3, 0, "Back       Enter");
				
				LCD_Display_Words(p_SysParamHandle->u2FigrPrtMngI + 1, 0, "*");
				break;

			case Page_AdminFingerprintInput:
				LCD_Display_Words(0, 0, "****ָ��¼��****");
				LCD_Display_Words(1, 0, "������ѡ��ָ��ID");
				LCD_Display_Words(2, 0, "  ID��Χ:1-99");
				LCD_Display_Words(3, 0, "Back       Enter");
				break;

			case Page_AdminFingerprintDelete:
				LCD_Display_Words(0, 0, "****ָ��ɾ��****");
				LCD_Display_Words(1, 0, "������ѡ��ָ��ID");
				LCD_Display_Words(2, 0, "  ID��Χ:1-99");
				LCD_Display_Words(3, 0, "Back       Enter");
				break;
		#endif
			case Page_AdminRFIDManage:
				LCD_Display_Words(0, 0, "****ID������****");
				LCD_Display_Words(1, 0, "    ���ID��");
				LCD_Display_Words(2, 0, "    ɾ��ID��");
				LCD_Display_Words(3, 0, "Back       Enter");

				LCD_Display_Words(p_SysParamHandle->u2RFIDMngI + 1, 0, "*");
				break;
			
			case Page_AdminRFIDInput:
				LCD_Display_Words(0, 0, "****ID�����****");
				LCD_Display_Words(1, 0, "������ѡ��ID");
				LCD_Display_Words(2, 0, "  ID��Χ:1-9");
				LCD_Display_Words(3, 0, "Back       Enter");	

				break;

			case Page_AdminRFIDDelete:
				LCD_Display_Words(0, 0, "****ID��ɾ��****");
				LCD_Display_Words(1, 0, "������ѡ��ID");
				LCD_Display_Words(2, 0, "  ID��Χ:1-9");
				LCD_Display_Words(3, 0, "Back       Enter");	
				break;

			case Page_AdminWifiConfig:
				LCD_Display_Words(0, 0, "****WIFI����****");
				LCD_Display_Words(1, 2, "�ȵ�����");
				LCD_Display_Words(2, 2, "һ������");
				LCD_Display_Words(3, 0, "Back       Enter");

				LCD_Display_Words(p_SysParamHandle->u1WifiConfigI + 1, 0, "*");
				break;
				
			case Page_AdminRestoreFactory:
				LCD_Display_Words(0, 0, "  ������������  ");
				LCD_Display_Words(3, 0, "Back  �ָ�����");	
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
  * Description��  //ҳ��-��ҳʱ�䴦��
  *Input:  p_SysParamHandle, ϵͳ�������
  *Output:  //���������˵��
  *Return:  //��������ֵ��˵��
  *Others:  //����˵��
**/
void app_KeyEvent_Handle( SysParam_t * p_SysParamHandle )
{
	if (IsSetBit(p_SysParamHandle->u8EventReg, KEY_EVENT_BIT))
	{
		ResetBit(p_SysParamHandle->u8EventReg, KEY_EVENT_BIT);
		/* ����ҳ�� ID �����¼������� */
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
  * Description��  //ҳ��-��ҳʱ�䴦��
  *Input:  p_SysParamHandle, ϵͳ�������
  *Output:  //���������˵��
  *Return:  //��������ֵ��˵��
  *Others:  //����˵��
**/
void app_IDCardEvent_Handle( SysParam_t * p_SysParamHandle )
{
	RC522Handle_t	*p_rc522handle = p_SysParamHandle->p_rc522handle;
	u8 u8Index;
	u8 id_str[2] = {'0', '\0'};
	if (IsSetBit(p_SysParamHandle->u8EventReg, RFID_EVENT_BIT))
	{
		ResetBit(p_SysParamHandle->u8EventReg, RFID_EVENT_BIT);
		/* ����ҳ�� ID �����¼������� */
		switch (p_SysParamHandle->PageID)
		{
			case Page_Main:
				for (u8Index=0; u8Index<IDCARD_NUM; u8Index++)
				{
					if ( !User_MemCmp(p_rc522handle->SN, &p_SysParamHandle->p_eeprom_data->IDCardSN[u8Index][0], IDCARE_SN_LEN) )
					{
						LCD_Display_Words(1, 2, "ID��: ");	
						id_str[0] += (u8Index+1);
						LCD_Display_Words(1, 5, id_str);	
						app_LcdDispStrDelay(1, 2, NULL, 1500, Page_Default);
						app_LcdDispStrDelay(2, 2, "�ɹ�����", 1500, Page_Default);
						/* �����̵������� */
						Switch_On( );
						
						break;
					}
				}
				//if (u8Index == p_SysParamHandle->p_eeprom_data->nID)
				if (u8Index == IDCARD_NUM)
				{
					app_LcdDispStrDelay(2, 2, "ˢ������", 1500, Page_Default);
					/* ���������� */
					longBeep( );
				}
				break;
				
			case Page_AdminRFIDInput:
				if (p_SysParamHandle->u4RFCard_ID != 0 		/* ���id�Ƿ������� */
				&& p_SysParamHandle->u8CodeNumIndex == 2)	/* enter�����Ѱ��� */
				{
					/* ���ػ��� */
					User_MemCpy(&p_SysParamHandle->p_eeprom_data->IDCardSN[p_SysParamHandle->u4RFCard_ID-1][0], \
								p_SysParamHandle->p_rc522handle->SN, IDCARE_SN_LEN);

					/* ������EEPROM */
					AT24CXX_Write(IDCARE_SN_EEPROM_ADDR+(p_SysParamHandle->u4RFCard_ID-1)*IDCARE_SN_LEN, \
								 &p_SysParamHandle->p_eeprom_data->IDCardSN[p_SysParamHandle->u4RFCard_ID-1][0], \
								 IDCARE_SN_LEN);
					app_LcdDispStrDelay(2, 2, "¼��ɹ�", 1500, Page_AdminRFIDManage);
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
  * Description��  //ҳ��-��ҳʱ�䴦��
  *Input:  p_SysParamHandle, ϵͳ�������
  *Output:  //���������˵��
  *Return:  //��������ֵ��˵��
  *Others:  //����˵��
**/
void app_FingerPrintEvent_Handle( SysParam_t * p_SysParamHandle )
{
	AS608Handle_t	*p_as608handle = p_SysParamHandle->p_as608handle;
	u8 str[20] = {0};
	if (IsSetBit(p_SysParamHandle->u8EventReg, FP_EVENT_BIT))
	{
		ResetBit(p_SysParamHandle->u8EventReg, FP_EVENT_BIT);
		/* ����ҳ�� ID �����¼������� */
		switch (p_SysParamHandle->PageID)
		{
			case Page_Main:
				if ( p_SysParamHandle->u8pf_check_result == FpResult_CheckOK)
				{
					int2str(p_as608handle->pserch_result->ID, str);//��ָ��IDת���ַ����ͷ�����ʾ
					LCD_Display_Words(2, 0, "     ID:");
					LCD_Display_Words(2, 4, str);
					
					app_LcdDispStrDelay(1, 2, "�ɹ�����", 1500, Page_Default);
					app_LcdDispStrDelay(2, 0, NULL, 1500, Page_Default);
					/* �����̵������� */
					Switch_On( );
				}
				else
				{
					app_LcdDispStrDelay(2, 2, "ָ�ƴ���", 1500, Page_Default);
					/* ���������� */
					longBeep( );
				}
				break;
				
			case Page_AdminFingerprintInput:
				if ( p_SysParamHandle->u8pf_check_result == FpResult_CheckOK )		/* enter�����Ѱ��� */
				{
					app_LcdDispStrDelay(1, 2, "¼��ɹ�", 1500, Page_AdminFingerprintManage);
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
  * Description��  //ҳ��-��ҳʱ�䴦��
  *Input:  p_SysParamHandle, ϵͳ�������
  *Output:  //���������˵��
  *Return:  //��������ֵ��˵��
  *Others:  //����˵��
**/
void app_GizwitsDataEvent_Handle( SysParam_t * p_SysParamHandle )
{
	dataPoint_t	*p_dataPoint = p_SysParamHandle->p_DataPoint;
	if (IsSetBit(p_SysParamHandle->u8EventReg, Gizwits_EVENT_BIT))
	{
		ResetBit(p_SysParamHandle->u8EventReg, Gizwits_EVENT_BIT);
		/* ����ҳ�� ID �����¼������� */
		switch (p_SysParamHandle->PageID)
		{
			case Page_Main:
				if ( p_dataPoint->valueunlock == 1)
				{
					app_LcdDispStrDelay(2, 1, "Զ�̽����ɹ�", 1500, Page_Default);
					/* �����̵������� */
					Switch_On( );
					/* app������ʱ�ָ� */
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

