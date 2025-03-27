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
 * decription: led ��ʼ��
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
 * decription: led ��ʼ��
 */
void Buzzer_Init( void )
{
	GPIO_InitTypeDef  GPIO_InitStructure;
	RCC_APB2PeriphClockCmd(BUZZER_RCC, ENABLE);	//ʹ��PA�˿�ʱ��

	GPIO_InitStructure.GPIO_Pin = BUZZER_PIN;				//LED0-->PA �˿�����
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP; 		//��©���
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;		//IO���ٶ�Ϊ50MHz
	GPIO_Init(BUZZER_PORT, &GPIO_InitStructure);			//�����趨������ʼ��GPIOA.4

	//����
	//Buzzer_LongBeep(  );
}

/**
 * name: Buzzer_ShortBeep
 * decription: ����������
 */
void Buzzer_ShortBeep( void )
{
	BUZZER_ON;
	WARN_LED_ON;
	u32BuzzerTickCnt = 20;	//����ʱ��
}


/**
 * name: Buzzer_LongBeep
 * decription: ����������
 */
void Buzzer_LongBeep( void )
{
	BUZZER_ON;
	WARN_LED_ON;
	u32BuzzerTickCnt = 100;	//����ʱ��
}

/**
 * name: Buzzer_WarnOn
 * decription: ��������������
 */
void Buzzer_WarnOn( void )
{
	blBuzzerWarn = TRUE;
	
	//u32BuzzerWarnCnt = 0;
}

/**
 * name: Buzzer_WarnOff
 * decription: �رշ���������
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

