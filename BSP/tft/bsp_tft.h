#ifndef __BSP_TFT_H
#define __BSP_TFT_H

#include "stm32f10x.h"
//颜色控制相关宏
#define RED  	0xf800
#define GREEN	0x07e0
#define BLUE 	0x001f
#define WHITE	0xffff
#define BLACK	0x0000
#define PURPLE	0xf23e
#define YELLOW	0xFFE0

#define	TFT_SCL_PORT							GPIOB
#define	TFT_SDA_PORT							GPIOB
#define	TFT_CS_PORT					 			GPIOB
#define	TFT_CS_PIN								GPIO_Pin_12
#define	TFT_SCL_PIN								GPIO_Pin_13
#define	TFT_SDA_PIN								GPIO_Pin_15

#define TFT_SPI									SPI2
//液晶屏信号发送语句
#define	TFT_SDA_HIGH							GPIO_SetBits(TFT_SDA_PORT, TFT_SDA_PIN)
#define TFT_SDA_LOW			 					GPIO_ResetBits(TFT_SDA_PORT, TFT_SDA_PIN)
#define	TFT_SCL_HIGH							GPIO_SetBits(TFT_SCL_PORT, TFT_SCL_PIN)
#define TFT_SCL_LOW			 					GPIO_ResetBits(TFT_SCL_PORT, TFT_SCL_PIN)
#define	TFT_CS_HIGH								GPIO_SetBits(TFT_CS_PORT, TFT_CS_PIN)
#define TFT_CS_LOW			 					GPIO_ResetBits(TFT_CS_PORT, TFT_CS_PIN)

//液晶屏控制相关引脚
#define	TFT_RES_PORT							GPIOB
#define	TFT_DC_PORT								GPIOB
#define	TFT_BLK_PORT							GPIOB

#define	TFT_RES_PIN								GPIO_Pin_0
#define TFT_DC_PIN								GPIO_Pin_1
#define	TFT_BLK_PIN								GPIO_Pin_11
//液晶屏控制语句
#define	TFT_DC_HIGH								GPIO_SetBits(TFT_DC_PORT, TFT_DC_PIN)
#define TFT_DC_LOW			 					GPIO_ResetBits(TFT_DC_PORT, TFT_DC_PIN)
#define	TFT_RES_HIGH							GPIO_SetBits(TFT_RES_PORT, TFT_RES_PIN)
#define TFT_RES_LOW			 					GPIO_ResetBits(TFT_RES_PORT, TFT_RES_PIN)
#define TFT_BLK_HIGH							GPIO_SetBits(TFT_BLK_PORT, TFT_BLK_PIN)
#define TFT_BLK_LOW								GPIO_ResetBits(TFT_BLK_PORT, TFT_BLK_PIN)


#define NOP										0X00
#define	TST_Reset								0x01		//重启
#define SLEEP_IN								0X10		//睡眠
#define SLEEP_OUT								0X11		//唤醒睡眠
#define	Normal_Display_Mode_On 			  		0x0b  		//正常显示
#define Display_Off								0X28		//显示开
#define Display_ON								0X29		//显示关

#define X_MAX									128
#define Y_MAX									128
#define X_CLEAR									81
#define Y_CLEAR									86


void Lcd_Init(void);
void TFT_GPIO_Init_Config(void);
void TFT_SPI_Init_Config(void);
void TFT_Send_Byte(uint8_t Data);
void TFT_Send_HalfWord(uint16_t Data);
void TFT_Send_Cmd(uint8_t Cmd);
void TFT_SPI_SendByte(uint8_t Data);

void TFT_Draw(uint16_t X,uint16_t Y,uint8_t Width,uint8_t Length, uint8_t* Data,uint16_t Color_Data);
void TFT_SET_START_END(uint16_t XS,uint16_t YS,uint16_t XE,uint16_t YE);
void TFT_Draw_Dot(uint16_t x,uint16_t y,uint16_t Color_Data);
void TFT_Draw_8_16(uint16_t X,uint16_t Y, uint8_t* Data,uint16_t Color_Data);
void TFT_Draw_16_16(uint16_t X,uint16_t Y, uint8_t* Data,uint16_t Color_Data);
void TFT_SET_Image(uint16_t XS,uint16_t YS,uint16_t XE,uint16_t YE, uint8_t* Data);
void Lcd_Reset(void);
void TFT_Display_All(uint16_t Color_Data);

#endif

