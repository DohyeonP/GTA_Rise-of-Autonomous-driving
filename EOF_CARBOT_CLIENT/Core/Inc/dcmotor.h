#ifndef _DCMOTOR_H_
#define _DCMOTOR_H_

#include "main.h"
#include <stdlib.h>

#define PWM_MIN 0
#define PWM_MAX 100
#define JOYSTICK_MEDIAN_VALUE 100

typedef enum _DIRECTION
{
	FORWARD = 0,
	BACKWARD,
	BREAK
} DIRECTION;

void init_RCcar(void);
void terminate_RCcar(void);
void set_RCcar(int32_t direction, int32_t left_wheel_pwm, int32_t right_wheel_pwm);
void move_RCcar(int32_t control_value[]);

#endif /*_DCMOTOR_H_*/
