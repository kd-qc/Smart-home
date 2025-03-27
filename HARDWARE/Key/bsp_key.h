#ifndef __BSP_KEY_H
#define __BSP_KEY_H

/* define --------------------------------------------------------------------*/


/* 按键寄存器 key register 位定义 */
#define NO_KEY                              0x00000000	/* 初始 		*/
#define KEY_DOWN                            0x10000000	/* 31bit 	*/
#define KEY_UP                              0x20000000	/* 30bit 	*/
#define KEY_LIAN                            0x40000000	/* 29bit 	*/
#define KEY_LONG                            0x80000000	/* 28bit 	*/
#define KEY_LONG_UP                      	0x01000000	/* 27bit 	*/
/* [0 : 26] -- key stat (1-press, 0-non press) 预留 */

#define KEY_SCAN_TIME			30		/* Key cycle scan time */
#define KEY_SOUND_TIME			200		/* Key cycle scan time */

#define PRESS_LONG_TIME			1500	/* Judged long press time */

/* 16bit set & reset */
#define G_SET_BIT(u32_register, bits)		(u32_register |= (1<<bits))
#define G_RESET_BIT(u32_register, bits)		(u32_register &= ~(1<<bits))

#define G_IS_BIT_SET(u32_register, bits)	(u32_register & (1<<bits))
#define G_IS_BIT_RESET(u32_register, bits)	(!(u32_register & (1<<bits)))

#define KEY_DOWN_LEVEL		0

#define PIN_OUT_HIGH(port, pin)		GPIO_WriteBit(port, pin, Bit_SET)
#define PIN_OUT_LOW(port, pin)		GPIO_WriteBit(port, pin, Bit_RESET)
#define PIN_IN_STAT(port, pin)		GPIO_ReadInputDataBit(port, pin)



/* Matri key def */
#define MATRIX_ROW_NUM		4
#define MATRIX_COL_NUM		4
#define MATRIX_KEY_NUM		(MATRIX_ROW_NUM * MATRIX_COL_NUM)
/* typedef */

typedef void (*KeyFunction)(void);

typedef void (*KeySoundFun)(void);

/* Key state enumeration */
typedef enum enumKeyStat
{
	NO_Press = 0,
	Key_Press,
	Key_Short_Press,
	Key_Wate,
	Key_Long_Press,
	
}enumKeyStat_t;

/* Key type enumeration */
typedef enum enumKeysType
{
	Type_SingleKey = 0,
	Type_MatrixKey,
	
}enumKeysType_t;

#pragma pack(1)	
typedef struct KeyGPIOTypedef
{
	uint32_t		u32_keySysCtlPeriph;	/* Peripheral to which the button pin belongs */
	GPIO_TypeDef *	u32_key_gpio_base;		/* Key port base address */
	uint16_t		u32_key_gpio_pin;		/* Key pin */
}KeyGPIOTypedef_t;
#pragma pack()

#pragma pack(1)
/* Properties - key index, key port, key pin */
/* Method - long press, short press, short press to lift */
typedef struct SingleKeyTypedef
{
    uint8_t         u8_key_num;				/* Key register index */
    uint32_t       	u32_keySysCtlPeriph;	/* Peripheral to which the button pin belongs */
    GPIO_TypeDef * 	u32_key_gpio_base;		/* Key port base address */
    uint16_t        u32_key_gpio_pin;		/* Key pin */
    KeySoundFun		KeySound;				/* Callback function of press prompt */
    KeyFunction 	shortPress; 			/* Callback function of short press pointer */
    KeyFunction 	longPress; 				/* Callback function of long press pointer */
    KeyFunction 	longUpPress; 			/* Callback function of Long press to lift pointer */
}SingleKeyTypedef_t;
#pragma pack()

#pragma pack(1)
/* Properties - key index, key port, key pin */
/* Method - long press, short press, short press to lift */
typedef struct MatrixKeyTypedef
{
    uint8_t         u8_key_num;					/* Key register index */
    uint8_t         u8_row_num;					/* Matrix key row number */
    uint8_t         u8_col_num;					/* Matrix key column number */
    
    KeyGPIOTypedef_t row_gpios[MATRIX_ROW_NUM];	/* Matrix key row pin list */
	KeyGPIOTypedef_t col_gpios[MATRIX_COL_NUM];	/* Matrix key column pin list */

    KeySoundFun		KeySound;					/* Callback function of press prompt */
    KeyFunction 	shortPress; 				/* Callback function of short press pointer */
    KeyFunction 	longPress; 					/* Callback function of long press pointer */
    KeyFunction 	longUpPress; 				/* Callback function of Long press to lift pointer */
}MatrixKeyTypedef_t;
#pragma pack()


/* Key structure handle */
#pragma pack(1)
typedef struct 
{
	uint32_t u32_keyscan_time;			/* 按键扫描周期 */
	uint32_t u32_keySound_time;			/* 按键扫描周期 */
	uint8_t  u8_key_total_Num;			/* 按键总数 */
	enumKeysType_t enum_key_type;		/* 按键类型 */
	SingleKeyTypedef_t *singleKeyStruct;
	MatrixKeyTypedef_t *matrixKeyStruct;
}sKeyHandle_t;
#pragma pack()

//*****************************************************************************
//
// Prototypes for the APIs.
//
//*****************************************************************************
extern void Key_GPIO_Config(sKeyHandle_t *p_keyhandle);
extern void drv_Key_Handle(sKeyHandle_t *p_keyhandle);
extern uint32_t readKeyValue(sKeyHandle_t *p_keyhandle);
extern uint32_t getKeys(sKeyHandle_t *keys);
extern void resetAllRowsPin(sKeyHandle_t *keys);
//*****************************************************************************


#endif /* __BSP_KEY_H */

