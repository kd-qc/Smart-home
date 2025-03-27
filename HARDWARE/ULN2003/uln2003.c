#include "ULN2003/uln2003.h"

sMotorHandle gs_MotorHandle =
{
	0,
};

void Moto_Init( void )
{
	GPIO_InitTypeDef GPIO_InitStructure;

	RCC_APB2PeriphClockCmd(ULN2003_SYSCTL_PERIPH_CLK, ENABLE);

	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;

	GPIO_InitStructure.GPIO_Pin = A_PHASE_PIN;
	GPIO_Init(A_PHASE_PORT, &GPIO_InitStructure);

	GPIO_InitStructure.GPIO_Pin = B_PHASE_PIN;
	GPIO_Init(B_PHASE_PORT, &GPIO_InitStructure);

	GPIO_InitStructure.GPIO_Pin = C_PHASE_PIN;
	GPIO_Init(C_PHASE_PORT, &GPIO_InitStructure);

	GPIO_InitStructure.GPIO_Pin = D_PHASE_PIN;
	GPIO_Init(D_PHASE_PORT, &GPIO_InitStructure);

	ULN2003_ResetAllPhase( );

}

/**
  * @name		ULN2003_ResetAllPhase
  * @brief      复位A、B、C、D（相位）
  * @param[in]  void
  * @return  	void
  */
void ULN2003_ResetAllPhase ( void )
{
	A_PHASE_RESET;
	B_PHASE_RESET;
	C_PHASE_RESET;
	D_PHASE_RESET;
}

static u8 i = 0;  

/**
  * @name		Motorcw
  * @brief      电机正转
  * @param[in]  void
  * @return  	void
  */
void Motorcw( void )  
{  
  
    switch ( i++ )
	{
		case 0: //A
			A_PHASE_SET;B_PHASE_RESET;C_PHASE_RESET;D_PHASE_RESET;
			break;
		case 1: //AB
			A_PHASE_SET;B_PHASE_SET;C_PHASE_RESET;D_PHASE_RESET;
			break;
		
		case 2: //
			A_PHASE_RESET;B_PHASE_SET;C_PHASE_RESET;D_PHASE_RESET;
			break;
		case 3: //B
			A_PHASE_RESET;B_PHASE_SET;C_PHASE_SET;D_PHASE_RESET;
			break;
		case 4: //C
			A_PHASE_RESET;B_PHASE_RESET;C_PHASE_SET;D_PHASE_RESET;
			break;
		case 5: //CD
			A_PHASE_RESET;B_PHASE_RESET;C_PHASE_SET;D_PHASE_SET;
			break;
		case 6: //
			A_PHASE_RESET;B_PHASE_RESET;C_PHASE_RESET;D_PHASE_SET;
			break;
		case 7: //D
		i=0;
			A_PHASE_SET;B_PHASE_RESET;C_PHASE_RESET;D_PHASE_SET;
			break;
		default:
			break;
	}
}


void Motorccw( void )  
{  
	switch ( i-- )
	{
		case 0: //A
			i=7;
			A_PHASE_SET;B_PHASE_RESET;C_PHASE_RESET;D_PHASE_RESET;
			break;
		case 1: //AB
			A_PHASE_SET;B_PHASE_SET;C_PHASE_RESET;D_PHASE_RESET;
			break;
		
		case 2: //
			A_PHASE_RESET;B_PHASE_SET;C_PHASE_RESET;D_PHASE_RESET;
			break;
		case 3: //B
			A_PHASE_RESET;B_PHASE_SET;C_PHASE_SET;D_PHASE_RESET;
			break;
		case 4: //C
			A_PHASE_RESET;B_PHASE_RESET;C_PHASE_SET;D_PHASE_RESET;
			break;
		case 5: //CD
			A_PHASE_RESET;B_PHASE_RESET;C_PHASE_SET;D_PHASE_SET;
			break;
		case 6: //
			A_PHASE_RESET;B_PHASE_RESET;C_PHASE_RESET;D_PHASE_SET;
			break;
		case 7: //D
			A_PHASE_SET;B_PHASE_RESET;C_PHASE_RESET;D_PHASE_SET;
			break;
		default:
			break;
	}
}


void MotorStop( void )  
{  
    ULN2003_ResetAllPhase( );
}

//由于   *一个脉冲*   *输出轴*  转0.08789度（电机实转0.08789*64=5.625度），即步进角为5.625度。则转完A-B-C-D为  *8个脉冲*  ，即0.08789*8=0.70312度。若称A-B-C-D为一个周期，则j为需要的转完angle角度所需的周期数。



void Motor_PreSet(eMotorDutyCycle eM, u32 tim, u32 speed)
{
	gs_MotorHandle.eStatus = eM;
	gs_MotorHandle.u32Time = tim;
	gs_MotorHandle.u32Speed = speed;
}


void Motor_Millisecond( void )
{
	if (gs_MotorHandle.u32Time > 0)
	{
		gs_MotorHandle.u32Time--;
		if (gs_MotorHandle.u32Time == 0)
		{
			gs_MotorHandle.eStatus = Staus_None;
			MotorStop( );
		}
	}
	
	gs_MotorHandle.u32Cnt++;

	if (gs_MotorHandle.u32Cnt % gs_MotorHandle.u32Speed == 0)
	{
		switch (gs_MotorHandle.eStatus)
		{
			case Status_CW:
				Motorcw( );
				break;

			case Status_CCW:
				Motorccw( );
				break;
				
			case Staus_None:
			default:
				break;
		}
	}
	if (gs_MotorHandle.u32Cnt % 1000 == 0)
	{
		gs_MotorHandle.u32Cnt = 0;
	}
}


