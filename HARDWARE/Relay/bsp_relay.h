#ifndef __BSP_SWITCH_H
#define __BSP_SWITCH_H
#include "sys.h"
/* define --------------------------------------------------------------------*/
/* Bsp define */
#define LIGHT_SWITCH_SYSCTL_PERIPH_CLK		RCC_APB2Periph_GPIOB
#define LIGHT_SWITCH_PORT 					GPIOB
#define LIGHT_SWITCH_GPIO_PIN				(GPIO_Pin_6)     

#define AIRCONDI_SWITCH_SYSCTL_PERIPH_CLK		RCC_APB2Periph_GPIOB
#define AIRCONDI_SWITCH_PORT 					GPIOB
#define AIRCONDI_SWITCH_GPIO_PIN				(GPIO_Pin_5)  

#define LIGHT_SWITCH_ON						(PBout(6) = 1)
#define LIGHT_SWITCH_OFF					(PBout(6) = 0)
#define LIGHT_SWUTCH_STAT					(PBin(6) == 1)
#define AIRCONDI_SWITCH_ON					(PBout(5) = 1)
#define AIRCONDI_SWITCH_OFF					(PBout(5) = 0)
#define AIRCONDI_SWUTCH_STAT				(PBin(5) == 1)

//*****************************************************************************
//
// Prototypes for the APIs.
//
//*****************************************************************************
extern void Switch_GPIO_Config( void );
extern void Switch_1ms_tick( void );
extern void Switch_On( void );
//*****************************************************************************


#endif /* __BSP_SWITCH_H */


