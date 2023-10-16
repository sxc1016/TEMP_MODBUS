#ifndef __DELAY_H  
#define __DELAY_H  
  
#include "stm32f10x.h"

#define FLAG_TIMEOUT       				  ((uint32_t)0x1000)
#define LONG_TIMEOUT        			  ((uint32_t)(10 * SPIT_FLAG_TIMEOUT))

void delay_us(uint32_t nTimer);
void delay_ms(uint32_t nTimer);


#endif

