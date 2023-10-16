#ifndef __BSP_KEY_H
#define	__BSP_KEY_H

#include "stm32f10x.h"


//���岦�뿪�ص�����
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


uint8_t Set_MB_CH_Addr(void);//Ҫ�Ѵӻ���ַ�ͱ��ӻ�����ͨ���ĵ�ַ��ŵ�λ�á�
	

#endif /* __BSP_KEY_H */
