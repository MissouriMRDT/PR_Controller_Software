/*
    PR Controller Software 2021
    Jared Allen
*/

#include "PR_Controller_Software.h"

void setup()
{
    Serial.begin(115200);
    RoveCommWifiUdp RoveComm;

    for(int i = 0; i < 4; i++)
        wheelSpeeds[i] = 0;

    lcd.begin(lcdColumns,lcdRows);

    pinMode(D0,OUTPUT);
    pinMode(D3,INPUT);
    pinMode(D6,INPUT);
    pinMode(D4,INPUT);
    pinMode(SD2,INPUT);
    pinMode(SD3,INPUT);

    lcdStartupScreen();

    //////////////////////////////
    //  RoveComm Connect
    //////////////////////////////
    //RoveComm.begin();
    Serial.println("Attempting Connection");
    lcdPrintLogo();
    lcdPrintCenter("Connecting",0,3);
    lcdPrintCenter("Aurora",1,3);
    
    int timeout = millis();
    while((millis() < timeout + 10000) || WiFi.status() == WL_CONNECTED)
        yield();

    if(WiFi.status() != WL_CONNECTED)
    {
        lcd.clear();
        lcdPrintLogo();
        lcdPrintCenter("CONNECT",0,3);
        lcdPrintCenter("FAILED",1,2);
    }
    
}

void loop()
{
    
}