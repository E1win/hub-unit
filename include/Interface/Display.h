#pragma once

#include <TFT_eSPI.h>

#include "./config.h"
#include "./Data/Sensors.h"

class Display
{
public:
    enum Pages
    {
        Overview,
        Sensor,
    };

public:
    Display();

    void Init();

    void Reset();

    void ReloadPage();
    void LoadNextPage();
    void LoadPreviousPage();

    void Update();

private:
    TFT_eSPI m_tft;
    TFT_eSprite m_sprite;

    int pageIndex = 0;

    Pages currentPage = Overview;

    int pageRanges[2] = {
        1,
        SENSOR_COUNT};

    float m_barWidth;

    float xPadding = 10;
    float yPadding = 10;
    float spaceForIcon = 40;

    float rowOne = yPadding;
    float rowTwo = DISPLAY_WIDTH / 3 + yPadding;
    float rowThree = DISPLAY_WIDTH / 3 * 2 + yPadding;

    float colOne = xPadding;
    float colTwo = xPadding + spaceForIcon;
    float colThree = DISPLAY_HEIGHT / 2 + spaceForIcon;

private:
    void LoadPage();

    void DrawPageSensor(int id);

    bool PageIndexOutOfRange(int index);
    void DrawStatusBar(int id, bool status);
};