#ifndef API_H_INCLUDED
#define API_H_INCLUDED

#include <stdint.h> // integer definitions
#include <stdbool.h> // for the boolean variable

/** \brief It is the function that executes the main task of the robot system. It needs
    the command obtained from EEPROM.
    If robot operation is stopped by the RobotStop function, this function will restart its
    operation. This function can be interrupted.

    \param u8Command is the command obtained from EEPROM.

**/

void RobotTask(uint8_t u8Command);

/** \brief Stops immediately the robot operation.

**/

void RobotStop (void);

/** \brief Initializes a timer and enables its interrupt. The ISR is called TimerISR

**/

void TimerInit(void);

/** \brief Returns the number of us on the Timer since its initialization.

**/

uint32_t TimetGetus(void);

/** \brief Initializes the SPI module. It enables the proper configuration for operation
    with EEPROM and sensor.

**/

void SPIInit(void);

/** \brief Set to LOW the Chip select signal of the SPI protocol to allow communication
    with EEPROM.

**/

void SPIEepromEnable(void);

/** \brief Set to HIGH the Chip select signal of the SPI protocol to disable communication
    with EEPROM.

**/

void SPIEepromDisable(void);

/** \brief Set to LOW the Chip select signal of the SPI protocol to allow communication
    with Sensor.

**/

void SPISensorEnable(void);

/** \brief Set to HIGH the Chip select signal of the SPI protocol to disable communication
    with Sensor.

**/

void SPISensorDisable(void);

/** \brief Returns the value read from the SPI bus. Assume that dummy bytes
    are not needed.

    \return the value read from the SPI bus.

**/

uint8_t SPIRead(void);

#endif // API_H_INCLUDED
