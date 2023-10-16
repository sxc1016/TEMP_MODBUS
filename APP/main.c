#include "stm32f10x.h"
#include "mb.h"
#include "bsp_key.h"
#include "mbutils.h"

#include "bsp_led.h"
#include "bsp_Init.h"
#include "add.h"
#include "delay.h"
#include "bsp_usart.h"
#include "bsp_adc.h"
#include <stdio.h>
#include "bsp_tft.h"
#include "bsp_spi.h"


// ADC1转换的电压值通过MDA方式传到SRAM
extern __IO uint16_t ADC_ConvertedValue[NOFCHANEL];

// 局部变量，用于保存转换计算后的电压值 	 
float ADC_ConvertedValueLocal;  
//从站地址
uint8_t    ucMBAddress;		

//输入寄存器内容
uint16_t usRegInputBuf[REG_INPUT_NREGS] = {0x1000,0x1001,0x1002,0x1003,0x1004,0x1005,0x1006,0x1007};
//输入寄存器起始地址
uint16_t usRegInputStart = REG_INPUT_START;

//保持寄存器内容
uint16_t usRegHoldingBuf[REG_HOLDING_NREGS] = {0};
//保持寄存器起始地址
uint16_t usRegHoldingStart = REG_HOLDING_START;

//线圈状态
uint8_t ucRegCoilsBuf[REG_COILS_SIZE / 8] = {0x01,0x02};
//开关输入状态
uint8_t ucRegDiscreteBuf[REG_DISCRETE_SIZE / 8] = {0x01,0x02};

/**
 * @Brief : 读输入寄存器处理函数，功能码04
 * @param  pucRegBuffer    数据缓存区   大端模式，高字节在前
 * @param  usAddress       寄存器地址 
 * @param  usNRegs         读取个数
 * @return eMBErrorCode 
 */
eMBErrorCode
eMBRegInputCB( UCHAR * pucRegBuffer, USHORT usAddress, USHORT usNRegs )
{
    eMBErrorCode    eStatus = MB_ENOERR;
    int             iRegIndex;

    if( ( usAddress >= REG_INPUT_START )\
        && ( usAddress + usNRegs <= REG_INPUT_START + REG_INPUT_NREGS ) )
    {
        iRegIndex = ( int )( usAddress - usRegInputStart );
        while( usNRegs > 0 )
        {
            *pucRegBuffer++ = ( UCHAR )( usRegInputBuf[iRegIndex] >> 8 );
            *pucRegBuffer++ = ( UCHAR )( usRegInputBuf[iRegIndex] & 0xFF );
            iRegIndex++;
            usNRegs--;
        }
    }
    else
    {
        eStatus = MB_ENOREG;
    }

    return eStatus;
}

/**
 * @Brief : 读保持寄存器处理函数，功能码03
 * @param  pucRegBuffer     
 * @param  usAddress        
 * @param  usNRegs          
 * @param  eMode            
 * @return eMBErrorCode 
 */
eMBErrorCode
eMBRegHoldingCB( UCHAR * pucRegBuffer, USHORT usAddress, USHORT usNRegs, eMBRegisterMode eMode )
{
	eMBErrorCode    eStatus = MB_ENOERR;
	int             iRegIndex;


	if((usAddress >= REG_HOLDING_START)&&\
		((usAddress+usNRegs) <= (REG_HOLDING_START + REG_HOLDING_NREGS)))
	{
		iRegIndex = (int)(usAddress - usRegHoldingStart);
		switch(eMode)
		{                                       
			case MB_REG_READ://读 MB_REG_READ = 0
        	while(usNRegs > 0)
				{
					*pucRegBuffer++ = (u8)(usRegHoldingBuf[iRegIndex] >> 8);            
					*pucRegBuffer++ = (u8)(usRegHoldingBuf[iRegIndex] & 0xFF); 
          			iRegIndex++;
          			usNRegs--;					
				}                            
        	break;
			case MB_REG_WRITE://写 MB_REG_WRITE = 1
			while(usNRegs > 0)
				{
					usRegHoldingBuf[iRegIndex] = *pucRegBuffer++ << 8;
          			usRegHoldingBuf[iRegIndex] |= *pucRegBuffer++;
          			iRegIndex++;
          			usNRegs--;
        		}				
		}
	}
	else//错误
	{
		eStatus = MB_ENOREG;
	}	
	
	return eStatus;
}

/**
 * @Brief : 读线圈寄存器处理函数，功能码01
 * @param  pucRegBuffer     
 * @param  usAddress        
 * @param  usNCoils         
 * @param  eMode            
 * @return eMBErrorCode 
 */
eMBErrorCode
eMBRegCoilsCB( UCHAR * pucRegBuffer, USHORT usAddress, USHORT usNCoils,
              eMBRegisterMode eMode )
{
  //错误状态
  eMBErrorCode eStatus = MB_ENOERR;
  //寄存器个数
  int16_t iNCoils = ( int16_t )usNCoils;
  //寄存器偏移量
  int16_t usBitOffset;
  
  //检查寄存器是否在指定范围内
  if( ( (int16_t)usAddress >= REG_COILS_START ) &&
     ( usAddress + usNCoils <= REG_COILS_START + REG_COILS_SIZE ) )
  {
    //计算寄存器偏移量
    usBitOffset = ( int16_t )( usAddress - REG_COILS_START );
    switch ( eMode )
    {
      //读操作
    case MB_REG_READ:
      while( iNCoils > 0 )
      {
        *pucRegBuffer++ = xMBUtilGetBits( ucRegCoilsBuf, usBitOffset,\
                                         ( uint8_t )( iNCoils > 8 ? 8 : iNCoils ) );
        iNCoils -= 8;
        usBitOffset += 8;
      }
      break;
      
      //写操作
    case MB_REG_WRITE:
      while( iNCoils > 0 )
      {
        xMBUtilSetBits( ucRegCoilsBuf, usBitOffset,\
                       ( uint8_t )( iNCoils > 8 ? 8 : iNCoils ),
                       *pucRegBuffer++ );
        iNCoils -= 8;
      }
      break;
    }
    
  }
  else
  {
    eStatus = MB_ENOREG;
  }
  return eStatus;
}

/**
 * @Brief : 读离散量寄存器处理函数，功能码02
 * @param  pucRegBuffer     
 * @param  usAddress        
 * @param  usNDiscrete      
 * @return eMBErrorCode 
 */
eMBErrorCode
eMBRegDiscreteCB( UCHAR * pucRegBuffer, USHORT usAddress, USHORT usNDiscrete )
{
  //错误状态
  eMBErrorCode eStatus = MB_ENOERR;
  //操作寄存器个数
  int16_t iNDiscrete = ( int16_t )usNDiscrete;
  //偏移量
  uint16_t usBitOffset;
  
  //判断寄存器时候再制定范围内
  if( ( (int16_t)usAddress >= REG_DISCRETE_START ) &&
     ( usAddress + usNDiscrete <= REG_DISCRETE_START + REG_DISCRETE_SIZE ) )
  {
    //获得偏移量
    usBitOffset = ( uint16_t )( usAddress - REG_DISCRETE_START );
    
    while( iNDiscrete > 0 )
    {
      *pucRegBuffer++ = xMBUtilGetBits( ucRegDiscreteBuf, usBitOffset,
                                       ( uint8_t)( iNDiscrete > 8 ? 8 : iNDiscrete ) );
      iNDiscrete -= 8;
      usBitOffset += 8;
    }
    
  }
  else
  {
    eStatus = MB_ENOREG;
  }
  return eStatus;
}


int main(void)
{	
	uint8_t Key_Add;


//获取从机地址，以及通道地址
//	Key_Add = Set_MB_CH_Addr();
	
//	USART_Config(115200);
	
////ADC采样率167.832KHZ
//	ADCx_Init();

////LED初始化
//	LED_GPIO_*Config();
//	
	
//TFT屏幕
//	TFT_SPI_Init_Config();
//	TFT_GPIO_Init_Config();
//	Lcd_Init();
//	

//	//背景为黑色
//	GPIO_SetBits(GPIOB, GPIO_Pin_11);
//	TFT_Display_All(BLUE);
	

//modbus初始化
	eMBInit(MB_RTU, Key_Add, 0x00, 115200, MB_PAR_NONE);
	eMBEnable();


		
	while (1)
	{
		eMBPoll();
//		LED_CH1_OFF;
//		delay_ms(1000);
//	
//		LED_CH1_ON;
//		
//		delay_ms(1000);
	}
}




