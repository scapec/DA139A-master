/*
* PIDRegulation.h
*
* Created: 2015-08-19 23:25:14
*  Author: Rama
*/


#ifndef PID_H_
#define PID_H_

//Defines for creation of PIDRegulationTask
#define TASK_PIDRegulation_STACK_SIZE (2048/sizeof(portSTACK_TYPE))
#define TASK_PIDRegulation_STACK_PRIORITY (4)

void PIDTask (void *pvParameters);
void Regulation(void);
unsigned int get_distance(void);
void testPrintADC();
void testFans();
#endif /* PID_H_ */