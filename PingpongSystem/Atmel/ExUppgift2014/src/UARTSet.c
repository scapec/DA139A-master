/*
* UARTSet.c
*
* Created: 2015-12-10 16:04:29
*  Author: Ali and Matko
*/

#include <asf.h>
#include "UARTSet.h"
#include "uart.h"
#include "conf_uart_serial.h"
#include "all_variables.h"
#include "my_adc.h"


void ComTask (void *pvParameters)
{
	getPIDValues(); // Get Matlab Values

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

			printf("%i\n\r", error);
			printf("%i\n\r", value_out);
			printf("%i\n\r", distance_sensor);
			printf("%i\n\r", bor_varde);
	}
}


void configure_console(void){
	const usart_serial_options_t uart_serial_options = {
		.baudrate = CONF_UART_BAUDRATE,
	.paritytype = CONF_UART_PARITY};
	// Configure console UART.
	sysclk_enable_peripheral_clock(CONSOLE_UART_ID);
	stdio_serial_init(CONF_UART, &uart_serial_options);
	// configure RX0 pin as pull-up otherwise it won't receive anything (only receive 0)
	ioport_set_pin_mode(PIO_PA8_IDX, IOPORT_MODE_PULLUP);
}

/* Function that receives values from Matlab */
void getPIDValues()
{
	// divier which is used to decode encoded doubles sent from Matlab
	const uint8_t divider = 10;

	uint16_t kP_Gain_temp = 0;
	/*uint16_t kP_Gain_temp2 = 0;*/
	uint16_t kI_Gain_temp = 0;
	uint16_t kD_Gain_temp = 0;
	
	while (!uart_is_rx_ready (CONF_UART)){
		vTaskDelay(1);
	}
	uart_read(CONF_UART, &kP_Gain_temp);
	printf("%i\n\r", kP_Gain_temp);
	
	while (!uart_is_rx_ready (CONF_UART)){
		vTaskDelay(1);
	}
	uart_read(CONF_UART, &kI_Gain_temp);
	printf("%i\n\r", kI_Gain_temp);
	
	while (!uart_is_rx_ready (CONF_UART)){
		vTaskDelay(1);
	};
	uart_read(CONF_UART, &kD_Gain_temp);
	printf("%i\n\r", kD_Gain_temp);

	while (!uart_is_rx_ready (CONF_UART)){
		vTaskDelay(1);
	};
	uart_read(CONF_UART, &bor_varde);
	printf("%i\n\r", bor_varde);

	//Convert to correct data types
	p_value = (double) ((double) kP_Gain_temp / divider);
	i_value = (double) (kI_Gain_temp / divider);
	d_value = (double) (kD_Gain_temp / divider);

	// Wait here until start signal is sent from matlab
	while (!uart_is_rx_ready (CONF_UART)){
		vTaskDelay(1);
	};
	printf("%i\n\r", 1);
	
	// Clear RX buffer
	while (uart_is_rx_ready (CONF_UART)){
		uint8_t clearBuffer = 0;
		uart_read(CONF_UART, &clearBuffer);
	};

}