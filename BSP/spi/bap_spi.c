#include "bsp_spi.h"
#include "delay.h"
#include<stdio.h>



void SPI_Init_Config(void)
{
	SPI_InitTypeDef SPI_InitStruct;
	GPIO_InitTypeDef GPIO_InitStruct;	
	//开时钟
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_SPI1,ENABLE);
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA,ENABLE);
	
	//初始化GPIO,CLK
  GPIO_InitStruct.GPIO_Mode	= GPIO_Mode_AF_PP;
	GPIO_InitStruct.GPIO_Pin	= SPI1_CLK_Pin ;
	GPIO_InitStruct.GPIO_Speed= GPIO_Speed_50MHz;
	
	GPIO_Init(SPI1_GPIO_PORT, &GPIO_InitStruct);
	//初始化GPIO,MOSI
  GPIO_InitStruct.GPIO_Mode	= GPIO_Mode_AF_PP;
	GPIO_InitStruct.GPIO_Pin	= SPI1_MOSI_Pin ;
	GPIO_InitStruct.GPIO_Speed= GPIO_Speed_50MHz;
	
	GPIO_Init(SPI1_GPIO_PORT, &GPIO_InitStruct);
	//初始化GPIO,MISO
	GPIO_InitStruct.GPIO_Mode	= GPIO_Mode_AF_PP;
	GPIO_InitStruct.GPIO_Pin	= SPI1_MISO_Pin;
	GPIO_InitStruct.GPIO_Speed= GPIO_Speed_50MHz;
	
	GPIO_Init(SPI1_GPIO_PORT, &GPIO_InitStruct);
	//初始化NSS
	GPIO_InitStruct.GPIO_Mode	= GPIO_Mode_Out_PP;
	GPIO_InitStruct.GPIO_Pin	= SPI1_NSS_Pin;
	GPIO_InitStruct.GPIO_Speed= GPIO_Speed_50MHz;
	
	GPIO_Init(SPI1_GPIO_PORT, &GPIO_InitStruct);
	
	//初始化SPI结构体
	SPI_InitStruct.SPI_BaudRatePrescaler	=	SPI_BaudRatePrescaler_4;
	SPI_InitStruct.SPI_CPOL		=		SPI_CPOL_Low;
	SPI_InitStruct.SPI_CPHA		=   SPI_CPHA_1Edge;														//空闲时为低电平
	SPI_InitStruct.SPI_CRCPolynomial	=	7;
	SPI_InitStruct.SPI_DataSize	=	SPI_DataSize_8b;		
	SPI_InitStruct.SPI_Direction	=	SPI_Direction_2Lines_FullDuplex;		//全双工
	SPI_InitStruct.SPI_FirstBit	=	SPI_FirstBit_MSB;
	SPI_InitStruct.SPI_Mode	= SPI_Mode_Master;
	SPI_InitStruct.SPI_NSS	=	SPI_NSS_Soft;
	
	SPI_Init(SPI1, &SPI_InitStruct);
	//开SPI使能
	SPI_Cmd(SPI1, ENABLE);
}


uint8_t SPI_SendByte(SPI_TypeDef * SPI_X,uint8_t Data)
{
	uint8_t ReceiveData;
	uint32_t SPI_Time_Out = SPIT_FLAG_TIMEOUT;
	//等待发送寄存器为空
	while( SPI_I2S_GetFlagStatus(SPI_X, SPI_I2S_FLAG_TXE) == RESET )
	{
		if( (SPI_Time_Out) == 0)
		{
			printf("SPI等待超时");
			return 0;
		}
		SPI_Time_Out--;
	}
	//发送数据
	SPI_I2S_SendData(SPI_X,Data);
	
	//等待接收，检测接收寄存器是否为空
	SPI_Time_Out = SPIT_FLAG_TIMEOUT;
	while( SPI_I2S_GetFlagStatus(SPI_X,SPI_I2S_FLAG_RXNE) == RESET )
	{
		if( (SPI_Time_Out) == 0)
		{
			printf("SPI等待超时");
			return 0;
		}
		SPI_Time_Out--;
	}
	ReceiveData = SPI_I2S_ReceiveData(SPI_X);
	//将接收的数据再发送出去
	return ReceiveData;	
}

//读取一个字节
uint8_t SPI_ReadByte(SPI_TypeDef* SPI_X)
{
	return SPI_SendByte(SPI_X,0X00);
}



