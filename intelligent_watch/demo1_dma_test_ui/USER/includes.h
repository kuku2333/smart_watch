/*×÷    Õß:ÔÁÇ¶.ÎÂ¹¤*/
#ifndef __INCLUDES_H__
#define __INCLUDES_H__

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdint.h>
#include "stm32f4xx.h"
#include "stm32f4xx_it.h"
#include "sys.h"
#include "usart.h"
#include "delay.h"
#include "led.h"
#include "beep.h"
#include "key.h"
#include "tim.h"
#include "tft.h"
#include "bmp.h"
#include "touch.h"  
#include "lvgl.h"
#include "lv_port_disp.h"
#include "lv_port_indev.h"
#include "lv_demo_widgets.h"
#include "ui.h"
#include "ui_helpers.h"
//#include "ui_events.h"

//#include "lv_demo_benchmark.h"


extern GPIO_InitTypeDef  	GPIO_InitStructure;
extern NVIC_InitTypeDef 	NVIC_InitStructure;		
extern SPI_InitTypeDef  	SPI_InitStructure;

extern lv_disp_drv_t *g_disp_drvp;  


#endif
