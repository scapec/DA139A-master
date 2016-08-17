/*
* PIDTask.c
*
*/
#include <asf.h>
#include "PIDTask.h"
#include "global_variables.h"
#include "PIDRegulation.h"


void PIDRegulationTask (void *pvParameters)
{
//	printf("PID Task initialized and PAUSED\n\r");
	
	// Pause here untill Matlab sent values
	xSemaphoreTake(sem, portMAX_DELAY);
	xSemaphoreTake(sem, portMAX_DELAY);
	
	portTickType xLastWakeTime = xTaskGetTickCount();
	const portTickType xFrequency =  dTimeRtos; // Run between 50-100ms
		
//		printf("%d\n\r", dTimeRtos);
		
//	printf("PID Task LOOP started\n\r");
	
	for(;;){
		vTaskDelayUntil(&xLastWakeTime,xFrequency);	// Samplingstid
		PIDRegulate(); // Run PID
	}
}
