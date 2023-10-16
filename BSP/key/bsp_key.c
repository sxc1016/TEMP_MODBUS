#include "stm32f10x.h"
#include "bsp_key.h"


uint8_t Set_MB_CH_Addr(void)//Ҫ�Ѵӻ���ַ�ͱ��ӻ�����ͨ���ĵ�ַ��ŵ�λ�á�
{
	uint8_t Add_Data = 0;			//�ӻ���ַ��ͨ����ַ���
	GPIO_InitTypeDef GPIO_InitStructure;
	
	//GPIOBʱ��
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB,ENABLE);
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB,ENABLE);//����ĸ���I/Oʱ��д������
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO, ENABLE);//����afioʱ�ӣ���3.
	//���Ĳ��뿪�ص���������Ϊ��������ģʽ
	GPIO_InitStructure.GPIO_Mode =  GPIO_Mode_IPD;
	GPIO_InitStructure.GPIO_Pin  =  MB_Addr_1_Pin | MB_Addr_2_Pin | MB_Addr_4_Pin | MB_Addr_8_Pin | MB_Addr_16_Pin | MB_Addr_32_Pin| MB_Addr_64_Pin |MB_Addr_128_Pin ;
						
	GPIO_PinRemapConfig(GPIO_Remap_SWJ_NoJTRST,ENABLE);//���Ǹ���Ҫ�õ��ĺ������Ȳ��ܼ�4.��	
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
