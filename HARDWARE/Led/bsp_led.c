/*********************************************************************************
  *Copyright(C),2020-2021, SIRI
  *FileName:  bsp_buzzer.c
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
#include "/Led/bsp_led.h"
/*--------------------------------------------------------------------------------*/

/*
  *Function:  Key_GPIO_Config
  * Description：  //页面-主页时间处理
  *Input:  p_SysParamHandle, 系统参数句柄
  *Output:  //输出参数的说明
  *Return:  //函数返回值的说明
  *Others:  //其他说明
**/
void Led_GPIO_Config( void )
{
	GPIO_InitTypeDef  GPIO_InitStructure;
	
	RCC_APB2PeriphClockCmd(LED_SYSCTL_PERIPH_CLK, ENABLE);	//使能PA端口时钟

	GPIO_InitStructure.GPIO_Pin = LED_GPIO_PIN;				//LED0-->PA 端口配置
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP; 		//开漏输出
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_10MHz;		//IO口速度为50MHz
	GPIO_Init(LED_PORT, &GPIO_InitStructure);			//根据设定参数初始化GPIOA.4

	LED_OFF;
}


/*------------------------------------------ end file --------------------------------------*/



