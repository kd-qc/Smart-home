#include "stm32f10x.h"
#include "pwm.h"

 /**
  * @brief  ����COLOR_TIMx�������PWMʱ�õ���I/O
  * @param  ��
  * @retval ��
  */
void PWM_TIMx_GPIO_Config(void) 
{

  	/******************************** ���� pwm ͨ������ ********************************/

  	GPIO_InitTypeDef GPIO_InitStructure;

  	/* GPIO clock enable */
	RCC_APB2PeriphClockCmd(PWM_TIM_GPIO_CLK, ENABLE); 

	//!< CH1 Config
	GPIO_InitStructure.GPIO_Pin = PWM_TIM_CH1_PIN;		
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;		    // �����������
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(PWM_TIM_CH1_PORT, &GPIO_InitStructure);

	//!< CH2 Config
	GPIO_InitStructure.GPIO_Pin = PWM_TIM_CH2_PIN;		
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;		    // �����������
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(PWM_TIM_CH2_PORT, &GPIO_InitStructure);

	//!< CH3 Config
	GPIO_InitStructure.GPIO_Pin = PWM_TIM_CH3_PIN;		
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;		    // �����������
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(PWM_TIM_CH3_PORT, &GPIO_InitStructure);

	//!< CH4 Config
	GPIO_InitStructure.GPIO_Pin = PWM_TIM_CH4_PIN;		
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;		    // �����������
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(PWM_TIM_CH4_PORT, &GPIO_InitStructure);
	
}

 /**
  * @brief  ����COLOR_TIMx�������PWMʱ�õ���I/O
  * @param  ��
  * @retval ��
  */
void PWM_TIMx_GPIO_Reset_Config(void) 
{
  	//GPIO_InitTypeDef GPIO_InitStructure;

  	/* GPIO clock enable */
	//RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE); 
	
  	/* ����LED���õ������� */
	//GPIO_InitStructure.GPIO_Pin =  PWM_TIM_CH1_PIN | PWM_TIM_CH2_PIN | PWM_TIM_CH3_PIN | PWM_TIM_CH4_PIN;	
	//GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;		    // �����������
	//GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;

	//GPIO_Init(PWM_TIM_CH1_PORT, &GPIO_InitStructure);
	
	//!< ����ͨ����ƽ ��λ
	GPIO_ResetBits(PWM_TIM_CH1_PORT, PWM_TIM_CH1_PIN);
	GPIO_ResetBits(PWM_TIM_CH2_PORT, PWM_TIM_CH2_PIN);
	GPIO_ResetBits(PWM_TIM_CH3_PORT, PWM_TIM_CH3_PIN);
	GPIO_ResetBits(PWM_TIM_CH4_PORT, PWM_TIM_CH4_PIN);
}

/**
  * @brief  ����COLOR_TIMx�����PWM�źŵ�ģʽ�������ڡ�����
  * @param  ��
  * @retval ��
  */
void PWM_TIMx_Mode_Config(u16 arr, u16 psc)
{
	TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;
	TIM_OCInitTypeDef  TIM_OCInitStructure;																				
	
	/* ����TIM CLK ʱ�� */
	PWM_TIM_APBxClock_FUN(PWM_TIM_CLK, ENABLE);		//ʹ��TIMxʱ��

	/* ������ʱ������ */		 
	TIM_TimeBaseStructure.TIM_Period = arr;       					//����ʱ����0������255����Ϊ256�Σ�Ϊһ����ʱ����
	TIM_TimeBaseStructure.TIM_Prescaler = psc;	    				//����Ԥ��Ƶ
	TIM_TimeBaseStructure.TIM_ClockDivision = TIM_CKD_DIV1 ;		//����ʱ�ӷ�Ƶϵ��������Ƶ(�����ò���)
	TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;  	//���ϼ���ģʽ
	TIM_TimeBaseInit(PWM_TIMx, &TIM_TimeBaseStructure);

  	/* PWMģʽ���� */
	TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM2;	    		//����ΪPWMģʽ2
	TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable;	//ʹ�����
	TIM_OCInitStructure.TIM_Pulse = 0;								//���ó�ʼPWM������Ϊ0	
	TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_Low;  	  	//����ʱ������ֵС��CCR_ValʱΪ�͵�ƽ
	
	TIM_OCInitStructure.TIM_OCNPolarity = TIM_OCNPolarity_High;
	TIM_OCInitStructure.TIM_OCIdleState = TIM_OCIdleState_Set;
	TIM_OCInitStructure.TIM_OCNIdleState = TIM_OCIdleState_Reset;


	//ʹ��ͨ����Ԥװ��
	PWM_TIM_CH1_OCxInit(PWM_TIMx, &TIM_OCInitStructure);	 							
  	PWM_TIM_CH1_OCxPreloadConfig(PWM_TIMx, TIM_OCPreload_Enable);						
	//ʹ��ͨ����Ԥװ��
	PWM_TIM_CH2_OCxInit(PWM_TIMx, &TIM_OCInitStructure);	 							
  	PWM_TIM_CH2_OCxPreloadConfig(PWM_TIMx, TIM_OCPreload_Enable);	
  	//ʹ��ͨ����Ԥװ��
	PWM_TIM_CH3_OCxInit(PWM_TIMx, &TIM_OCInitStructure);	 							
  	PWM_TIM_CH3_OCxPreloadConfig(PWM_TIMx, TIM_OCPreload_Enable);	
  	//ʹ��ͨ����Ԥװ��
	PWM_TIM_CH4_OCxInit(PWM_TIMx, &TIM_OCInitStructure);	 							
  	PWM_TIM_CH4_OCxPreloadConfig(PWM_TIMx, TIM_OCPreload_Enable);	
  	
	TIM_ARRPreloadConfig(PWM_TIMx, ENABLE);		//ʹ��COLOR_TIMx���ؼĴ���ARR

  	/* COLOR_TIMx enable counter */
	TIM_Cmd(PWM_TIMx, ENABLE); 	//ʹ�ܶ�ʱ��		
}

/**
  * @brief  PWM_TIMx_Init
  *         ����PWMģʽ��GPIO
  * @param  ��
  * @retval ��
  */
void PWM_TIMx_Init(void)
{
	PWM_TIMx_GPIO_Config();
	PWM_TIMx_Mode_Config(19999, 71);	// 50hz - 20ms 
}

//ֹͣpwm���
void PWM_TIMx_Close(void)
{
	TIM_Cmd(PWM_TIMx, DISABLE);          			//ʧ�ܶ�ʱ��						
	PWM_TIM_APBxClock_FUN(PWM_TIM_CLK, DISABLE); 	//ʧ�ܶ�ʱ��ʱ��
	PWM_TIMx_GPIO_Reset_Config();
}


 //����pwm���
 void PWM_TIMx_Open(void)
 {
	 PWM_TIMx_Init();
 }

/**
* @brief  ����RGB LED����ɫ
* @param  u8_lightness:Ҫ����LED��ʾ����ɫֵ��ʽRGB888
* @retval ��
*/
void setCannel1(uint16_t u16_Val)
{
	//������ɫֵ�޸Ķ�ʱ���ıȽϼĴ���ֵ
	PWM_TIMx->CCR1 = (uint16_t)u16_Val;
}
 /**
  * @brief  ����RGB LED����ɫ
	* @param  u8_lightness:Ҫ����LED��ʾ����ɫֵ��ʽRGB888
  * @retval ��
  */
void setCannel2(uint16_t u16_Val)
{
	//������ɫֵ�޸Ķ�ʱ���ıȽϼĴ���ֵ
	PWM_TIMx->CCR2 = (uint16_t)u16_Val;
}

/**
* @brief  ����RGB LED����ɫ
* @param  u8_lightness:Ҫ����LED��ʾ����ɫֵ��ʽRGB888
* @retval ��
*/
void setCannel3(uint16_t u16_Val)
{
	//������ɫֵ�޸Ķ�ʱ���ıȽϼĴ���ֵ
	PWM_TIMx->CCR3 = (uint16_t)u16_Val;
}
 /**
  * @brief  ����RGB LED����ɫ
	* @param  u8_lightness:Ҫ����LED��ʾ����ɫֵ��ʽRGB888
  * @retval ��
  */
void setCannel4(uint16_t u16_Val)
{
	//������ɫֵ�޸Ķ�ʱ���ıȽϼĴ���ֵ
	PWM_TIMx->CCR4 = (uint16_t)u16_Val;
}


