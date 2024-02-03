#ifndef _ROBOT__ARM_H_
#define _ROBOT__ARM_H_

#include "main.h"
#include <stdlib.h>
#include "timer_management.h"

#define PWM_SERVO_MIN 50
#define PWM_SERVO_MEDIAN 75
#define PWM_SERVO_MAX 100
#define JOYSTICK_MEDIAN_VALUE 512

void init_RobotArm(void);
void terminate_RobotArm(void);
inline void init_RobotArm_position(void);
void move_RobotArm(int32_t control_value[]);

#endif /*_ROBOT__ARM_H_*/
