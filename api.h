#ifndef API_H_INCLUDED
#define API_H_INCLUDED

#include <stdint.h> // integer definitions
#include <stdbool.h> // for the boolean variable


void RobotTask(uint8_t u8Command);

void RobotStop (void);

void TimerInit(void);

uint32_t TimetGetus(void);

void SPIInit(void);

void SPIEepromEnable(void);

void SPIEepromDisable(void);

void SPISensorEnable(void);

void SPISensorDisable(void);

uint8_t SPIRead(void);

#endif // API_H_INCLUDED
