#include <stdio.h>  // for the fprintf

#include "api.h"

volatile bool mutex = 0; //Binary mutex semaphore for the SPI
volatile bool emergency_stop = 0; //1 when an obstacle is detected, set by the ISR

void setup(void);
void main_loop(void);
uint8_t ReadEeprom(void);
uint8_t ReadSensor(void);
bool Test_and_Set(bool mutex);

/** \brief ISR. It is called every 1 ms once the TimerInit() function is executed.

**/

void TimerISR(void);



int main()
{
    printf("Running setup...\n");
    setup();
    printf("Setup finished\n");
    main_loop();

    return 0;
}

//-------------------------------- functions----------------------------------------------


void setup()
{
    SPIInit();
    TimerInit();

}

void main_loop(void)
{
    while(1)
    {
        if(emergency_stop == 1) //Must be an atomic operation
        {
            break; //the system must remain in stop state until the power supply is cycled
        }
        uint8_t u8Command = ReadEeprom();
        RobotTask(u8Command);
        printf("New loop!\n");

    }
}

//--------------------------------other functions----------------------------------------------

uint8_t ReadEeprom(void)
{
    uint8_t read;
    while(Test_and_Set(mutex) == 1) //mutex variable
    {}

    SPIEepromEnable();
    read = SPIRead();
    SPIEepromDisable();

    mutex = 0;
    return read;
}

uint8_t ReadSensor(void)
{
    uint8_t read;
    while(Test_and_Set(mutex) == 1) //mutex variable
    {}

    SPISensorEnable();
    read = SPIRead();
    SPISensorDisable();

    mutex = 0;
    return read;
}

void TimerISR(void) // The ISR
{
    uint8_t read = ReadSensor(); // The worst delay is: 1+5+1 = 7 us, which is negligible,
    // due to be reading the EEPROM. It is executed each 1000 us.
    if(read > 128 && emergency_stop == 0) // Only done once
    {
        RobotStop();
        emergency_stop = 1; // Setting the global flag
    }
}

bool Test_and_Set(bool mutex) // An atomic test&set function
{
    return 0;
}

