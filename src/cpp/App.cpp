#include "./App.h"

App::App() : m_btn1(BUTTON1_PIN),
             m_btn2(BUTTON2_PIN)
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
    m_display.ReloadPage();

    while (true)
    {
        // Can probably refactor this to avoid having to loop

        if (DataReceiver::dataReceived)
        {
            Serial.println("App: New Data Received");
            m_display.ReloadPage();
        }

        if (m_btn1.IsPressed())
        {
            m_display.LoadNextPage();
        }
        else if (m_btn2.IsPressed())
        {
            m_display.LoadPreviousPage();
        }

        delay(400);
    }
}