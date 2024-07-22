/****************************************************************
*Ãû    ³Æ:´¥ÆÁ²âÊÔ³ÌĞò£¨1.69Ó¢´çÆÁ£©
*×÷    Õß:ÔÁÇ¶.ÎÂ¹¤
*´´½¨ÈÕÆÚ:2024/1/17
*Öª Ê¶ µã:
	1.Ó²¼şSPI·½Ê½Çı¶¯tftÆÁÏÔÊ¾
	2.Ö§³Ö´¥Ãş¿ØÖÆ
		.ºêTP_PIN_DEF¾ö¶¨ÁË´¥ÃşÒı½Å²»Í¬µÄÁ¬½Ó·½Ê½£¬²âÊÔ´úÂëÇ°Îñ±ØÁË½â¸Ãºê
*Ëµ  Ã÷:
	1.ÏÔÊ¾µÄÇı¶¯Ğ¾Æ¬ÎªST7789V
	2.´¥ÃşµÄÇı¶¯Ğ¾Æ¬ÎªCST816T
	3.»¬¶¯ÆÁÄ»µÊ±ÏÔÊ¾×ø±êÖµÓëÃèµã
*×¢  Òâ:
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

// Ö÷º¯Êı
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
	
	/* ÏÔÊ¾±êÌâ */
	//lcd_show_string(30,140,"TP Test By Teacher.Wen",RED,WHITE,16,0);
	
	while (1)
	{
		lv_task_handler();
		delay_ms(5);
	}
	return 0;
}
