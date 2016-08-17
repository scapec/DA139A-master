/*
 * UARTFunctions.h
 *
 * Created: 2015-11-14 01:49:50
 *  Author: Stefan
 */ 


#ifndef UARTFUNCTIONS_H_
#define UARTFUNCTIONS_H_

int receiveByte(void);
void configure_console(void);

void getPIDValues(void);
void setPIDValues(void);
void sendValues(void);

void printDouble(double, int);
#endif /* UARTFUNCTIONS_H_ */