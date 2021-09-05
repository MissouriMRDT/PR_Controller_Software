/*
    PR Controller Software 2021
    Jared Allen
*/

#include "PR_Controller_Software.h"

void setup()
{
    Serial.begin(115200);
    RoveCommWifiUdp RoveComm;

    //for(int i = 0; i < 4; i++)
        //wheelSpeeds[i] = 0;

    lcd.begin(lcdColumns,lcdRows);

    pinMode(D0,OUTPUT);
    pinMode(D3,INPUT);
    pinMode(D6,INPUT);
    pinMode(D4,INPUT);
    pinMode(SD2,INPUT);
    pinMode(SD3,INPUT);

    lcdStartupScreen();
    lcd.createChar(5, leftMarker);
    lcd.createChar(6, rightMarker);

    //////////////////////////////
    //  RoveComm Connect
    //////////////////////////////
    //RoveComm.begin();
    Serial.println("Attempting Connection");
    lcdPrintLogo();
    lcdPrintCenter("Connecting",0,3);
    lcdPrintCenter("Aurora",1,3);
    
    int timeout = millis();
    while((millis() < timeout + 1000) || WiFi.status() == WL_CONNECTED)
        yield();

    if(WiFi.status() != WL_CONNECTED)
    {
        lcd.clear();
        lcdPrintLogo();
        lcdPrintCenter("CONNECT",0,3);
        lcdPrintCenter("FAILED",1,2);
        delay(2000);
    }
    lcd.clear();
    lcd.home();
}

void loop()
{
    //////////////////////////////  Configuration: L_SPEED   |LF_ANGLE RF_ANGLE
    //  LCD Idling Display                         R_SPEED   |LR_ANGLE RR_ANGLE
    //////////////////////////////
    lcd.home();
    lcd.write(5);
    lcd.print(String(wheelSpeeds[0]));
    lcd.setCursor(5,0);
    lcd.print(" |" + String(wheelAngles[0]) + " " + String(wheelAngles[2]));
    lcd.setCursor(0,1);
    lcd.write(6);
    lcd.print(String(wheelSpeeds[2]));
    lcd.setCursor(5,1);
    lcd.print(" |" + String(wheelAngles[1]) + " " + String(wheelAngles[3]));

    /*lcd.print("VEL:(" + String(wheelSpeeds[0]) + ","
              + String(wheelSpeeds[2]) + ")");
    lcd.setCursor(0,1);
    String anglePrint = "AGL:(" + String(wheelAngles[0]) + "," +
                        String(wheelAngles[1]) + "," + String(wheelAngles[2])
                        + "," + String(wheelAngles[3]) + ")";
    lcd.print(anglePrint);
    int charDifference = anglePrint.length() - lcdColumns;
    if(charDifference > 0)
    {
        for(int i = 0; i < charDifference; i++)
        {
            lcd.scrollDisplayLeft();
            delay(1000);
        }
        delay(1000);
        for(int i = 0; i < charDifference; i++)
        {
            lcd.scrollDisplayRight();
            delay(1000);
        }
        delay(1000);
    }*/
}