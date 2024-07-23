#ifndef __DELAY_H
#define __DELAY_H

#include "stm32f4xx.h"                  // Device header

#define 	RTOS_DELAY 		1

void Delay_ms(uint32_t xms);
void Delay_us(uint32_t xus);
void Delay_s(uint32_t ns);

#endif
