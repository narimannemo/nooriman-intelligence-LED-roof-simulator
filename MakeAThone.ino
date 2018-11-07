#include "FastLED.h"
#include <ESP8266WiFi.h>
WiFiServer server(80);

#define NUM_LEDS 50
#define DATA_PIN 4

CRGB leds[NUM_LEDS];
//ESP8266WiFi webserver;

const char *ssid ="iPhone";
const char *pass ="123456aa";

String IP = "";
String html = "<html><head><h1>salam</h1></head></html>";

int s[8][3] = {{0,8,16},{1,9,17},{2,10,18},{3,11,19},{24,32,40},{25,33,41},{26,34,42},{27,35,43}};

int command = -1;
int brightness = 50;
bool change = true;

void setup() 
{ 
  FastLED.addLeds<WS2811, DATA_PIN, BRG>(leds, NUM_LEDS);
  WiFi.begin(ssid,pass);
  Serial.begin(9600);
  while(WiFi.status() != WL_CONNECTED)
  {
    Serial.print('.');
    delay(200);
  }
  Serial.println(WiFi.localIP());
  IPAddress ip  = WiFi.localIP();
  IP = String(ip[0])+'.';
  IP+= String(ip[1])+'.';
  IP+= String(ip[2])+'.';
  IP+= String(ip[3])+'.';
  server.begin();
}


void loop() 
{ 
  if(change)
  {
    leds[48] = CHSV(20,255,3);
    leds[49] = CHSV(20,255,3);
    FastLED.show();
    for(int i = 0;i<9;i++)
    {
      for (int j = 0; j<4 ;j++)
      {

          switch (command) 
          {
          case 0:  
            leds[s[i][j]] = CHSV(255,0,2);
            break;
          case 1:
            if(i==0 || i == 5)
            {
              leds[s[i][j]] = CHSV(102,0,40); 
            }
            else if(i==4)
            {
              leds[s[i][j]] = CHSV(102,0,255);
            }
            else
            {
              leds[s[i][j]]=CHSV(255,0,1);
            }
            break;
          case 2:
            if(i==4 || i==0)
            {
              leds[s[i][j]] = CHSV(102,0,255);
            }
            else if(i==1 || i==5)
            {
              leds[s[i][j]] = CHSV(102,0,20);
            }
            else
            {
              leds[s[i][j]] = CHSV(102,0,1);
            } 
            break;
          case 3:
            if(i==0)
            {
              leds[s[i][j]] = CHSV(102,0,255);
            }
            else if(i==1 || i == 4)
            {
              leds[s[i][j]] = CHSV(102,0,70);
            }
            else
            {
              leds[s[i][j]] = CHSV(102,0,1);
            }  
            break;
          case 4:
            if(i == 1 || i==2 || i == 5 || i == 6)
            {
              leds[s[i][j]] = CHSV(102,0,255);
            }
            else
            {
              leds[s[i][j]] = CHSV(102,0,1);
            }
            break;
          case 5:
            if(i == 3)
            {
              leds[s[i][j]] = CHSV(102,0,255);
            }
            else if(i==2 || i == 7)
            {
              leds[s[i][j]] = CHSV(102,0,70);
            }
            else
            {
              leds[s[i][j]] = CHSV(102,0,1);
            }
            break;
          case 6:
            if(i == 3 || i == 7)
            {
              leds[s[i][j]] = CHSV(102,0,255);
            }
            else if(i == 2 || i == 6)
            {
              leds[s[i][j]] = CHSV(102,0,20);
            }
            else
            {
              leds[s[i][j]] = CHSV(102,0,1);
            }
            break;
          case 7:
            if(i == 7)
            {
              leds[s[i][j]] = CHSV(102,0,255);
            }
            else if(i == 3 || i == 6)
            {
              leds[s[i][j]] = CHSV(102,0,70);
            }
            else
            {
              leds[s[i][j]] = CHSV(102,0,1);
            }
            break;
         case 8:
            leds[s[i][j]] = CHSV(102,0,255);
            break;
         case 9:
            if((j==2 && i<4)||(j==0 && i>3))
            {
              leds[s[i][j]] = CRGB::White;
            }
            else if((j==0 || j == 1) && i<4)
            {
              leds[s[i][j]] = CRGB::Green;
            }
            else
            {
              leds[s[i][j]] = CRGB::Red;
            }
            break;
         case 10:
            leds[s[i][j]] = CRGB::Black;
            
         
          }
        
      }
    }
  FastLED.show();
  change = false;
  } 
  
  
  WiFiClient client = server.available();
  if(!client)
  {
    return;
  }
  
  while(!client.available())
  {
    delay(1);
  }
  
  String req = client.readStringUntil('\r');
  
  if(req.indexOf("GET / HTTP/1.1") != -1)
  {
    client.print(html);
    change = true;
    command++;
    if (command == 11)
    {
      command = 0;
    }

  }
  if(req.indexOf("POST") != -1)
  {
   change = true; 
   
  }

}
