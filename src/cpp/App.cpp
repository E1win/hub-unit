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

    Serial.println("Starting Program...");

    // Initialize sensors
    Sensors::Init();

    m_dataReceiver.Init();

    // Initialize display
    m_display.Init();

    // Update display
    m_display.Update();

    while (true)
    {
        // Can probably refactor this to avoid having to loop

        if (DataReceiver::dataReceived)
        {
            Serial.println("App: New Data Received");
            m_display.Update();
        }

        delay(500);
    }
}