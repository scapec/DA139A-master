/*
 * PWMSet.h
 *
 * Created: 2015-12-10 16:04:29
 *  Author: Ali and Matko
 */


#ifndef REGLSTYR_H_
#define REGLSTYR_H_

//Defines for creation of PIDRegulationTask
#define TASK_PIDRegulation_STACK_SIZE (2048/sizeof(portSTACK_TYPE))
#define TASK_PIDRegulation_STACK_PRIORITY (2)

void task_pid (void *pvParameters);


void setup_pwm(void);
void duty_cycle_pwm(int);




#endif /* REGLSTYR_H_ */
