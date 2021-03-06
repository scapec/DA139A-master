/*
*
* Created: 2013-11-25 16:16:35
* Author: Tommy
*
* Modified by Ali & Matko
*
*/

#include "asf.h"
#include "adc_dac.h"

void adc_configur()
{
	
	adc_enable_channel(ADC, ADC_CHANNEL_10);				//PB17 - AD8 for Arduino Due
	adc_configure_timing(ADC, 0, 0, 0);
	adc_set_resolution(ADC, ADC_MR_LOWRES_BITS_12);			//0-4095
	adc_configure_trigger(ADC, ADC_TRIG_SW, 0);				//trig just by software
	pmc_enable_periph_clk(ID_ADC);
	adc_init(ADC, sysclk_get_main_hz(), 2000000, 0);		//Configure for maximum frequency @ 84 MHz
		
}