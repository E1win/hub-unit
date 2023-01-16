#pragma once

#include "Arduino.h"
#include "./config.h"

#include "./Data/Sensors.h"
#include "./Interface/Display.h"
#include "./Interface/MyButton.h"
#include "./Net/DataReceiver.h"

class App
{
public:
    App();

    void Run();

private:
    Display m_display;
    DataReceiver m_dataReceiver;
    MyButton m_btn1;
    MyButton m_btn2;
};