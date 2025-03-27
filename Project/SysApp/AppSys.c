/*********************************************************************************
  *Copyright(C),2020-2021, SIRI
  *FileName:  AppSys.c
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
#include "stm32f10x.h"

#include "SysApp/AppSys.h"
#include "SysApp/AppParam.h"

#ifndef TRUE
#define TRUE  1
#endif

#ifndef FALSE
#define FALSE  0
#endif

#ifndef NULL
#define NULL  0
#endif

u8 buff[30];//������ʾ��������

void Key2_short_press_up_handle( void );
void Key2_long_press_down_handle( void );
void TurnONLight( void );
void TurnOffLight( void );
void TurnOnAirCondit( void );
void TurnOffAirCondit( void );
void SetAutoMode( void );
void SetManualMode( void );
void OpenCurtain( void );
void CloseCurtain( void );


static void drv_Sensor_Handle(SysParam_t *psSysParamHandle);


/*--------------------------------------------------------------------------------*/
/* ���� */
void assert_failed(uint8_t* file, uint32_t line)
{
	DEBUG_LOG("file path:%s, line: %d", file, line);
}

static u32 u32SysTick = 0;

#define CMD_NUM 	10

/* ָ���б� */
CmdHandle_t CmdList[CMD_NUM] = 
{

	"����",			TurnONLight,
	"�ص�",			TurnOffLight,

	"������",			TurnOnAirCondit,
	"�ط���",			TurnOffAirCondit,
	"������",			OpenCurtain,
	"�ش���",			CloseCurtain,
	"�Զ�ģʽ",			SetAutoMode,
	"�ֶ�ģʽ",			SetManualMode,
	"�ȵ�����",			Key2_short_press_up_handle,
	"һ������",			Key2_long_press_down_handle,
};

void TurnONLight( void )
{
	if (!LIGHT_SWUTCH_STAT)
	LIGHT_SWITCH_ON;
}

void TurnOffLight( void )
{
	if (LIGHT_SWUTCH_STAT)
	LIGHT_SWITCH_OFF;
}
void TurnOnAirCondit( void )
{
	if (!AIRCONDI_SWUTCH_STAT)
		AIRCONDI_SWITCH_ON;
}

void TurnOffAirCondit( void )
{
	if (AIRCONDI_SWUTCH_STAT)
	AIRCONDI_SWITCH_OFF;
}

void OpenCurtain( void )
{
	if (SysParamHandle.u8CurtainFlg == 0)
	{
		Motor_PreSet (Status_CW, 5000, 2);
		LED_TIP_ON;
	}
	SysParamHandle.u8CurtainFlg = 1;
}

void CloseCurtain( void )
{
	if (SysParamHandle.u8CurtainFlg == 1)
	{
		Motor_PreSet (Status_CCW, 5000, 2);
		LED_TIP_OFF;
	}
	SysParamHandle.u8CurtainFlg = 0;
}
void SetAutoMode( void )
{
	SysParamHandle.eMode = AutoMode;
}

void SetManualMode( void )
{
	SysParamHandle.eMode = ManualMode;
}



/*--------------------------------------------------------------------------------*/
/*
  *Function:  GizwitsDataEventHandle
  * Description��  //ҳ��-��ҳʱ�䴦��
  *Input:  p_SysParamHandle, ϵͳ�������
  *Output:  //���������˵��
  *Return:  //��������ֵ��˵��
  *Others:  //����˵��
**/
static void GizwitsDataEventHandle ( int code, void *pvParam )
{
	DEBUG_LOG("**********GizwitsDataEventHandle***********\n");
	dataPoint_t *psCurrentDP = (dataPoint_t *)pvParam;
	if (SysParamHandle.eMode == AutoMode)
	{
		return;
	}
	
	switch (code)
	{
		case EVENT_light:
			if (psCurrentDP->valuelight == 1)
			{
				TurnONLight( );
			}
			else
			{
				TurnOffLight( );
			}
			break;
			
		case EVENT_aircondi:
			if (psCurrentDP->valueaircondi == 1)
			{
				TurnOnAirCondit( );
			}
			else
			{
				TurnOffAirCondit( );
			}
			break;

		case EVENT_curtain:
			if (psCurrentDP->valuecurtain == 1)
			{
				OpenCurtain( );
			}
			else
			{
				CloseCurtain( );
			}
			break;
			
		case WIFI_NTP:
			break;	
			
		default:
			/* �����¼� - ��λ */
			//SetBit(SysParamHandle.u8EventReg, Gizwits_EVENT_BIT);
			break;
	}
}


/*--------------------------------------------------------------------------------*/
/*
  *Function:  KeyEventHandle
  * Description��  //ҳ��-��ҳʱ�䴦��
  *Input:  p_SysParamHandle, ϵͳ�������
  *Output:  //���������˵��
  *Return:  //��������ֵ��˵��
  *Others:  //����˵��
**/
static void KeyEventHandle( u8 u8_code)
{
	DEBUG_LOG("**********KeyEventHandle***********\n");
	DEBUG_LOG("key_code: %d\n", u8_code);
	/* �����¼� - ��λ */
	SetBit(SysParamHandle.u8EventReg, KEY_EVENT_BIT);
	SysParamHandle.u8KeyCode = u8_code;
}



/*--------------------------------------------------------------------------------*/
/**
 * name: Sys_timer_handle
 * decription: ����ϵͳʱ��Ƭ
 * aparam��void
 *
*/
static void Sys_timer_handle( void )
{
	u32SysTick++;
	static u32 warnLed_tick = 0;
	/* ����ʱ��Ƭ */
	if (SysParamHandle.p_keyhandle->u32_keyscan_time > 0)
	{
		SysParamHandle.p_keyhandle->u32_keyscan_time--;	
	} 
	if (SysParamHandle.u32SensorTim > 0)
	{
		SysParamHandle.u32SensorTim--;	
	} 
	if (SysParamHandle.u32LcdUpdateTim > 0)
	{
		SysParamHandle.u32LcdUpdateTim--;	
	} 
	if (SysParamHandle.u32SyncDataTim > 0)
	{
		SysParamHandle.u32SyncDataTim--;	
	}
	if (SysParamHandle.u32CycleWarnTim > 0)
	{
		SysParamHandle.u32CycleWarnTim--;	
	}

	if (u32SysTick - warnLed_tick > 500)
	{
		warnLed_tick  = u32SysTick;

		if (SysParamHandle.blWarn == TRUE)
		{
			WARN_LED_FLASH;
		}
		else
		{
			WARN_LED_OFF;
		}
	}
	/* �̵��� */
	gizTimerMs();
}



/**
 * name: Gizwits_Init
 * decription: APP�����ʼ
 * param: void
*/
void gizwits_dataPoint_Init( void )
{
	memset((uint8_t*)&currentDataPoint, 0, sizeof(dataPoint_t));
    
    /** Warning !!! DataPoint Variables Init , Must Within The Data Range **/ 
    currentDataPoint.valuetempGate = 40;
    currentDataPoint.valuelightnessGate = 800;

}

/**
 * name: Gizwits_Init
 * decription: ������Э��֧�����֧�ֳ�ʼ��
 * param: void
*/
void Gizwits_Init( void )
{
    uart1_init(9600); 
    gizwitsInit();
    gizwits_dataPoint_Init();
    
    extern GizwitsCallback gfunCallback;
    gfunCallback = GizwitsDataEventHandle;
}

/*--------------------------------------------------------------------------------*/

/**
 * name: Sys_ctl_task
 * decription: ϵͳ���ƽ��� -- ʵ�ʳ�������ģ��
 * param: 
 * @psSysParamHandle: ϵͳ�������
*/
void app_Ctl_Task( SysParam_t *p_SysParamHandle )
{
	/* �Ƿ�Ϊ�Զ�ģʽ */ 
	if (p_SysParamHandle->eMode == AutoMode)
	{
		/* �¶ȴ�����ֵ */ 
		if (p_SysParamHandle->psDHT11DataHandle->temp_int >= p_SysParamHandle->p_DataPoint->valuetempGate)
		{
			//�򿪿յ����򿪷���
			TurnOnAirCondit( );
		}
		else
		{
			//�رտյ����򿪷���
			TurnOffAirCondit( );
		}
		
		/* �ж������Ƿ������ֵ */ 
		if (p_SysParamHandle->u16Lightness > p_SysParamHandle->p_DataPoint->valuelightnessGate)
		{
			//���ƣ��رմ���
			TurnOffLight( );
			CloseCurtain( );
		}
		else
		{
			//�صƣ��򿪴���
			TurnONLight( );
			OpenCurtain( );
		}
		
	}

	static u8 status = 0;
	status = 0;
	//����ֵ�ж�
	if (p_SysParamHandle->fMqValue > 0.6)
	{
		status |= 1;
	}
	if (p_SysParamHandle->psDHT11DataHandle->temp_int >= p_SysParamHandle->p_DataPoint->valuetempGate)
	{
		status |= (1<<1);
	}
	switch (status)
	{
		case 0:
			p_SysParamHandle->status = 0;
			break;
		case 1:
			p_SysParamHandle->status = 1;
			break;
		case (1<<1):
			p_SysParamHandle->status = 2;
			break;
		case (1|(1<<1)):
			p_SysParamHandle->status = 3;
			break;
		default:
			break;
	}

	//������ģʽ���򿪱���
	if (status != 0)
	{
		Buzzer_WarnOn(  );
		//WARN_LED_ON;
	}
	else
	{
		Buzzer_WarnOff( );
		//WARN_LED_OFF;
	}
}

void OLED_InitPage(void)
{
	/* ���� */
	OLED_Clear();				//OLED����
	
	OLED_ShowCHinese(0,		0,	0);	//��
	OLED_ShowCHinese(16,	0,	2);	//��
	OLED_ShowString(32,		0,	":",16);	
	
	OLED_ShowCHinese(0,		2,	1);	//ʪ
	OLED_ShowCHinese(16,	2,	2);	//��
	OLED_ShowString(32,		2,	":",16);	
	
	OLED_ShowCHinese(0,		4,	5);	//��
	OLED_ShowCHinese(16,	4,	6);	//��
	OLED_ShowString(32,		4,	":",16);	
	
	OLED_ShowCHinese(0,		6,	13);	//��
	OLED_ShowCHinese(16,	6,	14);	//��
	OLED_ShowCHinese(32,	6,	15);	//Ũ
	OLED_ShowCHinese(48,	6,	16);	//��
	OLED_ShowString(64,		6,	":",16);	
	
//	OLED_ShowCHinese(0,2,2);
//	OLED_ShowCHinese(0,4,2);
//	OLED_ShowCHinese(0,6,2);
	
}

/**
 * name: OLED_UpdateParam
 * decription: OLED ��������
 * aparam��void
 *
*/
void app_OledUpdateParam( SysParam_t *p_SysParamHandle )
{
	char str[16] = {0};
	if (p_SysParamHandle->u32LcdUpdateTim == 0)
	{
		/* ����ʱ����װ�� */
		p_SysParamHandle->u32LcdUpdateTim = 1000;
		
	
		sprintf((char *)buff,"%4d",p_SysParamHandle->psDHT11DataHandle->temp_int);
		OLED_ShowString(40,0,buff,16);
		

		sprintf((char *)buff,"%4d",p_SysParamHandle->psDHT11DataHandle->humi_int);
		OLED_ShowString(40,2,buff,16);
		
		
		
		sprintf((char *)buff,"%4d",p_SysParamHandle->u16Lightness);
		OLED_ShowString(40,4,buff,16);
		
		sprintf((char *)buff,"%.2f",p_SysParamHandle->fMqValue);
		OLED_ShowString(80,6,buff,16);
		
		
		
	}
}

/**
 * name: Get_sendor_task
 * decription: ��ȡ����������
 * param: 
 * @p_sensor_data_handle: �������������
*/
void drv_Sensor_Handle( SysParam_t *p_SysParamHandle )
{
	if (p_SysParamHandle->u32SensorTim == 0)
	{
		p_SysParamHandle->u32SensorTim = 200;

		p_SysParamHandle->u16Lightness = bh_data_read( );	//!< ��ȡ����ǿ��

		get_mq2_value( &p_SysParamHandle->fMqValue );	//!< ��ȡ����Ũ��
		
		DHT11_Read_TempAndHumidity( p_SysParamHandle->psDHT11DataHandle );	//!< ��ȡ��ʪ��

	}
}


/**
 * name: app_SyncData_Task
 * decription: ͬ�����ݵ㣬��������
 * param: 
 * @p_SysParamHandle: ϵͳ�������
*/
void app_SyncData_Task( SysParam_t *p_SysParamHandle )
{
	if (p_SysParamHandle->u32SyncDataTim == 0)
	{
		p_SysParamHandle->u32SyncDataTim = 500;

		p_SysParamHandle->p_DataPoint->valuelight = LIGHT_SWUTCH_STAT;
		p_SysParamHandle->p_DataPoint->valueaircondi = AIRCONDI_SWUTCH_STAT;
		p_SysParamHandle->p_DataPoint->valuecurtain = p_SysParamHandle->u8CurtainFlg;
		p_SysParamHandle->p_DataPoint->valuemode = p_SysParamHandle->eMode;
		p_SysParamHandle->p_DataPoint->valuetemp = p_SysParamHandle->psDHT11DataHandle->temp_int;
		p_SysParamHandle->p_DataPoint->valuehumi = p_SysParamHandle->psDHT11DataHandle->humi_int;
		p_SysParamHandle->p_DataPoint->valuelightness = p_SysParamHandle->u16Lightness;
		p_SysParamHandle->p_DataPoint->valuemq2 = p_SysParamHandle->fMqValue;
		p_SysParamHandle->p_DataPoint->valuestatus = p_SysParamHandle->status;

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
		switch (p_SysParamHandle->u8GizwistCode)
		{
			
		}
	}
}

/*--------------------------------------------------------------------------------*/



/*--------------------------------------------------------------------------------*/
/*
  *Function:  app_BspInit
  * Description��  //ҳ��-��ҳʱ�䴦��
  *Input:  p_SysParamHandle, ϵͳ�������
  *Output:  //���������˵��
  *Return:  //��������ֵ��˵��
  *Others:  //����˵��
**/
void app_BspInit( SysParam_t *p_SysParamHandle )
{
	/* debug log uart config */
	DEBUG_UART_Config( );
	DEBUG_LOG("Bsp init\n");
	
	/* �ϵ���ʱ���ȴ�����ģ�������ȶ� */
	delay_ms( 200 );
	
	/* ��ʼ����ʱ��3�� �ж�Ƶ�� 1000hz */
    FML_TIME_Init();
    /*****************************************************************************************************************/
    /* *************************ע��ϵͳʱ��Ƭ������************************************************************** */
    /*****************************************************************************************************************/
    FML_TIME_Register(Sys_timer_handle, 1);	//ϵͳʱ��Ƭ��1tick = 1ms
    FML_TIME_Start(Sys_timer_handle); //������ʱ 
	/*****************************************************************************************************************/
	/* *************************** ��ʼ��IO�豸 ******************************************************************** */
	/*****************************************************************************************************************/
	/* ���ð������� */
	Key_GPIO_Config(p_SysParamHandle->p_keyhandle);	

	/* LED Fan IO ��ʼ�� */
	LED_Init( );

	/*****************************************************************************************************************/
	/* ************************* ��ģ�鿪�����м�� ***************************************************************** */
	/******************************************************************************************************************/

	/* dht11 ��ʼ�� */
	DHT11_Init();
	/* ������ ��ʼ�� */
	Buzzer_Init( );
	FML_TIME_Register(Buzzer_Millisecond_Tick, 10); //ϵͳʱ��Ƭ��1tick = 1ms
	FML_TIME_Start(Buzzer_Millisecond_Tick); //������ʱ 
	
	/* ����ģ���ʼ�� */
	ld3322_init( );
	RegisterLd3322(p_SysParamHandle->psLdHandle, CmdList, CMD_NUM);	/*!< ע��ָ������� */

	/* ���������ʼ�� */
	Moto_Init( );
	FML_TIME_Register(Motor_Millisecond, 1); //ϵͳʱ��Ƭ��1tick = 1ms
	FML_TIME_Start(Motor_Millisecond); //������ʱ 

	/* 0.96OLED��ʼ�� */
	OLED_Init();

	/* �̵�����ʼ�� */
	Switch_GPIO_Config( );
	/* ���մ�������ʼ�� */
	BH1750_Init( );
	/* �̸�ADC��ʼ�� */
	ADC_Sensor_Init( );
	
	/* ������SDK��ʼ�� */
	Gizwits_Init();
	
	/*!< ��ʱȷ����ʼҳ����� */
	delay_ms(300);
	/* OLED��ʾ��ʼ���� */
	OLED_Clear();	
	OLED_InitPage(); 
	

}

/*--------------------------------------------------------------------------------*/
/*
  *Function:  app_Process
  * Description��  //ҳ��-��ҳʱ�䴦��
  *Input:  p_SysParamHandle, ϵͳ�������
  *Output:  //���������˵��
  *Return:  //��������ֵ��˵��
  *Others:  //����˵��
**/
void app_Process( SysParam_t *p_SysParamHandle )
{
/***************** �ײ����� **********************/
	/* �������ɨ�� - ���� */
	//drv_Key_Handle( p_SysParamHandle->p_keyhandle );  
	
	/* ���������ݹ�ȥ - �߳� */ 
	drv_Sensor_Handle( p_SysParamHandle );
	
	/* ld3320����ʶ��ģ�� - �߳� */ 
	drv_Ld3322_Handle(p_SysParamHandle->psLdHandle);
	
/***************** �м�� **********************/	 

	/* �������ƶ�Э�鴦�� - ���� */
	gizwitsHandle( p_SysParamHandle->p_DataPoint );

	/* ����������ͬ�� - ���� */
	app_SyncData_Task( p_SysParamHandle );
	
	/* oled�������� - ���� */
	//OLED_CLS();
	app_OledUpdateParam( p_SysParamHandle );

	
/***************** Ӧ�ò��¼� **********************/	 

	/* �������¼����� - �߳� */ 
	app_GizwitsDataEvent_Handle( p_SysParamHandle );
	
	/* ϵͳ�������� - �߳� */ 
	app_Ctl_Task( p_SysParamHandle );
	
	
}

/**
 * name: Key_long_press_Up_handle
 * decription: �̰������ص�����
*/
void Key1_short_press_up_handle( void )
{
	DEBUG_LOG("Key1 short press\n");
	gizwitsSetMode(WIFI_PRODUCTION_TEST);
}

/**
 * name: Key_long_press_Up_handle
 * decription: ���������ص�����
*/
void Key1_long_press_down_handle( void )
{
	DEBUG_LOG("Key1 long press\n");
	gizwitsSetMode(WIFI_RESET_MODE);
}

/**
 * name: Key_long_press_Up_handle
 * decription: ��������̧��ص�����
*/
void Key1_long_press_up_handle( void )
{
	DEBUG_LOG("Key1 long press up\n");
}


/**
 * name: Key_long_press_Up_handle
 * decription: �̰������ص�����
*/
void Key2_short_press_up_handle( void )
{
	DEBUG_LOG("Key2 short press\n");
	LED_TIP_ON;
	delay_ms(800);
	LED_TIP_OFF;
	gizwitsSetMode(WIFI_SOFTAP_MODE);
}

/**
 * name: Key_long_press_Up_handle
 * decription: ���������ص�����
*/
void Key2_long_press_down_handle( void )
{
	DEBUG_LOG("Key2 long press\n");
	LED_TIP_ON;
	delay_ms(800);
	LED_TIP_OFF;
	delay_ms(800);
	LED_TIP_ON;
	delay_ms(800);
	LED_TIP_OFF;
	gizwitsSetMode(WIFI_AIRLINK_MODE);
}

/**
 * name: Key_long_press_Up_handle
 * decription: ��������̧��ص�����
*/
void Key2_long_press_up_handle( void )
{
	DEBUG_LOG("Key2 long press up\n");
	LIGHT_OFF;
}

/*--------------------------------------------------------------------------------*/

/****************************************** end file ********************************************/

