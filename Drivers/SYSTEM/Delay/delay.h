#ifndef __DELAY_H
#define __DELAY_H

#include "./SYSTEM/sys/sys.h"

void TIM10_delay_init(void);
void TIM10_delay_us(uint32_t nus);                // 延时nus 要小于5000
void TIM10_delay_ms(uint16_t nms);                // 延时nms 


#endif /* __DELAY_H */
