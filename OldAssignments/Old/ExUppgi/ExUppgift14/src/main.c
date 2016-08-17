/*
* main.c
*
*	Hardware:
*	-Pin 3 on the shield should not connect to pin 3 on the Arduino
*	-Pin 7 on the Arduino should connect to pin 3 on the Shield
*	-VIN and GND on the shield connects to a 12V power regulator
*	-"+" and "-" at port "A" on the shield connects the theh fan motor
*	-Distance sensor connects the A8 on the Arduino
*
* 
* Author: Rama
*/

#include <asf.h>
#include "adc_dac.h"
#include "pwm_custom.h"
#include "delay.h"
#include "PID.h"
#include "SerialComTask.h"
#include "config/conf_board.h"
#include "config/conf_clock.h "

static void configure_console(void)
{
	const usart_serial_options_t uart_serial_options = { .baudrate =
	CONF_UART_BAUDRATE, .paritytype = CONF_UART_PARITY };
	/* Konfigurera konsol UART. */
	sysclk_enable_peripheral_clock(CONSOLE_UART_ID);
	stdio_serial_init(CONF_UART, &uart_serial_options);
	
	/* configure RX0 pin as pull-up - this is tailored towards use with Matlab*/
	ioport_set_pin_mode(PIO_PA8_IDX, IOPORT_MODE_PULLUP);
}

int main (void)
{
	sysclk_init(); // Initialize system clock
	board_init(); // Initialize Arduino Due board
	ioport_init(); // Initialize the IO-port
	adc_configur(); // Setup ADC for sensor values
	fan_init(); // Initialize PWM for fan control
	configure_console(); // Initialize UART for Communication
	printf("Booted Due\n");
	
	/* Creating the serial-printing task */
	if (xTaskCreate(SerialCommunicationTask, (const signed char * const) "SerialComTask",
	TASK_SerialComTask_STACK_SIZE, NULL, TASK_SerialComTask_STACK_PRIORITY, NULL) != pdPASS)
	{
		printf("Failed to create SerialCommunicationTask\r\n");
	}
	
	/* Creating the sensor-reading task */
	if (xTaskCreate(PIDTask, (const signed char * const) "PIDTask",
	TASK_PIDRegulation_STACK_SIZE, NULL, TASK_PIDRegulation_STACK_PRIORITY, NULL) != pdPASS)
	{
		printf("Failed to create PIDTask\r\n");
	}
	

	/* Start the FreeRTOS scheduler running all tasks indefinitely*/
	vTaskStartScheduler();
	
	while(1);
	return 0;
}