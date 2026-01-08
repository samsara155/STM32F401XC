#include "./BSP/KEY/key.h"
#include "./SYSTEM/usart/usart.h"

void key_init(void)
{
    GPIO_InitTypeDef gpio_init_struct;
    
    KEY1_GPIO_CLK_ENABLE();                                 /* LED0时钟使能 */

    gpio_init_struct.Pin = KEY1_GPIO_PIN;                   /* LED0引脚 */
    gpio_init_struct.Mode = GPIO_MODE_INPUT;            	/* 输入 */
    gpio_init_struct.Pull = GPIO_PULLUP;                    /* 上拉 */
    gpio_init_struct.Speed = GPIO_SPEED_FREQ_HIGH;          /* 高速 */
    HAL_GPIO_Init(KEY1_GPIO_PORT, &gpio_init_struct);       /* 初始化LED0引脚 */

 	
}

uint8_t len;
uint8_t key_scan(void)
{
	printf("请输入数据,以得到键值\r\n");
	if (g_usart_rx_sta & 0x8000)         /* 接收到了数据? */
	{
		len = g_usart_rx_sta & 0x3fff;  /* 得到此次接收到的数据长度 */
		printf("\r\n您发送的消息为:\r\n");

		HAL_UART_Transmit(&g_uart1_handle,(uint8_t*)g_usart_rx_buf,len,1000);    /* 发送接收到的数据 */
		while(__HAL_UART_GET_FLAG(&g_uart1_handle,UART_FLAG_TC)!=SET);           /* 等待发送结束 */
		printf("\r\n\r\n");             /* 插入换行 */
		g_usart_rx_sta = 0;
		return (g_usart_rx_buf[0]-0x30);
	}
	return 0;
	
}

