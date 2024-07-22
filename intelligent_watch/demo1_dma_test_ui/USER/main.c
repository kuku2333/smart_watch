/****************************************************************
*��    ��:LVGL8.3���Գ���1.69Ӣ������
*��    ��:��Ƕ.�¹�
*��������:2024/5/14
*֪ ʶ ��:
	1.Ӳ��SPI+DMA��ʽ����tft����ʾ
	2.֧�ִ�������
	
*˵  ��:
	1.��ʾ����оƬΪST7796S
	2.��������оƬΪCST816T
	3.ʹ����DMA�������Ż��ȼ�ֻ��Ϊ-O0
	
*ע  ��:
	1.lv_conf.h
	��1��ʹ��DMAʱע��16λɫ�ߵ��ֽڽ��������ú� LV_COLOR_16_SWAP 1
	��2����ɫ���Ϊ16ɫ�����ú� LV_COLOR_DEPTH 16
	��3��LVGL�ڴ��С48Kbytes�����ú�LV_MEM_SIZE (48 * 1024U)
	��4��֡�ʣ����� LV_DISP_DEF_REFR_PERIOD
	��5�����������ȣ����� LV_INDEV_DEF_READ_PERIOD
	��6��ʵʱ��ʾ֡�ʣ����� LV_USE_PERF_MONITOR 1
	��7��Ĭ�����壬���� LV_FONT_DEFAULT &lv_font_montserrat_14
	     ����С�㣬���������֮��С
	��8�����ڴ��� IC �ͻ�ÿ�� 10ms ������һ���жϣ����ظ����ж϶�ȡʵʱ����
	     LV_INDEV_DEF_READ_PERIOD ֵ������Ϊ10����10ms��ѯһ�δ���IC�¼������ⶪʧ����ֵ
*****************************************************************/


#include "includes.h"

GPIO_InitTypeDef GPIO_InitStructure;
NVIC_InitTypeDef NVIC_InitStructure;
SPI_InitTypeDef SPI_InitStructure;


void tim3_init(void);

// ������
int main(void)
{
	uint32_t i=0;
	uint16_t tp_x,tp_y;
	
	// led��ʼ��
	led_init();

	// beep��ʼ��
	beep_init();
		
	
	// key��ʼ��
	key_init();
	
	
	// ����1��ʼ��������Ϊ115200bps
	usart1_init(115200);

	// �����ӳ�һ�ᣬȷ��оƬ�ڲ����ȫ����ʼ��,printf���������
	delay_ms(1000);

	printf("\r\n This is tft test with ST7796S and LVGL by Teacher.Wen\r\n");
	
	// ��ʼ��lvgl
	lv_init();
	
	// ��ʼ��lvgl��ʾ�豸
	lv_port_disp_init();

	// ��ʼ��lvgl�����豸
	lv_port_indev_init();

	// ��ʼ��lvgl demo
//	lv_demo_widgets();

	ui_init();
	//lv_demo_benchmark();	
	

	// tim3��ʼ������ʱ����Ϊ1ms
	tim3_init();


	
	while (1)
	{

		lv_task_handler();

	}
	

	return 0;
}
