#include "./SYSTEM/sys/sys.h"

/**
 * @brief       ʱ�����ú���
 * @param       plln: ��PLL��Ƶϵ��(PLL��Ƶ), ȡֵ��Χ: 50~432.
 * @param       pllm: ��PLL����ƵPLLԤ��Ƶϵ��(��PLL֮ǰ�ķ�Ƶ), ȡֵ��Χ: 2~63.
 * @param       pllp: ��PLL��p��Ƶϵ��(PLL֮��ķ�Ƶ), ��Ƶ����Ϊϵͳʱ��, ȡֵ��Χ: 2, 4, 6, 8.(������4��ֵ)
 * @param       pllq: ��PLL��q��Ƶϵ��(PLL֮��ķ�Ƶ), ȡֵ��Χ: 2~15.
 * @note
 *
 *              Fvco: VCOƵ��
 *              Fsys: ϵͳʱ��Ƶ��, Ҳ����PLL��p��Ƶ���ʱ��Ƶ��
 *              Fq:   ��PLL��q��Ƶ���ʱ��Ƶ��
 *              Fs:   ��PLL����ʱ��Ƶ��, ������HSI, HSE��.
 *              Fvco = Fs * (plln / pllm);
 *              Fsys = Fvco / pllp = Fs * (plln / (pllm * pllp));
 *              Fq   = Fvco / pllq = Fs * (plln / (pllm * pllq));
 *
 *              �ⲿ����Ϊ 25M: plln = 168, pllm = 25, pllp = 2, pllq = 4.
 *              �õ�:Fvco = 25 * (168 / 25) = 168Mhz
 *                   Fsys = pll_p_ck = 168 / 2 = 84Mhz
 *                   Fq   = pll_q_ck = 168 / 4 = 42Mhz
 *
 *              F401Ĭ����Ҫ���õ�Ƶ������:
 *              CPUƵ��(HCLK) = pll_p_ck = 84Mhz
 *              APB1 = pll_p_ck / 2 = 42Mhz
 *				��Ҫע��APB1 Timer clocks�̶�2��Ƶ=84Mhz
 *              APB2 = pll_p_ck / 1 = 84Mhz
 *
 * @retval      �������: 0, �ɹ�; 1, ����;
 */
uint8_t SystemClock_Config(uint32_t plln, uint32_t pllm, uint32_t pllp, uint32_t pllq)
{
	HAL_StatusTypeDef ret = HAL_OK;
	RCC_OscInitTypeDef RCC_OscInitStruct = {0};
	RCC_ClkInitTypeDef RCC_ClkInitStruct = {0};

	__HAL_RCC_PWR_CLK_ENABLE();/* ʹ��PWRʱ�� */
	__HAL_PWR_VOLTAGESCALING_CONFIG(PWR_REGULATOR_VOLTAGE_SCALE2);/* ���õ�ѹ�������ѹ�����Ա�������δ�����Ƶ�ʹ��� */

	/* ʹ��HSE����ѡ��HSE��ΪPLLʱ��Դ������PLL1������USBʱ�� */
	RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSE;/* ʱ��ԴΪHSE */
	RCC_OscInitStruct.HSEState = RCC_HSE_ON;/* ��HSE */
	RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;/* ��PLL */
	RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSE;/* PLLʱ��Դѡ��HSE */
	RCC_OscInitStruct.PLL.PLLM = pllm;//25
	RCC_OscInitStruct.PLL.PLLN = plln;//168
	RCC_OscInitStruct.PLL.PLLP = pllp;//RCC_PLLP_DIV2
	RCC_OscInitStruct.PLL.PLLQ = pllq;//4
	ret = HAL_RCC_OscConfig(&RCC_OscInitStruct);/* ��ʼ��RCC */
    if(ret != HAL_OK)
    {
        return 1;                                                /* ʱ�ӳ�ʼ��ʧ�ܣ���������������Լ��Ĵ��� */
    }
	/* ѡ��PLL��Ϊϵͳʱ��Դ��������HCLK,PCLK1��PCLK2 */
	RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK
								 |RCC_CLOCKTYPE_SYSCLK
								 |RCC_CLOCKTYPE_PCLK1
								 |RCC_CLOCKTYPE_PCLK2;
	RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;/* ����ϵͳʱ��ʱ��ԴΪPLL */
	RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;/* AHB��Ƶϵ��Ϊ1 */
	RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV2;/* APB1��Ƶϵ��Ϊ2 */
	RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV1;/* APB2��Ƶϵ��Ϊ1 */
	ret = HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_2);
    if(ret != HAL_OK)
    {
        return 1;                                                /* ʱ�ӳ�ʼ��ʧ�� */
    }
	HAL_RCC_MCOConfig(RCC_MCO1, RCC_MCO1SOURCE_HSE, RCC_MCODIV_4); //������ƵHSE 4��Ƶ6.25Mhz�����PA8��
	
	/*STM32F401CCU6 ΢�������߱� Flash Ԥ��ȡ��Ԥȡָ�����ܣ�����ͨ�������õ� ART Accelerator������Ӧʵʱ�������� ʵ��
	__HAL_FLASH_PREFETCH_BUFFER_ENABLE();                     ʹ��flashԤȡ 
	����֪����stm32f4xx_hal_conf.h���Ѿ�������PREFETCH_ENABLE�꣬��HAL_Init���Ѿ�ʹ����Ԥ��ȡ���ܣ�������Ͳ���Ҫ����
	*/
	return 0;
}

