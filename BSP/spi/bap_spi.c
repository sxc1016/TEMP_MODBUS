#include "bsp_spi.h"
#include "delay.h"
#include<stdio.h>



void SPI_Init_Config(void)
{
	SPI_InitTypeDef SPI_InitStruct;
	GPIO_InitTypeDef GPIO_InitStruct;	
	//��ʱ��
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_SPI1,ENABLE);
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA,ENABLE);
	
	//��ʼ��GPIO,CLK
  GPIO_InitStruct.GPIO_Mode	= GPIO_Mode_AF_PP;
	GPIO_InitStruct.GPIO_Pin	= SPI1_CLK_Pin ;
	GPIO_InitStruct.GPIO_Speed= GPIO_Speed_50MHz;
	
	GPIO_Init(SPI1_GPIO_PORT, &GPIO_InitStruct);
	//��ʼ��GPIO,MOSI
  GPIO_InitStruct.GPIO_Mode	= GPIO_Mode_AF_PP;
	GPIO_InitStruct.GPIO_Pin	= SPI1_MOSI_Pin ;
	GPIO_InitStruct.GPIO_Speed= GPIO_Speed_50MHz;
	
	GPIO_Init(SPI1_GPIO_PORT, &GPIO_InitStruct);
	//��ʼ��GPIO,MISO
	GPIO_InitStruct.GPIO_Mode	= GPIO_Mode_AF_PP;
	GPIO_InitStruct.GPIO_Pin	= SPI1_MISO_Pin;
	GPIO_InitStruct.GPIO_Speed= GPIO_Speed_50MHz;
	
	GPIO_Init(SPI1_GPIO_PORT, &GPIO_InitStruct);
	//��ʼ��NSS
	GPIO_InitStruct.GPIO_Mode	= GPIO_Mode_Out_PP;
	GPIO_InitStruct.GPIO_Pin	= SPI1_NSS_Pin;
	GPIO_InitStruct.GPIO_Speed= GPIO_Speed_50MHz;
	
	GPIO_Init(SPI1_GPIO_PORT, &GPIO_InitStruct);
	
	//��ʼ��SPI�ṹ��
	SPI_InitStruct.SPI_BaudRatePrescaler	=	SPI_BaudRatePrescaler_4;
	SPI_InitStruct.SPI_CPOL		=		SPI_CPOL_Low;
	SPI_InitStruct.SPI_CPHA		=   SPI_CPHA_1Edge;														//����ʱΪ�͵�ƽ
	SPI_InitStruct.SPI_CRCPolynomial	=	7;
	SPI_InitStruct.SPI_DataSize	=	SPI_DataSize_8b;		
	SPI_InitStruct.SPI_Direction	=	SPI_Direction_2Lines_FullDuplex;		//ȫ˫��
	SPI_InitStruct.SPI_FirstBit	=	SPI_FirstBit_MSB;
	SPI_InitStruct.SPI_Mode	= SPI_Mode_Master;
	SPI_InitStruct.SPI_NSS	=	SPI_NSS_Soft;
	
	SPI_Init(SPI1, &SPI_InitStruct);
	//��SPIʹ��
	SPI_Cmd(SPI1, ENABLE);
}


uint8_t SPI_SendByte(SPI_TypeDef * SPI_X,uint8_t Data)
{
	uint8_t ReceiveData;
	uint32_t SPI_Time_Out = SPIT_FLAG_TIMEOUT;
	//�ȴ����ͼĴ���Ϊ��
	while( SPI_I2S_GetFlagStatus(SPI_X, SPI_I2S_FLAG_TXE) == RESET )
	{
		if( (SPI_Time_Out) == 0)
		{
			printf("SPI�ȴ���ʱ");
			return 0;
		}
		SPI_Time_Out--;
	}
	//��������
	SPI_I2S_SendData(SPI_X,Data);
	
	//�ȴ����գ������ռĴ����Ƿ�Ϊ��
	SPI_Time_Out = SPIT_FLAG_TIMEOUT;
	while( SPI_I2S_GetFlagStatus(SPI_X,SPI_I2S_FLAG_RXNE) == RESET )
	{
		if( (SPI_Time_Out) == 0)
		{
			printf("SPI�ȴ���ʱ");
			return 0;
		}
		SPI_Time_Out--;
	}
	ReceiveData = SPI_I2S_ReceiveData(SPI_X);
	//�����յ������ٷ��ͳ�ȥ
	return ReceiveData;	
}

//��ȡһ���ֽ�
uint8_t SPI_ReadByte(SPI_TypeDef* SPI_X)
{
	return SPI_SendByte(SPI_X,0X00);
}



