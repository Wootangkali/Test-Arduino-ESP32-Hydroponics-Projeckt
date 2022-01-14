
#include <EEPROM.h>
#include "other.h"

#define ADR_PH4 0
#define ADR_PH7 4
#define RESOLUTION 4095.0f

class PHSensor
{
private:
    float ph7, ph4, m, b;
    const uint8_t phSensorPin;
    float _readPH(int reading) { return m * (reading / RESOLUTION) + b; }

public:
    PHSensor(uint8_t phSensorPin_) : phSensorPin(phSensorPin_) {}

    void init();
    float readPH();
    uint16_t getReading() { return analogRead(phSensorPin); }
    void calibrate(char input);
    void clear();
    uint8_t EEPROMstatus();
    String retEEPROMvalues();
};

void PHSensor::init()
{
    EEPROM.get(ADR_PH7, ph7);        //0.4;
    EEPROM.get(ADR_PH4, ph4);        //0.36;
    m = (7.0f - 4.0f) / (ph7 - ph4); // slope 3/-0.04 = 75
    b = 7.0f - (m * ph7);            // y intercept 7-(75*0.4) = -23
}

float PHSensor::readPH()
{
    uint8_t amount = 100;
    float avg = 0.0f;
    for (uint8_t i = 0; i < amount; i++)
    {
        if (EEPROMstatus() == 3)
            avg += _readPH(getReading());
        else
            avg += fmap((float)getReading(), 0.0f, RESOLUTION, 0.0f, 14.0f);
        delay(1000 / amount);
    }
    return avg / amount;
}

void PHSensor::calibrate(char input)
{
    if (input == '7')
        EEPROM.put(ADR_PH7, getReading() / RESOLUTION);
    else if (input == '4')
        EEPROM.put(ADR_PH4, getReading() / RESOLUTION);
    EEPROM.commit();
    init();
}

void PHSensor::clear()
{
    EEPROM.put(ADR_PH4, 0.0f);
    EEPROM.put(ADR_PH7, 0.0f);
    EEPROM.commit();
    init();
}

uint8_t PHSensor::EEPROMstatus()
{
    // returns 0 if empty, 1 if ph4 is full, 2 if ph7 is full, and 3 if everything is full
    uint8_t result = 0;
    if (ph4)
        result += 1;
    if (ph7)
        result += 2;
    return result;
}

String PHSensor::retEEPROMvalues()
{
    return "7: " + String(ph7) + ", 4: " + String(ph4);
}
