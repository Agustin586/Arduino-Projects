#line 1 "c:\\Users\\aguat\\Documents\\GitHub\\Arduino-Projects\\ESP32\\Esp32_UsoDac.ino"
#include <stdint.h>
#include <Arduino.h>
#include <FunctionalInterrupt.h>

#line 5 "c:\\Users\\aguat\\Documents\\GitHub\\Arduino-Projects\\ESP32\\Esp32_UsoDac.ino"
void setup();
#line 10 "c:\\Users\\aguat\\Documents\\GitHub\\Arduino-Projects\\ESP32\\Esp32_UsoDac.ino"
void loop();
#line 5 "c:\\Users\\aguat\\Documents\\GitHub\\Arduino-Projects\\ESP32\\Esp32_UsoDac.ino"
void setup()
{
	
}

void loop()
{
    for (int i=0;i<360;i++)
    {
        // dacWrite(26,int(128+127*(sin(i*PI/180))));
        dacWrite(26,i);
        dacWrite(25,int(128+127*(sin(i*PI/180))));
    }
}

