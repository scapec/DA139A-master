/*
 * global_variables.h
 *
 * Created: 2015-08-26 12:47:20
 *  Author: Datorlabbstudent
 */ 



#ifndef GLOBAL_VARIABLES_H_
#define GLOBAL_VARIABLES_H_

#include "asf.h"

//Defines which is used for the PID
#define P_VALUE_SET 8
//Defines which is used for the PID
#define DISTANCE_SET 1300

extern pwm_channel_t pwm_channel_instance; // PWM variable	
extern int32_t distance_value; // ADC variable
extern int32_t result_value; // PID variable

#endif /* GLOBAL_VARIABLES_H_ */