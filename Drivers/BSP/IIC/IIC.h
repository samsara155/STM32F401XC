#ifndef __IIC_H
#define __IIC_H

#include "./SYSTEM/sys/sys.h"


/******************************************************************************************/
/* IIC1 引脚 定义 */

#define IIC1_SCL_GPIO_PORT              GPIOB
#define IIC1_SCL_GPIO_PIN               GPIO_PIN_6
#define IIC1_SCL_GPIO_CLK_ENABLE()      do{ __HAL_RCC_GPIOB_CLK_ENABLE(); }while(0)   /* PA口时钟使能 */

#define IIC1_SDA_GPIO_PORT              GPIOB
#define IIC1_SDA_GPIO_PIN               GPIO_PIN_7
#define IIC1_SDA_GPIO_CLK_ENABLE()      do{ __HAL_RCC_GPIOB_CLK_ENABLE(); }while(0)   /* PA口时钟使能 */

/* IIC1相关定义 */
#define IIC1_I2C                        I2C1
#define I2C1_I2C_CLK_ENABLE()           do{ __HAL_RCC_I2C1_CLK_ENABLE(); }while(0)    /* SPI1时钟使能 */

/******************************************************************************************/


void IIC1_init(void);
void IIC_write_byt(uint8_t Device_addr,uint8_t addr,uint8_t LENGTH,uint8_t *buff);
void IIC_read_byt(uint8_t Device_addr,uint8_t addr,uint8_t LENGTH,uint8_t *buff);

#endif
























