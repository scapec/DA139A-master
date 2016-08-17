/*
* PWMSet.c
*
* Created: 2016-08-10 10:54:59
*  Author: Ali and Matko
*/
#include <asf.h>
#include "ReglStyr.h"
#include "all_variables.h"
#include "inttypes.h"
#include "my_adc.h"
#include "UARTSet.h"

void task_pid (void *pvParameters)
{
	duty_cycle_pwm(0);	
	portTickType xLastWakeTime = xTaskGetTickCount();
	const portTickType xFrequency =  d_time_ms; // 50ms
	vTaskDelay(3000); // Wait for MATLAB
	printf("%i\n\r", 9);

//infinite loop
	for(;;){
		// Pausa 50ms
		vTaskDelayUntil(&xLastWakeTime,xFrequency);	//
		//distance_sensor=1;
// 		error=2;
// 		value_out=3;
 		//bor_varde=30;
		
		
 		distance_sensor = sensor_read_adc();
		// Kp
		error = -1*(bor_varde - distance_sensor);
		
		//I-regulation
// 								 I_Output += error*d_time_ms/1000;
// 								if(I_Output > 1000){ // Remove windup induced lag
// 									I_Output = 1000;
// 									} else if(I_Output < -1000){
// 									I_Output = -1000;
// 								}
// 								
// 								// D-regulation
// 								D_Output = (float)(error-last_error);
// 								last_error = error;
								
		
		// Ki
		sum_of_error = (double)sum_of_error + error*(d_time_ms/1000); // till sekunder
				double I_Output;
			I_Output = (double)i_value*sum_of_error;
				// Kd
				double D_Output;
				D_Output = (double)d_value*(error - last_error)/(d_time_ms/1000);
				last_error = error;

				 
		//to apprehend pwm
		value_out = value_out+value_pwm;
		if (value_out < min_pid_pwm)
			value_out = min_pid_pwm;
		else if (value_out > max_pid_pwm)
			value_out = max_pid_pwm;
		// pid to pwm
		duty_cycle_pwm(value_out);
	}
}

void setup_pwm()
{
	pmc_enable_periph_clk(ID_PWM);
	pwm_channel_disable(PWM, PWM_CHANNEL_6); // change channel
	pwm_clock_t pwm_clock ={
		.ul_clka = 100000*100,
		.ul_clkb = 0,
		.ul_mck = sysclk_get_cpu_hz()
	};
	pwm_init(PWM, &pwm_clock);

	pwm_channel.alignment = PWM_ALIGN_LEFT;
	pwm_channel.polarity = PWM_LOW;
	pwm_channel.ul_prescaler = PWM_CMR_CPRE_CLKA;
	pwm_channel.ul_duty = 0;
	pwm_channel.ul_period = 999;
	pwm_channel.channel = PWM_CHANNEL_6;
	pwm_channel_init(PWM, &pwm_channel);
	pwm_channel_enable(PWM, PWM_CHANNEL_6);
}

void duty_cycle_pwm(int value){
	pwm_channel_update_duty(PWM, &pwm_channel, value);
}

