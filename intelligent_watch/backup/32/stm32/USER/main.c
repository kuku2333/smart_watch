/****************************************************************
*名    称:触屏测试程序（1.69英寸屏）
*作    者:粤嵌.温工
*创建日期:2024/1/17
*知 识 点:
	1.硬件SPI方式驱动tft屏显示
	2.支持触摸控制
		.宏TP_PIN_DEF决定了触摸引脚不同的连接方式，测试代码前务必了解该宏
*说  明:
	1.显示的驱动芯片为ST7789V
	2.触摸的驱动芯片为CST816T
	3.滑动屏幕凳毕允咀曛涤朊璧�
*注  意:
*****************************************************************/
#include "includes.h"

GPIO_InitTypeDef GPIO_InitStructure;
NVIC_InitTypeDef NVIC_InitStructure;
SPI_InitTypeDef SPI_InitStructure;

RTC_TimeTypeDef  	RTC_TimeStructure;
RTC_InitTypeDef  	RTC_InitStructure;
RTC_DateTypeDef 	RTC_DateStructure;

static void timer_cb(lv_timer_t *timer)
{	
	char buf[16] = {0};
	
	uint8_t hour;
	
	RTC_GetDate(RTC_Format_BIN, &RTC_TimeStructure);
	
	hour = RTC_TimeStructure.RTC_Hours;
	
	lv_arc_set_value(ui_ArcTimechina, RTC_TimeStructure.RTC_Hours;);
	
	sprintf(buf, "%02d:%02d", huour, RTC_TimeStructure.RTC_Minutes);
	lv_label_set_text(ui_LabelTimeChina, buf);
}

// 主函数
int main(void)
{
	RTC_Calendar_Init();
	
	lv_init();
	
	lv_port_disp_init();
	
	lv_port_indev_init();
	
	// lv_demo_widgets();
	
	ui_init();
	
	tim3_init();
	
	lv_timer_create(timer_cb, 1000, NULL);
	
	//tp_init();
	
	/* 显示标题 */
	//lcd_show_string(30,140,"TP Test By Teacher.Wen",RED,WHITE,16,0);
	
	while (1)
	{
		lv_task_handler();
		delay_ms(5);
	}
	return 0;
}
