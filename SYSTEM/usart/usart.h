#ifndef __USART_H
#define __USART_H
#include "stdio.h"	
#include "sys.h" 
/* 调试信息接口 - 当前功能被关闭 */
#define USART_ESP8266                       USART1  // PB10_TX  PB11_RX

#define DEBUG_UART_Config()			//uart1_init(115200)
#define DEBUG_LOG(s, ...)			//printf(""s"", ##__VA_ARGS__)
#define DEBUG_PRINTF 				DEBUG_LOG
#define FML_USART_Transmit 			Uart_SendBuf	

#define UART2_BUF_SIZE				32

#define USART2_MAX_RECV_LEN		400					//最大接收缓存字节数
#define USART2_MAX_SEND_LEN		400					//最大发送缓存字节数
#define USART2_RX_EN 			1					//0,不接收;1,接收.
#define usart2_baund  57600		/*串口2波特率，根据指纹模块波特率更改*/


extern u8  USART2_RX_BUF[USART2_MAX_RECV_LEN]; 		//接收缓冲,最大USART2_MAX_RECV_LEN字节
extern u8  USART2_TX_BUF[USART2_MAX_SEND_LEN]; 		//发送缓冲,最大USART2_MAX_SEND_LEN字节
extern vu16 USART2_RX_STA;   						//接收数据状态

//如果想串口中断接收，请不要注释以下宏定义

void uart1_init(u32 bound);
void uart2_init(u32 bound);
void uart3_init(u32 bound);
extern void Uart2_RevTimeOut( void );
extern void Uart_SendStr(USART_TypeDef *USARTx, const u8 *pStr);
extern void Uart_SendByte(USART_TypeDef *USARTx, u8 u8_data);
extern void Uart_SendBuf(USART_TypeDef *USARTx, const u8 *pBuffer, u16 Len);
#endif


