#include "add.h"
#include "stm32f10x.h"

//将数据的起始地址，和总数传入函数,求和函数，
uint8_t	add_(uint8_t * Data,uint8_t Num)
{
	uint8_t i;
	uint8_t Data_Sum = 0;
	for(i = 0; i < Num; i++)
	{
		Data_Sum += *Data;
		Data++;
	}
	return Data_Sum;
}
