#ifndef _TIMER__MANAGEMENT_H_
#define _TIMER__MANAGEMENT_H_

#include "main.h"

void delay_ms(uint32_t ms);

#if 0 // 추후 기능확장을 대비한 스켈레톤 코드
void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim);
void HAL_TIM_IC_CaptureCallback(TIM_HandleTypeDef *htim);
#endif

#endif /*_TIMER__MANAGEMENT_H_*/
