#include "ADC.h"


vu16 AD_Value[ADC_Channel_Num];

void ADC_Sensor_Init(void)
{
	ADC_GPIO_Config();
	ADC_NVIC_Config();
	ADC_COnfig();
	//DMA_Configuration();
}



void ADC_GPIO_Config(void)
{
	GPIO_InitTypeDef   GPIO_InitStruct;
	RCC_APB2PeriphClockCmd(ADC_GPIO_RCC,  ENABLE);
	
	GPIO_InitStruct.GPIO_Pin = ADC_GPIO_PIN ;
	GPIO_InitStruct.GPIO_Mode = ADC_GPIO_MODE ;
	
	GPIO_Init(ADC_GPIO_PORT , &GPIO_InitStruct);
}

void ADC_NVIC_Config(void)
{

	NVIC_InitTypeDef NVIC_InitStruct ;
	
	/* �����ж����ȼ�����(������ռ���ȼ��������ȼ��ķ���)���ں�����misc.c */
	//NVIC_PriorityGroupConfig(NVIC_PriorityGroup_1) ;
	
	/* ���ó�ʼ���ṹ�� ��misc.h�� */
	/* �����ж�Դ ��stm32f10x.h�� */
	NVIC_InitStruct.NVIC_IRQChannel = ADC_IRQn ;
	/* ������ռ���ȼ� */
	NVIC_InitStruct.NVIC_IRQChannelPreemptionPriority = 1 ;
	/* ���������ȼ� */
	NVIC_InitStruct.NVIC_IRQChannelSubPriority = 1 ;
	/* ʹ���ж�ͨ�� */
	NVIC_InitStruct.NVIC_IRQChannelCmd = ENABLE ;
	/* ���ó�ʼ������ */
	NVIC_Init(&NVIC_InitStruct) ;
}

void ADC_COnfig(void)
{
	ADC_InitTypeDef  ADC_InitStruct;
	RCC_APB2PeriphClockCmd(ADC_RCC,  ENABLE);
	
	/* ���ó�ʼ���ṹ�壬�����ͷ�ļ� */
	ADC_InitStruct.ADC_ContinuousConvMode = ADCx_ContinuousConvMode  ;
	ADC_InitStruct.ADC_DataAlign = ADCx_DataAlign ;
	ADC_InitStruct.ADC_ExternalTrigConv = ADCx_ExternalTrigConv ;
	ADC_InitStruct.ADC_Mode = ADCx_Mode ;
	ADC_InitStruct.ADC_NbrOfChannel = ADCx_NbrOfChannel ;
	ADC_InitStruct.ADC_ScanConvMode = ADCx_ScanConvMode ;
	
	ADC_Init(ADCx, &ADC_InitStruct);
	
	/* ����ADCʱ��Ϊ8��Ƶ����9M */
	RCC_ADCCLKConfig(RCC_PCLK2_Div8);
	/* ����ADCͨ��ת��˳���ʱ�� */
	ADC_RegularChannelConfig(ADCx, ADC_Channel, 1, ADC_SampleTime );
	/* ����Ϊת������������ж� ���ж��ж�ȡ��Ϣ */
	ADC_ITConfig(ADCx, ADC_IT_EOC,ENABLE);
	/* ����ADC������ת�� */
	ADC_Cmd(ADCx, ENABLE );
	/* ����ADCУ׼ */
	ADC_ResetCalibration(ADCx);
	/* �ȴ���ʼ����� */
	while(ADC_GetResetCalibrationStatus( ADCx))
	/* ��ʼУ׼ */
	ADC_StartCalibration(ADCx);
	/* �ȴ�У׼��� */
	while (ADC_GetCalibrationStatus(ADCx));
	/* �������ADCת�� */
	ADC_SoftwareStartConvCmd(ADCx, ENABLE);
	
}


void DMA_Configuration(void)
{
	DMA_InitTypeDef DMA_InitStructure;
	RCC_AHBPeriphClockCmd(RCC_AHBPeriph_DMA1,  ENABLE);
	DMA_DeInit(DMA1_Channel1); //��DMA��ͨ��1�Ĵ�������Ϊȱʡֵ
	DMA_InitStructure.DMA_PeripheralBaseAddr = (u32)&ADCx->DR; //DMA����ADC����ַ
	DMA_InitStructure.DMA_MemoryBaseAddr = (u32)&AD_Value; //DMA�ڴ����ַ
	DMA_InitStructure.DMA_DIR = DMA_DIR_PeripheralSRC; //�ڴ���Ϊ���ݴ����Ŀ�ĵ�
	DMA_InitStructure.DMA_BufferSize = ADC_Channel_Num; //DMAͨ����DMA����Ĵ�С
	DMA_InitStructure.DMA_PeripheralInc = DMA_PeripheralInc_Disable; //�����ַ�Ĵ�������
	DMA_InitStructure.DMA_MemoryInc = DMA_MemoryInc_Enable; //�ڴ��ַ�Ĵ�������
	DMA_InitStructure.DMA_PeripheralDataSize = DMA_PeripheralDataSize_HalfWord; //���ݿ��Ϊ16λ
	DMA_InitStructure.DMA_MemoryDataSize = DMA_MemoryDataSize_HalfWord; //���ݿ��Ϊ16λ
	DMA_InitStructure.DMA_Mode = DMA_Mode_Circular; //������ѭ������ģʽ
	DMA_InitStructure.DMA_Priority = DMA_Priority_High; //DMAͨ�� xӵ�и����ȼ�
	DMA_InitStructure.DMA_M2M = DMA_M2M_Disable; //DMAͨ��xû������Ϊ�ڴ浽�ڴ洫��
	DMA_Init(DMA1_Channel1, &DMA_InitStructure); //����DMA_InitStruct��ָ���Ĳ�����ʼ��DMA��ͨ��
	DMA_Cmd(DMA1_Channel1, ENABLE); //����DMAͨ��

}


uint16_t resurt;
void ADC1_2_IRQHandler(void)
{
    /* �жϲ����ж����� */
	while(ADC_GetITStatus(ADCx, ADC_IT_EOC) == SET)
		resurt=ADC_GetConversionValue(ADCx);
	/* ����жϱ�־ */
	ADC_ClearITPendingBit(ADCx, ADC_IT_EOC);
}


void Water_GetResult(u16 *p_data)
{
	*p_data = resurt; // -1.08;
}

void get_mq2_value(float *pf_data)
{
	*pf_data = ((float)resurt*(5.0/4096.0))*0.36; // -1.08;
}


