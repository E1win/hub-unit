#include "./App.h"

App::App()
{
}

void App::Run()
{
    Serial.begin(9600);

    while (!Serial)
    {
    }

    Serial.println("Starting Program");

    // Initialize sensors
    Sensors::Init();

    // Initialize display
    m_display.Init();

    // Update display
    m_display.Update();
}