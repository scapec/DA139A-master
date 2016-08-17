/*
* PIDSet.c
*
* Created: 2015-12-10 16:04:29
*  Author: Ali and Matko
* T
*/
#include <asf.h>
#include "inttypes.h"
//#include "ReglStyr.h"
#include "ADCSet.h"
#include "allVariables.h"
#include "UARTSet.h"

void PIDTask (void *pvParameters)
{

	// Pause here untill Matlab sent values
	xSemaphoreTake(sem, portMAX_DELAY);
	xSemaphoreTake(sem, portMAX_DELAY);

	portTickType xLastWakeTime = xTaskGetTickCount();
	const portTickType xFrequency =  DTIME_MS; // Run between 50-100ms

	vTaskDelay(1000);

	for(;;){
		vTaskDelayUntil(&xLastWakeTime,xFrequency);	// Samplingstid
		PIDReglering(); // Run PID
	}
}


/* PID Funktion */
void PIDReglering(void){

	// moving average filter of sampled sensor values
	uint32_t valuesTotal = 0;
	for(int i = 0; i<FILTER_AVERAGE_SAMPLES-1; i++){
		valuesTotal += ADCReadSensor();
	}
	distanceSensor = valuesTotal / FILTER_AVERAGE_SAMPLES;

	// Propertionell-del
	error = (setPoint - distanceSensor);

	// Integrerande-del
	sumOfError = (double)sumOfError + (double)((double)error*(double)DT_SECONDS);
	double I_Output;
	if(kI == 0)
	{
		I_Output = 0;
		} else {
		I_Output = (double)kI*sumOfError;
	}

	// Deriverande-del
	double D_Output;

	if(error == 1)
	{
		D_Output = 0;
		} else {
		D_Output = (double)((double)((double)kD*(double)(error - lastError))/(double)DT_SECONDS);
	}
	lastError = error;

	// Add up P, I and D outputs
	output_value = (kP*error)+I_Output+D_Output;
	
	// Protection vs overflow/underflow
	if (output_value < PID_PWM_MIN)
	{
		output_value = PID_PWM_MIN;
	}
	else if (output_value > PID_PWM_MAX)
	{
		output_value = PID_PWM_MAX;
	}

	// Write PID value to PWM
	PWMDutyCycle(output_value);
}
