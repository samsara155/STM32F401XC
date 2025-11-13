#ifndef __SYS_H
#define __SYS_H

#include "stm32f4xx.h"
#include "core_cm4.h"
#include "stm32f4xx_hal.h"

/******************************************************************************************/
/* 引脚 定义 */

#define RCC_MCO_GPIO_PORT                  GPIOA
#define RCC_MCO_GPIO_PIN                   GPIO_PIN_8
#define RCC_MCO_GPIO_CLK_ENABLE()          do{ __HAL_RCC_GPIOA_CLK_ENABLE(); }while(0)             /* PA口时钟使能 */



uint8_t SystemClock_Config(uint32_t plln, uint32_t pllm, uint32_t pllp, uint32_t pllq);		/* 配置系统时钟 */
void RCC_MCO_GPIO_init(void);

#endif /* __SYS_H */
