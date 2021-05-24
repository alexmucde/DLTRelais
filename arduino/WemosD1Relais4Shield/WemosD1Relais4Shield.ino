#include <WLed.h>
#include <WRelais.h>
#include <WSerial.h>

WLed led;
WRelais relais1(D7);
WRelais relais2(D6);
WRelais relais3(D5);
WRelais relais4(D2);
WSerial serial;
WTimer timer;

void setup()
{
  serial.setup();
  led.setup();
  relais1.setup();
  relais2.setup();
  relais3.setup();
  relais4.setup();
  timer.setup();
  timer.start(1000);
  relais1.off();
  relais2.off();
  relais3.off();
  relais4.off();
  
  Serial.println("R10");
  Serial.println("R20");
  Serial.println("R30");
  Serial.println("R40");
}

void loop()
{
  relais1.loop();
  relais2.loop();
  relais3.loop();
  relais4.loop();

  switch(timer.event())
  {
    case WTimer::Expired:
      Serial.println("WD");     
      timer.start(1000);
      break;
  }
  
  switch(serial.event())
  {
    case WSerial::Connected:
      if(relais1.isOn())
        Serial.println("R11");
      else
        Serial.println("R10");
      if(relais2.isOn())
        Serial.println("R21");
      else
        Serial.println("R20");
      if(relais3.isOn())
        Serial.println("R31");
      else
        Serial.println("R30");
      if(relais4.isOn())
        Serial.println("R41");
      else
        Serial.println("R40");
      break;
    case WSerial::Disconnected:
      break;
    case WSerial::Line:
      String text = serial.line();
      if(text[0]=='R')
      {
        if(text[1]>='1' || text[1]<='5')
        {          
          if(text[2]=='0')
          {
            if(text[1]=='1')
              relais1.off();
            else if(text[1]=='2')
              relais2.off();
            else if(text[1]=='3')
              relais3.off();
            else if(text[1]=='4')
              relais4.off();
          }      
          else if(text[2]=='1')
          {
            if(text[1]=='1')
              relais1.on();
            else if(text[1]=='2')
              relais2.on();
            else if(text[1]=='3')
              relais3.on();
            else if(text[1]=='4')
              relais4.on();
          }      
          else if(text[2]=='T')
          {
            if(text[1]=='1')
              relais1.trigger(500);
            else if(text[1]=='2')
              relais2.trigger(500);
            else if(text[1]=='3')
              relais3.trigger(500);
            else if(text[1]=='4')
              relais4.trigger(500);
          }      
        }
      }
      break;
  }
  
}
