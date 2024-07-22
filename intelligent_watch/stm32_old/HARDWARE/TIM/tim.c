#include "stm32f4xx.h"
#include "sys.h"
#include "../lvgl.h"
#include "tim.h"

void tim3_init(void)
{
	TIM_TimeBaseInitTypeDef  	TIM_TimeBaseStructure;
	NVIC_InitTypeDef   		NVIC_InitStructure;
	
	//��TIM3Ӳ��ʱ��
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3, ENABLE);
		
	TIM_TimeBaseStructure.TIM_Period = 10000/1000-1;//����ֵ�����ڶ�ʱʱ�������
	TIM_TimeBaseStructure.TIM_Prescaler = 8399;//Ԥ��Ƶֵ������
	TIM_TimeBaseStructure.TIM_ClockDivision = 0;//F407û�У�����Ҫ����
	TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;//���ϼ���������0 -> TIM_Period��Ȼ��ͻᴥ��ʱ������ж�
	TIM_TimeBaseInit(TIM3, &TIM_TimeBaseStructure);
	
	/* ��ʱ��ʱ������ж�ʹ�� */
	TIM_ITConfig(TIM3, TIM_IT_Update, ENABLE);

	//����NVIC�����ڴ�TIM3���ж�����ͨ��
	NVIC_InitStructure.NVIC_IRQChannel = TIM3_IRQn;	//TIM3������ͨ��
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0x03;//��ռ���ȼ�0xF
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0x03;//��Ӧ���ȼ�0xF
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;//��������ͨ��
	NVIC_Init(&NVIC_InitStructure);
	
	/* ʹ��TIM3���� */
	TIM_Cmd(TIM3, ENABLE);	
}

void TIM3_IRQHandler(void)
{
	static uint32_t usart1_rx_cnt_last=0;
	static uint32_t irq_cnt=0;
	
	//���ʱ������жϵı�־λ�Ƿ���λ
	if (TIM_GetITStatus(TIM3, TIM_IT_Update) == SET)
	{
		irq_cnt++;
		
		if(irq_cnt>=10 && g_usart1_rx_cnt)
		{
			//����ȣ����ʾ����3Ŀǰ�����������
			if(g_usart1_rx_cnt == usart1_rx_cnt_last)
			{
				g_usart1_rx_end=1;
			}
			else
			{
				usart1_rx_cnt_last = g_usart1_rx_cnt;
			}
			
			irq_cnt=0;
		}
		
		lv_tick_inc(1);
		
		//��ձ�־λ
		TIM_ClearITPendingBit(TIM3, TIM_IT_Update);
	}
}

void Tim14_Init(void)
{
	//����ʱ����GPIO������ȽϽṹ��
	TIM_TimeBaseInitTypeDef		TIM_TimeBaseStructure;
	GPIO_InitTypeDef			GPIO_InitStructure;
	TIM_OCInitTypeDef  			TIM_OCInitStructure;

	//������ʱ����GPIO��ʱ��
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM4, ENABLE);//����TIM14��ʱ�ӣ���APB1��
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOB, ENABLE);
	
	/* GPIOF ����: TIM14 CH1 (PF9)*/
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_6;//����9
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;//����ģʽ
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;
    GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
    GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;
    GPIO_Init(GPIOB, &GPIO_InitStructure);//��ʼ��
	
	GPIO_PinAFConfig(GPIOB, GPIO_PinSource6, GPIO_AF_TIM4);//����ӳ�䵽��ʱ��
	
	/*��ʱ��14��APB1�ϣ�2��Ƶ����84MHZ������Ľṹ����TIM_Prescaler��Ԥ��Ƶֵ����
	TIM_Period������ֵ������ؼ��ģ�84MHZ����8400��Ƶ�󣬳���1KHZ��
	1HZ����˼����1s�ڵ�Ƶ��Ϊ1��1/f=t�����ھ���ʱ�䡣Ҳ����˵��1/1HZ��Ӧ
	1s����ô1/1000HZ=1ms����ô���ھ��Ǽ�����ÿ��һ�������͹���1ms�����Խ���������ֵ
	���ó�100���͹���100ms���˴���Ҫ��ʱ100ms������������Ƚϵ�һ������*/
	TIM_TimeBaseStructure.TIM_Prescaler			=	84000 - 1;
	TIM_TimeBaseStructure.TIM_Period			=	100 -  1;
	TIM_TimeBaseStructure.TIM_CounterMode		=	TIM_CounterMode_Up;
	TIM_TimeBaseInit(TIM4, &TIM_TimeBaseStructure);
	
	/* Output Compare Toggle Mode configuration: Channel1 */
    TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM1;//ѡ��PWM1ģʽ��
    TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable;
    TIM_OCInitStructure.TIM_Pulse = 30;
    TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_Low;
    TIM_OC1Init(TIM4, &TIM_OCInitStructure);

	/*Enables or disables the TIMx peripheral Preload register on CCR2.
	ʹ�ܻ���ʧ��TIMx�������ڼĴ�����CCR2�ϣ����������岨ʱ�����������ǿ��ʹ�õ�*/
	TIM_OC2PreloadConfig(TIM4, TIM_OCPreload_Disable);
	
	TIM_Cmd(TIM4, ENABLE);//ʹ�ܶ�ʱ��
}
