#include "./Interface/Display.h"

Display::Display() : m_tft(DISPLAY_WIDTH, DISPLAY_HEIGHT),
                     m_sprite(&m_tft)
{
    m_barWidth = DISPLAY_HEIGHT / SENSOR_COUNT;
}

void Display::Init()
{
    m_tft.init();

    m_tft.setRotation(1);
    m_tft.setTextDatum(MC_DATUM);

    m_sprite.createSprite(DISPLAY_HEIGHT, DISPLAY_WIDTH);

    Reset();
}

void Display::Reset()
{
    m_tft.fillScreen(TFT_BLACK);

    m_sprite.setTextSize(2);
    m_sprite.setTextDatum(MC_DATUM);
    m_sprite.setTextColor(TFT_BLACK);
    m_sprite.fillRect(0, 0, DISPLAY_HEIGHT, DISPLAY_WIDTH, TFT_BLACK);
    m_sprite.pushSprite(0, 0);
}

void Display::Update()
{
    for (int i = 0; i < SENSOR_COUNT; i++)
    {
        Serial.print("Drawing status bar: ");
        Serial.println(i);
        DrawStatusBar(i, Sensors::GetSensorStatus(i));
    }

    m_sprite.pushSprite(0, 0);
}

void Display::DrawStatusBar(int id, bool status)
{
    float xPos = id * m_barWidth;

    u_int32_t color = TFT_GREEN;

    if (status)
        color = TFT_RED;

    // Create bar with color indicating status of sensor
    m_sprite.fillRect(xPos, 0, m_barWidth, DISPLAY_WIDTH, color);

    // Create outlines to separate bars
    m_sprite.drawRect(xPos, 0, m_barWidth, DISPLAY_WIDTH, TFT_BLACK);

    // Draw text showing ID of sensor
    m_sprite.drawString(String(id), xPos + (m_barWidth / 2), 20);
}