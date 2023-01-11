#include <Arduino.h>
#include "App.h"

App app;

void setup()
{
  app.Run();
}

void loop()
{
  // Delay to allow IDLE task time to execute.
  delay(100);
}