#include <stdint.h>
#include <Arduino.h>
#include <FunctionalInterrupt.h>

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
