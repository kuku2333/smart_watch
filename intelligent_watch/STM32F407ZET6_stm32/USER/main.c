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

TaskHandle_t Task1_Handle = NULL;  //用于存储创建的任务句柄
TaskHandle_t Task2_Handle = NULL;  //用于存储创建的任务句柄

//任务的接口
void task1(void *arg)
{
	printf("task1 is create success!\r\n");
	
	for(;;)
	{
		
		 printf("task1 is running!\r\n");
		 
	}

}
//任务的接口
void task2(void *arg)
{
	
	printf("task2 is create success!\r\n");
	
	for(;;)
	{
		 
		 //P操作   如果没有获取到则一直阻塞
		 
		 
		 printf("task2 is running!\r\n");
		
	}

}

int main(void)
{
//	Uasrt1_Init();
//	
//	// 初始化lvgl
//	lv_init();
//	
//	// 初始化lvgl显示设备
//	lv_port_disp_init();
//	
//	// 初始化lvgl输入设备
//	lv_port_indev_init();

//	// 初始化lvgl demo
//	lv_demo_widgets();
//	
////	ui_init();
//	
//	// tim3初始化，定时周期为1ms
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
								task1,       				//任务的地址
								"task1",     				//任务的描述
								128,      					//任务的堆栈大小  128 * 32 / 8 = 512字节
								NULL,    						//任务接口的参数，无需传参则填NULL
								1,									//任务的优先级    范围 0 ~ configMAX_PRIORITIES - 1
								&Task1_Handle 			//任务的句柄，是为了提供给其他函数使用的
													);
	
	xReturned = xTaskCreate(
								task2,       				//任务的地址
								"task2",     				//任务的描述
								128,      					//任务的堆栈大小  128 * 32 / 8 = 512字节
								NULL,    						//任务接口的参数，无需传参则填NULL
								2,									//任务的优先级    范围 0 ~ configMAX_PRIORITIES - 1
								&Task2_Handle 			//任务的句柄，是为了提供给其他函数使用的
													);
													
	if( xReturned != pdPASS )
	{

	}

	//4.启动调度器
	vTaskStartScheduler();
	
	while(1)
	{
		
	}
}
