#ifndef __PWM_H
#define __PWM_H	 

/********************定时器通道**************************/

#define PWM_TIMx                  		TIM3

#define PWM_TIM_APBxClock_FUN  			RCC_APB1PeriphClockCmd
#define PWM_TIM_CLK               		RCC_APB1Periph_TIM3
#define PWM_TIM_GPIO_CLK      			(RCC_APB2Periph_GPIOA | RCC_APB2Periph_GPIOB | RCC_APB2Periph_AFIO)
			
#define PWM_TIM_CH1_PORT               	GPIOA
#define PWM_TIM_CH1_PIN  				GPIO_Pin_6

#define PWM_TIM_CH2_PORT               	GPIOA
#define PWM_TIM_CH2_PIN  				GPIO_Pin_7

#define PWM_TIM_CH3_PORT               	GPIOB
#define PWM_TIM_CH3_PIN  				GPIO_Pin_0

#define PWM_TIM_CH4_PORT               	GPIOB
#define PWM_TIM_CH4_PIN  				GPIO_Pin_1

#define PWM_TIM_CH1_OCxInit         	TIM_OC1Init            	//通道初始化函数
#define PWM_TIM_CH1_OCxPreloadConfig  	TIM_OC1PreloadConfig	//通道重载配置函数

#define PWM_TIM_CH2_OCxInit         	TIM_OC2Init            	//通道初始化函数
#define PWM_TIM_CH2_OCxPreloadConfig  	TIM_OC2PreloadConfig	//通道重载配置函数

#define PWM_TIM_CH3_OCxInit         	TIM_OC3Init            	//通道初始化函数
#define PWM_TIM_CH3_OCxPreloadConfig  	TIM_OC3PreloadConfig	//通道重载配置函数

#define PWM_TIM_CH4_OCxInit         	TIM_OC4Init            	//通道初始化函数
#define PWM_TIM_CH4_OCxPreloadConfig  	TIM_OC4PreloadConfig	//通道重载配置函数


void PWM_TIMx_GPIO_Config(void);
void PWM_TIMx_GPIO_Reset_Config(void);

void PWM_TIMx_GPIO_Config(void);
void PWM_TIMx_Mode_Config(u16 arr, u16 psc);

void PWM_TIMx_Init(void);
void PWM_TIMx_Close(void);
void PWM_TIMx_Open(void);

void setCannel1(uint16_t u16_Val);		    
void setCannel2(uint16_t u16_Val);
void setCannel3(uint16_t u16_Val);		    
void setCannel4(uint16_t u16_Val);

#endif /* __PWM_H */
