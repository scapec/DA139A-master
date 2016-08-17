/*
* PID.c
*
* Created: 2015-08-19 23:22:11
*  Author: Rama
*/
#include <asf.h>
#include "PID.h"
#include "adc.h"
#include "pwm_custom.h"
#include "inttypes.h"
#include "global_variables.h"

void PIDTask (void *pvParameters)
{
	portTickType xLastWakeTime = xTaskGetTickCount();
	const portTickType xFrequency = 1; // Run every few ms
	
	for(;;){
		
		//testFans(); // Gets stuck in this function which just test fans
		
		vTaskDelayUntil(&xLastWakeTime,xFrequency);	// Samplingstime
		
		Regulation(); // Run PID
	}
}


void Regulation(void)
{
	
	// Read raw sensor distance from ADC
	distance_value = get_distance();
	
	// P-regulation
	int32_t error = 0;
	error = DISTANCE_SET - distance_value; //get the error value of distance sensor
	
	//output_value = (int32_t)(tempP*(uP+uI+uD));  // Calculate full PID
	
	// Convert ADC to PWM range
	result_value = (((int32_t)P_VALUE_SET*error)); // Calculate P

	// Make sure the values do not exceed the PWM Duty Cycle range (0-100%)
	if (result_value < 0)
	{
		result_value = 0;
	}
	else if (result_value > 4096)
	{
		result_value = 4096;
	}

	result_value = (result_value * 100) / 4096;
	
	//send the output_value to fan
	pwm_channel_update_duty(PWM, &pwm_channel_instance, result_value);
}

unsigned int get_distance(void)
{
	adc_start(ADC);
	while((adc_get_status(ADC) & 0x1<<24)==0);  // Wait until DRDY(Data Ready) is HIGH
	return (adc_get_channel_value(ADC, ADC_CHANNEL_10));
}

// Cycles between 0,50 and 100% Duty Cycle on PWM
void testFans(void)
{
	portTickType xLastWakeTime = xTaskGetTickCount();
	const portTickType xFrequency = 5000; // Run every few seconds
	vTaskDelayUntil(&xLastWakeTime,xFrequency);
	pwm_channel_update_duty(PWM, &pwm_channel_instance, 100);
	printf("100\n");
	
	vTaskDelayUntil(&xLastWakeTime,xFrequency);
	pwm_channel_update_duty(PWM, &pwm_channel_instance, 0);
	printf("0\n");
	
	vTaskDelayUntil(&xLastWakeTime,xFrequency);
	pwm_channel_update_duty(PWM, &pwm_channel_instance, 50);
	printf("50\n");
}