#include <Wire.h>
#include <MCP3008.h>
#include <SPI.h>
#include <LiquidCrystal_I2C.h>
#include <ESP8266WiFi.h>

#include "PR_Controller.h"
#include "RoveComm.h"
#include "RoveCommManifest.h"
#include "RoveCommPacket.h"

#ifndef STASSID

RoveCommWifiUdp RoveComm;

MCP3008 adc(CLK,Din,Dout,CS);

/////////DRIVEBOARD CONTROLS/////////
int MAX_SPEED = 1000;
int LEFTRIGHT_VEL[2];

/////////ESP SD PORTS/////////
int SD3 = 10;         //use as digitalRead(SD3)
int SD2 = 9;

/////////LCD INITIZALIZATION/////////
int lcdColumns = 16;
int lcdRows = 2;
LiquidCrystal_I2C lcd(0x38,2,1,0,4,5,6,7,3,POSITIVE);
//NOTE: 0x38 is the I2C address for the specific PCF chip on this board, use an
//      I2C address scanner for future iterations to determine which address is 
//      appropriate for I2C bus. I2C scanner in folder "Test Code"

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void setup() {
  Serial.begin(115200);
  LEFTRIGHT_VEL[0] = 0;
  LEFTRIGHT_VEL[1] = 0;
  
/////////LCD AND PIN SETUP/////////
  lcd.begin(lcdColumns,lcdRows);
  pinMode(D0,OUTPUT);
  pinMode(D3,INPUT);
  pinMode(D6,INPUT);
  pinMode(D4,INPUT);
  pinMode(SD2,INPUT);
  pinMode(SD3,INPUT);
  RoverWelcome(lcd);
  
  //WiFi Setup
  String NET_NAME = RoverSelectMenu(lcd,adc,SD3,SD2);
  #define STASSID NET_NAME
  //#define STAPSK "test1234"     //use only if network has password
  IPAddress ip(192,168,1,141);
  IPAddress gateway(192,168,1,1);
  IPAddress subnet(255,255,255,0);
  WiFi.config(ip,gateway,subnet);
  WiFi.begin(STASSID);
  Serial.print("Connecting to Network");
  while(WiFi.status() != WL_CONNECTED){
    Serial.print(".");
    delay(500);
  }
  Serial.println();
  Serial.print("Connected! IP address: ");
  Serial.println(WiFi.localIP());

  lcd.clear();

}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void loop() {
  //MainDisplay(lcd,adc);
  //DisplayTest(lcd,adc);
  menu(lcd,adc,SD3,SD2);
  
  if(WiFi.status() == WL_CONNECTED)
    digitalWrite(D0,HIGH);
  else
    digitalWrite(D0,LOW);


  //Tank Drive and Safe Drive
  maxSpeed(adc,MAX_SPEED,SD2);
    
  if(adc.readADC(TANK) > 100)
  {
   tankDrive(adc,LEFTRIGHT_VEL,MAX_SPEED);
   RoveComm.write(RC_DRIVEBOARD_DRIVELEFTRIGHT_DATAID,RC_DRIVEBOARD_DRIVELEFTRIGHT_DATACOUNT,LEFTRIGHT_VEL);  //currently without static IP
  }
  else
  {
    safeDrive(adc,LEFTRIGHT_VEL,MAX_SPEED);
    RoveComm.write(RC_DRIVEBOARD_DRIVELEFTRIGHT_DATAID,RC_DRIVEBOARD_DRIVELEFTRIGHT_DATACOUNT,LEFTRIGHT_VEL);  //currently without static IP
  }
  

  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print("LV " + String(LEFTRIGHT_VEL[0]));
  lcd.setCursor(8,0);
  lcd.print("STR:");
  lcd.print(WiFi.RSSI());         //Signal strength above -85 may be unusable or too weak
  lcd.setCursor(0,1);
  lcd.print("RV " + String(LEFTRIGHT_VEL[1]));
  lcd.setCursor(8,1);
  lcd.print("MAX:" + String(MAX_SPEED));
  delay(50);
  
  return;

}

#endif
