#pragma once

#include "config.h"
#include "Arduino.h"

class Sensors
{
public:
    static void Init();

    static bool GetSensorStatus(int id);

    static void GetSensorData(
        int id,
        bool *outStatus,
        float *outTemperature,
        float *outIdealTemperature,
        float *outHumidity,
        float *outIdealHumidity,
        float *outMaxTemperatureDeviation,
        float *outMaxHumidityDeviation);

    static void SetSensorStatus(int id, bool status);

    static void SetSensorData(
        int id,
        bool status,
        float temperature,
        float idealTemperature,
        float humidity,
        float idealHumidity);

private:
    Sensors();

    static bool IDInRange(int id);
};