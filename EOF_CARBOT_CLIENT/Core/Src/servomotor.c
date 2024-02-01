/**
  * APB1 bus에 연결되어 있는 Timer3에는 84mHz 클락이 적용되는데, 그것을 1680으로 분주하여 50kHz로 클락 신호가 들어오게 된다.
  * T = 1/f 이므로 1 / 50000 = 0.00002s(=0.02ms =20us) 였다.
  *
  * < MG90S servo motor's datasheet >
  * Position "0" (1.5ms pulse) is middle,
  *  - 0.02ms * 75 duty cycle = 1.5ms pulse
  *
  * Position "-90" (~ 1.5 ms pulse) is all the way to the left,
  *  - 0.02ms * 50 duty cycle = 1ms pulse
  *
  * Position "90" (~ 2ms pulse) is all the way to the right.
  *  - 0.02ms * 100 duty cycle = 2ms pulse
  */

#include "servomotor.h"

extern TIM_HandleTypeDef htim3;


/**
  * @brief 로봇팔 작동을 위한 PWM 타이머를 start합니다. PWM duty cycle 초기값을 0으로 셋팅합니다.
  * @retval None
  */
void init_RobotArm(void)
{
	HAL_TIM_PWM_Start_IT(&htim3, TIM_CHANNEL_1);
	HAL_TIM_PWM_Start_IT(&htim3, TIM_CHANNEL_2);
	HAL_TIM_PWM_Start_IT(&htim3, TIM_CHANNEL_3);
	HAL_TIM_PWM_Start_IT(&htim3, TIM_CHANNEL_4);

	init_RobotArm_position();
}

/**
  * @brief 로봇팔 작동을 위한 PWM 타이머를 stop합니다. PWM duty cycle 값을 0으로 셋팅합니다.
  * @retval None
  */
void terminate_RobotArm(void)
{
	init_RobotArm_position();

	HAL_TIM_PWM_Stop_IT(&htim3, TIM_CHANNEL_1);
	HAL_TIM_PWM_Stop_IT(&htim3, TIM_CHANNEL_2);
	HAL_TIM_PWM_Stop_IT(&htim3, TIM_CHANNEL_3);
	HAL_TIM_PWM_Stop_IT(&htim3, TIM_CHANNEL_4);
}

/**
  * @brief 로봇팔의 관절 셋팅을 초기화 합니다.
  * @retval None
  */
void init_RobotArm_position(void)
{
	__HAL_TIM_SET_COMPARE(&htim3, TIM_CHANNEL_1, PWM_SERVO_MEDIAN);
	__HAL_TIM_SET_COMPARE(&htim3, TIM_CHANNEL_2, PWM_SERVO_MEDIAN);
	__HAL_TIM_SET_COMPARE(&htim3, TIM_CHANNEL_3, PWM_SERVO_MEDIAN);
	__HAL_TIM_SET_COMPARE(&htim3, TIM_CHANNEL_4, PWM_SERVO_MEDIAN);
}

/**
  * @brief 4개의 servo motor를 사용하여 움직임을 만들어냅니다.
  * @retval None
  * @param 서버로부터 전달받은 컨트롤값 배열 { 앞/뒤를 제어하는 joystick_1의 값, 좌/우를 제어하는 joystick_2의 값 }
  * @detail
    	[ control_value의 length는 4 ]
		  - control_value[0] : joystick_1의 x값
		  - control_value[1] : joystick_1의 y값
		  - control_value[2] : joystick_2의 x값
		  - control_value[3] : joystick_2의 y값

		[ x, y 값의 바운더리는 무조건 0~200이어야함 ]
	      - 조이스틱 값 0   : PWM 50  : 서보모터 포지션 -90 (왼쪽 회전 끝)
          - 조이스틱 값 100 : PWM 75  : 서보모터 포지션 0
	      - 조이스틱 값 200 : PWM 100 : 서보모터 포지션 +90 (오른쪽 회전 끝)
  */
void move_RobotArm(int32_t control_value[])
{
	int32_t joint_1_pwm, joint_2_pwm, joint_3_pwm, joint_4_pwm;

	joint_1_pwm = control_value[0] / 4 + PWM_SERVO_MEDIAN;
	joint_2_pwm = control_value[1] / 4 + PWM_SERVO_MEDIAN;
	joint_3_pwm = control_value[2] / 4 + PWM_SERVO_MEDIAN;
	joint_4_pwm = control_value[3] / 4 + PWM_SERVO_MEDIAN;

	__HAL_TIM_SET_COMPARE(&htim3, TIM_CHANNEL_1, joint_1_pwm);
	__HAL_TIM_SET_COMPARE(&htim3, TIM_CHANNEL_2, joint_2_pwm);
	__HAL_TIM_SET_COMPARE(&htim3, TIM_CHANNEL_3, joint_3_pwm);
	__HAL_TIM_SET_COMPARE(&htim3, TIM_CHANNEL_4, joint_4_pwm);
}





