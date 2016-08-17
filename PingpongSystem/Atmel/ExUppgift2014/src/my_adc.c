/*
* ADCSet
*
* Created: 2015-12-10 16:04:29
*  Author: Ali and Matko
*/
#include <asf.h>
#include "my_adc.h"
#include "all_variables.h"
#include "ReglStyr.h"

/* Setup Function for ADC */
void adc_setup()
{
	pmc_enable_periph_clk(ID_ADC);
	adc_init(ADC, sysclk_get_main_hz(), 20000000, 0);		// Configure for maximum frequency @ 20 MHz
	adc_configure_timing(ADC, 0, 0, 0);
	adc_set_resolution(ADC, ADC_MR_LOWRES_BITS_12);			// 0-4095
	adc_configure_trigger(ADC, ADC_TRIG_SW, 0);				// trig just by software
	adc_enable_channel(ADC, ADC_CHANNEL_10);				// PB17 - AD8 for Arduino Due
}

/* Read ADC value*/
int16_t sensor_read_adc()
{// gör plats i buffer för senaste värdet
	for(int i = 10; i>0; i--){
		buffer_filter[i] = buffer_filter[i-1];
	}
	
	adc_start(ADC);
	while((adc_get_status(ADC) & 0x1<<24)==0);  // Wait until DRDY(Data Ready) is HIGH
	buffer_filter[0] = adc_get_latest_value(ADC);
	if(buffer_filter[0] < 0){
		buffer_filter[0] = buffer_filter[0]*-1;
	}
	for( int i = 0; i<10;i++){buffer_filter_res = buffer_filter_res + buffer_filter[i];
	
	}
	 buffer_filter_res = buffer_filter_res / 10;  // average
	 	if(buffer_filter_res < 0){
		 	buffer_filter_res = buffer_filter_res*-1;
	 	}
		 
		return buffer_filter_res;
	 
// Linjärisering med värde efter kalibrering.
// 	if (buffer_filter_res <= 1300)
// 		return 50;
// 	 else if(buffer_filter_res > 1300 && buffer_filter_res <= 1340)
// 		return 45;
// 	else if(buffer_filter_res > 1340 && buffer_filter_res <= 1460)
// 		return 40;
// 	else if(buffer_filter_res > 1460 && buffer_filter_res <= 1537)
// 		return 35;
// 	else if(buffer_filter_res > 1537 && buffer_filter_res <= 1732)
// 		return 30;
// 	else if(buffer_filter_res > 1732 && buffer_filter_res <= 1950)
// 		return 25;
// 	else if(buffer_filter_res > 1950 && buffer_filter_res <= 2147)
// 		return 20;
// 	else if(buffer_filter_res > 2147 && buffer_filter_res <= 2620)
// 		return 15;
// 	else if(buffer_filter_res > 2620)
// 		return 10;
}


