#include "PHControlSystem.h"

PHControlSystem app{ { 0, 10 }, 8, { 9, 3 }, { 10, 2 }, { 11, 1 } };

void setup()
{
    Serial.begin(9600);
    app.Run();
}

void loop() 
{
    app.Refresh();
}
