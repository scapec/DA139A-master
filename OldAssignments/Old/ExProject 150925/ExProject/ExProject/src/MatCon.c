/*
* MatCon.c
*
* Created: 2015-08-20 21:32:36
*  Author: Rama
*/

#include <asf.h>
#include "MatCon.h"
#include "stdio.h"
#include "conf_uart_serial.h"
#include <inttypes.h>

int state = 0;
int count = 0;


int h1 = 5;
int h2 = 6;
int W = 7;



void start_comm(){

	//Stuck in loop untill Matlab gives signal
	// Spams character 'A' while waiting
	while (!uart_is_rx_ready (CONF_UART)){
		printf("%c\n",'A');
		delay_ms(100);
	}
	
	// Start reading data sent from Matlab
	// P,I,D & samplingstime data
	uint8_t p_cal, i_cal, d_cal, samp_rate;
	uart_read(CONF_UART, &p_cal);
	while (!uart_is_rx_ready (CONF_UART)){};
	uart_read(CONF_UART, &i_cal);
	while (!uart_is_rx_ready (CONF_UART)){};
	uart_read(CONF_UART, &d_cal);
	while (!uart_is_rx_ready (CONF_UART)){};
 	uart_read(CONF_UART, &samp_rate);
	 
	// Print out everything out again for debugging
	printf("%c\n", p_cal);
	printf("%c\n", i_cal);
	printf("%c\n", d_cal);
	printf("%u\n", samp_rate);
	
	// Print counting from 0 and up
	int i = 0;
	for(;;)
	{
		printf("%i\n", i);
		i = i + 1;
		delay_ms(100);	}
}