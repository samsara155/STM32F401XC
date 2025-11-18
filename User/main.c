#include "main.h"
#include "./SYSTEM/sys/sys.h"
#include "./SYSTEM/delay/delay.h"
#include "./SYSTEM/usart/usart.h"

#include "./BSP/SPI/spi.h"
#include "./BSP/DMA/dma.h"
	#include "./BSP/LCD/lcd.h"
		#include "./BSP/GUI/gui.h"
#include "./BSP/LED/led.h"


uint8_t USART1_BUF[] = "Hello world\r\n";









int main(void)
{
	HAL_Init();
	
	SystemClock_Config(168, 25, 2, 4);
	
	TIM10_delay_init();
	led_init();

	usart_init(115200);
	
	DMA_Init();
	spi1_init();
	LCD_Init();
	
	RCC_MCO_GPIO_init();
	while(1)
	{
		TIM10_delay_ms(1000);
		LCD_Clear(BLACK);
		LCD_ShowNum(0,0,7789,4,12);
		TIM10_delay_ms(1000);
		LCD_Clear(YELLOW);
		LCD_ShowString(0,0,16,"ABC",1);
		TIM10_delay_ms(1000);
		LCD_Clear(BLUE);
		LCD_ShowString(0,0,16,"12345",1);
		
		
	}
	
}

