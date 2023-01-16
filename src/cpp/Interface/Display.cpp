#include "./Interface/Display.h"

Display::Display() : m_tft(DISPLAY_WIDTH, DISPLAY_HEIGHT),
                     m_sprite(&m_tft)
{
    m_barWidth = DISPLAY_HEIGHT / SENSOR_COUNT;

    pageIndex = 0;
    currentPage = Overview;
}

void Display::Init()
{
    m_tft.init();

    m_tft.setRotation(1);
    m_tft.setTextDatum(MC_DATUM);

    m_sprite.setTextDatum(TL_DATUM);
    m_sprite.createSprite(DISPLAY_HEIGHT, DISPLAY_WIDTH);

    Reset();
}

void Display::Reset()
{
    m_tft.fillScreen(TFT_BLACK);

    m_sprite.setTextSize(2);
    m_sprite.setTextDatum(TL_DATUM);
    m_sprite.setTextColor(TFT_BLACK);
    m_sprite.fillRect(0, 0, DISPLAY_HEIGHT, DISPLAY_WIDTH, TFT_BLACK);
    m_sprite.pushSprite(0, 0);
}

void Display::ReloadPage()
{
    LoadPage();
}

void Display::LoadNextPage()
{
    int newIndex = pageIndex + 1;

    if (PageIndexOutOfRange(newIndex))
    {
        // If it's not the last page,
        // Set current page to next page
        if (currentPage != Sensor)
        {
            Reset();
            currentPage = (Pages)(currentPage + 1);
        }
    }
    else
    {
        pageIndex = newIndex;
    }

    LoadPage();
}

void Display::LoadPreviousPage()
{
    int newIndex = pageIndex - 1;

    if (PageIndexOutOfRange(newIndex))
    {
        // If it's not the first page,
        // Set current page to previous page
        if (currentPage != Overview)
        {
            Reset();
            currentPage = (Pages)(currentPage - 1);
        }
    }
    else
    {
        pageIndex = newIndex;
    }

    LoadPage();
}

void Display::LoadPage()
{
    switch (currentPage)
    {
    case Overview:
        pageIndex = 0;
        m_sprite.setTextDatum(MC_DATUM);

        for (int i = 0; i < SENSOR_COUNT; i++)
        {
            Serial.print("Drawing status bar: ");
            Serial.println(i);
            bool alarmGoingOff = Sensors::GetSensorStatus(i);

            DrawStatusBar(i, Sensors::GetSensorStatus(i));
            if (alarmGoingOff)
            {
                float temperature, idealTemperature, humidity, idealHumidity, maxTemperatureDeviation, maxHumidityDeviation;

                Sensors::GetSensorData(
                    i,
                    &alarmGoingOff,
                    &temperature,
                    &idealTemperature,
                    &humidity,
                    &idealHumidity,
                    &maxTemperatureDeviation,
                    &maxHumidityDeviation);

                float xPos = i * m_barWidth + (m_barWidth / 2);
                float yPos = DISPLAY_WIDTH - 10;

                // replace background of sensor

                if (abs(temperature - idealTemperature) >= maxTemperatureDeviation)
                {
                    m_sprite.drawString("C", xPos, yPos);
                    yPos -= 20;
                }

                Serial.println(maxHumidityDeviation);
                if (abs(humidity - idealHumidity) >= maxHumidityDeviation)
                {
                    m_sprite.drawString("RV", xPos, yPos);
                }

                // Draw icon of reason why alarm is going off
                // put at bottom of bar
            }
        }
        break;
    case Sensor:
        DrawPageSensor(pageIndex);
        break;
    }

    m_sprite.pushSprite(0, 0);
}

void Display::Update()
{
}

void Display::DrawPageSensor(int id)
{
    m_sprite.setTextColor(TFT_WHITE, TFT_BLACK, true);

    float temperature, idealTemperature, humidity, idealHumidity, maxTemperatureDeviation, maxHumidityDeviation;

    bool status;

    Sensors::GetSensorData(
        id,
        &status,
        &temperature,
        &idealTemperature,
        &humidity,
        &idealHumidity,
        &maxTemperatureDeviation,
        &maxHumidityDeviation);

    Serial.println("Drawing Sensor Page using these values");
    Serial.println(id);
    Serial.println(status);
    Serial.println(temperature);
    // ROW 1
    m_sprite.drawString(String(id), colOne, rowOne);
    m_sprite.drawString("Huidig", colTwo, rowOne);
    m_sprite.drawString("Gewenst", colThree, rowOne);

    // BAR INDICATING ALARM STATUS
    uint32_t color = status ? TFT_RED : TFT_GREEN;
    m_sprite.fillRect(rowOne - yPadding, 0, 5, DISPLAY_WIDTH / 3, color);

    // DIVIDING LINE ROW 1 - ROW 2
    m_sprite.drawLine(0, rowTwo - yPadding, DISPLAY_HEIGHT, rowTwo - yPadding, TFT_WHITE);

    // DIVIDING LINE ROW 2 - ROW 3
    m_sprite.drawLine(0, rowThree - yPadding, DISPLAY_HEIGHT, rowThree - yPadding, TFT_WHITE);

    // DIVIDING LINE COL 1 - COL 2
    m_sprite.drawLine(colTwo - xPadding, 0, colTwo - xPadding, DISPLAY_WIDTH, TFT_WHITE);

    // ROW 2

    m_sprite.drawString("C", colOne, rowTwo);
    m_sprite.drawString(String(temperature) + "C", colTwo, rowTwo);
    m_sprite.drawString(String(idealTemperature) + "C", colThree, rowTwo);

    // ROW 3

    m_sprite.drawString("RV", colOne, rowThree);
    m_sprite.drawString(String(humidity) + "%", colTwo, rowThree);
    m_sprite.drawString(String(idealHumidity) + "%", colThree, rowThree);
}

/////////////////////////////////
// PRIVATE
/////////////////////////////////

bool Display::PageIndexOutOfRange(int index)
{
    int range = pageRanges[currentPage];

    if (index < 0 || index >= range)
    {
        return true;
    }

    return false;
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