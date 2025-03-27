#include "Buzzer/bsp_buzzer.h"
#include "Led/led.h"

#ifndef TRUE
#define TRUE 1
#endif /* TRUE */

#ifndef FALSE
#define FALSE 0
#endif /* FALSE */

static u32 u32BuzzerTickCnt = 0;
static u32 u32BuzzerWarnCnt = 0; 
static u8 blBuzzerWarn = FALSE; 
/**
 * name: Buzzer_Millisecond
 * decription: led 初始化
 */
void Buzzer_Millisecond_Tick( void )
{
	if (u32BuzzerTickCnt > 0)
	{
		u32BuzzerTickCnt--;
		if (u32BuzzerTickCnt == 0)
		{
			BUZZER_OFF;
			WARN_LED_OFF;
		}
	}

	if (blBuzzerWarn == TRUE)
	{
		u32BuzzerWarnCnt++;
		if (u32BuzzerWarnCnt == 50)
		{
			u32BuzzerWarnCnt = 0;

			BUZZER_TOGGLE;
			WARN_LED_TOGGLE;
		}
	}
}

/**
 * name: LED_Init
 * decription: led 初始化
 */
void Buzzer_Init( void )
{
	GPIO_InitTypeDef  GPIO_InitStructure;
	RCC_APB2PeriphClockCmd(BUZZER_RCC, ENABLE);	//使能PA端口时钟

	GPIO_InitStructure.GPIO_Pin = BUZZER_PIN;				//LED0-->PA 端口配置
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP; 		//开漏输出
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;		//IO口速度为50MHz
	GPIO_Init(BUZZER_PORT, &GPIO_InitStructure);			//根据设定参数初始化GPIOA.4

	//长鸣
	//Buzzer_LongBeep(  );
}

/**
 * name: Buzzer_ShortBeep
 * decription: 蜂鸣器短鸣
 */
void Buzzer_ShortBeep( void )
{
	BUZZER_ON;
	WARN_LED_ON;
	u32BuzzerTickCnt = 20;	//短鸣时间
}


/**
 * name: Buzzer_LongBeep
 * decription: 蜂鸣器短鸣
 */
void Buzzer_LongBeep( void )
{
	BUZZER_ON;
	WARN_LED_ON;
	u32BuzzerTickCnt = 100;	//长鸣时间
}

/**
 * name: Buzzer_WarnOn
 * decription: 开启蜂鸣器报警
 */
void Buzzer_WarnOn( void )
{
	blBuzzerWarn = TRUE;
	
	//u32BuzzerWarnCnt = 0;
}

/**
 * name: Buzzer_WarnOff
 * decription: 关闭蜂鸣器报警
 */
void Buzzer_WarnOff( void )
{
	if (blBuzzerWarn == TRUE)
	{
		blBuzzerWarn = FALSE;
		u32BuzzerWarnCnt = 0;
		BUZZER_OFF;
		WARN_LED_OFF;
	}
}

