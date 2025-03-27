/*********************************************************************************
  *Copyright(C),2020-2021, SIRI
  *FileName:  AppSys.c
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

u8 buff[30];//参数显示缓存数组

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
/* 断言 */
void assert_failed(uint8_t* file, uint32_t line)
{
	DEBUG_LOG("file path:%s, line: %d", file, line);
}

static u32 u32SysTick = 0;

#define CMD_NUM 	10

/* 指令列表 */
CmdHandle_t CmdList[CMD_NUM] = 
{

	"开灯",			TurnONLight,
	"关灯",			TurnOffLight,

	"开风扇",			TurnOnAirCondit,
	"关风扇",			TurnOffAirCondit,
	"开窗帘",			OpenCurtain,
	"关窗帘",			CloseCurtain,
	"自动模式",			SetAutoMode,
	"手动模式",			SetManualMode,
	"热点配网",			Key2_short_press_up_handle,
	"一键配网",			Key2_long_press_down_handle,
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
  * Description：  //页面-主页时间处理
  *Input:  p_SysParamHandle, 系统参数句柄
  *Output:  //输出参数的说明
  *Return:  //函数返回值的说明
  *Others:  //其他说明
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
			/* 按键事件 - 置位 */
			//SetBit(SysParamHandle.u8EventReg, Gizwits_EVENT_BIT);
			break;
	}
}


/*--------------------------------------------------------------------------------*/
/*
  *Function:  KeyEventHandle
  * Description：  //页面-主页时间处理
  *Input:  p_SysParamHandle, 系统参数句柄
  *Output:  //输出参数的说明
  *Return:  //函数返回值的说明
  *Others:  //其他说明
**/
static void KeyEventHandle( u8 u8_code)
{
	DEBUG_LOG("**********KeyEventHandle***********\n");
	DEBUG_LOG("key_code: %d\n", u8_code);
	/* 按键事件 - 置位 */
	SetBit(SysParamHandle.u8EventReg, KEY_EVENT_BIT);
	SysParamHandle.u8KeyCode = u8_code;
}



/*--------------------------------------------------------------------------------*/
/**
 * name: Sys_timer_handle
 * decription: 处理系统时间片
 * aparam：void
 *
*/
static void Sys_timer_handle( void )
{
	u32SysTick++;
	static u32 warnLed_tick = 0;
	/* 键盘时间片 */
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
	/* 继电器 */
	gizTimerMs();
}



/**
 * name: Gizwits_Init
 * decription: APP界面初始
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
 * decription: 机智云协议支持相关支持初始化
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
 * decription: 系统控制进程 -- 实际场景条件模拟
 * param: 
 * @psSysParamHandle: 系统操作句柄
*/
void app_Ctl_Task( SysParam_t *p_SysParamHandle )
{
	/* 是否为自动模式 */ 
	if (p_SysParamHandle->eMode == AutoMode)
	{
		/* 温度大于阈值 */ 
		if (p_SysParamHandle->psDHT11DataHandle->temp_int >= p_SysParamHandle->p_DataPoint->valuetempGate)
		{
			//打开空调，打开风扇
			TurnOnAirCondit( );
		}
		else
		{
			//关闭空调，打开风扇
			TurnOffAirCondit( );
		}
		
		/* 判断亮度是否大于阈值 */ 
		if (p_SysParamHandle->u16Lightness > p_SysParamHandle->p_DataPoint->valuelightnessGate)
		{
			//开灯，关闭窗帘
			TurnOffLight( );
			CloseCurtain( );
		}
		else
		{
			//关灯，打开窗帘
			TurnONLight( );
			OpenCurtain( );
		}
		
	}

	static u8 status = 0;
	status = 0;
	//烟雾值判断
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

	//非正常模式，打开报警
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
	/* 清屏 */
	OLED_Clear();				//OLED清屏
	
	OLED_ShowCHinese(0,		0,	0);	//温
	OLED_ShowCHinese(16,	0,	2);	//度
	OLED_ShowString(32,		0,	":",16);	
	
	OLED_ShowCHinese(0,		2,	1);	//湿
	OLED_ShowCHinese(16,	2,	2);	//度
	OLED_ShowString(32,		2,	":",16);	
	
	OLED_ShowCHinese(0,		4,	5);	//光
	OLED_ShowCHinese(16,	4,	6);	//照
	OLED_ShowString(32,		4,	":",16);	
	
	OLED_ShowCHinese(0,		6,	13);	//烟
	OLED_ShowCHinese(16,	6,	14);	//雾
	OLED_ShowCHinese(32,	6,	15);	//浓
	OLED_ShowCHinese(48,	6,	16);	//度
	OLED_ShowString(64,		6,	":",16);	
	
//	OLED_ShowCHinese(0,2,2);
//	OLED_ShowCHinese(0,4,2);
//	OLED_ShowCHinese(0,6,2);
	
}

/**
 * name: OLED_UpdateParam
 * decription: OLED 参数更新
 * aparam：void
 *
*/
void app_OledUpdateParam( SysParam_t *p_SysParamHandle )
{
	char str[16] = {0};
	if (p_SysParamHandle->u32LcdUpdateTim == 0)
	{
		/* 任务时间重装载 */
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
 * decription: 获取传感器数据
 * param: 
 * @p_sensor_data_handle: 传感器操作句柄
*/
void drv_Sensor_Handle( SysParam_t *p_SysParamHandle )
{
	if (p_SysParamHandle->u32SensorTim == 0)
	{
		p_SysParamHandle->u32SensorTim = 200;

		p_SysParamHandle->u16Lightness = bh_data_read( );	//!< 读取光照强度

		get_mq2_value( &p_SysParamHandle->fMqValue );	//!< 读取烟雾浓度
		
		DHT11_Read_TempAndHumidity( p_SysParamHandle->psDHT11DataHandle );	//!< 读取温湿度

	}
}


/**
 * name: app_SyncData_Task
 * decription: 同步数据点，数据上行
 * param: 
 * @p_SysParamHandle: 系统操作句柄
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
		switch (p_SysParamHandle->u8GizwistCode)
		{
			
		}
	}
}

/*--------------------------------------------------------------------------------*/



/*--------------------------------------------------------------------------------*/
/*
  *Function:  app_BspInit
  * Description：  //页面-主页时间处理
  *Input:  p_SysParamHandle, 系统参数句柄
  *Output:  //输出参数的说明
  *Return:  //函数返回值的说明
  *Others:  //其他说明
**/
void app_BspInit( SysParam_t *p_SysParamHandle )
{
	/* debug log uart config */
	DEBUG_UART_Config( );
	DEBUG_LOG("Bsp init\n");
	
	/* 上电延时，等待各个模块运行稳定 */
	delay_ms( 200 );
	
	/* 初始化定时器3， 中断频率 1000hz */
    FML_TIME_Init();
    /*****************************************************************************************************************/
    /* *************************注册系统时间片处理函数************************************************************** */
    /*****************************************************************************************************************/
    FML_TIME_Register(Sys_timer_handle, 1);	//系统时间片，1tick = 1ms
    FML_TIME_Start(Sys_timer_handle); //开启定时 
	/*****************************************************************************************************************/
	/* *************************** 初始化IO设备 ******************************************************************** */
	/*****************************************************************************************************************/
	/* 配置按键引脚 */
	Key_GPIO_Config(p_SysParamHandle->p_keyhandle);	

	/* LED Fan IO 初始化 */
	LED_Init( );

	/*****************************************************************************************************************/
	/* ************************* 主模块开机运行检测 ***************************************************************** */
	/******************************************************************************************************************/

	/* dht11 初始化 */
	DHT11_Init();
	/* 蜂鸣器 初始化 */
	Buzzer_Init( );
	FML_TIME_Register(Buzzer_Millisecond_Tick, 10); //系统时间片，1tick = 1ms
	FML_TIME_Start(Buzzer_Millisecond_Tick); //开启定时 
	
	/* 语音模块初始化 */
	ld3322_init( );
	RegisterLd3322(p_SysParamHandle->psLdHandle, CmdList, CMD_NUM);	/*!< 注册指令参数表 */

	/* 步进电机初始化 */
	Moto_Init( );
	FML_TIME_Register(Motor_Millisecond, 1); //系统时间片，1tick = 1ms
	FML_TIME_Start(Motor_Millisecond); //开启定时 

	/* 0.96OLED初始化 */
	OLED_Init();

	/* 继电器初始化 */
	Switch_GPIO_Config( );
	/* 光照传感器初始化 */
	BH1750_Init( );
	/* 烟感ADC初始化 */
	ADC_Sensor_Init( );
	
	/* 机智云SDK初始化 */
	Gizwits_Init();
	
	/*!< 延时确保初始页面错误 */
	delay_ms(300);
	/* OLED显示初始画面 */
	OLED_Clear();	
	OLED_InitPage(); 
	

}

/*--------------------------------------------------------------------------------*/
/*
  *Function:  app_Process
  * Description：  //页面-主页时间处理
  *Input:  p_SysParamHandle, 系统参数句柄
  *Output:  //输出参数的说明
  *Return:  //函数返回值的说明
  *Others:  //其他说明
**/
void app_Process( SysParam_t *p_SysParamHandle )
{
/***************** 底层驱动 **********************/
	/* 矩阵键盘扫描 - 任务 */
	//drv_Key_Handle( p_SysParamHandle->p_keyhandle );  
	
	/* 传感器数据过去 - 线程 */ 
	drv_Sensor_Handle( p_SysParamHandle );
	
	/* ld3320语音识别模块 - 线程 */ 
	drv_Ld3322_Handle(p_SysParamHandle->psLdHandle);
	
/***************** 中间层 **********************/	 

	/* 机智云云端协议处理 - 任务 */
	gizwitsHandle( p_SysParamHandle->p_DataPoint );

	/* 机智云数据同步 - 任务 */
	app_SyncData_Task( p_SysParamHandle );
	
	/* oled参数更新 - 任务 */
	//OLED_CLS();
	app_OledUpdateParam( p_SysParamHandle );

	
/***************** 应用层事件 **********************/	 

	/* 机智云事件处理 - 线程 */ 
	app_GizwitsDataEvent_Handle( p_SysParamHandle );
	
	/* 系统控制任务 - 线程 */ 
	app_Ctl_Task( p_SysParamHandle );
	
	
}

/**
 * name: Key_long_press_Up_handle
 * decription: 短按按键回调函数
*/
void Key1_short_press_up_handle( void )
{
	DEBUG_LOG("Key1 short press\n");
	gizwitsSetMode(WIFI_PRODUCTION_TEST);
}

/**
 * name: Key_long_press_Up_handle
 * decription: 长按按键回调函数
*/
void Key1_long_press_down_handle( void )
{
	DEBUG_LOG("Key1 long press\n");
	gizwitsSetMode(WIFI_RESET_MODE);
}

/**
 * name: Key_long_press_Up_handle
 * decription: 长按按键抬起回调函数
*/
void Key1_long_press_up_handle( void )
{
	DEBUG_LOG("Key1 long press up\n");
}


/**
 * name: Key_long_press_Up_handle
 * decription: 短按按键回调函数
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
 * decription: 长按按键回调函数
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
 * decription: 长按按键抬起回调函数
*/
void Key2_long_press_up_handle( void )
{
	DEBUG_LOG("Key2 long press up\n");
	LIGHT_OFF;
}

/*--------------------------------------------------------------------------------*/

/****************************************** end file ********************************************/

