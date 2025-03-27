#include "Led/led.h"
#include "delay.h"	   

/**
 * name: LED_Init
 * decription: led 初始化
 */
void LED_Init( void )
{	
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA|RCC_APB2Periph_GPIOB|RCC_APB2Periph_GPIOC, ENABLE);//开启时钟
	
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO, ENABLE);
	GPIO_PinRemapConfig(GPIO_Remap_SWJ_Disable, ENABLE); //改变指定管脚的映射完全禁用（JTAG+SW-DP）
	GPIO_PinRemapConfig(GPIO_Remap_SWJ_JTAGDisable,ENABLE);//改变指定管脚的映射，JTAG-DP 禁用 + SW-DP 使能
	GPIO_InitTypeDef  GPIO_InitStructure;
	
#if 1
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC, ENABLE);	//使能PA端口时钟

	GPIO_InitStructure.GPIO_Pin = LED_TIP_PIN;				//LED0-->PA 端口配置
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP; 		//开漏输出
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_10MHz;		//IO口速度为50MHz
	GPIO_Init(LED_TIP_PORT, &GPIO_InitStructure);			//根据设定参数初始化GPIOA.4

	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);	//使能PA端口时钟
	GPIO_InitStructure.GPIO_Pin = WARN_LED_PIN;				//LED0-->PA 端口配置
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP; 		//开漏输出
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_10MHz;		//IO口速度为50MHz
	GPIO_Init(WARN_LED_PORT, &GPIO_InitStructure);			//根据设定参数初始化GPIOA.4
#endif
	LED_TIP_ON;
	WARN_LED_ON;
	
}


/**
  * @brief  Toggles the specified GPIO pin
  * @param  GPIOx: where x can be (A..G depending on device used) to select the GPIO peripheral 
  * @param  GPIO_Pin: Specifies the pins to be toggled.
  * @retval None
  */
void GPIO_TogglePin(GPIO_TypeDef* GPIOx, uint16_t GPIO_Pin)
{
  /* Check the parameters */
  assert_param(IS_GPIO_PIN(GPIO_Pin));

  GPIOx->ODR ^= GPIO_Pin;
}

