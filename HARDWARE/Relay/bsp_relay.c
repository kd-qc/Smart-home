/*********************************************************************************
  *Copyright(C),2020-2021, SIRI
  *FileName:  bsp_switch.c
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
#include "Relay/bsp_relay.h"

/*--------------------------------------------------------------------------------*/

static u32 u32_switch_time = 0;

/*
  *Function:  Key_GPIO_Config
  * Description��  //ҳ��-��ҳʱ�䴦��
  *Input:  p_SysParamHandle, ϵͳ�������
  *Output:  //���������˵��
  *Return:  //��������ֵ��˵��
  *Others:  //����˵��
**/
void Switch_GPIO_Config( void )
{
	GPIO_InitTypeDef  GPIO_InitStructure;
	
	RCC_APB2PeriphClockCmd(LIGHT_SWITCH_SYSCTL_PERIPH_CLK, ENABLE);	//ʹ��PA�˿�ʱ��
	
	GPIO_InitStructure.GPIO_Pin = LIGHT_SWITCH_GPIO_PIN|AIRCONDI_SWITCH_GPIO_PIN;				//LED0-->PA �˿�����
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;		//��©���
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_10MHz;		//IO���ٶ�Ϊ50MHz
	GPIO_Init(LIGHT_SWITCH_PORT, &GPIO_InitStructure);			//�����趨������ʼ��GPIOA.4

	LIGHT_SWITCH_OFF;	
	AIRCONDI_SWITCH_OFF;	
	
}

/*--------------------------------------------------------------------------------*/
/*
  *Function:  Switch_1ms_tick
  * Description��  //ҳ��-��ҳʱ�䴦��
  *Input:  p_SysParamHandle, ϵͳ�������
  *Output:  //���������˵��
  *Return:  //��������ֵ��˵��
  *Others:  //����˵��
**/
void Switch_1ms_tick( void )
{
	if (u32_switch_time > 0)
	{
		u32_switch_time--;
		return;
	}
}

/*--------------------------------------------------------------------------------*/
/*
  *Function:  Key_GPIO_Config
  * Description��  //ҳ��-��ҳʱ�䴦��
  *Input:  p_SysParamHandle, ϵͳ�������
  *Output:  //���������˵��
  *Return:  //��������ֵ��˵��
  *Others:  //����˵��
**/
void Switch_On( void )
{
	u32_switch_time = 800;
}

/*------------------------------------------ end file --------------------------------------*/



