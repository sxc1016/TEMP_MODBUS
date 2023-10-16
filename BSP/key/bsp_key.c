#include "stm32f10x.h"
#include "bsp_key.h"


uint8_t Set_MB_CH_Addr(void)//要把从机地址和本从机三个通道的地址存放的位置。
{
	uint8_t Add_Data = 0;			//从机地址和通道地址存放
	GPIO_InitTypeDef GPIO_InitStructure;
	
	//GPIOB时钟
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB,ENABLE);
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB,ENABLE);//上面的复用I/O时钟写在这里
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO, ENABLE);//开启afio时钟，见3.
	//将的拨码开关的引脚配置为浮空输入模式
	GPIO_InitStructure.GPIO_Mode =  GPIO_Mode_IPD;
	GPIO_InitStructure.GPIO_Pin  =  MB_Addr_1_Pin | MB_Addr_2_Pin | MB_Addr_4_Pin | MB_Addr_8_Pin | MB_Addr_16_Pin | MB_Addr_32_Pin| MB_Addr_64_Pin |MB_Addr_128_Pin ;
						
	GPIO_PinRemapConfig(GPIO_Remap_SWJ_NoJTRST,ENABLE);//这是复用要用到的函数，先不管见4.。	
	GPIO_Init(GPIOB, &GPIO_InitStructure);

	
	while(1)
	{
		Add_Data = Add_Data | GPIO_ReadInputDataBit(MB_Addr_128_Port, MB_Addr_128_Pin);
		Add_Data<<=1;
		Add_Data = Add_Data | GPIO_ReadInputDataBit(MB_Addr_64_Port, MB_Addr_64_Pin);
		Add_Data<<=1;
		Add_Data = Add_Data | GPIO_ReadInputDataBit(MB_Addr_32_Port, MB_Addr_32_Pin);
		Add_Data<<=1;
		Add_Data = Add_Data | GPIO_ReadInputDataBit(MB_Addr_16_Port, MB_Addr_16_Pin);
		Add_Data<<=1;
		Add_Data = Add_Data | GPIO_ReadInputDataBit(MB_Addr_8_Port, MB_Addr_8_Pin);
		Add_Data<<=1;
		Add_Data = Add_Data | GPIO_ReadInputDataBit(MB_Addr_4_Port, MB_Addr_4_Pin);
		Add_Data<<=1;
		Add_Data = Add_Data | GPIO_ReadInputDataBit(MB_Addr_2_Port, MB_Addr_2_Pin);
		Add_Data<<=1;
		Add_Data = Add_Data | GPIO_ReadInputDataBit(MB_Addr_1_Port, MB_Addr_1_Pin);
		if( Add_Data != 0)
			break;
	}

	return Add_Data;
}
