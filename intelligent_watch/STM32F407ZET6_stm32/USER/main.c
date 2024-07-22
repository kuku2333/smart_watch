/**
   ******************************************************************************
   * @file    STM32F407ZET6_stm32\USER\main.c 
   * @author  xzdtx2333@outlook.com
   * @version V1.0.0
   * @date    2024-07-19
   * @brief   
   ******************************************************************************
   * 
   ******************************************************************************
**/

#include "stm32f4xx.h"                  // Device header
#include "includes.h"

GPIO_InitTypeDef 		GPIO_InitStructure;
NVIC_InitTypeDef 		NVIC_InitStructure;
SPI_InitTypeDef 		SPI_InitStructure;

//RTC_TimeTypeDef  	RTC_TimeStructure;
//RTC_InitTypeDef  	RTC_InitStructure;
//RTC_DateTypeDef 	RTC_DateStructure;

//__IO uint32_t 		RTCTimeDisplay = 0;

//static void timer_cb(lv_timer_t *timer)
//{	
//	char buf[16] = {0};
//	
//	uint8_t hour;
//	
//	RTC_GetTime(RTC_Format_BIN, &RTC_TimeStructure);
//	
//	hour = RTC_TimeStructure.RTC_Hours;
//	
//	lv_arc_set_value(ui_uiArcTimechina, RTC_TimeStructure.RTC_Hours);
//	
//	sprintf(buf, "%02d:%02d", hour, RTC_TimeStructure.RTC_Minutes);
//	lv_label_set_text(ui_uiLabelTimeChina, buf);
//}

TaskHandle_t Task1_Handle = NULL;  //���ڴ洢������������
TaskHandle_t Task2_Handle = NULL;  //���ڴ洢������������

//����Ľӿ�
void task1(void *arg)
{
	printf("task1 is create success!\r\n");
	
	for(;;)
	{
		
		 printf("task1 is running!\r\n");
		 
	}

}
//����Ľӿ�
void task2(void *arg)
{
	
	printf("task2 is create success!\r\n");
	
	for(;;)
	{
		 
		 //P����   ���û�л�ȡ����һֱ����
		 
		 
		 printf("task2 is running!\r\n");
		
	}

}

int main(void)
{
//	Uasrt1_Init();
//	
//	// ��ʼ��lvgl
//	lv_init();
//	
//	// ��ʼ��lvgl��ʾ�豸
//	lv_port_disp_init();
//	
//	// ��ʼ��lvgl�����豸
//	lv_port_indev_init();

//	// ��ʼ��lvgl demo
//	lv_demo_widgets();
//	
////	ui_init();
//	
//	// tim3��ʼ������ʱ����Ϊ1ms
//	tim3_init();
//	
////	tp_init();
//	
//	while(1)
//	{
//		lv_task_handler();
//		Delay_ms(5);
//	}


//FreeRTOS test
	BaseType_t xReturned;
	Uasrt1_Init();
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_4);
	
	xReturned = xTaskCreate(
								task1,       				//����ĵ�ַ
								"task1",     				//���������
								128,      					//����Ķ�ջ��С  128 * 32 / 8 = 512�ֽ�
								NULL,    						//����ӿڵĲ��������贫������NULL
								1,									//��������ȼ�    ��Χ 0 ~ configMAX_PRIORITIES - 1
								&Task1_Handle 			//����ľ������Ϊ���ṩ����������ʹ�õ�
													);
	
	xReturned = xTaskCreate(
								task2,       				//����ĵ�ַ
								"task2",     				//���������
								128,      					//����Ķ�ջ��С  128 * 32 / 8 = 512�ֽ�
								NULL,    						//����ӿڵĲ��������贫������NULL
								2,									//��������ȼ�    ��Χ 0 ~ configMAX_PRIORITIES - 1
								&Task2_Handle 			//����ľ������Ϊ���ṩ����������ʹ�õ�
													);
													
	if( xReturned != pdPASS )
	{

	}

	//4.����������
	vTaskStartScheduler();
	
	while(1)
	{
		
	}
}
