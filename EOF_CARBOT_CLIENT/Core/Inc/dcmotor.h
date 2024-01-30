#ifndef _DCMOTOR_H_
#define _DCMOTOR_H_

#include "main.h"
#include <stdlib.h>

#define JOYSTICK_MEDIAN_VALUE 90

typedef enum _DIRECTION
{
	FORWARD = 0,
	BACKWARD,
	BREAK
} DIRECTION;

void init_DCmotor(void);
void terminate_DCmotor(void);
void set_DCmotor(int8_t direction, int8_t left_wheel_pwm, int8_t right_wheel_pwm);
void move(int32_t control_value[]);

#endif /*_DCMOTOR_H_*/
