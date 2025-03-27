#ifndef __ADC_H
#define __ADC_H

#include "stm32f10x.h"

/* ����ADC1��ͨ��5����ΪPA^5 ģʽ������ģ������*/
#define ADC_GPIO_RCC     RCC_APB2Periph_GPIOA
#define ADC_GPIO_PORT    GPIOA
#define ADC_GPIO_PIN     GPIO_Pin_1// | GPIO_Pin_5 | GPIO_Pin_7
#define ADC_GPIO_MODE    GPIO_Mode_AIN  

/* �������ж��йص���Ϣ */
#define ADC_IRQn         ADC1_2_IRQn
#define ADC_RCC          RCC_APB2Periph_ADC1


/* ����ADC��ʼ���ṹ��ĺ궨�� */
#define ADCx                          ADC1
#define ADCx_ContinuousConvMode       ENABLE                 		 //����ת��ģʽ
#define ADCx_DataAlign                ADC_DataAlign_Right    		 //ת������Ҷ���
#define ADCx_ExternalTrigConv         ADC_ExternalTrigConv_None      //��ʹ���ⲿ����ת���������������
#define ADCx_Mode                     ADC_Mode_Independent   		 //ֻʹ��һ��ADC������ģʽ
#define ADCx_NbrOfChannel             1                     		 //һ��ת��ͨ��
#define ADCx_ScanConvMode             ENABLE                		 //ɨ��ģʽ����ͨ��ʱʹ��

/* ͨ����Ϣ�Ͳ������� */
#define ADC_Channel                   	ADC_Channel_1
#define ADC_Potentiometer_Channel 		ADC_Channel_6
#define ADC_Pressure_Channel 			ADC_Channel_7

#define ADC_SampleTime                ADC_SampleTime_239Cycles5


/* ����MQ3 
Din */
#define MQ3_DIN_GPIO_RCC     RCC_APB2Periph_GPIOA
#define MQ3_DIN_GPIO_PORT    GPIOA
#define MQ3_DIN_GPIO_PIN     GPIO_Pin_12
#define MQ3_DIN_GPIO_MODE    GPIO_Mode_IN_FLOATING  


#define MQ3_DIN_TRIGGER    	(PAin(12) == 0)  

#define ADC_Channel_Num 	1 //ÿͨ����50��

extern vu16 AD_Value[ADC_Channel_Num];

/* �������� */
void ADC_COnfig(void);
void ADC_NVIC_Config(void);
void ADC_GPIO_Config(void);
void ADCx_Init(void);
void ADC_Sensor_Init(void);
void DMA_Configuration(void);
void Water_GetResult(u16 *p_data);
void get_mq2_value(float *pf_data);

#endif  /* __ADC_H */


