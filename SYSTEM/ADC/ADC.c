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
	
	/* 配置中断优先级分组(设置抢占优先级和子优先级的分配)，在函数在misc.c */
	//NVIC_PriorityGroupConfig(NVIC_PriorityGroup_1) ;
	
	/* 配置初始化结构体 在misc.h中 */
	/* 配置中断源 在stm32f10x.h中 */
	NVIC_InitStruct.NVIC_IRQChannel = ADC_IRQn ;
	/* 配置抢占优先级 */
	NVIC_InitStruct.NVIC_IRQChannelPreemptionPriority = 1 ;
	/* 配置子优先级 */
	NVIC_InitStruct.NVIC_IRQChannelSubPriority = 1 ;
	/* 使能中断通道 */
	NVIC_InitStruct.NVIC_IRQChannelCmd = ENABLE ;
	/* 调用初始化函数 */
	NVIC_Init(&NVIC_InitStruct) ;
}

void ADC_COnfig(void)
{
	ADC_InitTypeDef  ADC_InitStruct;
	RCC_APB2PeriphClockCmd(ADC_RCC,  ENABLE);
	
	/* 配置初始化结构体，详情见头文件 */
	ADC_InitStruct.ADC_ContinuousConvMode = ADCx_ContinuousConvMode  ;
	ADC_InitStruct.ADC_DataAlign = ADCx_DataAlign ;
	ADC_InitStruct.ADC_ExternalTrigConv = ADCx_ExternalTrigConv ;
	ADC_InitStruct.ADC_Mode = ADCx_Mode ;
	ADC_InitStruct.ADC_NbrOfChannel = ADCx_NbrOfChannel ;
	ADC_InitStruct.ADC_ScanConvMode = ADCx_ScanConvMode ;
	
	ADC_Init(ADCx, &ADC_InitStruct);
	
	/* 配置ADC时钟为8分频，即9M */
	RCC_ADCCLKConfig(RCC_PCLK2_Div8);
	/* 配置ADC通道转换顺序和时间 */
	ADC_RegularChannelConfig(ADCx, ADC_Channel, 1, ADC_SampleTime );
	/* 配置为转换结束后产生中断 在中断中读取信息 */
	ADC_ITConfig(ADCx, ADC_IT_EOC,ENABLE);
	/* 开启ADC，进行转换 */
	ADC_Cmd(ADCx, ENABLE );
	/* 重置ADC校准 */
	ADC_ResetCalibration(ADCx);
	/* 等待初始化完成 */
	while(ADC_GetResetCalibrationStatus( ADCx))
	/* 开始校准 */
	ADC_StartCalibration(ADCx);
	/* 等待校准完成 */
	while (ADC_GetCalibrationStatus(ADCx));
	/* 软件触发ADC转换 */
	ADC_SoftwareStartConvCmd(ADCx, ENABLE);
	
}


void DMA_Configuration(void)
{
	DMA_InitTypeDef DMA_InitStructure;
	RCC_AHBPeriphClockCmd(RCC_AHBPeriph_DMA1,  ENABLE);
	DMA_DeInit(DMA1_Channel1); //将DMA的通道1寄存器重设为缺省值
	DMA_InitStructure.DMA_PeripheralBaseAddr = (u32)&ADCx->DR; //DMA外设ADC基地址
	DMA_InitStructure.DMA_MemoryBaseAddr = (u32)&AD_Value; //DMA内存基地址
	DMA_InitStructure.DMA_DIR = DMA_DIR_PeripheralSRC; //内存作为数据传输的目的地
	DMA_InitStructure.DMA_BufferSize = ADC_Channel_Num; //DMA通道的DMA缓存的大小
	DMA_InitStructure.DMA_PeripheralInc = DMA_PeripheralInc_Disable; //外设地址寄存器不变
	DMA_InitStructure.DMA_MemoryInc = DMA_MemoryInc_Enable; //内存地址寄存器递增
	DMA_InitStructure.DMA_PeripheralDataSize = DMA_PeripheralDataSize_HalfWord; //数据宽度为16位
	DMA_InitStructure.DMA_MemoryDataSize = DMA_MemoryDataSize_HalfWord; //数据宽度为16位
	DMA_InitStructure.DMA_Mode = DMA_Mode_Circular; //工作在循环缓存模式
	DMA_InitStructure.DMA_Priority = DMA_Priority_High; //DMA通道 x拥有高优先级
	DMA_InitStructure.DMA_M2M = DMA_M2M_Disable; //DMA通道x没有设置为内存到内存传输
	DMA_Init(DMA1_Channel1, &DMA_InitStructure); //根据DMA_InitStruct中指定的参数初始化DMA的通道
	DMA_Cmd(DMA1_Channel1, ENABLE); //启动DMA通道

}


uint16_t resurt;
void ADC1_2_IRQHandler(void)
{
    /* 判断产生中断请求 */
	while(ADC_GetITStatus(ADCx, ADC_IT_EOC) == SET)
		resurt=ADC_GetConversionValue(ADCx);
	/* 清除中断标志 */
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


