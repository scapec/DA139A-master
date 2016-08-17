/*
* PIDRegulation.c
*
*/
#include <asf.h>
#include "PIDRegulation.h"
#include "inttypes.h"
#include "PWMCustom.h"
#include "ADCCustom.h"
#include "global_variables.h"
#include "UARTFunctions.h"

// PID function
void PIDRegulate(void){
	
	double P_SET = 0;
	double I_SET = 0;
	double D_SET = 0;
		float temp = 0;
		 	int k;
		 	static float xbuff[M+1] = {0};
		 	static float b[M+1] = {0.25,0.25,0.25,0.25};
		
		// Read raw sensor distance from ADC
		adc_start(ADC);
		while((adc_get_status(ADC) & 0x1<<24)==0);  // Wait until DRDY(Data Ready) is HIGH
		distance = adc_get_latest_value(ADC);
		
		for(k = M-1;k >= 0;k--)
		{
		xbuff[k+1] = xbuff[k];
		}
		xbuff[0] = distance;
		
		for(k = 0;k <= M;k++)
		{
		temp += b[k]*xbuff[k];
		}
		
		distance = (uint16_t)temp;
	
	// Calculate error
	error = (distanceSetCM - distance);

//	 P_SET = error;
 	I_SET = (I_SET + (error * dTime));
 	D_SET = (double) ((error - old_error) / dTime);
 	old_error = error;
 	
 	output_value = (P_CONSTANT * (error + (D_SET * D_CONSTANT) + (I_CONSTANT / I_SET)));
 
// 	output_value = P_CONSTANT * error;

	if (output_value > 999)
	{
		output_value = 999;
	}
	else if (output_value < 0)
	{
		output_value = 0;
	}

	// Send the output_value to fan
	PWMDutyCycle(output_value);
	
	//printf("00000000\n\r");
}
