#include "./Data/Sensors.h"

namespace
{
    bool DEFAULT_STATUS = false;

    typedef struct Sensor
    {
        int id;
        bool status;
        float temperature;
        float idealTemperature;
        float humidity;
        float idealHumidity;
        float maxTemperatureDeviation;
        float maxHumidityDeviation;
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
        sensorArr[i] = {i, DEFAULT_STATUS, 10.f, 10.f, 10.f, 10.f, 2.f, 10.f};
    }
}

void Sensors::GetSensorData(
    int id,
    bool *outStatus,
    float *outTemperature,
    float *outIdealTemperature,
    float *outHumidity,
    float *outIdealHumidity,
    float *outMaxTemperatureDeviation,
    float *outMaxHumidityDeviation)
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
    *outTemperature = sensorArr[id].temperature;
    *outIdealTemperature = sensorArr[id].idealTemperature;
    *outHumidity = sensorArr[id].humidity;
    *outIdealHumidity = sensorArr[id].idealHumidity;
    *outMaxTemperatureDeviation = sensorArr[id].maxTemperatureDeviation;
    *outMaxHumidityDeviation = sensorArr[id].maxHumidityDeviation;
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

void Sensors::SetSensorData(
    int id,
    bool status,
    float temperature,
    float idealTemperature,
    float humidity,
    float idealHumidity)
{
    if (IDInRange(id))
    {
        sensorArr[id].status = status;
        sensorArr[id].temperature = temperature;
        sensorArr[id].idealTemperature = idealTemperature;
        sensorArr[id].humidity = humidity;
        sensorArr[id].idealHumidity = idealHumidity;
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