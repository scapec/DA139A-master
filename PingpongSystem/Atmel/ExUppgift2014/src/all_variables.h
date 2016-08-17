/*
* all_variables.h
*
* Created: 2016-07-10 11:10:56
*  Author: Ali and Matko
*/


#ifndef ALL_VARIABLES_H_
#define All_VARIABLES_H_

//Min/Max for PWM 

#define min_pid_pwm 0
#define max_pid_pwm 999

/* PID / UART */
// Variables bellow are used for both PID calculation and storing values sent from Matlab
extern double p_value;
extern double i_value;
extern double d_value;
extern int16_t bor_varde;
extern double I_Output;
extern double D_Output;
extern double value_pwm;

// dt �r 50ms eller 0.05s
#define d_time_ms 50




extern int16_t value_out;
extern int16_t distance_sensor;
extern int16_t error;
extern int16_t sum_of_error;
extern int16_t last_error;

/* PWM */
pwm_channel_t pwm_channel;

// buffer for filter
extern int16_t buffer_filter[];
extern int16_t buffer_filter_res;

#endif /* ALL_VARIABLES_H_ */
