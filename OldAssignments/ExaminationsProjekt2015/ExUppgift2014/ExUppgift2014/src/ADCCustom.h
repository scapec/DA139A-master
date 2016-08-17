/*
 * ADCCustom.h
 *
 */ 


#ifndef ADCCUSTOM_H_
#define ADCCUSTOM_H_

void ADCSetup(void);
int ADCReadSensor(void);
void calibrate(void);
int smoothSignal(void);
int smoothError(void);
void calibrateInit(void);

#endif /* ADCCUSTOM_H_ */