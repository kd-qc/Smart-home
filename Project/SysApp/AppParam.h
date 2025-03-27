#ifndef _APP_PARAM_H
#define _APP_PARAM_H
/* include --------------------------------------*/
#include "sys.h"
#include "usart.h"
#include "timer.h"
#include "delay.h" 

#include "Key/bsp_key.h" 
#include "Relay/bsp_relay.h"	
#include "DHT11/bsp_dht11.h"
#include "SNR1806/snr1806.h"
#include "Led/led.h"
#include "ULN2003/uln2003.h"
#include "GY30/BH1750FVI.h"
#include "ADC/ADC.h"
#include "OLED/oled.h"

#include "Buzzer/bsp_buzzer.h"

#include "user_common.h"

/*!< 机智云 ----------------------- */
#include "gizwits_product.h"
#include "common.h"


/* define --------------------------------------*/
#define LCD_PAGE_EVENT_BIT	(1 << 0)
#define KEY_EVENT_BIT		(1 << 1)
#define RFID_EVENT_BIT		(1 << 2)
#define FP_EVENT_BIT		(1 << 3)
#define Gizwits_EVENT_BIT	(1 << 4)

#define RecyclableStatusBit (1 << 0)
#define KitchenStatusBit 	(1 << 1)
#define HazardousStatusBit 	(1 << 2)
#define OtherStatusBit 		(1 << 3)

#define ADMIN_PASSWORD_LEN	6
#define UNLOCK_PASSWORD_LEN	6
#define IDCARE_SN_LEN		4
#define IDCARD_NUM			9
#define EEPROM_DATA_LEN		(ADMIN_PASSWORD_LEN + UNLOCK_PASSWORD_LEN + IDCARE_SN_LEN * IDCARD_NUM + 1)

#define ADMIN_PASSWORD_EEPROM_ADDR		0
#define UNLOCK_PASSWORD_EEPROM_ADDR		(ADMIN_PASSWORD_EEPROM_ADDR + ADMIN_PASSWORD_LEN)
#define IDCARE_SN_EEPROM_ADDR			(UNLOCK_PASSWORD_EEPROM_ADDR + UNLOCK_PASSWORD_LEN)
#define IDCARE_INDEX_EEPROM_ADDR		(IDCARE_SN_EEPROM_ADDR + IDCARD_NUM * IDCARE_SN_LEN)

#define RESET_FLG_EEPROM_ADDR			255

/* 浮点转换因子，本协议采用十进制转换 */
#define FA10_0		(1.0f) 			/* 0位小数(分辨率1) 			- 10^0 = 1 		*/
#define FA10_1		(10.0f) 		/* 1位小数(分辨率0.1) 		- 10^1 = 10		*/
#define FA10_2		(100.0f) 		/* 2位小数(分辨率0.01) 		- 10^2 = 100	*/
#define FA10_3		(1000.0f) 		/* 3位小数(分辨率0.001) 		- 10^3 = 1000	*/
#define FA10_4		(10000.0f)		/* 4位小数(分辨率0.001)	- 10^4 = 1000		*/
#define FA10_5		(100000.0f)		/* 5位小数(分辨率0.001)	- 10^5 = 1000		*/
#define FA10_6		(1000000.0f)	/* 6位小数(分辨率0.001)	- 10^6 = 1000		*/


/************************* reload time ****************************/
#define GET_SENSOR_DATA_TIME	500
#define SERVER_UPDATE_TIME		1000

/************************* keys ****************************/

#define CURRENT_KEYS_TYPE			Type_SingleKey

#define KEY_NUM						2

#define KEY1_SYSCTL_PERIPH_CLK		RCC_APB2Periph_GPIOA
#define KEY1_GPIO_PORT				GPIOA
#define KEY1_GPIO_PIN				GPIO_Pin_0

#define KEY2_SYSCTL_PERIPH_CLK		RCC_APB2Periph_GPIOA
#define KEY2_GPIO_PORT				GPIOA
#define KEY2_GPIO_PIN				GPIO_Pin_1

#define GET_U16_HIGH_BYTE(u16_data)		((u16_data & 0xFF00)>>8)	
#define GET_U16_LOW_BYTE(u16_data)		(u16_data & 0x00FF)

/* typedef --------------------------------------*/

typedef enum 
{
	Page_Default = 0,
	Page_Main,
	
	Page_Admin_Login,
	Page_Admin,
	
	Page_AdminPasswordManage,
	Page_UnlockPassword,
	Page_AdminPassword,
	Page_AdminFingerprintInput,
	Page_AdminFingerprintDelete,
	Page_AdminFingerprintManage,
	Page_AdminRFIDManage,
	Page_AdminRFIDInput,
	Page_AdminRFIDDelete,

	Page_AdminWifiConfig,
	
	Page_AdminRestoreFactory,
}ePageIDType; 

typedef enum
{
	AutoMode = 0,
	ManualMode = 1,
}eModeType;

typedef struct SysParamType
{
	ePageIDType PageID;
	eModeType eMode;
	u8 u8EventReg;
	u8 u8GizwistCode;
	u8 u8KeyCode;
	u8 u8TrashStatusBits;
	u8 u8CurtainFlg;
	u16 u16Lightness;
	float fMqValue;
	bool blWarn;
	u8 status;
	
	u32 u32SensorTim;
	u32 u32LcdUpdateTim;
	u32 u32SyncDataTim;
	u32 u32CycleWarnTim;
	
	eMotorDutyCycle    eMotorStat;
	DHT11_Data_TypeDef 	*psDHT11DataHandle;
	LD3322Handle_t 		*psLdHandle;

	sKeyHandle_t 		*p_keyhandle; 
	dataPoint_t			*p_DataPoint;
}SysParam_t;

/* extern --------------------------------------*/
extern sKeyHandle_t keyhandle;
extern SysParam_t SysParamHandle;
#endif /* _APP_PARAM_H */

