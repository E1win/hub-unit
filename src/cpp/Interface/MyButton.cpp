#include "./Interface/MyButton.h"

MyButton::MyButton(byte pin)
{
    pinMode(pin, INPUT_PULLUP);

    m_pin = pin;

    xTaskCreate(
        Loop,     // Task to be executed
        "Button", // Name of task (for debugging)
        1000,     // Bytes to reserve for program
        this,     // Parameters
        1,        // Priority
        NULL);    // Handler
}

void MyButton::Loop(void *params)
{
    MyButton *instance = (MyButton *)params;

    int _prevState = HIGH;
    int _state = HIGH;

    for (;;)
    {
        _prevState = _state;

        _state = digitalRead(instance->m_pin);

        if (_prevState == HIGH && _state == LOW)
        {
            instance->m_pressed = true;
        }

        // Delay to give IDLE task time to execute.
        vTaskDelay(100);
    }
}

bool MyButton::IsPressed()
{
    if (m_pressed)
    {
        m_pressed = false;
        return true;
    }

    return false;
}