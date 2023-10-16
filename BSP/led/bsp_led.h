#ifndef __LED_H
#define	__LED_H


#include "stm32f10x.h"


// 通道1,LD激光管控制引脚定义
#define LED_CH1_GPIO_PORT	    	GPIOA			              /* GPIO端口 */
#define LED_CH1_GPIO_CLK 	   		RCC_APB2Periph_GPIOA		/* GPIO端口时钟 */
#define LED_CH1_GPIO_PIN			GPIO_Pin_11			        /* 连接到SCL时钟线的GPIO */

// 通道2,LD激光管控制引脚定义
#define LED_CH2_GPIO_PORT    		GPIOA			              /* GPIO端口 */
#define LED_CH2_GPIO_CLK 	   	 	RCC_APB2Periph_GPIOA		/* GPIO端口时钟 */
#define LED_CH2_GPIO_PIN			GPIO_Pin_12			        /* 连接到SCL时钟线的GPIO */

// 通道3,LD激光管控制引脚定义
#define LED_CH3_GPIO_PORT   		GPIOA			              /* GPIO端口 */
#define LED_CH3_GPIO_CLK 	    	RCC_APB2Periph_GPIOA		/* GPIO端口时钟 */
#define LED_CH3_GPIO_PIN			GPIO_Pin_13			        /* 连接到SCL时钟线的GPIO */


/** the macro definition to trigger the led on or off 
  * 1 - off
  *0 - on
  */
#define ON  0
#define OFF 1

#define LED_CH1_ON			GPIO_SetBits(LED_CH1_GPIO_PORT,LED_CH1_GPIO_PIN)
#define LED_CH1_OFF			GPIO_ResetBits(LED_CH1_GPIO_PORT,LED_CH1_GPIO_PIN)

#define LED_CH2_ON			GPIO_SetBits(LED_CH2_GPIO_PORT,LED_CH2_GPIO_PORT)
#define LED_CH2_OFF			GPIO_ResetBits(LED_CH2_GPIO_PORT,LED_CH2_GPIO_PORT)

#define LED_CH3_ON			GPIO_SetBits(LED_CH3_GPIO_PORT,LED_CH3_GPIO_PIN)
#define LED_CH3_OFF			GPIO_ResetBits(LED_CH3_GPIO_PORT,LED_CH3_GPIO_PIN)

////红
//#define LED_CH1_ON  \
//					LED1(ON);\
//					LED2(OFF)\
//					LED3(OFF)

////绿
//#define LED_CH2_ON		\
//					LED1(OFF);\
//					LED2(ON)\
//					LED3(OFF)

////蓝
//#define LED_CH3_ON	\
//					LED1(OFF);\
//					LED2(OFF)\
//					LED3(ON)


//					
////黑(全部关闭)
//#define LED_OFF	\
//					LED1(OFF);\
//					LED2(OFF)\
//					LED3(OFF)

void LED_GPIO_Config(void);

#endif /* __LED_H */
