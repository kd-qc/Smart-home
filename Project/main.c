
/* Includes ------------------------------------------------------------------*/
#include "stm32f10x.h"
#include "SysApp/AppSys.h"

/**
 * name: RCC_Configuration
 * brief: 系统时钟树配置
 */
void RCC_Configuration(void)
{
#if 1
	ErrorStatus HSEStartUpStatus;
	/* RCC 系统复位 */
	RCC_DeInit();
	/* 开启 HSE */
	RCC_HSEConfig(RCC_HSE_ON);
	/* 等待 HSE 准备好 */
	HSEStartUpStatus = RCC_WaitForHSEStartUp();
	if (HSEStartUpStatus == SUCCESS)
	{
		/* Enable Prefetch Buffer */
		FLASH_PrefetchBufferCmd(FLASH_PrefetchBuffer_Enable);
		/* Set 2 Latency cycles */
		FLASH_SetLatency(FLASH_Latency_2);
		/* PLLCLK = 8MHz * 9 = 72 MHz */
		RCC_PLLConfig(RCC_PLLSource_HSE_Div1, RCC_PLLMul_9);
		/* AHB clock = SYSCLK = 72 MHz */
		RCC_HCLKConfig(RCC_SYSCLK_Div1);
		/* APB2 clock = HCLK   = 72 MHz */
		RCC_PCLK2Config(RCC_HCLK_Div1);
		/* APB1 clock = HCLK/2 = 36 MHz */
		RCC_PCLK1Config(RCC_HCLK_Div2);
		/* Enable PLL */
		RCC_PLLCmd(ENABLE);
		/* Wait till PLL is ready */
		while(RCC_GetFlagStatus(RCC_FLAG_PLLRDY) == RESET);
		/* elect PLL as system clock source */
		RCC_SYSCLKConfig(RCC_SYSCLKSource_PLLCLK);
	}
#else	
	SystemInit();
#endif
}


/**
  *@brief   NVIC_Configuration实现NVIC配置
  *
  */
static void NVIC_Configuration(void)
{
    NVIC_PriorityGroupConfig(NVIC_PriorityGroup_1); 
}

/******************************************************************************************************************/
/* *********************	Name: Smart Lock System ***************************************************************/
/************************	MCU: STM32F103C8T6  	***************************************************************/
/******************************************************************************************************************/
/**
 * name: main
 * brief: 主函数
 */
int main ( void )
{
	/* 系统时钟树配置 */
	RCC_Configuration();
	/* 中断系统配置 */
	NVIC_Configuration();
	/* 初始化硬件延时， 使用滴答定时器完成 */
	delay_init();
	/* 板级初始化 */
	app_BspInit( &SysParamHandle );
	/* 主循环 */
	Key2_long_press_down_handle();
	while ( 1 )
	{  
		app_Process( &SysParamHandle );
	}
}

