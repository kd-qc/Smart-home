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
#include <stdio.h>
#include "SysApp/AppParam.h"

/*--------------------------------------------------------------------------------*/


extern  void Key1_short_press_up_handle( void );
extern  void Key1_long_press_down_handle( void );
extern  void Key1_long_press_up_handle( void );
extern  void Key2_short_press_up_handle( void );
extern  void Key2_long_press_down_handle( void );
extern  void Key2_long_press_up_handle( void );



/* 按键对象结构注册表 */
SingleKeyTypedef_t single_key_table[KEY_NUM] =
{
	{0, KEY1_SYSCTL_PERIPH_CLK, KEY1_GPIO_PORT, KEY1_GPIO_PIN, NULL, Key1_short_press_up_handle, Key1_long_press_down_handle, Key1_long_press_up_handle},
	{1, KEY2_SYSCTL_PERIPH_CLK, KEY2_GPIO_PORT, KEY2_GPIO_PIN, NULL, Key2_short_press_up_handle, Key2_long_press_down_handle, Key2_long_press_up_handle},
};

/* 按键对象结构注册表 */
MatrixKeyTypedef_t matrix_key_table[KEY_NUM] =
{
	0,
};

/* 按键结构处理句柄 */
sKeyHandle_t keyhandle = {KEY_SCAN_TIME, 0, KEY_NUM, CURRENT_KEYS_TYPE, (SingleKeyTypedef_t *)single_key_table, (MatrixKeyTypedef_t *)matrix_key_table};

DHT11_Data_TypeDef dht11_data = 
{
	0
};


SysParam_t SysParamHandle = 
{
	.PageID = Page_Main,
	.u8EventReg = 0,
	.u8KeyCode = 0xFF, 
	
	.psDHT11DataHandle		= &dht11_data,
	.psLdHandle				= &gs_Ld3322Handle,
	
	.p_keyhandle 			= &keyhandle, 
	.p_DataPoint 			= &currentDataPoint,
};

/*--------------------------------------------------------------------------------*/

/****************************************** end file ********************************************/

