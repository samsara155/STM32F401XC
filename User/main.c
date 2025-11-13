#include "main.h"
#include "./SYSTEM/sys/sys.h"
#include "./SYSTEM/delay/delay.h"
#include "./SYSTEM/usart/usart.h"
#include "./BSP/LED/led.h"

uint8_t USART1_BUF[] = "Hello world\r\n";









int main(void)
{
	HAL_Init();
	
	SystemClock_Config(168, 25, 2, 4);
	
	TIM10_delay_init();
	led_init();
	LED0_TOGGLE();
	TIM10_delay_ms(50);
	LED0_TOGGLE();
	usart_init(115200);
	RCC_MCO_GPIO_init();
	while(1)
	{
		LED0_TOGGLE();
		TIM10_delay_ms(500);
		LED0_TOGGLE();
		TIM10_delay_ms(500);
		printf("123");
	}
	
}

