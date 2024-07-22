/**
   ******************************************************************************
   * @file    STM32F407ZET6_1.69��LCD\HARDWARE\touch.h 
   * @author  xzdtx2333@outlook.com
   * @version V1.0.0
   * @date    2024-07-19
   * @brief   
   ******************************************************************************
   * 	ʵ���봥��оƬ����ͨ�ţ�����tft���Ͻ��д������õ���IICЭ�飬ģ��IIC����ʱ
   *	�ü򵥵ĺ�����������ã������ٸ�Ϊͳһ�Ľӿڣ�����һ��IIC�ļ���
   *	SCL-->PD0,SDA-->PD14,RET-->PD4,IRQ-->PF12
   ******************************************************************************
**/

#ifndef __TOUCH_H
#define __TOUCH_H

#include "stm32f4xx.h"                  // Device header
#include "Delay.h"
#include "sys.h"

/*********************
 *	MACRO
 *********************/
 
#define TP_PIN_DEF_1 1
#define TP_PIN_DEF_2 2

#define TP_PIN_DEF   TP_PIN_DEF_2

#if TP_PIN_DEF == TP_PIN_DEF_1

 //�봥����оƬ��������	   
#define TP_SCL_W	PDout(0)
#define TP_SDA_W	PDout(14)
#define TP_SDA_R	PDin(14)
#define TP_RST		PDout(4)
#define TP_IRQ		PFin(12)

#endif 

#if TP_PIN_DEF == TP_PIN_DEF_2

//�봥����оƬ��������	   
#define TP_SCL_W	PDout(6)
#define TP_SDA_W	PDout(7)
#define TP_SDA_R	PDin(7)
#define TP_RST		PCout(6)
#define TP_IRQ		PCin(8)

#endif 

#define DELAY_TIME 	5

#define IIC_TIME_QU 1
/*********************
 *	MACRO
 *********************/

/*********************
 *	GLOBAL VALUE
 *********************/

extern uint16_t g_tp_x,g_tp_y;
extern volatile uint32_t g_tp_event;

//extern uint32_t g_lcd_width;
//extern uint32_t g_lcd_height;
//extern uint32_t g_lcd_direction;

/*********************
 *	GLOBAL VALUE
 *********************/

/*********************
 *	FUNCTION
 *********************/
 
extern void tp_init(void);

extern uint8_t tp_read_xy(uint16_t *x,uint16_t *y);
extern uint8_t tp_read(uint16_t *screen_x,uint16_t *screen_y);
extern void tp_send_byte(uint8_t addr,uint8_t* data); 	
extern void tp_recv_byte(uint8_t addr,uint8_t* data);

 /*********************
 *	FUNCTION
 *********************/
#endif
