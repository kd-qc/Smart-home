/**
************************************************************
* @file         gizwits_product.c
* @brief        Gizwits control protocol processing, and platform-related       hardware initialization 
* @author       Gizwits
* @date         2017-07-19
* @version      V03030000
* @copyright    Gizwits
* 
* @note         ����??ֻΪ����Ӳ������
*               Gizwits Smart Cloud  for Smart Products
*               ����|��ֵ?|����|����|��ȫ|����|����|��??*               www.gizwits.com
*
***********************************************************/

#include <stdio.h>
#include <string.h>
#include "gizwits_product.h"
#include "common.h"

#include "usart.h"
static uint32_t timerMsCount;
uint8_t aRxBuffer;

/** User area the current device state structure*/
dataPoint_t currentDataPoint;
GizwitsCallback gfunCallback;

/**@} */
/**@name Gizwits User Interface
* @{
*/

/**
* @brief Event handling interface

* Description:

* 1. Users can customize the changes in WiFi module status

* 2. Users can add data points in the function of event processing logic, such as calling the relevant hardware peripherals operating interface

* @param [in] info: event queue
* @param [in] data: protocol data
* @param [in] len: protocol data length
* @return NULL
* @ref gizwits_protocol.h
*/
int8_t gizwitsEventProcess(eventInfo_t *info, uint8_t *gizdata, uint32_t len)
{
  uint8_t i = 0;
  dataPoint_t *dataPointPtr = (dataPoint_t *)gizdata;
  moduleStatusInfo_t *wifiData = (moduleStatusInfo_t *)gizdata;
  protocolTime_t *ptime = (protocolTime_t *)gizdata;
  
#if MODULE_TYPE
  gprsInfo_t *gprsInfoData = (gprsInfo_t *)gizdata;
#else
  moduleInfo_t *ptModuleInfo = (moduleInfo_t *)gizdata;
#endif

  if((NULL == info) || (NULL == gizdata))
  {
    return -1;
  }

  for(i=0; i<info->num; i++)
  {
    switch(info->event[i])
    {
      case EVENT_light:
        currentDataPoint.valuelight = dataPointPtr->valuelight;
        GIZWITS_LOG("Evt: EVENT_light %d \n", currentDataPoint.valuelight);
        if(0x01 == currentDataPoint.valuelight)
        {
          //user handle
        }
        else
        {
          //user handle    
        }

        if (gfunCallback != NULL)
        {
        	gfunCallback(info->event[i], &currentDataPoint);
        }
        break;
      case EVENT_aircondi:
        currentDataPoint.valueaircondi = dataPointPtr->valueaircondi;
        GIZWITS_LOG("Evt: EVENT_aircondi %d \n", currentDataPoint.valueaircondi);
        if(0x01 == currentDataPoint.valueaircondi)
        {
          //user handle
        }
        else
        {
          //user handle    
        }

         if (gfunCallback != NULL)
        {
        	gfunCallback(info->event[i], &currentDataPoint);
        }
        break;
      case EVENT_curtain:
        currentDataPoint.valuecurtain = dataPointPtr->valuecurtain;
        GIZWITS_LOG("Evt: EVENT_curtain %d \n", currentDataPoint.valuecurtain);
        if(0x01 == currentDataPoint.valuecurtain)
        {
          //user handle
        }
        else
        {
          //user handle    
        }

         if (gfunCallback != NULL)
        {
        	gfunCallback(info->event[i], &currentDataPoint);
        }
        break;

	case EVENT_tempGate:
	  currentDataPoint.valuetempGate = dataPointPtr->valuetempGate;
	  GIZWITS_LOG("Evt:EVENT_tempGate %d\n",currentDataPoint.valuetempGate);
	  //user handle
	  break;
	case EVENT_lightnessGate:
	  currentDataPoint.valuelightnessGate = dataPointPtr->valuelightnessGate;
	  GIZWITS_LOG("Evt:EVENT_lightnessGate %d\n",currentDataPoint.valuelightnessGate);
	  //user handle
	  break;



      case WIFI_SOFTAP:
        break;
      case WIFI_AIRLINK:
        break;
      case WIFI_STATION:
        break;
      case WIFI_CON_ROUTER:
 
        break;
      case WIFI_DISCON_ROUTER:
 
        break;
      case WIFI_CON_M2M:
 
        break;
      case WIFI_DISCON_M2M:
        break;
      case WIFI_RSSI:
        GIZWITS_LOG("RSSI %d\n", wifiData->rssi);
        break;
      case TRANSPARENT_DATA:
        GIZWITS_LOG("TRANSPARENT_DATA \n");
        //user handle , Fetch data from [data] , size is [len]
        break;
      case WIFI_NTP:
        GIZWITS_LOG("WIFI_NTP : [%d-%d-%d %02d:%02d:%02d][%d] \n",ptime->year,ptime->month,ptime->day,ptime->hour,ptime->minute,ptime->second,ptime->ntp);
        break;
      case MODULE_INFO:
            GIZWITS_LOG("MODULE INFO ...\n");
      #if MODULE_TYPE
            GIZWITS_LOG("GPRS MODULE ...\n");
            //Format By gprsInfo_t
      #else
            GIZWITS_LOG("WIF MODULE ...\n");
            //Format By moduleInfo_t
            GIZWITS_LOG("moduleType : [%d] \n",ptModuleInfo->moduleType);
      #endif
    break;
      default:
        break;
    }
  }

  return 0;
}


/**
* User data acquisition

* Here users need to achieve in addition to data points other than the collection of data collection, can be self-defined acquisition frequency and design data filtering algorithm

* @param none
* @return none
*/
void userHandle(void)
{
 /*
    currentDataPoint.valueFan_Switch = ;//Add Sensor Data Collection
    currentDataPoint.valueWarn = ;//Add Sensor Data Collection
    currentDataPoint.valueTemperature = ;//Add Sensor Data Collection
    currentDataPoint.valueHumidity = ;//Add Sensor Data Collection
    currentDataPoint.valueCO = ;//Add Sensor Data Collection
    currentDataPoint.valueAir = ;//Add Sensor Data Collection
    currentDataPoint.valueSmog = ;//Add Sensor Data Collection

    */
    
}

/**
* Data point initialization function

* In the function to complete the initial user-related data
* @param none
* @return none
* @note The developer can add a data point state initialization value within this function
*/
void userInit(void)
{
    memset((uint8_t*)&currentDataPoint, 0, sizeof(dataPoint_t));
    
    /** Warning !!! DataPoint Variables Init , Must Within The Data Range **/ 
    /*
      currentDataPoint.valueLight = ;
      currentDataPoint.valueFan_Switch = ;
      currentDataPoint.valueWarn = ;
      currentDataPoint.valueTemperature = ;
      currentDataPoint.valueHumidity = ;
      currentDataPoint.valueCO = ;
      currentDataPoint.valueAir = ;
      currentDataPoint.valueSmog = ;
    */

}


/**
* @brief Millisecond timing maintenance function, milliseconds increment, overflow to zero

* @param none
* @return none
*/
void gizTimerMs(void)
{
    timerMsCount++;
}

/**
* @brief Read millisecond count

* @param none
* @return millisecond count
*/
uint32_t gizGetTimerCount(void)
{
    return timerMsCount;
}

/**
* @brief MCU reset function

* @param none
* @return none
*/
void mcuRestart(void)
{
    __set_FAULTMASK(1);
    NVIC_SystemReset();
}

/**@} */




/**
* @brief Timer TIM3 init function

* @param none
* @return none
*/
void timerInit(void)
{

}


/**
* @brief USART init function

* Serial communication between WiFi modules and device MCU
* @param none
* @return none
*/
void uartInit(void)
{

}

/**
* @brief Serial port write operation, send data to WiFi module
*
* @param buf      : buf address
* @param len      : buf length
*
* @return : Return effective data length;-1��return failure
*/
int32_t uartWrite(uint8_t *buf, uint32_t len)
{
    uint32_t i = 0;
	
    if(NULL == buf)
    {
        return -1;
    }

    for(i=0; i<len; i++)
    {
		Uart_SendByte(USART1, buf[i]);

        if(i >=2 && buf[i] == 0xFF)
        {
			Uart_SendByte(USART1, 0x55);
        }
    }

#ifdef PROTOCOL_DEBUG
    GIZWITS_LOG("MCU2WiFi[%4d:%4d]: ", gizGetTimerCount(), len);
    for(i=0; i<len; i++)
    {
        GIZWITS_LOG("%02x ", buf[i]);

        if(i >=2 && buf[i] == 0xFF)
        {
            GIZWITS_LOG("%02x ", 0x55);
        }
    }
    GIZWITS_LOG("\n");
#endif
		
	return len;
}  
