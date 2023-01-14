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
        float *outIdealHumidity);

    static void SetSensorStatus(int id, bool status);

private:
    Sensors();

    static bool IDInRange(int id);
};