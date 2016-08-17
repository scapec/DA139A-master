/*
* UARTTask.c
*
*/
#include <asf.h>
#include "UARTTask.h"
#include "global_variables.h"
#include "UARTFunctions.h"
#include "ADCCustom.h"

void SerialComTask (void *pvParameters)
{
	getPIDValues(); // Get Values from Matlab
	
	xSemaphoreGive(sem); // Tell PID Task to start

	for(;;){
		
		// Wait here for Matlab to send signal its ready to receive values
		while (!uart_is_rx_ready (CONF_UART)){
			vTaskDelay(1);
		};
		
		// Clear RX buffer
		while (uart_is_rx_ready (CONF_UART)){
			uint8_t clearBuffer = 0;
			uart_read(CONF_UART, &clearBuffer);
		};

		sendValues(); // Send values to MATLAB for graphing

		//printf("PWM:%i \tSP:%i \tDistance:%i \tE:%i \n", output_value,distanceSet, distance, error);
	}
}