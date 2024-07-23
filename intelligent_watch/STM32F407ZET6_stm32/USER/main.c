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

TaskHandle_t Init_Periph_Task_Handle = NULL;  //用于存储创建的任务句柄
TaskHandle_t LVGL_Run_Handle = NULL;  //用于存储创建的任务句柄

//任务的接口
void LVGL_Run(void *arg)
{
	printf("lvgl run is create success!\r\n");
	
	for(;;)
	{
		lv_task_handler();
		Delay_ms(5);
	}

}
//任务的接口
void Init_Periph_Task(void *arg)
{
	printf("initial peripheral task is create success!\r\n");
	
	Uasrt1_Init();
	
	Uasrt2_Init();
	
	RTC_Calendar_Init();
	
	Delay_ms(1000);
	
	// 初始化lvgl
	lv_init();
	
	// 初始化lvgl显示设备
	lv_port_disp_init();
	
	// 初始化lvgl输入设备
	lv_port_indev_init();

	// 初始化lvgl demo
//	lv_demo_widgets();
	
	ui_init();
	
	// tim3初始化，定时周期为1ms
	tim3_init();
	
	lv_timer_create(timer_cb, 1000, NULL);
	
	xTaskCreate(
								LVGL_Run,       				//任务的地址
								"LVGL",      				//任务的描述
								128,      					//任务的堆栈大小  128 * 32 / 8 = 512字节
								NULL,    						//任务接口的参数，无需传参则填NULL
								2,									//任务的优先级    范围 0 ~ configMAX_PRIORITIES - 1
								&LVGL_Run_Handle 			//任务的句柄，是为了提供给其他函数使用的
							);												
	
	vTaskDelete(NULL);
}

int main(void)
{
//	Uasrt1_Init();
//	Uasrt2_Init();
//	RTC_Calendar_Init();
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
////	lv_demo_widgets();
//	
//	ui_init();
//	
//	// tim3初始化，定时周期为1ms
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
								Init_Periph_Task,       				//任务的地址
								"外设初始化任务",     				//任务的描述
								512,      					//任务的堆栈大小  128 * 32 / 8 = 512字节
								NULL,    						//任务接口的参数，无需传参则填NULL
								5,									//任务的优先级    范围 0 ~ configMAX_PRIORITIES - 1
								&Init_Periph_Task_Handle 			//任务的句柄，是为了提供给其他函数使用的
							);
							
	if( xReturned != pdPASS )
	{
		printf("initial peripheral 任务创建失败\r\n");
		vTaskDelete( Init_Periph_Task_Handle );
	}
	
	//4.启动调度器
	vTaskStartScheduler();
	
//	while(1)
//	{
//		
//	}
}
