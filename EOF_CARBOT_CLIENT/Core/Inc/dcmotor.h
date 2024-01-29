#ifndef _DCMOTOR_H_
#define _DCMOTOR_H_

#include "main.h"

void DCmotor_Forward_Rotate(void);
void DCmotor_Backward_Rotate(void);
void DCmotor_Break(void);
void DCmotor_Set_DutyCycle(uint16_t duty_cycle);
uint16_t DCmotor_Get_DutyCycle(void);

#endif
