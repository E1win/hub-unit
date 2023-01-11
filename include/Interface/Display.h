#pragma once

#include <TFT_eSPI.h>

#include "./config.h"
#include "./Data/Sensors.h"

class Display
{
public:
    Display();

    void Init();

    void Reset();

    void Update();

private:
    TFT_eSPI m_tft;
    TFT_eSprite m_sprite;

    float m_barWidth;

private:
    void DrawStatusBar(int id, bool status);
};