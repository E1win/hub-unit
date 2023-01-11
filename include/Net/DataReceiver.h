#pragma once

#include "Arduino.h"
#include <WiFi.h>
#include "ESPNowW.h"

#include "./Data/Sensors.h"

class DataReceiver
{
public:
    DataReceiver();

    void Init();

    static bool dataReceived;

private:
    // 24:6F:28:25:30:30
    uint8_t mac[6] = {0x24, 0x6F, 0x28, 0x25, 0x30, 0x30};
};