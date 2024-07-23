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

#include "includes.h"

GPIO_InitTypeDef 		GPIO_InitStructure;
NVIC_InitTypeDef 		NVIC_InitStructure;
SPI_InitTypeDef 		SPI_InitStructure;

RTC_TimeTypeDef  		RTC_TimeStructure;
RTC_InitTypeDef  		RTC_InitStructure;
RTC_DateTypeDef 		RTC_DateStructure;

__IO 	uint32_t 		RTCTimeDisplay = 0;

static void timer_cb(lv_timer_t *timer)
{	
	char buf[16] = {0};
	
	uint8_t hours, minutes, seconds;
	
	RTC_GetTime(RTC_Format_BIN, &RTC_TimeStructure);
	
	seconds = RTC_TimeStructure.RTC_Seconds;
	
	minutes = RTC_TimeStructure.RTC_Minutes;
	
	hours = RTC_TimeStructure.RTC_Hours;
	
	lv_arc_set_value(ui_ArcTimeSeconds, seconds);
	
	sprintf(buf, "%02d:%02d:%02d", hours, minutes, seconds);
	lv_label_set_text(ui_LabelTimes, buf);
}

TaskHandle_t Init_Periph_Task_Handle = NULL;  //���ڴ洢������������
TaskHandle_t LVGL_Run_Handle = NULL;  //���ڴ洢������������

//����Ľӿ�
void LVGL_Run(void *arg)
{
	printf("lvgl run is create success!\r\n");
	
	for(;;)
	{
		lv_task_handler();
		Delay_ms(5);
	}

}
//����Ľӿ�
void Init_Periph_Task(void *arg)
{
	printf("initial peripheral task is create success!\r\n");
	
	Uasrt1_Init();
	
	Uasrt2_Init();
	
	RTC_Calendar_Init();
	
	Delay_ms(1000);
	
	// ��ʼ��lvgl
	lv_init();
	
	// ��ʼ��lvgl��ʾ�豸
	lv_port_disp_init();
	
	// ��ʼ��lvgl�����豸
	lv_port_indev_init();

	// ��ʼ��lvgl demo
//	lv_demo_widgets();
	
	ui_init();
	
	// tim3��ʼ������ʱ����Ϊ1ms
	tim3_init();
	
	lv_timer_create(timer_cb, 1000, NULL);
	
	xTaskCreate(
								LVGL_Run,       				//����ĵ�ַ
								"LVGL",      				//���������
								128,      					//����Ķ�ջ��С  128 * 32 / 8 = 512�ֽ�
								NULL,    						//����ӿڵĲ��������贫������NULL
								2,									//��������ȼ�    ��Χ 0 ~ configMAX_PRIORITIES - 1
								&LVGL_Run_Handle 			//����ľ������Ϊ���ṩ����������ʹ�õ�
							);												
	
	vTaskDelete(NULL);
}

int main(void)
{
//	Uasrt1_Init();
//	Uasrt2_Init();
//	RTC_Calendar_Init();
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
////	lv_demo_widgets();
//	
//	ui_init();
//	
//	// tim3��ʼ������ʱ����Ϊ1ms
//	tim3_init();
//	
////	lv_timer_create(timer_cb, 1000, NULL);
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
								Init_Periph_Task,       				//����ĵ�ַ
								"�����ʼ������",     				//���������
								512,      					//����Ķ�ջ��С  128 * 32 / 8 = 512�ֽ�
								NULL,    						//����ӿڵĲ��������贫������NULL
								5,									//��������ȼ�    ��Χ 0 ~ configMAX_PRIORITIES - 1
								&Init_Periph_Task_Handle 			//����ľ������Ϊ���ṩ����������ʹ�õ�
							);
							
	if( xReturned != pdPASS )
	{
		printf("initial peripheral ���񴴽�ʧ��\r\n");
		vTaskDelete( Init_Periph_Task_Handle );
	}
	
	//4.����������
	vTaskStartScheduler();
	
//	while(1)
//	{
//		
//	}
}
