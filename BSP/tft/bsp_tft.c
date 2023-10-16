#include "bsp_tft.h"
#include "bsp_spi.h"
#include "delay.h"
#include "stdio.h"
void TFT_GPIO_Init_Config(void)
{
	GPIO_InitTypeDef GPIO_InitStruct;
	//开时钟
	
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);

	//初始化GPIO结构体
	GPIO_InitStruct.GPIO_Mode	=	GPIO_Mode_Out_PP;
	GPIO_InitStruct.GPIO_Pin	=	TFT_RES_PIN | TFT_DC_PIN | TFT_BLK_PIN;
	GPIO_InitStruct.GPIO_Speed = GPIO_Speed_50MHz;
	
	GPIO_Init(TFT_RES_PORT, &GPIO_InitStruct);
}
void TFT_SPI_Init_Config(void)
{
	SPI_InitTypeDef SPI_InitStruct;
	GPIO_InitTypeDef GPIO_InitStruct;	
	//开时钟
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_SPI2,ENABLE);
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB,ENABLE);
	
	//初始化GPIO,CLK
	GPIO_InitStruct.GPIO_Mode	= GPIO_Mode_AF_PP;
	GPIO_InitStruct.GPIO_Pin	= TFT_SCL_PIN ;
	GPIO_InitStruct.GPIO_Speed= GPIO_Speed_50MHz;
	
	GPIO_Init(TFT_SCL_PORT, &GPIO_InitStruct);
	//初始化GPIO,MOSI
	GPIO_InitStruct.GPIO_Mode	= GPIO_Mode_AF_PP;
	GPIO_InitStruct.GPIO_Pin	= TFT_SDA_PIN ;
	GPIO_InitStruct.GPIO_Speed= GPIO_Speed_50MHz;
	
	GPIO_Init(TFT_SDA_PORT, &GPIO_InitStruct);
	//初始化NSS
	GPIO_InitStruct.GPIO_Mode	= GPIO_Mode_Out_PP;
	GPIO_InitStruct.GPIO_Pin	= TFT_CS_PIN;
	GPIO_InitStruct.GPIO_Speed= GPIO_Speed_50MHz;
	
	GPIO_Init(TFT_CS_PORT, &GPIO_InitStruct);
	
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
	
	SPI_Init(SPI2, &SPI_InitStruct);
	//开SPI使能
	SPI_Cmd(SPI2, ENABLE);
}
//软件模拟SPI
void TFT_SPI_SendByte(uint8_t Data)
{
	uint8_t i;
	for(i=8; i>0; i--)
	{
		if( (Data & 0x80) == 0 )
		{
			TFT_SDA_LOW;
		}
		else
		{
			TFT_SDA_HIGH;
		}
		TFT_SCL_LOW;
		TFT_SCL_HIGH;
		Data <<= 1;
	}
}
//LCD初始化
void Lcd_Init(void)
{	
	Lcd_Reset(); //Reset before LCD Init.

	//LCD Init For 1.44Inch LCD Panel with ST7735R.
	TFT_Send_Cmd(0x11);//Sleep exit 
	delay_ms(120);
	TFT_Send_Cmd(0x21);
	
	TFT_Send_Cmd(0xB1); 
	TFT_Send_Byte(0x05);
	TFT_Send_Byte(0x3A);
	TFT_Send_Byte(0x3A);

	TFT_Send_Cmd(0xB2);
	TFT_Send_Byte(0x05);
	TFT_Send_Byte(0x3A);
	TFT_Send_Byte(0x3A);

	TFT_Send_Cmd(0xB3); 
	TFT_Send_Byte(0x05);  
	TFT_Send_Byte(0x3A);
	TFT_Send_Byte(0x3A);
	TFT_Send_Byte(0x05);
	TFT_Send_Byte(0x3A);
	TFT_Send_Byte(0x3A);

	TFT_Send_Cmd(0xB4);
	TFT_Send_Byte(0x03);

	TFT_Send_Cmd(0xC0);
	TFT_Send_Byte(0x62);
	TFT_Send_Byte(0x02);
	TFT_Send_Byte(0x04);

	TFT_Send_Cmd(0xC1);
	TFT_Send_Byte(0xC0);

	TFT_Send_Cmd(0xC2);
	TFT_Send_Byte(0x0D);
	TFT_Send_Byte(0x00);

	TFT_Send_Cmd(0xC3);
	TFT_Send_Byte(0x8D);
	TFT_Send_Byte(0x6A);   

	TFT_Send_Cmd(0xC4);
	TFT_Send_Byte(0x8D); 
	TFT_Send_Byte(0xEE); 

	TFT_Send_Cmd(0xC5);  /*VCOM*/
	TFT_Send_Byte(0x0E);    

	TFT_Send_Cmd(0xE0);
	TFT_Send_Byte(0x10);
	TFT_Send_Byte(0x0E);
	TFT_Send_Byte(0x02);
	TFT_Send_Byte(0x03);
	TFT_Send_Byte(0x0E);
	TFT_Send_Byte(0x07);
	TFT_Send_Byte(0x02);
	TFT_Send_Byte(0x07);
	TFT_Send_Byte(0x0A);
	TFT_Send_Byte(0x12);
	TFT_Send_Byte(0x27);
	TFT_Send_Byte(0x37);
	TFT_Send_Byte(0x00);
	TFT_Send_Byte(0x0D);
	TFT_Send_Byte(0x0E);
	TFT_Send_Byte(0x10);

	TFT_Send_Cmd(0xE1);
	TFT_Send_Byte(0x10);
	TFT_Send_Byte(0x0E);
	TFT_Send_Byte(0x03);
	TFT_Send_Byte(0x03);
	TFT_Send_Byte(0x0F);
	TFT_Send_Byte(0x06);
	TFT_Send_Byte(0x02);
	TFT_Send_Byte(0x08);
	TFT_Send_Byte(0x0A);
	TFT_Send_Byte(0x13);
	TFT_Send_Byte(0x26);
	TFT_Send_Byte(0x36);
	TFT_Send_Byte(0x00);
	TFT_Send_Byte(0x0D);
	TFT_Send_Byte(0x0E);
	TFT_Send_Byte(0x10);

//	TFT_Send_Cmd(0x2a);			//列地址集
//	TFT_Send_Byte(0x00);
//	TFT_Send_Byte(0x00);
//	TFT_Send_Byte(0x00);
//	TFT_Send_Byte(0x50);
//	
//	TFT_Send_Cmd(0x2b);//hang地址集
//	TFT_Send_Byte(0x00);
//	TFT_Send_Byte(0x00);
//	TFT_Send_Byte(0x00);
//	TFT_Send_Byte(0xA0);
//	
//	TFT_Send_Cmd(0x2c);
	
	
	TFT_Send_Cmd(0x3A); 
	TFT_Send_Byte(0x05);

	TFT_Send_Cmd(0x36);
	TFT_Send_Byte(0xA8);//

	TFT_Send_Cmd(0x29); 

}

//向液晶屏发送一个8位的数据
void TFT_Send_Byte(uint8_t Data)
{
	//拉低片选线
	TFT_CS_LOW;
	//DC位拉高，写数据
	TFT_DC_HIGH;
	//写入数据
	SPI_SendByte(TFT_SPI,Data);
	//拉高片选线
	TFT_CS_HIGH;
}
//写16位数据
void TFT_Send_HalfWord(uint16_t Data)
{
	uint8_t Data_High,Data_Low;
	
	Data_Low = (Data & 0xff);
	Data >>= 8;
	Data_High = (Data & 0xff);
	
	//拉低片选线
	TFT_CS_LOW;
	//DC位拉高，写数据
	TFT_DC_HIGH;
	//写入数据
	SPI_SendByte(TFT_SPI,Data_High);
	SPI_SendByte(TFT_SPI,Data_Low);
	//拉高片选线
	TFT_CS_HIGH;
}
//写8位命令
void TFT_Send_Cmd(uint8_t Cmd)
{
	TFT_CS_LOW;
	//DC位拉高，写命令
	TFT_DC_LOW;
	//写入数据
	SPI_SendByte(TFT_SPI,Cmd);
	//拉高片选线
	TFT_CS_HIGH;
}

void Lcd_Reset(void)
{
	TFT_RES_LOW;
	delay_ms(100);
	TFT_RES_HIGH;
	delay_ms(50);
}



//设置显示区域的起始左边XS,YS和终止坐标XE,YE
void TFT_SET_START_END(uint16_t XS,uint16_t YS,uint16_t XE,uint16_t YE)
{
		TFT_Send_Cmd(0x2a);			//列地址集
		TFT_Send_HalfWord(XS);
		TFT_Send_HalfWord(XE);
	
		TFT_Send_Cmd(0x2b);//hang地址集
		TFT_Send_HalfWord(YS);
		TFT_Send_HalfWord(YE);
	
		TFT_Send_Cmd(0x2c);
}
//设置全屏
void TFT_SET_FULL(void)
{
	TFT_SET_START_END( 0,0,0X81,0X86);
}
//描绘一个点
void TFT_Draw_Dot(uint16_t x,uint16_t y,uint16_t Color_Data)
{
	TFT_SET_START_END(x,y,x+1,y+1);
	TFT_Send_HalfWord(Color_Data);
}

//对一个区域，X--起始，Y--起始，Width--宽度，Length--长度
void TFT_Draw(uint16_t X,uint16_t Y,uint8_t Width,uint8_t Length, uint8_t* Data,uint16_t Color_Data)
{
	uint8_t i,j,k,m,n,count;
	n = 0;
	TFT_SET_START_END(X,Y,X+Width-1,X+Length-1);
	for(i=0; i<Length; i++)
	{		
		count = Width/8;
		for(m=0;m<count; m++)
		{
			//程序卡死在这里
			k = *Data;
			for(j=0; j<8; j++)
			{
				if( (k & 0x80) != 0 )
				{
					TFT_Send_HalfWord(Color_Data);
				}
				else
				{
					TFT_Send_HalfWord(BLACK);
				}
				k <<= 1;
			}
			Data++;
		}
	}
}
//在8*16的区域写入一个字母
void TFT_Draw_8_16(uint16_t X,uint16_t Y, uint8_t* Data,uint16_t Color_Data)
{
	uint8_t i,j,k;
	TFT_SET_START_END(X,Y,X+7,X+15);
	for(i=16; i>0; i--)
	{
		 k = *Data;
		for(j=8; j>0; j--)
		{
			if( (k & 0x80) != 0 )
			{
				TFT_Send_HalfWord(Color_Data);
			}
			else
			{
				TFT_Send_HalfWord(BLACK);
			}
			 k <<= 1;
		}
		Data++;
	}
}
//在16*16的区域写入一个汉字
void TFT_Draw_16_16(uint16_t X,uint16_t Y, uint8_t* Data,uint16_t Color_Data)
{
	uint8_t x,y,k,i;
	TFT_SET_START_END(X,Y,X+15,X+15);
	for(x=16; x>0; x--)
	{
		 k = *Data;
		 i = *(Data+1);
		for(y=8; y>0; y--)
		{
			if( (k & 0x80) != 0 )
			{
				TFT_Send_HalfWord(Color_Data);
			}
			else
			{
				TFT_Send_HalfWord(BLACK);
			}
			 k <<= 1;
		}
		for(y=8; y>0; y--)
		{
			if( (i & 0x80) != 0 )
			{
				TFT_Send_HalfWord(Color_Data);
			}
			else
			{
				TFT_Send_HalfWord(BLACK);
			}
			 i <<= 1;
		}
		Data+=2;
	}
}
//显示图片
void TFT_SET_Image(uint16_t XS,uint16_t YS,uint16_t XE,uint16_t YE, uint8_t* Data)
{
	uint8_t j,i;
	TFT_SET_START_END(XS,YS,XE-1,YE-1);
	for(i=(XE-XS); i>0; i--)
	{
		for(j=(YE-YS); j>0; j--)
		{
			TFT_Send_Byte(*Data);
			TFT_Send_Byte(*(Data+1));
			Data+=2;
		}
	}
	
}

void TFT_Display_All(uint16_t Color_Data)
{
	uint8_t i,j;
	TFT_SET_START_END(0,0,161,110);
	for(i=0; i<160; i++)
	{
		for(j=0; j<109; j++)
		{
			TFT_Send_HalfWord(Color_Data);
		}
	}
	
}
