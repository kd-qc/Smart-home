#ifndef __BSP_LED_H
#define __BSP_LED_H

/* define --------------------------------------------------------------------*/
/* Bsp define */
#define LED_SYSCTL_PERIPH_CLK		RCC_APB2Periph_GPIOC
#define LED_PORT 					GPIOC
#define LED_GPIO_PIN				GPIO_Pin_13

#define LED_ON						GPIO_ResetBits(LED_PORT, LED_GPIO_PIN)
#define LED_OFF						GPIO_SetBits(LED_PORT, LED_GPIO_PIN)

//*****************************************************************************
//
// Prototypes for the APIs.
//
//*****************************************************************************
extern void Led_GPIO_Config( void );
//*****************************************************************************


#endif /* __BSP_LED_H */


