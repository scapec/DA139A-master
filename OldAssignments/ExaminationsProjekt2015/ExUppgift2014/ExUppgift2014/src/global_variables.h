/*
* global_variables.h
*
*/


#ifndef GLOBAL_VARIABLES_H_
#define GLOBAL_VARIABLES_H_

extern xSemaphoreHandle sem;

/* PID */
// Values that will be received from Matlab
extern uint8_t P_CONSTANT_temp;
extern uint8_t I_CONSTANT_temp;
extern uint8_t D_CONSTANT_temp;
extern double P_CONSTANT;
extern double I_CONSTANT;
extern double D_CONSTANT;

extern uint8_t distanceSetCM_temp;
extern int distanceSetCM;

extern uint8_t dTime_temp;
extern double dTime;
extern uint8_t dTimeRtos;

extern int output_value;
extern int distance;
extern int error;
extern int old_error;

extern uint8_t testByte;
extern uint8_t testByte2;

/* PWM */
pwm_channel_t pwm_channel;

#endif /* GLOBAL_VARIABLES_H_ */