# 1 "c:\\Users\\aguat\\Documents\\GitHub\\Arduino-Projects\\ESP32\\Esp32_UsoDac.ino"
# 2 "c:\\Users\\aguat\\Documents\\GitHub\\Arduino-Projects\\ESP32\\Esp32_UsoDac.ino" 2
# 3 "c:\\Users\\aguat\\Documents\\GitHub\\Arduino-Projects\\ESP32\\Esp32_UsoDac.ino" 2
# 4 "c:\\Users\\aguat\\Documents\\GitHub\\Arduino-Projects\\ESP32\\Esp32_UsoDac.ino" 2

void setup()
{

}

void loop()
{
    for (int i=0;i<360;i++)
    {
        // dacWrite(26,int(128+127*(sin(i*PI/180))));
        dacWrite(26,i);
        dacWrite(25,int(128+127*(sin(i*3.1415926535897932384626433832795/180))));
    }
}
