#ifndef __ADC_H
#define __ADC_H

#include "stm32f10x.h"

/* 采用ADC1的通道5引脚为PA^5 模式必须是模拟输入*/
#define ADC_GPIO_RCC     RCC_APB2Periph_GPIOA
#define ADC_GPIO_PORT    GPIOA
#define ADC_GPIO_PIN     GPIO_Pin_1// | GPIO_Pin_5 | GPIO_Pin_7
#define ADC_GPIO_MODE    GPIO_Mode_AIN  

/* 配置与中断有关的信息 */
#define ADC_IRQn         ADC1_2_IRQn
#define ADC_RCC          RCC_APB2Periph_ADC1


/* 配置ADC初始化结构体的宏定义 */
#define ADCx                          ADC1
#define ADCx_ContinuousConvMode       ENABLE                 		 //连续转换模式
#define ADCx_DataAlign                ADC_DataAlign_Right    		 //转换结果右对齐
#define ADCx_ExternalTrigConv         ADC_ExternalTrigConv_None      //不使用外部触发转换，采用软件触发
#define ADCx_Mode                     ADC_Mode_Independent   		 //只使用一个ADC，独立模式
#define ADCx_NbrOfChannel             1                     		 //一个转换通道
#define ADCx_ScanConvMode             ENABLE                		 //扫描模式，多通道时使用

/* 通道信息和采样周期 */
#define ADC_Channel                   	ADC_Channel_1
#define ADC_Potentiometer_Channel 		ADC_Channel_6
#define ADC_Pressure_Channel 			ADC_Channel_7

#define ADC_SampleTime                ADC_SampleTime_239Cycles5


/* 采用MQ3 
Din */
#define MQ3_DIN_GPIO_RCC     RCC_APB2Periph_GPIOA
#define MQ3_DIN_GPIO_PORT    GPIOA
#define MQ3_DIN_GPIO_PIN     GPIO_Pin_12
#define MQ3_DIN_GPIO_MODE    GPIO_Mode_IN_FLOATING  


#define MQ3_DIN_TRIGGER    	(PAin(12) == 0)  

#define ADC_Channel_Num 	1 //每通道采50次

extern vu16 AD_Value[ADC_Channel_Num];

/* 函数声明 */
void ADC_COnfig(void);
void ADC_NVIC_Config(void);
void ADC_GPIO_Config(void);
void ADCx_Init(void);
void ADC_Sensor_Init(void);
void DMA_Configuration(void);
void Water_GetResult(u16 *p_data);
void get_mq2_value(float *pf_data);

#endif  /* __ADC_H */


