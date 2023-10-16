#ifndef __BSP_KEY_H
#define	__BSP_KEY_H

#include "stm32f10x.h"


//定义拨码开关的引脚
#define MB_Addr_1_Port			GPIOB
#define MB_Addr_1_Pin			GPIO_Pin_10
#define MB_Addr_2_Port			GPIOB
#define MB_Addr_2_Pin			GPIO_Pin_9
#define MB_Addr_4_Port			GPIOB
#define MB_Addr_4_Pin			GPIO_Pin_8
#define MB_Addr_8_Port			GPIOB
#define MB_Addr_8_Pin			GPIO_Pin_7
#define MB_Addr_16_Port			GPIOB
#define MB_Addr_16_Pin			GPIO_Pin_6
#define MB_Addr_32_Port			GPIOB
#define MB_Addr_32_Pin			GPIO_Pin_5
#define MB_Addr_64_Port			GPIOB
#define MB_Addr_64_Pin			GPIO_Pin_4
#define MB_Addr_128_Port		GPIOB	
#define MB_Addr_128_Pin			GPIO_Pin_3


uint8_t Set_MB_CH_Addr(void);//要把从机地址和本从机三个通道的地址存放的位置。
	

#endif /* __BSP_KEY_H */
