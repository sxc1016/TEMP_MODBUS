#ifndef __BSP_INIT_H
#define	__BSP_INIT_H

#include "stm32f10x.h"
//����Ĵ�����ʼ��ַ
#ifndef	REG_INPUT_START
#define REG_INPUT_START       0x0001
#endif
//����Ĵ�������
#ifndef	REG_INPUT_NREGS
#define REG_INPUT_NREGS       8
#endif
//���ּĴ�����ʼ��ַ
#ifndef	REG_HOLDING_START
#define REG_HOLDING_START     0x0001
#endif
//���ּĴ�������
#ifndef	REG_HOLDING_NREGS
#define REG_HOLDING_NREGS     8
#endif

//��Ȧ��ʼ��ַ
#ifndef	REG_COILS_START
#define REG_COILS_START       0x0001
#endif
//��Ȧ����
#ifndef	REG_COILS_SIZE
#define REG_COILS_SIZE        16
#endif

//���ؼĴ�����ʼ��ַ
#ifndef	REG_DISCRETE_START
#define REG_DISCRETE_START    0x0001
#endif
//���ؼĴ�������
#ifndef	REG_DISCRETE_SIZE
#define REG_DISCRETE_SIZE     16
#endif




#endif /* __BSP_INIT_H */
