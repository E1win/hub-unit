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

void Sensors::GetSensorData(
    int id,
    bool *outStatus,
    float *outTemperature,
    float *outIdealTemperature,
    float *outHumidity,
    float *outIdealHumidity)
{
    if (!IDInRange(id))
    {
        Serial.println("Given Sensor ID not in range, returning default values");

        *outStatus = false;
        *outTemperature = 0.f;
        *outIdealTemperature = 0.f;
        *outHumidity = 0.f;
        *outIdealHumidity = 0.f;
    }

    *outStatus = sensorArr[id].status;

    // TEMPORARY VALUES FOR TESTING
    *outTemperature = 20.f;
    *outIdealTemperature = 20.f;
    *outHumidity = 20.f;
    *outIdealHumidity = 20.f;
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