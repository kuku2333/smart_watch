#include "BLT_cmd.h"

/**
	*****************************************************************************
	*@brief 用串口2与蓝牙模块进行通信，映射的引脚为TX--PA2，RX--PA3
	*@steps 1.打开串口2的时钟和对应引脚的时钟
	*		2.用GPIO_PinAFConfig()函数配置引脚的复用功能
	*		3.配置引脚结构体，功能选服用，引脚初始化结构体
	*		4.配置串口结构体并用初始化函数进行初始化
	*		6.配置NVIC，然后要使用这个USART_ITConfig()函数
	*		7.使能串口
	*****************************************************************************
**/

uint8_t buffer[100]; // 根据需要调整大小
uint8_t buffer_index = 0;

static USART_InitTypeDef   		USART_InitStructure;
static GPIO_InitTypeDef 		GPIO_InitStructure;
static NVIC_InitTypeDef   		NVIC_InitStructure;

volatile uint8_t  g_usart1_rx_buf[1280];
volatile uint32_t g_usart1_rx_cnt=0;
volatile uint32_t g_usart1_rx_end=0;

//#pragma import(__use_no_semihosting_swi)

/*	
	uart2:tx-->pa2	rx-->pa3d
	串口2连接蓝牙模块，手机蓝牙连接蓝牙模块后，发送数据到
	蓝牙模块，蓝牙模块再通过串口2把数据给MCU，MCU再通过串口
	1把数据发送到电脑。这是测试。
	最终只需要数据到了MCU后，存起来，然后解析指令，再判断需要
	做什么动作。注意，解析指令的动作在中断服务函数中，所以动作
	太长的话，记得用标志位。
*/
void Uasrt2_Init(void)
{
//	USART_InitTypeDef USART_InitStructure;
//    NVIC_InitTypeDef NVIC_InitStructure;
//    GPIO_InitTypeDef GPIO_InitStructure;
	
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA, ENABLE);
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_USART2, ENABLE);
	
	GPIO_PinAFConfig(GPIOA, GPIO_PinSource2,  GPIO_AF_USART2);
	GPIO_PinAFConfig(GPIOA, GPIO_PinSource3, GPIO_AF_USART2);

	/* Configure USART Tx and Rx as alternate function push-pull */
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_2 | GPIO_Pin_3;
	GPIO_Init(GPIOA, &GPIO_InitStructure);
	
	USART_InitStructure.USART_BaudRate = 115200;
    USART_InitStructure.USART_WordLength = USART_WordLength_8b;
    USART_InitStructure.USART_StopBits = USART_StopBits_1;
    USART_InitStructure.USART_Parity = USART_Parity_No;
    USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
    USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;
    USART_Init(USART2, &USART_InitStructure);

	/* Enable the USARTx Interrupt */
    NVIC_InitStructure.NVIC_IRQChannel = USART2_IRQn;
    NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;
    NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;
    NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
    NVIC_Init(&NVIC_InitStructure);
    
	USART_ITConfig(USART2, USART_IT_RXNE, ENABLE);
	
    /* Enable USART */
    USART_Cmd(USART2, ENABLE);
}

/* 在串口2收到指令后，进行指令解析，解析成功后，
	再做对应动作。*/
void USART2_IRQHandler(void)
{
	uint8_t data;
	
	/* USART in Receiver mode */
    if (USART_GetITStatus(USART2, USART_IT_RXNE) == SET)
    {
		//printf("receive\r\n");
        /* Receive Transaction data */
		data = USART_ReceiveData(USART2);
		//printf("data: %c\r\n", data);
//		USART_SendData(USART1, data);
		
		// 读取接收到的字节
        //uint8_t data = USART_ReceiveData(USART2);

        // 检查是否为结束符，例如'\n'或'\r'
        if(data == 'n' || data == '\r') 
		{
            // 结束符，处理命令
            buffer[buffer_index] = '\0'; // 添加字符串结束符
            buffer_index = 0; // 重置缓冲区索引
			//printf("ok1\r\n");
            process_command(buffer); // 处理命令
        } 
		else 
		{
            // 将数据存储到缓冲区
            if(buffer_index < sizeof(buffer) - 1) 
			{
                buffer[buffer_index++] = data;
            }
		}	
    }
	
	//USART_ClearITPendingBit(USART1, USART_IT_RXNE);
}

/* 	判断是什么命令*/
void process_command(uint8_t *cmd)
{
	// 检查命令格式是否为"SETTIME:HH:MM:SS"
    if(strstr((char *)cmd, "SETTIME:") == cmd) 
	{
		uint8_t *pos = strstr((char *)cmd, "SETTIME:");
		printf("into prase\r\n");
        // 解析时间并设置RTC
        //RTC_TimeTypeDef RTC_TimeStructure;
        // 假设函数parse_time成功解析时间并填充RTC_TimeStructure
        if(parse_time((char *)(pos + strlen("SETTIME:")), &RTC_TimeStructure)) 
		{
            RTC_SetTime(RTC_Format_BIN, &RTC_TimeStructure);
			RTC_ShowTime();
        }
		//RTC_SetTime(RTC_Format_BIN, &RTC_TimeStructure);
    }
}

/* 
	解析出字符串中的时间
	ex:SETTIME:125500
*/
bool parse_time(char *time_str, RTC_TimeTypeDef *RTC_TimeStructure)
{
	uint8_t hours, minutes, seconds;
	
	sscanf(time_str, "%2d%2d%2d", &hours, &minutes, &seconds);
	
	RTC_TimeStructure->RTC_Hours		=	hours; 
	RTC_TimeStructure->RTC_Minutes		=	minutes;
	RTC_TimeStructure->RTC_Seconds		=	seconds;
	
	return true;
}

//void Send_String(char *string)
//{
//	uint8_t i = 0;
//	char temp;
//	
//	while(1)
//	{
//		temp = string[i];
//		USART_SendData(USART1, temp);
//		i++;
//		Delay_ms(10);
//		if(temp == 0x00 || temp == 0xFF)
//		{
//			break;
//		}	
//	}
//}

//void Uasrt1_Init(void)
//{
//	USART_InitTypeDef USART_InitStructure;
//    NVIC_InitTypeDef NVIC_InitStructure;
//    GPIO_InitTypeDef GPIO_InitStructure;
//	
//	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA, ENABLE);
//	RCC_APB2PeriphClockCmd(RCC_APB2Periph_USART1, ENABLE);
//	
//	GPIO_PinAFConfig(GPIOA, GPIO_PinSource9,  GPIO_AF_USART1);
//	GPIO_PinAFConfig(GPIOA, GPIO_PinSource10, GPIO_AF_USART1);

//	/* Configure USART Tx and Rx as alternate function push-pull */
//	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;
//	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;
//	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
//	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;
//	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_9 | GPIO_Pin_10;
//	GPIO_Init(GPIOA, &GPIO_InitStructure);
//	
//	USART_InitStructure.USART_BaudRate = 9600;
//    USART_InitStructure.USART_WordLength = USART_WordLength_8b;
//    USART_InitStructure.USART_StopBits = USART_StopBits_1;
//    USART_InitStructure.USART_Parity = USART_Parity_No;
//    USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
//    USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;
//    USART_Init(USART1, &USART_InitStructure);

//	/* Enable the USARTx Interrupt */
//    NVIC_InitStructure.NVIC_IRQChannel = USART1_IRQn;
//    NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;
//    NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;
//    NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
//    NVIC_Init(&NVIC_InitStructure);
//    
//	USART_ITConfig(USART1, USART_IT_RXNE, ENABLE);
//	
//    /* Enable USART */
//    USART_Cmd(USART1, ENABLE);
//}

//void USART1_IRQHandler(void)
//{
//	uint8_t d=0;
//	
//	//检测是否接收到数据
//	if (USART_GetITStatus(USART1, USART_IT_RXNE) == SET)
//	{
//		d=USART_ReceiveData(USART1);
//		
//		
//		g_usart1_rx_buf[g_usart1_rx_cnt++]=d;
//	
//		if(g_usart1_rx_cnt >= sizeof g_usart1_rx_buf)
//		{
//			g_usart1_rx_end=1;
//		}			
//	
//		//清空标志位，可以响应新的中断请求
//		USART_ClearITPendingBit(USART1, USART_IT_RXNE);
//	}
//}

//void usart1_send_bytes(uint8_t *buf,uint32_t len)
//{
//	uint8_t *p = buf;
//	
//	while(len--)
//	{
//		USART_SendData(USART1,*p);
//		
//		p++;
//		
//		//等待数据发送成功
//		while(USART_GetFlagStatus(USART1,USART_FLAG_TXE)==RESET);
//		USART_ClearFlag(USART1,USART_FLAG_TXE);
//	}
//}

//struct __FILE { int handle; /* Add whatever you need here */ };
//FILE __stdout;
//FILE __stdin;

//int fputc(int ch, FILE *f)
//{
//	USART_SendData(USART2, ch);	
//	while( USART_GetFlagStatus(USART2, USART_FLAG_TXE) == RESET );
//		
//	return ch;
//}
