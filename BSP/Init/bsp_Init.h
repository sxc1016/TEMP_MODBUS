#ifndef __BSP_INIT_H
#define	__BSP_INIT_H

#include "stm32f10x.h"
//输入寄存器起始地址
#ifndef	REG_INPUT_START
#define REG_INPUT_START       0x0001
#endif
//输入寄存器数量
#ifndef	REG_INPUT_NREGS
#define REG_INPUT_NREGS       8
#endif
//保持寄存器起始地址
#ifndef	REG_HOLDING_START
#define REG_HOLDING_START     0x0001
#endif
//保持寄存器数量
#ifndef	REG_HOLDING_NREGS
#define REG_HOLDING_NREGS     8
#endif

//线圈起始地址
#ifndef	REG_COILS_START
#define REG_COILS_START       0x0001
#endif
//线圈数量
#ifndef	REG_COILS_SIZE
#define REG_COILS_SIZE        16
#endif

//开关寄存器起始地址
#ifndef	REG_DISCRETE_START
#define REG_DISCRETE_START    0x0001
#endif
//开关寄存器数量
#ifndef	REG_DISCRETE_SIZE
#define REG_DISCRETE_SIZE     16
#endif




#endif /* __BSP_INIT_H */
