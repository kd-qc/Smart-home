#include "Led/led.h"
#include "delay.h"	   

/**
 * name: LED_Init
 * decription: led ��ʼ��
 */
void LED_Init( void )
{	
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA|RCC_APB2Periph_GPIOB|RCC_APB2Periph_GPIOC, ENABLE);//����ʱ��
	
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO, ENABLE);
	GPIO_PinRemapConfig(GPIO_Remap_SWJ_Disable, ENABLE); //�ı�ָ���ܽŵ�ӳ����ȫ���ã�JTAG+SW-DP��
	GPIO_PinRemapConfig(GPIO_Remap_SWJ_JTAGDisable,ENABLE);//�ı�ָ���ܽŵ�ӳ�䣬JTAG-DP ���� + SW-DP ʹ��
	GPIO_InitTypeDef  GPIO_InitStructure;
	
#if 1
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC, ENABLE);	//ʹ��PA�˿�ʱ��

	GPIO_InitStructure.GPIO_Pin = LED_TIP_PIN;				//LED0-->PA �˿�����
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP; 		//��©���
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_10MHz;		//IO���ٶ�Ϊ50MHz
	GPIO_Init(LED_TIP_PORT, &GPIO_InitStructure);			//�����趨������ʼ��GPIOA.4

	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);	//ʹ��PA�˿�ʱ��
	GPIO_InitStructure.GPIO_Pin = WARN_LED_PIN;				//LED0-->PA �˿�����
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP; 		//��©���
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_10MHz;		//IO���ٶ�Ϊ50MHz
	GPIO_Init(WARN_LED_PORT, &GPIO_InitStructure);			//�����趨������ʼ��GPIOA.4
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

