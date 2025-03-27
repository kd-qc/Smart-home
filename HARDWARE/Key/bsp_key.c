/*************************************************************************************
 *file name: bsp_key.c
 *decription: 单体按键驱动 -- 修改 getKeys() 适应不同按键
 			  现 key register为16bit， 其中前5bit为状态位，后11bit为按键状态位
 *date: 20201124
 *autor: XR.Zhneng
 *************************************************************************************/

/* include --------------------------------------*/
#include <stdint.h>
#include <stdbool.h>
#include <stdio.h> 

#include "stm32f10x.h"  
#include "bsp_key.h"

/**
* @brief Key initialization function
* @param [in] keys :Key global structure pointer
* @return none
*/
void Key_GPIO_Config(sKeyHandle_t *p_keyhandle)
{
	uint8_t u8_key_index;
	uint8_t key_num = p_keyhandle->u8_key_total_Num;
	
	assert_param(p_keyhandle != NULL);
	assert_param(key_num > 0);
	
	GPIO_InitTypeDef  GPIO_InitStructure;

	//DEBUG_LOG("Keys num are %d\n", p_keyhandle->u8_key_total_Num);
	if (p_keyhandle->enum_key_type == Type_SingleKey)
	{
		assert_param(p_keyhandle->singleKeyStruct != NULL);
		SingleKeyTypedef_t *pkeyType = p_keyhandle->singleKeyStruct;
		for (u8_key_index=0; u8_key_index<key_num; u8_key_index++)
		{
			/* Enable peripheral clock */
			RCC_APB2PeriphClockCmd(pkeyType[u8_key_index].u32_keySysCtlPeriph, ENABLE);
			/* key pin */
			GPIO_InitStructure.GPIO_Pin = pkeyType[u8_key_index].u32_key_gpio_pin;
			/* Direction as input */
			GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;
			/* Initalize key port */
			GPIO_Init(pkeyType[u8_key_index].u32_key_gpio_base, &GPIO_InitStructure);
		}
	}
	else if (p_keyhandle->enum_key_type == Type_MatrixKey)
	{
		assert_param(p_keyhandle->matrixKeyStruct != NULL);
		
		for (u8_key_index=0; u8_key_index<p_keyhandle->matrixKeyStruct->u8_row_num; u8_key_index++)
		{
			/* Enable peripheral clock */
			RCC_APB2PeriphClockCmd(u8_key_index<p_keyhandle->matrixKeyStruct->row_gpios[u8_key_index].u32_keySysCtlPeriph, ENABLE);
			/* key pin */
			GPIO_InitStructure.GPIO_Pin = u8_key_index<p_keyhandle->matrixKeyStruct->row_gpios[u8_key_index].u32_key_gpio_pin;
			/* Direction as input */
			GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
			/* Initalize key port */
			GPIO_Init(p_keyhandle->matrixKeyStruct->row_gpios[u8_key_index].u32_key_gpio_base, &GPIO_InitStructure);
			/* Reset all row pins */
  			resetAllRowsPin(p_keyhandle);
		}
		for (u8_key_index=0; u8_key_index<p_keyhandle->matrixKeyStruct->u8_col_num; u8_key_index++)
		{
			/* Enable peripheral clock */
			RCC_APB2PeriphClockCmd(u8_key_index<p_keyhandle->matrixKeyStruct->col_gpios[u8_key_index].u32_keySysCtlPeriph, ENABLE);
			/* key pin */
			GPIO_InitStructure.GPIO_Pin = u8_key_index<p_keyhandle->matrixKeyStruct->col_gpios[u8_key_index].u32_key_gpio_pin;
			/* Direction as output */
			GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;
			/* Initalize key port */
			GPIO_Init(p_keyhandle->matrixKeyStruct->col_gpios[u8_key_index].u32_key_gpio_base, &GPIO_InitStructure);
		}
	}
}

/**
* @brief Key processing drv_key_handle
* @param [in] keys :Key global structure pointer
* @return none
*/
void drv_Key_Handle(sKeyHandle_t *p_keyhandle)
{
	assert_param(p_keyhandle != NULL);
	
    uint8_t u8_key_index;
    uint32_t key_value = 0;
	
	/* Read the key value */
    key_value = readKeyValue(p_keyhandle);

	/* Key value is 0 */
    if (key_value == NO_KEY) return;
    
    /* Check short press button */
    if (key_value & KEY_UP)
    {
        //Valid key is detected
        for (u8_key_index = 0; u8_key_index < p_keyhandle->u8_key_total_Num; u8_key_index++)
        {
            if (G_IS_BIT_SET(key_value, p_keyhandle->singleKeyStruct[u8_key_index].u8_key_num)) 
            {
				if (p_keyhandle->singleKeyStruct[u8_key_index].KeySound != NULL) 
                {
                	/* key sound callback */
                	p_keyhandle->singleKeyStruct[u8_key_index].KeySound();
				}
                if (p_keyhandle->singleKeyStruct[u8_key_index].shortPress != NULL) 
                {
                	/* key callback function of short press */
                    p_keyhandle->singleKeyStruct[u8_key_index].shortPress(); 
                }
            }
        }
    }
    /* Check short long button */
    else if (key_value & KEY_LONG)
    {
        for (u8_key_index = 0; u8_key_index < p_keyhandle->u8_key_total_Num; u8_key_index++)
        {
            if (G_IS_BIT_SET(key_value, p_keyhandle->singleKeyStruct[u8_key_index].u8_key_num)) 
            {
            	if (p_keyhandle->singleKeyStruct[u8_key_index].KeySound != NULL) 
                {
                	/* key sound callback */
                	p_keyhandle->singleKeyStruct[u8_key_index].KeySound();
				}
                /* key callback function of long press */
                if (p_keyhandle->singleKeyStruct[u8_key_index].longPress != NULL) 
                {
                	/* key callback function of long press */
                    p_keyhandle->singleKeyStruct[u8_key_index].longPress(); 
                }
            }
        }
    }
    /* Check short long up button */
    else if (key_value & KEY_LONG_UP)
    {
        for (u8_key_index = 0; u8_key_index < p_keyhandle->u8_key_total_Num; u8_key_index++)
        {
            if (G_IS_BIT_SET(key_value, p_keyhandle->singleKeyStruct[u8_key_index].u8_key_num)) 
            {
            	if (p_keyhandle->singleKeyStruct[u8_key_index].KeySound != NULL) 
                {
                	/* key sound callback */
                	p_keyhandle->singleKeyStruct[u8_key_index].KeySound();
				}
                if (p_keyhandle->singleKeyStruct[u8_key_index].longUpPress != NULL) 
                {
                	/* key callback function of long press up */
                    p_keyhandle->singleKeyStruct[u8_key_index].longUpPress(); 
                }
            }
        }
    }
} 

/**
* @brief Read the KEY value
* @param [in] Key handle global structure pointer
* @return GPIO status
*/
uint32_t readKeyValue(sKeyHandle_t *p_keyhandle)
{    
	assert_param(p_keyhandle != NULL);
	
    static enumKeyStat_t keyState = NO_Press;
    static uint16_t keyLongCheck = 0;
    static uint32_t keyPrev = 0;      //last key

    uint32_t keyPress = 0;
    uint32_t keyReturn = 0;

    if (0 == p_keyhandle->u32_keyscan_time)
    {
    	/* Key scan cycle reload */
    	p_keyhandle->u32_keyscan_time = KEY_SCAN_TIME;
    	/* Read key register (custom) */
        keyPress = getKeys(p_keyhandle);
   	    /* key state machine */
        switch (keyState)
        {
            case NO_Press:
                if (keyPress != 0)
                {
                    keyPrev = keyPress;
                    keyState = Key_Press;
                }
                break;
                
            case Key_Press:
                if (keyPress == keyPrev)
                {
                    keyState = Key_Short_Press;
                    keyReturn= keyPrev | KEY_DOWN;
                }
                else	/* Button lift, jitter, no response button */
                {
                    keyState = NO_Press;
                }
                break;
                
            case Key_Short_Press:

                if (keyPress != keyPrev)
                {
                    keyState = NO_Press;
                    keyLongCheck = 0;
                    keyReturn = keyPrev | KEY_UP;
                    
                    return keyReturn;
                }
               	else
                {
                    keyLongCheck++;
                    if (keyLongCheck >= (PRESS_LONG_TIME / KEY_SCAN_TIME))    //Long press 2S effective
                    {
                        keyLongCheck = 0;
                        keyState = Key_Long_Press;
                        keyReturn= keyPress | KEY_LONG;
                        return keyReturn;
                    }
                }
                break;

            case Key_Long_Press:
                if (keyPress != keyPrev)
                {
                    keyState = NO_Press;
                    keyReturn = keyPrev | KEY_LONG_UP;
                    return keyReturn;
                }
                break;
        }
    }
    return  NO_KEY;
}

/**
* @brief Reset all row pins
* @param [in] keys :Key global structure pointer
* @return void
*/
void resetAllRowsPin(sKeyHandle_t *keys)
{
	assert_param(keys != NULL);
	
	uint8_t u8_row_index;
	for (u8_row_index = 0; u8_row_index < keys->matrixKeyStruct->u8_row_num; u8_row_index++)
	{
		PIN_OUT_LOW(	keys->matrixKeyStruct->row_gpios[u8_row_index].u32_key_gpio_base, 	\
						keys->matrixKeyStruct->row_gpios[u8_row_index].u32_key_gpio_pin	);
	}
}

/**
* @brief Read the GPIO state
* @param [in] keys :Key global structure pointer
* @return GPIO status 
*/
uint32_t getKeys(sKeyHandle_t *keys)
{
	assert_param(keys != NULL);
	
    uint8_t u8_key_index = 0; 
    uint16_t u32_key_register = 0;
  	if (keys->enum_key_type == Type_SingleKey)
  	{
  		/* Key GPIO cyclic scan */
		for (u8_key_index=0; u8_key_index<keys->u8_key_total_Num; u8_key_index++)
		{
			/* Low level active */
		    if (KEY_DOWN_LEVEL == PIN_IN_STAT(keys->singleKeyStruct[u8_key_index].u32_key_gpio_base, \
		    								  keys->singleKeyStruct[u8_key_index].u32_key_gpio_pin))
		    {
		    	/* According to index key register bit-set */
		        G_SET_BIT(u32_key_register, keys->singleKeyStruct[u8_key_index].u8_key_num);
		    }
		}
  	}
  	else if (keys->enum_key_type == Type_MatrixKey)
  	{
  		uint8_t u8_row_index;
  		uint8_t u8_col_index;
  		uint8_t u8_key_index;
  		
  		for (u8_row_index = 0; u8_row_index < keys->matrixKeyStruct->u8_row_num; u8_row_index++)
  		{
  			PIN_OUT_HIGH(	keys->matrixKeyStruct->row_gpios[u8_row_index].u32_key_gpio_base, 	\
  							keys->matrixKeyStruct->row_gpios[u8_row_index].u32_key_gpio_pin	);
			for (u8_col_index = 0; u8_col_index < keys->matrixKeyStruct->u8_col_num; u8_col_index++)
			{
				if (KEY_DOWN_LEVEL == PIN_IN_STAT(keys->matrixKeyStruct->col_gpios[u8_key_index].u32_key_gpio_base, \
		    									  keys->matrixKeyStruct->col_gpios[u8_key_index].u32_key_gpio_pin))
				{
					u8_key_index = u8_row_index * keys->matrixKeyStruct->u8_col_num + u8_col_index;
					/* According to index key register bit-set */
			        G_SET_BIT(u32_key_register, u8_key_index);
				}
			}
			
  			/* Reset all row pins */
  			resetAllRowsPin(keys);
  		}
  	}
    
    
    return u32_key_register;
}

/* end file --------------------------------------------------- */

