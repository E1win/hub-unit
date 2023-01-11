#include "./Data/Sensors.h"

namespace
{
    bool DEFAULT_STATUS = false;

    typedef struct Sensor
    {
        int id;
        bool status;
    } Sensor;

    Sensor sensorArr[SENSOR_COUNT];
}

Sensors::Sensors()
{
}

void Sensors::Init()
{
    // Initialize Sensor Array
    for (int i = 0; i < SENSOR_COUNT; i++)
    {
        sensorArr[i] = {i, DEFAULT_STATUS};
    }
}

bool Sensors::GetSensorStatus(int id)
{
    if (IDInRange(id))
    {
        return sensorArr[id].status;
    }

    Serial.print("Given ID Not In Range: ");
    Serial.println(id);

    return false;
}

void Sensors::SetSensorStatus(int id, bool status)
{
    if (IDInRange(id))
    {
        sensorArr[id].status = status;
    }
    else
    {
        Serial.print("Given ID Not In Range: ");
        Serial.println(id);
    }
}

bool Sensors::IDInRange(int id)
{
    return id >= 0 && id < SENSOR_COUNT;
}