#include "sys.h"
#include "usart.h"	
/*ʹ��microLib�ķ���*/
int fputc(int ch, FILE *f)
{
	USART_SendData(USART1, (uint8_t) ch);

	while (USART_GetFlagStatus(USART1, USART_FLAG_TC) == RESET);
   
    return ch;
}

int GetKey (void)  
{ 
    while (USART_GetFlagStatus(USART1, USART_FLAG_RXNE) == SET);

    return ((int)USART_ReceiveData(USART1));
}


//��ʼ��IO ����1 
//bound:������
void uart1_init(u32 bound)
{
    //GPIO�˿�����
    GPIO_InitTypeDef GPIO_InitStructure;
	USART_InitTypeDef USART_InitStructure;
	NVIC_InitTypeDef NVIC_InitStructure;
	 
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_USART1|RCC_APB2Periph_GPIOA, ENABLE);	//ʹ��USART1��GPIOAʱ��
 	USART_DeInit(USART1);  //��λ����1
	 //USART1_TX   PA.9
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_9; //PA.9
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;	//�����������
    GPIO_Init(GPIOA, &GPIO_InitStructure); //��ʼ��PA9
   
    //USART1_RX	  PA.10
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_10;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;//��������
    GPIO_Init(GPIOA, &GPIO_InitStructure);  //��ʼ��PA10

   //Usart1 NVIC ����
    NVIC_InitStructure.NVIC_IRQChannel = USART1_IRQn;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority= 0;//��ռ���ȼ�3
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 1;		//�����ȼ�3
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;			//IRQͨ��ʹ��
	NVIC_Init(&NVIC_InitStructure);	//����ָ���Ĳ�����ʼ��VIC�Ĵ���

   //USART ��ʼ������

	USART_InitStructure.USART_BaudRate = bound;//һ������Ϊ9600;
	USART_InitStructure.USART_WordLength = USART_WordLength_8b;//�ֳ�Ϊ8λ���ݸ�ʽ
	USART_InitStructure.USART_StopBits = USART_StopBits_1;//һ��ֹͣλ
	USART_InitStructure.USART_Parity = USART_Parity_No;//����żУ��λ
	USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;//��Ӳ������������
	USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;	//�շ�ģʽ

    USART_Init(USART1, &USART_InitStructure); //��ʼ������
    USART_ITConfig(USART1, USART_IT_RXNE, ENABLE);//�����ж�
    USART_ITConfig(USART1, USART_IT_IDLE, ENABLE);
    USART_Cmd(USART1, ENABLE);                    //ʹ�ܴ��� 

}


//��ʼ��IO ����2
//pclk1:PCLK1ʱ��Ƶ��(Mhz)
//bound:������	  
void uart2_init(u32 bound)
{  

	NVIC_InitTypeDef NVIC_InitStructure;
	GPIO_InitTypeDef GPIO_InitStructure;
	USART_InitTypeDef USART_InitStructure;

	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);	// GPIOAʱ��
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_USART2,ENABLE); //����2ʱ��ʹ��

	USART_DeInit(USART2);  //��λ����2
	 //USART2_TX   PA2
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_2; //PA2
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;	//�����������
	GPIO_Init(GPIOA, &GPIO_InitStructure); //��ʼ��PA2

	//USART2_RX   PA3
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_3;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;//��������
	GPIO_Init(GPIOA, &GPIO_InitStructure);  //��ʼ��PA3

	USART_InitStructure.USART_BaudRate = bound;//����������
	USART_InitStructure.USART_WordLength = USART_WordLength_8b;//�ֳ�Ϊ8λ���ݸ�ʽ
	USART_InitStructure.USART_StopBits = USART_StopBits_1;//һ��ֹͣλ
	USART_InitStructure.USART_Parity = USART_Parity_No;//����żУ��λ
	USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;//��Ӳ������������
	USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx; //�շ�ģʽ

	USART_Init(USART2, &USART_InitStructure); //��ʼ������2


	//ʹ�ܽ����ж�
	USART_ITConfig(USART2, USART_IT_RXNE, ENABLE);//�����ж�	 
	USART_ITConfig(USART2, USART_IT_IDLE, ENABLE);

	//�����ж����ȼ�
	NVIC_InitStructure.NVIC_IRQChannel = USART2_IRQn;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority=3 ;//��ռ���ȼ�3
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 3;		//�����ȼ�3
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE; 		//IRQͨ��ʹ��
	NVIC_Init(&NVIC_InitStructure); //����ָ���Ĳ�����ʼ��VIC�Ĵ���
	
	

	USART_Cmd(USART2, ENABLE);					  //ʹ�ܴ��� 

}

//��ʼ��IO ����1 
//bound:������
void uart3_init(u32 bound)
{
	//GPIO�˿�����
	GPIO_InitTypeDef GPIO_InitStructure;
	USART_InitTypeDef USART_InitStructure;
	NVIC_InitTypeDef NVIC_InitStructure;
	 RCC_APB1PeriphClockCmd(RCC_APB1Periph_USART3, ENABLE);
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);	//ʹ��USART3��GPIOBʱ��
	USART_DeInit(USART3);  //��λ����3
	 //USART3_TX   PB.10
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_10; //PB10
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP; //�����������
	GPIO_Init(GPIOB, &GPIO_InitStructure); //��ʼ��PB10
   
	//USART3_RX   PB.11
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_11;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;//��������
	GPIO_Init(GPIOB, &GPIO_InitStructure);	//��ʼ��PB11

   //USART3 NVIC ����
	NVIC_InitStructure.NVIC_IRQChannel = USART3_IRQn;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority=3 ;//��ռ���ȼ�3
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 3;		//�����ȼ�3
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE; 		//IRQͨ��ʹ��
	NVIC_Init(&NVIC_InitStructure); //����ָ���Ĳ�����ʼ��VIC�Ĵ���
  
   //USART ��ʼ������
	USART_InitStructure.USART_BaudRate = bound;
	USART_InitStructure.USART_WordLength = USART_WordLength_8b;//�ֳ�Ϊ8λ���ݸ�ʽ
	USART_InitStructure.USART_StopBits = USART_StopBits_1;//һ��ֹͣλ
	USART_InitStructure.USART_Parity = USART_Parity_No;//����żУ��λ
	USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;//��Ӳ������������
	USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx; //�շ�ģʽ

	USART_Init(USART3, &USART_InitStructure); //��ʼ������
	USART_ITConfig(USART3, USART_IT_RXNE, ENABLE);//�����ж�
	USART_ITConfig(USART3, USART_IT_IDLE, ENABLE);
	USART_Cmd(USART3, ENABLE);	//ʹ�ܴ��� 

}


//���ڷ����ַ���
void Uart_SendStr(USART_TypeDef *USARTx, const u8 *pStr)
{
	while(*pStr++ != 0)
	{
		Uart_SendByte(USARTx, *pStr);
	}
}

//���ڷ����ַ�
void Uart_SendByte(USART_TypeDef *USARTx, u8 u8_data)
{
	USART_SendData(USARTx, (u16) u8_data);
	while(USART_GetFlagStatus(USARTx, USART_FLAG_TC) == RESET);
}

//���ڷ����ַ�
void Uart_SendBuf(USART_TypeDef *USARTx, const u8 *pBuffer, u16 Len)
{
	u16 index;
	for (index=0; index<Len; index++)
	{
		Uart_SendByte(USARTx, pBuffer[index] );
	}
}



u8 Uart1_Rx_Buf[50] = {0};
extern int32_t gizPutData(uint8_t *buf, uint32_t len);
//����1�жϷ������
void USART1_IRQHandler(void)
{
	__IO u16 u16_clear;
	static u16 u16_index = 0;
	if(USART_GetITStatus(USART1, USART_IT_RXNE) != RESET)
	{
		Uart1_Rx_Buf[u16_index] = (u8)USART_ReceiveData(USART1);
		u16_index++;
	}
	else if (USART_GetITStatus(USART1, USART_IT_IDLE) != RESET)
	{
		u16_clear = USART_ReceiveData(USART1);
		gizPutData(Uart1_Rx_Buf, u16_index);
		u16_index = 0;
	}
} 

u8 Uart2_Rx_Buf[UART2_BUF_SIZE] = {0};
extern void Ld3322_RevOneFrameData(u8 * pDataBuf, u16 u16DataLen);
//����2�жϷ������
void USART2_IRQHandler(void)
{
	__IO u16 u16_clear;
	static u16 u16_index = 0;
	if(USART_GetITStatus(USART2, USART_IT_RXNE) != RESET)
	{
		Uart2_Rx_Buf[u16_index] = (u8)USART_ReceiveData(USART2);
		u16_index++;
	}
	else if (USART_GetITStatus(USART2, USART_IT_IDLE) != RESET)
	{
		u16_clear = USART_ReceiveData(USART2);
		Ld3322_RevOneFrameData( Uart2_Rx_Buf, u16_index );
		u16_index = 0;
	}
}

u8 Uart3_Rx_Buf[30] = {0};
//����3�жϷ������
void USART3_IRQHandler(void)
{
	__IO u16 u16_clear;
	static u16 u16_index = 0;
	if(USART_GetITStatus(USART3, USART_IT_RXNE) != RESET)
	{
		Uart3_Rx_Buf[u16_index] = (u8)USART_ReceiveData(USART3);
		u16_index++;
	}
	else if (USART_GetITStatus(USART3, USART_IT_IDLE) != RESET)
	{
		u16_clear = USART_ReceiveData(USART3);
		//gizPutData(Uart3_Rx_Buf, u16_index);
		u16_index = 0;
	}
}



