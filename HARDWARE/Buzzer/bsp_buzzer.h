#ifndef __BUZZER_H
#define __BUZZER_H

#include "sys.h"

#define BUZZER_RCC	RCC_APB2Periph_GPIOB
#define BUZZER_PORT	GPIOB
#define BUZZER_PIN	GPIO_Pin_3

#define BUZZER_MAP			(PBout(3))
#define BUZZER_ON			(BUZZER_MAP = 1)	// 位带
#define BUZZER_OFF			(BUZZER_MAP = 0)	// 位带
#define BUZZER_TOGGLE		(BUZZER_MAP = !BUZZER_MAP)	// 位带
#define BUZZER_STATUS		(BUZZER_MAP == 1)	// 位带

extern void Buzzer_Millisecond_Tick( void );
extern void Buzzer_Init( void );
extern void Buzzer_ShortBeep( void );
extern void Buzzer_LongBeep( void );
extern void Buzzer_WarnOn( void );
extern void Buzzer_WarnOff( void );

#endif	/* __BUZZER_H */



