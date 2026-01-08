#include "./BSP/IIC/IIC.h"


I2C_HandleTypeDef IIC_handler; /* IIC1句柄 */
//DMA_HandleTypeDef dma_spi1;

/**
 * @brief       IIC初始化代码
 *   @note      主机模式
 * @param       无
 * @retval      无
 */
void IIC1_init(void)
{
	IIC_handler.Instance = IIC1_I2C;
	IIC_handler.Init.ClockSpeed = 400000;
	IIC_handler.Init.DutyCycle = I2C_DUTYCYCLE_2;
	IIC_handler.Init.OwnAddress1 = 0;
	IIC_handler.Init.AddressingMode = I2C_ADDRESSINGMODE_7BIT;
	IIC_handler.Init.DualAddressMode = I2C_DUALADDRESS_DISABLE;
	IIC_handler.Init.OwnAddress2 = 0;
	IIC_handler.Init.GeneralCallMode = I2C_GENERALCALL_DISABLE;
	IIC_handler.Init.NoStretchMode = I2C_NOSTRETCH_DISABLE;
    HAL_I2C_Init(&IIC_handler);                                     /* 初始化 */

//    __HAL_SPI_ENABLE(&spi1_handler); /* 使能SPI1 */

//    spi1_read_write_byte(0XFF); /* 启动传输, 实际上就是产生8个时钟脉冲, 达到清空DR的作用, 非必需 */
}

/**
 * @brief       IIC1底层驱动，时钟使能，引脚配置
 *   @note      此函数会被HAL_I2C_Init()调用
 * @param       i2cHandle:IIC句柄
 * @retval      无
 */
void HAL_I2C_MspInit(I2C_HandleTypeDef* i2cHandle)
{
	I2C1_I2C_CLK_ENABLE(); /* SPI1时钟使能 */
	
    GPIO_InitTypeDef gpio_init_struct;
    if (i2cHandle->Instance==I2C1)
    {
        IIC1_SCL_GPIO_CLK_ENABLE();  /* SPI1_SCK脚时钟使能 */
        IIC1_SDA_GPIO_CLK_ENABLE(); /* SPI1_MISO脚时钟使能 */

        /* SCK引脚模式设置(复用输出) */
        gpio_init_struct.Pin = IIC1_SCL_GPIO_PIN;
        gpio_init_struct.Mode = GPIO_MODE_AF_PP;
        gpio_init_struct.Pull = GPIO_PULLUP;
        gpio_init_struct.Speed = GPIO_SPEED_FREQ_VERY_HIGH;
        gpio_init_struct.Alternate = GPIO_AF4_I2C1;
        HAL_GPIO_Init(IIC1_SCL_GPIO_PORT, &gpio_init_struct);

        /* MOSI引脚模式设置(复用输出) */
        gpio_init_struct.Pin = IIC1_SDA_GPIO_PIN;
        HAL_GPIO_Init(IIC1_SDA_GPIO_PORT, &gpio_init_struct);
    }
}
#define INA228_ADDR 0x40 << 1
//读取函数
void IIC_write_byt(uint8_t Device_addr,uint8_t addr,uint8_t LENGTH,uint8_t *buff)
{
	HAL_I2C_Mem_Write(&IIC_handler,Device_addr,addr,I2C_MEMADD_SIZE_8BIT,buff,LENGTH,HAL_MAX_DELAY);
}

void IIC_read_byt(uint8_t Device_addr,uint8_t addr,uint8_t LENGTH,uint8_t *buff)
{
	HAL_I2C_Mem_Read(&IIC_handler,Device_addr,addr,I2C_MEMADD_SIZE_8BIT,buff,LENGTH,HAL_MAX_DELAY);
}


