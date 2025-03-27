#ifndef __ULN2003_H
#define __ULN2003_H	 
#include "sys.h"

/* Define -----------------------------------------------------------*/

#define ULN2003_SYSCTL_PERIPH_CLK		(RCC_APB2Periph_GPIOB)	


// A Phase	
#define A_PHASE_PORT				GPIOB
#define A_PHASE_PIN					GPIO_Pin_11

// B Phase	
#define B_PHASE_PORT				GPIOB
#define B_PHASE_PIN					GPIO_Pin_10

// C Phase	
#define C_PHASE_PORT				GPIOB
#define C_PHASE_PIN					GPIO_Pin_1

// D Phase	
#define D_PHASE_PORT				GPIOB
#define D_PHASE_PIN					GPIO_Pin_0

	
#define A_PHASE_SET					PBout(11) = 1;			
#define B_PHASE_SET					PBout(10) = 1;
#define C_PHASE_SET					PBout(1 ) = 1;
#define D_PHASE_SET					PBout(0 ) = 1;

#define A_PHASE_RESET				PBout(11) = 0;		
#define B_PHASE_RESET				PBout(10) = 0;
#define C_PHASE_RESET				PBout(1 ) = 0;
#define D_PHASE_RESET				PBout(0 ) = 0;



/* Private typedef -----------------------------------------------------------*/

typedef enum 
{
	Staus_None = 0,
	Status_CW,
	Status_CCW,
}eMotorDutyCycle;

/**
  * @brief TIME 句柄信息结构体定义
  */
	
typedef struct
{
	u8 u8Dir;
	u32 u32Cnt;
	u32 u32Speed;
	u32 u32Time;

	eMotorDutyCycle eStatus;

}sMotorHandle;

void Moto_Init( void );
void ULN2003_ResetAllPhase ( void );
void Motorcw( void ); 
void Motorccw( void );  
void MotorStop( void );  
void Motor_PreSet(eMotorDutyCycle eM, u32 tim, u32 speed);
void Motorccw_PreSet(u8 dir, u32 angle, u32 speed);
void Motor_Millisecond( void );
void Carding( u8 flg, eMotorDutyCycle *eStat);



#endif	/* __ULN2003_H */

