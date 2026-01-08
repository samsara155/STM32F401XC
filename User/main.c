#include "main.h"
#include "./SYSTEM/sys/sys.h"
#include "./SYSTEM/delay/delay.h"
#include "./SYSTEM/usart/usart.h"

#include "./BSP/KEY/key.h"
#include "./BSP/SPI/spi.h"
#include "./BSP/IIC/IIC.h"
	#include "./BSP/OLED/oled.h"
#include "./BSP/DMA/dma.h"
	#include "./BSP/LCD/lcd.h"
		#include "./BSP/GUI/gui.h"
			#include "./BSP/MENU/menu.h"
#include "./BSP/LED/led.h"


uint8_t USART1_BUF[] = "Hello world\r\n";
uint8_t data1[2]={0x00,0x80},data2[2]={0,0};



uint8_t key=0,t=0;




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
	IIC1_init();
	
	RCC_MCO_GPIO_init();
	DispCrtMenu();
	
	OLED_Init();
	OLED_ColorTurn(0);//0正常显示，1 反色显示
	OLED_DisplayTurn(0);//0正常显示 1 屏幕翻转显示
  
	while(1)
	{
//		printf("123");
////		TIM10_delay_ms(1000);
////		LCD_Clear(BLACK);
////		LCD_ShowNum(0,0,7789,4,,12);
////		TIM10_delay_ms(1000);
////		LCD_Clear(YELLOW);
////		LCD_ShowString(0,0,16,"ABC",1);
////		TIM10_delay_ms(1000);
////		LCD_Clear(BLUE);
////		LCD_ShowString(0,0,16,"12345",1);
////		IIC_write_byt(0x00,2,data1);
////		IIC_read_byt(0x00,2,data2);
////		LCD_ShowNum(0,20,data2[0],4,12);
////		LCD_ShowNum(0,40,data2[1],4,12);
//		Display(1);
//		TIM10_delay_ms(10000);
//       if (g_usart_rx_sta & 0x8000)         /* 接收到了数据? */
//        {
//            len = g_usart_rx_sta & 0x3fff;  /* 得到此次接收到的数据长度 */
//            printf("\r\n您发送的消息为:\r\n");

//            HAL_UART_Transmit(&g_uart1_handle,(uint8_t*)g_usart_rx_buf,len,1000);    /* 发送接收到的数据 */
//            while(__HAL_UART_GET_FLAG(&g_uart1_handle,UART_FLAG_TC)!=SET);           /* 等待发送结束 */
//            printf("\r\n\r\n");             /* 插入换行 */
//            g_usart_rx_sta = 0;
//        }
//        else
//        {
//            times++;

//            if (times % 5000 == 0)
//            {
//                printf("\r\n正点原子 STM32开发板 串口实验\r\n");
//                printf("正点原子@ALIENTEK\r\n\r\n\r\n");
//            }

//            if (times % 200 == 0) printf("请输入数据,以回车键结束\r\n");

//            if (times % 30  == 0) LED0_TOGGLE(); /* 闪烁LED,提示系统正在运行. */

//            TIM10_delay_ms(10);
//        }


//		key=key_scan();
//		Display(&key);
//		TIM10_delay_ms(100);

//		OLED_ShowPicture(0,0,128,8,BMP1);
		TIM10_delay_ms(500);
		OLED_Clear();
		OLED_ShowString(20,32,"2014/05/01",16);
		OLED_ShowString(0,48,"ASCII:",16);  
		OLED_ShowString(63,48,"CODE:",16);
		OLED_ShowChar(48,48,t,16);//显示ASCII字符	   
		t++;
		if(t>'~')t=' ';
		OLED_ShowNum(103,48,t,3,16);
		OLED_Refresh();
		TIM10_delay_ms(500);
		OLED_Clear();
		OLED_ShowChinese(0,0,0,16);  //16*16 中
		  OLED_ShowChinese(16,0,0,24); //24*24 中
		OLED_ShowChinese(24,20,0,32);//32*32 中
		OLED_ShowChinese(64,0,0,64); //64*64 中
		OLED_Refresh();
		TIM10_delay_ms(500);
		OLED_Clear();
		OLED_ShowString(0,0,"ABC",12);//6*12 “ABC”
		OLED_ShowString(0,12,"ABC",16);//8*16 “ABC”
		OLED_ShowString(0,28,"ABC",24);//12*24 “ABC”
		OLED_Refresh();
	}
	
}

