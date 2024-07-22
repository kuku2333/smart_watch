/****************************************************************
*��    ��:�������Գ���1.69Ӣ������
*��    ��:��Ƕ.�¹�
*��������:2024/1/17
*֪ ʶ ��:
	1.Ӳ��SPI��ʽ����tft����ʾ
	2.֧�ִ�������
		.��TP_PIN_DEF�����˴������Ų�ͬ�����ӷ�ʽ�����Դ���ǰ����˽�ú�
*˵  ��:
	1.��ʾ������оƬΪST7789V
	2.����������оƬΪCST816T
	3.������Ļ�ʱ��ʾ����ֵ�����
*ע  ��:
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

// ������
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
	
	/* ��ʾ���� */
	//lcd_show_string(30,140,"TP Test By Teacher.Wen",RED,WHITE,16,0);
	
	while (1)
	{
		lv_task_handler();
		delay_ms(5);
	}
	return 0;
}
