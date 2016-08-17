/*
 * UARTSet.h
 *
 * Created: 2015-12-10 16:04:29
 *  Author: Ali and Matko
 */


#ifndef UARTFUNCTIONS_H_
#define UARTFUNCTIONS_H_

void configure_console(void);

void getPIDValues(void);

#define TASK_SerialComTask_STACK_SIZE (2048/sizeof(portSTACK_TYPE))
#define TASK_SerialComTask_STACK_PRIORITY (1)

void ComTask (void *pvParameters);
#endif /* UARTFUNCTIONS_H_ */
