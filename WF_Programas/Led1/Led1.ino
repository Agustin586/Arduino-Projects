#include <Wire.h> 
#include <LiquidCrystal_I2C.h>
#include <string.h>

//Defines
#define BACKLIGHT_PIN     13
#define LED1  13
#define LED2  12
#define ADC1  A0

//Objeto
LiquidCrystal_I2C lcd(0x38);

//Variables
char cRecep[20] = {""};
uint8_t cInd=0;
bool  StringComplete=false;
bool bProc_Leds = false;
bool bProc_Lcd = false;

typedef enum
{
  est_Leds,
  est_Lcd,
  est_Adc,
  est_Uart,
  est_PcsUart
}est_Machine;
typedef struct 
{
  bool Led1;
  bool Led2;
  char lcd_buffer[20];
}stPerf_t;

est_Machine cEstate;  
stPerf_t stDate = {false,false};
uint16_t sAdcValue=0;

void setup() 
{
  Serial.begin(115200);
  pinMode(BACKLIGHT_PIN,OUTPUT);
  InitMachine(&cEstate);
}

void loop() 
{
  switch (cEstate)
  {
    case est_Uart:
    {
      char cRx;
      while(Serial.available() != 0)
      {
        cRx = Serial.read();
        if(cRx != '\n')
        {
          cRecep[cInd] = cRx;
          cInd++;
        }
        else
          StringComplete = true;
      }
      cEstate = est_PcsUart;
    break;
    }
    case est_PcsUart:
    {
      if(StringComplete == true)
      {
        if(strcmp(cRecep,"#Led1_On") == 0)
          stDate.Led1 = true,bProc_Leds = true;
        else if(strcmp(cRecep,"#Led1_Off") == 0)
        {
          stDate.Led1 = false,bProc_Leds = true;
        }
        if(strcmp(cRecep,"#Led2_On") == 0)
          stDate.Led2 = true,bProc_Leds = true;
        else if(strcmp(cRecep,"#Led2_Off") == 0)
        {
          stDate.Led2 = false,bProc_Leds = true;
        }
        if(memcmp(cRecep,"#Lcd:",sizeof(5))==0)
        {
          for(uint8_t i=4;i<cInd;i++)
            stDate.lcd_buffer[i-4] = cRecep[i];
          bProc_Lcd = true;
        }
        ClearBufferUart();
      }
      cEstate = est_Leds;
    break;
    }
    case est_Leds:
    {
      if(bProc_Leds == true)
      {
        if(stDate.Led1 == true)
          digitalWrite(LED1,HIGH),Serial.println("Led1 prendido");
        else
          digitalWrite(LED1,LOW),Serial.println("Led1 apagado");
        if(stDate.Led2 == true)
          digitalWrite(LED2,HIGH),Serial.println("Led2 prendido");
        else
          digitalWrite(LED2,LOW),Serial.println("Led2 apagado");

        bProc_Leds = false; 
      }
      cEstate = est_Lcd;   
    break;
    }
    case est_Lcd:
    {
      if(bProc_Lcd)
      {
        lcd.clear();
        lcd.setCursor(0,0);
        lcd.print(stDate.lcd_buffer);

        bProc_Lcd = false;
      }
      cEstate = est_Adc;
    break;
    }
    case est_Adc:
    {
      sAdcValue = analogRead(ADC1);
      Serial.println(sAdcValue);
      Serial.flush();

      if(Serial.available())  cEstate = est_Uart;
      else  cEstate = est_Leds;
    break;
    }
  }
}

void Inicializacion (void)
{
  pinMode(LED1,OUTPUT);
  pinMode(LED2,OUTPUT);
  digitalWrite(LED1,LOW);
  digitalWrite(LED2,LOW);

  lcd.begin(16,2);
  lcd.home();
  lcd.clear();
  lcd.setCursor(0,1);
  lcd.print("Bienvenido");
  lcd.cursor();
  lcd.blink();

  return;
}

void InitMachine(est_Machine *estate_t)
{
  *estate_t = est_Uart;

  return;
}

void ClearBufferUart(void)
{
  for(uint8_t i=0;i<20;i++)
  {
    cRecep[i] = 0;
  }
  cInd = 0;
  StringComplete = false;
}