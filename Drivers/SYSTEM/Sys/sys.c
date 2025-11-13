#include "./SYSTEM/sys/sys.h"

/**
 * @brief       时钟设置函数
 * @param       plln: 主PLL倍频系数(PLL倍频), 取值范围: 50~432.
 * @param       pllm: 主PLL和音频PLL预分频系数(进PLL之前的分频), 取值范围: 2~63.
 * @param       pllp: 主PLL的p分频系数(PLL之后的分频), 分频后作为系统时钟, 取值范围: 2, 4, 6, 8.(仅限这4个值)
 * @param       pllq: 主PLL的q分频系数(PLL之后的分频), 取值范围: 2~15.
 * @note
 *
 *              Fvco: VCO频率
 *              Fsys: 系统时钟频率, 也是主PLL的p分频输出时钟频率
 *              Fq:   主PLL的q分频输出时钟频率
 *              Fs:   主PLL输入时钟频率, 可以是HSI, HSE等.
 *              Fvco = Fs * (plln / pllm);
 *              Fsys = Fvco / pllp = Fs * (plln / (pllm * pllp));
 *              Fq   = Fvco / pllq = Fs * (plln / (pllm * pllq));
 *
 *              外部晶振为 25M: plln = 168, pllm = 25, pllp = 2, pllq = 4.
 *              得到:Fvco = 25 * (168 / 25) = 168Mhz
 *                   Fsys = pll_p_ck = 168 / 2 = 84Mhz
 *                   Fq   = pll_q_ck = 168 / 4 = 42Mhz
 *
 *              F401默认需要配置的频率如下:
 *              CPU频率(HCLK) = pll_p_ck = 84Mhz
 *              APB1 = pll_p_ck / 2 = 42Mhz
 *				需要注意APB1 Timer clocks固定2倍频=84Mhz
 *              APB2 = pll_p_ck / 1 = 84Mhz
 *
 * @retval      错误代码: 0, 成功; 1, 错误;
 */
uint8_t SystemClock_Config(uint32_t plln, uint32_t pllm, uint32_t pllp, uint32_t pllq)
{
	HAL_StatusTypeDef ret = HAL_OK;
	RCC_OscInitTypeDef RCC_OscInitStruct = {0};
	RCC_ClkInitTypeDef RCC_ClkInitStruct = {0};

	__HAL_RCC_PWR_CLK_ENABLE();/* 使能PWR时钟 */
	__HAL_PWR_VOLTAGESCALING_CONFIG(PWR_REGULATOR_VOLTAGE_SCALE2);/* 设置调压器输出电压级别，以便在器件未以最大频率工作 */

	/* 使能HSE，并选择HSE作为PLL时钟源，配置PLL1，开启USB时钟 */
	RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSE;/* 时钟源为HSE */
	RCC_OscInitStruct.HSEState = RCC_HSE_ON;/* 打开HSE */
	RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;/* 打开PLL */
	RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSE;/* PLL时钟源选择HSE */
	RCC_OscInitStruct.PLL.PLLM = pllm;//25
	RCC_OscInitStruct.PLL.PLLN = plln;//168
	RCC_OscInitStruct.PLL.PLLP = pllp;//RCC_PLLP_DIV2
	RCC_OscInitStruct.PLL.PLLQ = pllq;//4
	ret = HAL_RCC_OscConfig(&RCC_OscInitStruct);/* 初始化RCC */
    if(ret != HAL_OK)
    {
        return 1;                                                /* 时钟初始化失败，可以在这里加入自己的处理 */
    }
	/* 选中PLL作为系统时钟源并且配置HCLK,PCLK1和PCLK2 */
	RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK
								 |RCC_CLOCKTYPE_SYSCLK
								 |RCC_CLOCKTYPE_PCLK1
								 |RCC_CLOCKTYPE_PCLK2;
	RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;/* 设置系统时钟时钟源为PLL */
	RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;/* AHB分频系数为1 */
	RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV2;/* APB1分频系数为2 */
	RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV1;/* APB2分频系数为1 */
	ret = HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_2);
    if(ret != HAL_OK)
    {
        return 1;                                                /* 时钟初始化失败 */
    }
	
	/*STM32F401CCU6 微控制器具备 Flash 预读取（预取指）功能，这是通过其内置的 ART Accelerator（自适应实时加速器） 实现
	__HAL_FLASH_PREFETCH_BUFFER_ENABLE();                     使能flash预取 
	可以知道在stm32f4xx_hal_conf.h中已经配置了PREFETCH_ENABLE宏，在HAL_Init中已经使用了预读取功能，在这里就不需要打开了
	*/
	return 0;
}

/**
 * @brief       初始化MCO相关IO口, 并使能时钟
 * @param       无
 * @retval      无
 */
void RCC_MCO_GPIO_init(void)
{
	HAL_RCC_MCOConfig(RCC_MCO1, RCC_MCO1SOURCE_HSE, RCC_MCODIV_4); //测试主频HSE 4分频6.25Mhz输出到PA8上
	
    GPIO_InitTypeDef gpio_init_struct;
    
    RCC_MCO_GPIO_CLK_ENABLE();                                 /* MCO时钟使能 */

    gpio_init_struct.Pin = RCC_MCO_GPIO_PIN;                   /* MCO引脚 */
    gpio_init_struct.Mode = GPIO_MODE_AF_PP;            	   /* 复用推挽输出 */
    gpio_init_struct.Pull = GPIO_NOPULL;                       /* 上拉 */
    gpio_init_struct.Speed = GPIO_SPEED_FREQ_VERY_HIGH;        /* 高速 */
	gpio_init_struct.Alternate = GPIO_AF0_MCO;				   /*设置复用为MCO功能*/
    HAL_GPIO_Init(RCC_MCO_GPIO_PORT, &gpio_init_struct);       /* 初始化MCO引脚 */
}




