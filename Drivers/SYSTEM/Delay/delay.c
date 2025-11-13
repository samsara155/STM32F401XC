#include "./system/delay/delay.h"


TIM_HandleTypeDef htim10;
void TIME_base_init(uint16_t arr,uint16_t psc)
{
	htim10.Instance=TIM10;
	htim10.Init.Prescaler=psc;// 指定用于分割 TIM 时钟的预分频器值。该参数可以是 Min_Data = 0x0000 和 Max_Data = 0xFFFF 之间的数值 
	htim10.Init.CounterMode=TIM_COUNTERMODE_UP;																	// 虽然TIM6挂在APB1上但是时钟源进行了二倍。详情见时钟树。
	htim10.Init.Period=arr;//指定下一次更新时要加载到活动自动重载寄存器中的周期值。自动重载寄存器的周期值。该参数可以是 Min_Data = 0x0000 和 Max_Data = 0xFFFF 之间的数值。
	htim10.Init.ClockDivision=TIM_CLOCKDIVISION_DIV1;
	htim10.Init.AutoReloadPreload=TIM_AUTORELOAD_PRELOAD_ENABLE;
	
	HAL_TIM_Base_Init(&htim10);//初始化TIM6

	HAL_TIM_Base_Start_IT(&htim10);//启动TIM使能
}

void HAL_TIM_Base_MspInit(TIM_HandleTypeDef *htim)
{
	if(htim->Instance==TIM10)
	{
		__HAL_RCC_TIM10_CLK_ENABLE();
		HAL_NVIC_SetPriority(TIM1_UP_TIM10_IRQn,5,5);
		//HAL_NVIC_EnableIRQ(TIM1_UP_TIM10_IRQn);
	}
}

void TIM10_delay_init(void)
{
	TIME_base_init(5000 - 1, 84 - 1);//1Mhz的计数频率，计数1次为1us
}

void TIM10_delay_us(uint32_t nus)                // 延时nus 要小于5000
{
    uint32_t told, tnow, tcnt = 0;
    told = TIM10->CNT;                    // 刚进入时的计数器值 
    while (1)
    {
        tnow = TIM10->CNT;
        if (tnow != told)
        {
            if (tnow > told)
            {
                tcnt=tnow-told;        // 这里注意一下TIM6是一个递增的计数器
            }
            else
            {
                tcnt = TIM10->ARR + tnow - told;  //如果CNT在ARR附近，会出现cnt永远不会等于nus的情况，使用这个可以避免出现这个问题
            }
            if (tcnt >= nus)
            {
								//TIM6->CNT=0;							//也可以手动装载，这样就跑不到中断了
                break;                      // 等于要延迟的时间,则退出 
							
            }
        }
    }
}

void TIM10_delay_ms(uint16_t nms)                // 延时nms 
{
    uint32_t i;
    for (i=0; i<nms; i++)
    {
        TIM10_delay_us(1000);
    }
}

void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim)
{
	
	if(htim->Instance == TIM10)
	{
		
	}
}


