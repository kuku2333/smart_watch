/****************************************************************

*****************************************************************/
#include "includes.h"

GPIO_InitTypeDef 	GPIO_InitStructure;
NVIC_InitTypeDef 	NVIC_InitStructure;
SPI_InitTypeDef 	SPI_InitStructure;

RTC_TimeTypeDef  	RTC_TimeStructure;
RTC_InitTypeDef  	RTC_InitStructure;
RTC_DateTypeDef 	RTC_DateStructure;

__IO uint32_t 		RTCTimeDisplay = 0;

static void timer_cb(lv_timer_t *timer)
{	
	char buf[16] = {0};
	
	uint8_t hour;
	
	RTC_GetTime(RTC_Format_BIN, &RTC_TimeStructure);
	
	hour = RTC_TimeStructure.RTC_Hours;
	
	lv_arc_set_value(ui_Arc1, RTC_TimeStructure.RTC_Hours);
	
	sprintf(buf, "%02d:%02d", hour, RTC_TimeStructure.RTC_Minutes);
	lv_label_set_text(ui_Label1, buf);
}

// ������
int main(void)
{
	RTC_Calendar_Init();
	Uasrt1_Init();
	
	lv_init();
	
	lv_port_disp_init();
	
	lv_port_indev_init();
	
//	lv_demo_widgets();
	
	ui_init();
	
//	ui_init();
//	
	tim3_init();
//	
//	lv_timer_create(timer_cb, 1000, NULL);
	
	//tp_init();
	
	/* ��ʾ���� */
//	lcd_show_string(30,140,"TP Test By Teacher.Wen",RED,WHITE,16,0);
	
	while (1)
	{
		lv_task_handler();
		Delay_ms(5);
	}

//	Uasrt1_Init();
//	// ��ʼ��lvgl
//	lv_init();
//	
//	// ��ʼ��lvgl��ʾ�豸
//	lv_port_disp_init();
//	
//	// ��ʼ��lvgl�����豸
//	lv_port_indev_init();
//	
//	// ��ʼ��lvgl demo
//	lv_demo_widgets();
//	
//	// tim3��ʼ������ʱ����Ϊ1ms
//	tim3_init();
//	
//	while(1)
//	{
//		lv_task_handler();
//		Delay_ms(5);
//	}
}
