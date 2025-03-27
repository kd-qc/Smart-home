#include "stm32f10x.h"
#include "pwm.h"

 /**
  * @brief  配置COLOR_TIMx复用输出PWM时用到的I/O
  * @param  无
  * @retval 无
  */
void PWM_TIMx_GPIO_Config(void) 
{

  	/******************************** 配置 pwm 通道引脚 ********************************/

  	GPIO_InitTypeDef GPIO_InitStructure;

  	/* GPIO clock enable */
	RCC_APB2PeriphClockCmd(PWM_TIM_GPIO_CLK, ENABLE); 

	//!< CH1 Config
	GPIO_InitStructure.GPIO_Pin = PWM_TIM_CH1_PIN;		
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;		    // 复用推挽输出
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(PWM_TIM_CH1_PORT, &GPIO_InitStructure);

	//!< CH2 Config
	GPIO_InitStructure.GPIO_Pin = PWM_TIM_CH2_PIN;		
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;		    // 复用推挽输出
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(PWM_TIM_CH2_PORT, &GPIO_InitStructure);

	//!< CH3 Config
	GPIO_InitStructure.GPIO_Pin = PWM_TIM_CH3_PIN;		
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;		    // 复用推挽输出
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(PWM_TIM_CH3_PORT, &GPIO_InitStructure);

	//!< CH4 Config
	GPIO_InitStructure.GPIO_Pin = PWM_TIM_CH4_PIN;		
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;		    // 复用推挽输出
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(PWM_TIM_CH4_PORT, &GPIO_InitStructure);
	
}

 /**
  * @brief  配置COLOR_TIMx复用输出PWM时用到的I/O
  * @param  无
  * @retval 无
  */
void PWM_TIMx_GPIO_Reset_Config(void) 
{
  	//GPIO_InitTypeDef GPIO_InitStructure;

  	/* GPIO clock enable */
	//RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE); 
	
  	/* 配置LED灯用到的引脚 */
	//GPIO_InitStructure.GPIO_Pin =  PWM_TIM_CH1_PIN | PWM_TIM_CH2_PIN | PWM_TIM_CH3_PIN | PWM_TIM_CH4_PIN;	
	//GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;		    // 复用推挽输出
	//GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;

	//GPIO_Init(PWM_TIM_CH1_PORT, &GPIO_InitStructure);
	
	//!< 所有通道电平 复位
	GPIO_ResetBits(PWM_TIM_CH1_PORT, PWM_TIM_CH1_PIN);
	GPIO_ResetBits(PWM_TIM_CH2_PORT, PWM_TIM_CH2_PIN);
	GPIO_ResetBits(PWM_TIM_CH3_PORT, PWM_TIM_CH3_PIN);
	GPIO_ResetBits(PWM_TIM_CH4_PORT, PWM_TIM_CH4_PIN);
}

/**
  * @brief  配置COLOR_TIMx输出的PWM信号的模式，如周期、极性
  * @param  无
  * @retval 无
  */
void PWM_TIMx_Mode_Config(u16 arr, u16 psc)
{
	TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;
	TIM_OCInitTypeDef  TIM_OCInitStructure;																				
	
	/* 设置TIM CLK 时钟 */
	PWM_TIM_APBxClock_FUN(PWM_TIM_CLK, ENABLE);		//使能TIMx时钟

	/* 基本定时器配置 */		 
	TIM_TimeBaseStructure.TIM_Period = arr;       					//当定时器从0计数到255，即为256次，为一个定时周期
	TIM_TimeBaseStructure.TIM_Prescaler = psc;	    				//设置预分频
	TIM_TimeBaseStructure.TIM_ClockDivision = TIM_CKD_DIV1 ;		//设置时钟分频系数：不分频(这里用不到)
	TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;  	//向上计数模式
	TIM_TimeBaseInit(PWM_TIMx, &TIM_TimeBaseStructure);

  	/* PWM模式配置 */
	TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM2;	    		//配置为PWM模式2
	TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable;	//使能输出
	TIM_OCInitStructure.TIM_Pulse = 0;								//设置初始PWM脉冲宽度为0	
	TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_Low;  	  	//当定时器计数值小于CCR_Val时为低电平
	
	TIM_OCInitStructure.TIM_OCNPolarity = TIM_OCNPolarity_High;
	TIM_OCInitStructure.TIM_OCIdleState = TIM_OCIdleState_Set;
	TIM_OCInitStructure.TIM_OCNIdleState = TIM_OCIdleState_Reset;


	//使能通道和预装载
	PWM_TIM_CH1_OCxInit(PWM_TIMx, &TIM_OCInitStructure);	 							
  	PWM_TIM_CH1_OCxPreloadConfig(PWM_TIMx, TIM_OCPreload_Enable);						
	//使能通道和预装载
	PWM_TIM_CH2_OCxInit(PWM_TIMx, &TIM_OCInitStructure);	 							
  	PWM_TIM_CH2_OCxPreloadConfig(PWM_TIMx, TIM_OCPreload_Enable);	
  	//使能通道和预装载
	PWM_TIM_CH3_OCxInit(PWM_TIMx, &TIM_OCInitStructure);	 							
  	PWM_TIM_CH3_OCxPreloadConfig(PWM_TIMx, TIM_OCPreload_Enable);	
  	//使能通道和预装载
	PWM_TIM_CH4_OCxInit(PWM_TIMx, &TIM_OCInitStructure);	 							
  	PWM_TIM_CH4_OCxPreloadConfig(PWM_TIMx, TIM_OCPreload_Enable);	
  	
	TIM_ARRPreloadConfig(PWM_TIMx, ENABLE);		//使能COLOR_TIMx重载寄存器ARR

  	/* COLOR_TIMx enable counter */
	TIM_Cmd(PWM_TIMx, ENABLE); 	//使能定时器		
}

/**
  * @brief  PWM_TIMx_Init
  *         配置PWM模式和GPIO
  * @param  无
  * @retval 无
  */
void PWM_TIMx_Init(void)
{
	PWM_TIMx_GPIO_Config();
	PWM_TIMx_Mode_Config(19999, 71);	// 50hz - 20ms 
}

//停止pwm输出
void PWM_TIMx_Close(void)
{
	TIM_Cmd(PWM_TIMx, DISABLE);          			//失能定时器						
	PWM_TIM_APBxClock_FUN(PWM_TIM_CLK, DISABLE); 	//失能定时器时钟
	PWM_TIMx_GPIO_Reset_Config();
}


 //开启pwm输出
 void PWM_TIMx_Open(void)
 {
	 PWM_TIMx_Init();
 }

/**
* @brief  设置RGB LED的颜色
* @param  u8_lightness:要设置LED显示的颜色值格式RGB888
* @retval 无
*/
void setCannel1(uint16_t u16_Val)
{
	//根据颜色值修改定时器的比较寄存器值
	PWM_TIMx->CCR1 = (uint16_t)u16_Val;
}
 /**
  * @brief  设置RGB LED的颜色
	* @param  u8_lightness:要设置LED显示的颜色值格式RGB888
  * @retval 无
  */
void setCannel2(uint16_t u16_Val)
{
	//根据颜色值修改定时器的比较寄存器值
	PWM_TIMx->CCR2 = (uint16_t)u16_Val;
}

/**
* @brief  设置RGB LED的颜色
* @param  u8_lightness:要设置LED显示的颜色值格式RGB888
* @retval 无
*/
void setCannel3(uint16_t u16_Val)
{
	//根据颜色值修改定时器的比较寄存器值
	PWM_TIMx->CCR3 = (uint16_t)u16_Val;
}
 /**
  * @brief  设置RGB LED的颜色
	* @param  u8_lightness:要设置LED显示的颜色值格式RGB888
  * @retval 无
  */
void setCannel4(uint16_t u16_Val)
{
	//根据颜色值修改定时器的比较寄存器值
	PWM_TIMx->CCR4 = (uint16_t)u16_Val;
}


