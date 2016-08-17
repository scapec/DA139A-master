#include <asf.h>
#include "delay.h"
#include "config/conf_board.h"
#include "config/conf_clock.h "
#include "all_variables.h"
#include "my_adc.h"
#include "ReglStyr.h"
#include "UARTSet.h"


int main (void)
{
	// Board init
	
	
	sysclk_init();
	board_init();
	ioport_init();
	delay_init();
	configure_console(); // Initialize UART
	setup_pwm();
	
	// init shield
	ioport_set_pin_dir(PIO_PC21_IDX, IOPORT_DIR_OUTPUT); // byta kanal PIO
	ioport_set_pin_level(PIO_PC21_IDX, LOW);
	ioport_set_pin_dir(PIO_PD8_IDX, IOPORT_DIR_OUTPUT);
	ioport_set_pin_level(PIO_PD8_IDX, HIGH);
	adc_setup();
	
	// FREERTOS task for pid
 	if (xTaskCreate(task_pid, (const signed char * const) "PIDRegulation",
 	TASK_PIDRegulation_STACK_SIZE, NULL, TASK_PIDRegulation_STACK_PRIORITY, NULL) != pdPASS)
 	{
	 	printf("Failed to create PIDRegulationTask\r\n");
 	}
	
	/* Creating the serial communication task */
	if (xTaskCreate(ComTask, (const signed char * const) "SerialComTask",
	TASK_SerialComTask_STACK_SIZE, NULL, TASK_SerialComTask_STACK_PRIORITY, NULL) != pdPASS)
	{
	printf("Failed to create SerialComTask\r\n");
	}
	
	/* Start the FreeRTOS scheduler running all tasks indefinitely*/
	vTaskStartScheduler();
	printf("Insufficient RAM\r\n");
	while(1);
	
}