/*
* allVariables.c
*
* Created: 2016-07-10 11:10:56
*  Author: Ali and Matko
*/

#include <asf.h>
#include "all_variables.h"

/* PID */
// Processed values for the PID regulator, p_temp / divider ..
double p_value = 0;
double i_value = 0;
double d_value = 0;
double I_Output = 0;
double D_Output = 0;
double value_pwm = 0;
int16_t bor_varde = 0;

int16_t value_out = 0;
int16_t distance_sensor = 0;
int16_t error = 0;
int16_t sum_of_error = 0;
int16_t last_error = 0;



// buffer för filter

int16_t buffer_filter[] = {0,0,0,0,0};  // buffer beroende av samplingstid
	int16_t buffer_filter_res = 0;
