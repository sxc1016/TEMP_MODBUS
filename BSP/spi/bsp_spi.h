#ifndef __BSP_SPI_H
#define __BSP_SPI_H

#include "stm32f10x.h"

#define SPI1_NSS_Pin  	 													GPIO_Pin_4
#define SPI1_CLK_Pin   	 													GPIO_Pin_5
#define SPI1_MISO_Pin  	 													GPIO_Pin_6
#define SPI1_MOSI_Pin  	 													GPIO_Pin_7
#define SPI1_GPIO_PORT	 													GPIOA

#define SPIT_FLAG_TIMEOUT         ((uint32_t)0x1000)
#define SPIT_LONG_TIMEOUT         ((uint32_t)(10 * SPIT_FLAG_TIMEOUT))

#define SPI_NSS_HIGH 															GPIO_SetBits(SPI1_GPIO_PORT, SPI1_NSS_Pin)
#define SPI_NSS_LOW			 													GPIO_ResetBits(SPI1_GPIO_PORT, SPI1_NSS_Pin)


uint8_t SPI_ReadByte(SPI_TypeDef* SPI_X);
void SPI_Init_Config(void);
uint8_t SPI_SendByte(SPI_TypeDef* SPI_X,uint8_t Data);



#endif
