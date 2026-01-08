#ifndef __KEY_H__
#define __KEY_H__
#include "./SYSTEM/sys/sys.h"

/******************************************************************************************/
/* 引脚 定义 */

#define KEY1_GPIO_PORT                  GPIOC
#define KEY1_GPIO_PIN                   GPIO_PIN_14
#define KEY1_GPIO_CLK_ENABLE()          do{ __HAL_RCC_GPIOC_CLK_ENABLE(); }while(0)             /* PC口时钟使能 */

/******************************************************************************************/

/* KEY端口定义 */
#define KEY(x)   do{ x ? \
                      HAL_GPIO_WritePin(LED0_GPIO_PORT, LED0_GPIO_PIN, GPIO_PIN_SET) : \
                      HAL_GPIO_WritePin(LED0_GPIO_PORT, LED0_GPIO_PIN, GPIO_PIN_RESET); \
                  }while(0)       /* LED0 = RED */

/* KEY取反定义 */
#define LED0_TOGGLE()    do{ HAL_GPIO_TogglePin(LED0_GPIO_PORT, LED0_GPIO_PIN); }while(0)       

/******************************************************************************************/
/* 外部接口函数*/
void key_init(void);                                                                            /* 初始化 */
uint8_t key_scan(void);

#endif
