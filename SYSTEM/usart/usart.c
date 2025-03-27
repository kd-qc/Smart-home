#include "sys.h"
#include "usart.h"	
/*使用microLib的方法*/
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


//初始化IO 串口1 
//bound:波特率
void uart1_init(u32 bound)
{
    //GPIO端口设置
    GPIO_InitTypeDef GPIO_InitStructure;
	USART_InitTypeDef USART_InitStructure;
	NVIC_InitTypeDef NVIC_InitStructure;
	 
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_USART1|RCC_APB2Periph_GPIOA, ENABLE);	//使能USART1，GPIOA时钟
 	USART_DeInit(USART1);  //复位串口1
	 //USART1_TX   PA.9
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_9; //PA.9
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;	//复用推挽输出
    GPIO_Init(GPIOA, &GPIO_InitStructure); //初始化PA9
   
    //USART1_RX	  PA.10
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_10;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;//浮空输入
    GPIO_Init(GPIOA, &GPIO_InitStructure);  //初始化PA10

   //Usart1 NVIC 配置
    NVIC_InitStructure.NVIC_IRQChannel = USART1_IRQn;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority= 0;//抢占优先级3
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 1;		//子优先级3
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;			//IRQ通道使能
	NVIC_Init(&NVIC_InitStructure);	//根据指定的参数初始化VIC寄存器

   //USART 初始化设置

	USART_InitStructure.USART_BaudRate = bound;//一般设置为9600;
	USART_InitStructure.USART_WordLength = USART_WordLength_8b;//字长为8位数据格式
	USART_InitStructure.USART_StopBits = USART_StopBits_1;//一个停止位
	USART_InitStructure.USART_Parity = USART_Parity_No;//无奇偶校验位
	USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;//无硬件数据流控制
	USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;	//收发模式

    USART_Init(USART1, &USART_InitStructure); //初始化串口
    USART_ITConfig(USART1, USART_IT_RXNE, ENABLE);//开启中断
    USART_ITConfig(USART1, USART_IT_IDLE, ENABLE);
    USART_Cmd(USART1, ENABLE);                    //使能串口 

}


//初始化IO 串口2
//pclk1:PCLK1时钟频率(Mhz)
//bound:波特率	  
void uart2_init(u32 bound)
{  

	NVIC_InitTypeDef NVIC_InitStructure;
	GPIO_InitTypeDef GPIO_InitStructure;
	USART_InitTypeDef USART_InitStructure;

	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);	// GPIOA时钟
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_USART2,ENABLE); //串口2时钟使能

	USART_DeInit(USART2);  //复位串口2
	 //USART2_TX   PA2
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_2; //PA2
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;	//复用推挽输出
	GPIO_Init(GPIOA, &GPIO_InitStructure); //初始化PA2

	//USART2_RX   PA3
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_3;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;//浮空输入
	GPIO_Init(GPIOA, &GPIO_InitStructure);  //初始化PA3

	USART_InitStructure.USART_BaudRate = bound;//波特率设置
	USART_InitStructure.USART_WordLength = USART_WordLength_8b;//字长为8位数据格式
	USART_InitStructure.USART_StopBits = USART_StopBits_1;//一个停止位
	USART_InitStructure.USART_Parity = USART_Parity_No;//无奇偶校验位
	USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;//无硬件数据流控制
	USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx; //收发模式

	USART_Init(USART2, &USART_InitStructure); //初始化串口2


	//使能接收中断
	USART_ITConfig(USART2, USART_IT_RXNE, ENABLE);//开启中断	 
	USART_ITConfig(USART2, USART_IT_IDLE, ENABLE);

	//设置中断优先级
	NVIC_InitStructure.NVIC_IRQChannel = USART2_IRQn;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority=3 ;//抢占优先级3
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 3;		//子优先级3
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE; 		//IRQ通道使能
	NVIC_Init(&NVIC_InitStructure); //根据指定的参数初始化VIC寄存器
	
	

	USART_Cmd(USART2, ENABLE);					  //使能串口 

}

//初始化IO 串口1 
//bound:波特率
void uart3_init(u32 bound)
{
	//GPIO端口设置
	GPIO_InitTypeDef GPIO_InitStructure;
	USART_InitTypeDef USART_InitStructure;
	NVIC_InitTypeDef NVIC_InitStructure;
	 RCC_APB1PeriphClockCmd(RCC_APB1Periph_USART3, ENABLE);
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);	//使能USART3，GPIOB时钟
	USART_DeInit(USART3);  //复位串口3
	 //USART3_TX   PB.10
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_10; //PB10
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP; //复用推挽输出
	GPIO_Init(GPIOB, &GPIO_InitStructure); //初始化PB10
   
	//USART3_RX   PB.11
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_11;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;//浮空输入
	GPIO_Init(GPIOB, &GPIO_InitStructure);	//初始化PB11

   //USART3 NVIC 配置
	NVIC_InitStructure.NVIC_IRQChannel = USART3_IRQn;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority=3 ;//抢占优先级3
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 3;		//子优先级3
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE; 		//IRQ通道使能
	NVIC_Init(&NVIC_InitStructure); //根据指定的参数初始化VIC寄存器
  
   //USART 初始化设置
	USART_InitStructure.USART_BaudRate = bound;
	USART_InitStructure.USART_WordLength = USART_WordLength_8b;//字长为8位数据格式
	USART_InitStructure.USART_StopBits = USART_StopBits_1;//一个停止位
	USART_InitStructure.USART_Parity = USART_Parity_No;//无奇偶校验位
	USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;//无硬件数据流控制
	USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx; //收发模式

	USART_Init(USART3, &USART_InitStructure); //初始化串口
	USART_ITConfig(USART3, USART_IT_RXNE, ENABLE);//开启中断
	USART_ITConfig(USART3, USART_IT_IDLE, ENABLE);
	USART_Cmd(USART3, ENABLE);	//使能串口 

}


//串口发送字符串
void Uart_SendStr(USART_TypeDef *USARTx, const u8 *pStr)
{
	while(*pStr++ != 0)
	{
		Uart_SendByte(USARTx, *pStr);
	}
}

//串口发送字符
void Uart_SendByte(USART_TypeDef *USARTx, u8 u8_data)
{
	USART_SendData(USARTx, (u16) u8_data);
	while(USART_GetFlagStatus(USARTx, USART_FLAG_TC) == RESET);
}

//串口发送字符
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
//串口1中断服务程序
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
//串口2中断服务程序
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
//串口3中断服务程序
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



