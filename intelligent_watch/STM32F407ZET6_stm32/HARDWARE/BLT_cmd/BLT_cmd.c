#include "BLT_cmd.h"

/**
	*****************************************************************************
	*@brief �ô���2������ģ�����ͨ�ţ�ӳ�������ΪTX--PA2��RX--PA3
	*@steps 1.�򿪴���2��ʱ�ӺͶ�Ӧ���ŵ�ʱ��
	*		2.��GPIO_PinAFConfig()�����������ŵĸ��ù���
	*		3.�������Žṹ�壬����ѡ���ã����ų�ʼ���ṹ��
	*		4.���ô��ڽṹ�岢�ó�ʼ���������г�ʼ��
	*		6.����NVIC��Ȼ��Ҫʹ�����USART_ITConfig()����
	*		7.ʹ�ܴ���
	*****************************************************************************
**/

uint8_t buffer[100]; // ������Ҫ������С
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
	����2��������ģ�飬�ֻ�������������ģ��󣬷������ݵ�
	����ģ�飬����ģ����ͨ������2�����ݸ�MCU��MCU��ͨ������
	1�����ݷ��͵����ԡ����ǲ��ԡ�
	����ֻ��Ҫ���ݵ���MCU�󣬴�������Ȼ�����ָ����ж���Ҫ
	��ʲô������ע�⣬����ָ��Ķ������жϷ������У����Զ���
	̫���Ļ����ǵ��ñ�־λ��
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

/* �ڴ���2�յ�ָ��󣬽���ָ������������ɹ���
	������Ӧ������*/
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
		
		// ��ȡ���յ����ֽ�
        //uint8_t data = USART_ReceiveData(USART2);

        // ����Ƿ�Ϊ������������'\n'��'\r'
        if(data == 'n' || data == '\r') 
		{
            // ����������������
            buffer[buffer_index] = '\0'; // ����ַ���������
            buffer_index = 0; // ���û���������
			//printf("ok1\r\n");
            process_command(buffer); // ��������
        } 
		else 
		{
            // �����ݴ洢��������
            if(buffer_index < sizeof(buffer) - 1) 
			{
                buffer[buffer_index++] = data;
            }
		}	
    }
	
	//USART_ClearITPendingBit(USART1, USART_IT_RXNE);
}

/* 	�ж���ʲô����*/
void process_command(uint8_t *cmd)
{
	// ��������ʽ�Ƿ�Ϊ"SETTIME:HH:MM:SS"
    if(strstr((char *)cmd, "SETTIME:") == cmd) 
	{
		uint8_t *pos = strstr((char *)cmd, "SETTIME:");
		printf("into prase\r\n");
        // ����ʱ�䲢����RTC
        //RTC_TimeTypeDef RTC_TimeStructure;
        // ���躯��parse_time�ɹ�����ʱ�䲢���RTC_TimeStructure
        if(parse_time((char *)(pos + strlen("SETTIME:")), &RTC_TimeStructure)) 
		{
            RTC_SetTime(RTC_Format_BIN, &RTC_TimeStructure);
			RTC_ShowTime();
        }
		//RTC_SetTime(RTC_Format_BIN, &RTC_TimeStructure);
    }
}

/* 
	�������ַ����е�ʱ��
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
//	//����Ƿ���յ�����
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
//		//��ձ�־λ��������Ӧ�µ��ж�����
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
//		//�ȴ����ݷ��ͳɹ�
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
