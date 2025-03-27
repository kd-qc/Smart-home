#ifndef __USART_H
#define __USART_H
#include "stdio.h"	
#include "sys.h" 
/* ������Ϣ�ӿ� - ��ǰ���ܱ��ر� */
#define USART_ESP8266                       USART1  // PB10_TX  PB11_RX

#define DEBUG_UART_Config()			//uart1_init(115200)
#define DEBUG_LOG(s, ...)			//printf(""s"", ##__VA_ARGS__)
#define DEBUG_PRINTF 				DEBUG_LOG
#define FML_USART_Transmit 			Uart_SendBuf	

#define UART2_BUF_SIZE				32

#define USART2_MAX_RECV_LEN		400					//�����ջ����ֽ���
#define USART2_MAX_SEND_LEN		400					//����ͻ����ֽ���
#define USART2_RX_EN 			1					//0,������;1,����.
#define usart2_baund  57600		/*����2�����ʣ�����ָ��ģ�鲨���ʸ���*/


extern u8  USART2_RX_BUF[USART2_MAX_RECV_LEN]; 		//���ջ���,���USART2_MAX_RECV_LEN�ֽ�
extern u8  USART2_TX_BUF[USART2_MAX_SEND_LEN]; 		//���ͻ���,���USART2_MAX_SEND_LEN�ֽ�
extern vu16 USART2_RX_STA;   						//��������״̬

//����봮���жϽ��գ��벻Ҫע�����º궨��

void uart1_init(u32 bound);
void uart2_init(u32 bound);
void uart3_init(u32 bound);
extern void Uart2_RevTimeOut( void );
extern void Uart_SendStr(USART_TypeDef *USARTx, const u8 *pStr);
extern void Uart_SendByte(USART_TypeDef *USARTx, u8 u8_data);
extern void Uart_SendBuf(USART_TypeDef *USARTx, const u8 *pBuffer, u16 Len);
#endif


