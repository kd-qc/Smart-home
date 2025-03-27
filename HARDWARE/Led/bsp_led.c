/*********************************************************************************
  *Copyright(C),2020-2021, SIRI
  *FileName:  bsp_buzzer.c
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
#include "/Led/bsp_led.h"
/*--------------------------------------------------------------------------------*/

/*
  *Function:  Key_GPIO_Config
  * Description��  //ҳ��-��ҳʱ�䴦��
  *Input:  p_SysParamHandle, ϵͳ�������
  *Output:  //���������˵��
  *Return:  //��������ֵ��˵��
  *Others:  //����˵��
**/
void Led_GPIO_Config( void )
{
	GPIO_InitTypeDef  GPIO_InitStructure;
	
	RCC_APB2PeriphClockCmd(LED_SYSCTL_PERIPH_CLK, ENABLE);	//ʹ��PA�˿�ʱ��

	GPIO_InitStructure.GPIO_Pin = LED_GPIO_PIN;				//LED0-->PA �˿�����
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP; 		//��©���
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_10MHz;		//IO���ٶ�Ϊ50MHz
	GPIO_Init(LED_PORT, &GPIO_InitStructure);			//�����趨������ʼ��GPIOA.4

	LED_OFF;
}


/*------------------------------------------ end file --------------------------------------*/



