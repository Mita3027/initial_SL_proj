#include "display.h"


void setup()
{
  Serial.begin(115200);

  Display_Init();
}

void loop()
{
  Display_Timer();
  Display_loop();
}