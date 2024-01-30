#include "dcmotor.h"

extern TIM_HandleTypeDef htim4;


/**
  * @brief DC motor 작동을 위한 PWM 타이머를 start합니다.
  * @retval None
  */
void init_DCmotor(void)
{
	HAL_TIM_PWM_Start_IT(&htim4, TIM_CHANNEL_1);
	HAL_TIM_PWM_Start_IT(&htim4, TIM_CHANNEL_2);
}

/**
  * @brief DC motor 작동을 위한 PWM 타이머를 stop합니다.
  * @retval None
  */
void terminate_DCmotor(void)
{
	HAL_TIM_PWM_Stop_IT(&htim4, TIM_CHANNEL_1);
	HAL_TIM_PWM_Stop_IT(&htim4, TIM_CHANNEL_2);
}

/**
  * @brief 4개의 DC motor 상태를 설정합니다.
  * @retval None
  * @param 앞/뒤 설정 값, 왼쪽바퀴 PWM 값, 오른쪽바퀴 PWM 값
  * @detail
  */
void set_DCmotor(int32_t direction, int32_t left_wheel_pwm, int32_t right_wheel_pwm)
{
	if (direction == FORWARD)
	{
		HAL_GPIO_WritePin(GPIOE, LEFT_WHEEL_IN1_Pin, GPIO_PIN_SET);
		HAL_GPIO_WritePin(GPIOE, LEFT_WHEEL_IN2_Pin, GPIO_PIN_RESET);
		HAL_GPIO_WritePin(GPIOE, RIGHT_WHEEL_IN3_Pin, GPIO_PIN_SET);
		HAL_GPIO_WritePin(GPIOE, RIGHT_WHEEL_IN4_Pin, GPIO_PIN_RESET);
	}
	else if (direction == BACKWARD)
	{
		HAL_GPIO_WritePin(GPIOE, LEFT_WHEEL_IN1_Pin, GPIO_PIN_RESET);
		HAL_GPIO_WritePin(GPIOE, LEFT_WHEEL_IN2_Pin, GPIO_PIN_SET);
		HAL_GPIO_WritePin(GPIOE, RIGHT_WHEEL_IN3_Pin, GPIO_PIN_RESET);
		HAL_GPIO_WritePin(GPIOE, RIGHT_WHEEL_IN4_Pin, GPIO_PIN_SET);
	}
	else if (direction == BREAK)
	{
		HAL_GPIO_WritePin(GPIOE, LEFT_WHEEL_IN1_Pin, GPIO_PIN_SET);
		HAL_GPIO_WritePin(GPIOE, LEFT_WHEEL_IN2_Pin, GPIO_PIN_SET);
		HAL_GPIO_WritePin(GPIOE, RIGHT_WHEEL_IN3_Pin, GPIO_PIN_SET);
		HAL_GPIO_WritePin(GPIOE, RIGHT_WHEEL_IN4_Pin, GPIO_PIN_SET);
	}

	__HAL_TIM_SET_COMPARE(&htim4, TIM_CHANNEL_1, left_wheel_pwm);
	__HAL_TIM_SET_COMPARE(&htim4, TIM_CHANNEL_2, right_wheel_pwm);
}

/**
  * @brief 4개의 DC motor를 사용하여 움직임을 만들어냅니다.
  * @retval None
  * @param 서버로부터 전달받은 컨트롤값 배열 { 앞/뒤를 제어하는 joystick_1의 값, 좌/우를 제어하는 joystick_2의 값 }
  * @detail
  * 	// control_value의 length는 4
		// control_value[0] : joystick_1의 x값
		// control_value[1] : joystick_1의 y값
		// control_value[2] : joystick_2의 x값
		// control_value[3] : joystick_2의 y값
		// x, y 값의 바운더리는 무조건 0~180 혹은 0~200 이어야함.
		// 중앙값에서 엣지값까지의 거리가 100을 넘어가면 안됨.
		// x, y 값을 곧바로 PWM 듀티 사이클로 사용하고 있음.
  */
void move(int32_t control_value[])
{
	int32_t joystick_1_x, joystick_2_y;
	int32_t direction, left_wheel_pwm, right_wheel_pwm;

	joystick_1_x = control_value[0] - JOYSTICK_MEDIAN_VALUE;
	joystick_2_y = control_value[3] - JOYSTICK_MEDIAN_VALUE;

	if (joystick_1_x == 0 && joystick_2_y == 0) // 완전한 정지상태인 경우
	{
		direction = BREAK;

		left_wheel_pwm = 0;
		right_wheel_pwm = 0;
	}
	else
	{
		if (joystick_1_x <= 0) { direction = FORWARD; }
		else { direction = BACKWARD; }

		left_wheel_pwm = abs(joystick_1_x);
		right_wheel_pwm = abs(joystick_1_x);

		if (joystick_2_y < 0) { left_wheel_pwm -= abs(joystick_2_y); } // 왼쪽으로 회전하는 경우(왼쪽 바퀴 회전률 감소)
		else if (joystick_2_y > 0) { right_wheel_pwm -= abs(joystick_2_y); } // 오른쪽으로 회전하는 경우(오른쪽 바퀴 회전률 감소)
		else {}
	}

	set_DCmotor(direction, left_wheel_pwm, right_wheel_pwm);
}
