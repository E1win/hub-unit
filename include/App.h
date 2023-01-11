#pragma once

#include "Arduino.h"
#include "./config.h"

#include "./Data/Sensors.h"
#include "./Interface/Display.h"

class App
{
public:
    App();

    void Run();

private:
    Display m_display;
};