/****************************************************************
*名    称:LVGL8.3测试程序（1.69英寸屏）
*作    者:粤嵌.温工
*创建日期:2024/5/14
*知 识 点:
	1.硬件SPI+DMA方式驱动tft屏显示
	2.支持触摸控制
	
*说  明:
	1.显示驱动芯片为ST7796S
	2.触摸驱动芯片为CST816T
	3.使能了DMA，代码优化等级只能为-O0
	
*注  意:
	1.lv_conf.h
	（1）使用DMA时注意16位色高低字节交换，设置宏 LV_COLOR_16_SWAP 1
	（2）颜色深度为16色，设置宏 LV_COLOR_DEPTH 16
	（3）LVGL内存大小48Kbytes，设置宏LV_MEM_SIZE (48 * 1024U)
	（4）帧率，设置 LV_DISP_DEF_REFR_PERIOD
	（5）触摸灵敏度，设置 LV_INDEV_DEF_READ_PERIOD
	（6）实时显示帧率，设置 LV_USE_PERF_MONITOR 1
	（7）默认字体，设置 LV_FONT_DEFAULT &lv_font_montserrat_14
	     字体小点，代码体积随之减小
	（8）由于触摸 IC 就会每隔 10ms 左右拉一次中断，主控根据中断读取实时坐标
	     LV_INDEV_DEF_READ_PERIOD 值需设置为10，即10ms轮询一次触摸IC事件，避免丢失坐标值
*****************************************************************/


#include "includes.h"

GPIO_InitTypeDef GPIO_InitStructure;
NVIC_InitTypeDef NVIC_InitStructure;
SPI_InitTypeDef SPI_InitStructure;


void tim3_init(void);

// 主函数
int main(void)
{
	uint32_t i=0;
	uint16_t tp_x,tp_y;
	
	// led初始化
	led_init();

	// beep初始化
	beep_init();
		
	
	// key初始化
	key_init();
	
	
	// 串口1初始化波特率为115200bps
	usart1_init(115200);

	// 串口延迟一会，确保芯片内部完成全部初始化,printf无乱码输出
	delay_ms(1000);

	printf("\r\n This is tft test with ST7796S and LVGL by Teacher.Wen\r\n");
	
	// 初始化lvgl
	lv_init();
	
	// 初始化lvgl显示设备
	lv_port_disp_init();

	// 初始化lvgl输入设备
	lv_port_indev_init();

	// 初始化lvgl demo
//	lv_demo_widgets();

	ui_init();
	//lv_demo_benchmark();	
	

	// tim3初始化，定时周期为1ms
	tim3_init();


	
	while (1)
	{

		lv_task_handler();

	}
	

	return 0;
}
