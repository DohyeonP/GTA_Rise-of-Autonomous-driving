#include "dcmotor.h"

extern TIM_HandleTypeDef htim4;
extern volatile uint32_t TIM10_10ms_dcmotor_activate_time;

/*
 * desc: DC모터를 원하는 시간동안 정방향 회전시킨 뒤 멈춘다.
 * param1: DC모터가 가동하는 시간(초 단위)
 */
void DCmotor_Forward_Rotate(void)
{
	HAL_GPIO_WritePin(GPIOE, GPIO_PIN_8, GPIO_PIN_SET);
	HAL_GPIO_WritePin(GPIOE, GPIO_PIN_9, GPIO_PIN_RESET);
}

/*
 * desc: DC모터를 원하는 시간동안 역방향 회전시킨 뒤 멈춘다.
 * param1: DC모터가 가동하는 시간(초 단위)
 */
void DCmotor_Backward_Rotate(void)
{
	HAL_GPIO_WritePin(GPIOE, GPIO_PIN_8, GPIO_PIN_RESET);
	HAL_GPIO_WritePin(GPIOE, GPIO_PIN_9, GPIO_PIN_SET);
}

/*
 * desc: DC모터를 멈춘다.
 */
void DCmotor_Break(void)
{
	HAL_GPIO_WritePin(GPIOE, GPIO_PIN_8, GPIO_PIN_SET);
	HAL_GPIO_WritePin(GPIOE, GPIO_PIN_9, GPIO_PIN_SET);
}

void DCmotor_Set_DutyCycle(uint16_t duty_cycle)
{
	__HAL_TIM_SET_COMPARE(&htim4, TIM_CHANNEL_1, duty_cycle);
}

uint16_t DCmotor_Get_DutyCycle(void)
{
	return __HAL_TIM_GET_COMPARE(&htim4, TIM_CHANNEL_1);
}
