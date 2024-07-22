#include "Tim.h"

/**
  * @brief �ö�ʱ��������岨
  *
  * @steps 1.������ʱ���Ͷ�Ӧ���ŵ�ʱ��
  *		   2.���ö�ʱ����Ӧ�����ŵĽṹ�壬TIM14��Ӧ������ΪPF9
  *		   3.�ı����ŵ�ӳ��
  *		   3.���ö�ʱ��ʱ���ṹ�岢��ʼ��
  *		   4.���ö�ʱ������ȽϽṹ�岢��ʼ��
  *		   5.ʹ���������TIM_OCxPreloadConfig(TIMx, TIM_OCPreload_ENABLE);
  *		   6.ʹ�ܶ�ʱ��
  */
void Tim14_Init()
{
	//����ʱ����GPIO������ȽϽṹ��
	TIM_TimeBaseInitTypeDef		TIM_TimeBaseStructure;
	GPIO_InitTypeDef			GPIO_InitStructure;
	TIM_OCInitTypeDef  			TIM_OCInitStructure;

	//������ʱ����GPIO��ʱ��
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM14, ENABLE);//����TIM14��ʱ�ӣ���APB1��
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOF, ENABLE);
	
	/* GPIOF ����: TIM14 CH1 (PF9)*/
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_9;//����9
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;//����ģʽ
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;
    GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
    GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;
    GPIO_Init(GPIOF, &GPIO_InitStructure);//��ʼ��
	
	GPIO_PinAFConfig(GPIOF, GPIO_PinSource9, GPIO_AF_TIM14);//����ӳ�䵽��ʱ��
	
	/*��ʱ��14��APB1�ϣ�2��Ƶ����84MHZ������Ľṹ����TIM_Prescaler��Ԥ��Ƶֵ����
	TIM_Period������ֵ������ؼ��ģ�84MHZ����8400��Ƶ�󣬳���1KHZ��
	1HZ����˼����1s�ڵ�Ƶ��Ϊ1��1/f=t�����ھ���ʱ�䡣Ҳ����˵��1/1HZ��Ӧ
	1s����ô1/1000HZ=1ms����ô���ھ��Ǽ�����ÿ��һ�������͹���1ms�����Խ���������ֵ
	���ó�100���͹���100ms���˴���Ҫ��ʱ100ms������������Ƚϵ�һ������*/
	TIM_TimeBaseStructure.TIM_Prescaler			=	84000 - 1;
	TIM_TimeBaseStructure.TIM_Period			=	100 -  1;
	TIM_TimeBaseStructure.TIM_CounterMode		=	TIM_CounterMode_Up;
	TIM_TimeBaseInit(TIM14, &TIM_TimeBaseStructure);
	
	/* Output Compare Toggle Mode configuration: Channel1 */
    TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM1;//ѡ��PWM1ģʽ��
    TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable;
    TIM_OCInitStructure.TIM_Pulse = 30;
    TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_Low;
    TIM_OC1Init(TIM14, &TIM_OCInitStructure);

	/*Enables or disables the TIMx peripheral Preload register on CCR2.
	ʹ�ܻ���ʧ��TIMx�������ڼĴ�����CCR2�ϣ����������岨ʱ�����������ǿ��ʹ�õ�*/
	TIM_OC2PreloadConfig(TIM14, TIM_OCPreload_Disable);
	
	TIM_Cmd(TIM14, ENABLE);//ʹ�ܶ�ʱ��
}


/**
  * @brief �ö�ʱ��14������岨
  *
  * @steps 1.������ʱ��14��ʱ��
  *		   2.���ö�ʱ��14��Ӧ�����ţ�����ΪPF9
  *		   3.���ö�ʱ��14�Ľṹ�岢��ʼ��
  *		   4.���ö�ʱ��14������ȽϵĽṹ�岢��ʼ��
  *		   5.ʹ���������TIM_OCxPreloadConfig(TIMx, TIM_OCPreload_ENABLE);
  *		   6.ʹ�ܶ�ʱ��14
  */
void Tim13_Init()
{
	TIM_TimeBaseInitTypeDef		TIM_TimeBaseStructure;
	GPIO_InitTypeDef			GPIO_InitStructure;
	TIM_OCInitTypeDef  			TIM_OCInitStructure;

	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM13, ENABLE);//����TIM14��ʱ�ӣ���APB1��
	RCC_AHB1PeriphClockCmd( RCC_AHB1Periph_GPIOF, ENABLE);
	
	/* GPIOF ����: TIM14 CH1 (PF9)*/
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_8;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;
    GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
    GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;
    GPIO_Init(GPIOF, &GPIO_InitStructure);
	
	GPIO_PinAFConfig(GPIOF, GPIO_PinSource8, GPIO_AF_TIM13);
	
	TIM_TimeBaseStructure.TIM_Prescaler			=	84000 - 1;//
	TIM_TimeBaseStructure.TIM_Period			=	100 -  1;
	TIM_TimeBaseStructure.TIM_CounterMode		=	TIM_CounterMode_Up;
	TIM_TimeBaseInit(TIM13, &TIM_TimeBaseStructure);
	
	/* Output Compare Toggle Mode configuration: Channel1 */
    TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM1;
    TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable;
    TIM_OCInitStructure.TIM_Pulse = 30;
    TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_Low;
    TIM_OC1Init(TIM13, &TIM_OCInitStructure);

	TIM_OC2PreloadConfig(TIM13, TIM_OCPreload_Disable);
	
	TIM_Cmd(TIM13, ENABLE);
}
