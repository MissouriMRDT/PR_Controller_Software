#include <Wire.h>
#include <MCP3008.h>
#include <SPI.h>
#include <LiquidCrystal_I2C.h>
#include <ESP8266WiFi.h>

#include "PR_Controller_Header.h"
#include "RoveComm.h"
#include "RoveCommManifest.h"
#include "RoveCommPacket.h"

#ifndef STASSID
#endif

RoveCommWifiUdp RoveComm;


//ADC Setup
#define CLK D5
#define Dout D6
#define Din D7
#define CS D8
#define TANK 6
MCP3008 adc(CLK,Din,Dout,CS);

//Joystick Values
#define JOY_LEFT_Y 0  //adc.readADC(0) to read value 
#define JOY_LEFT_X 1  //Max JOY value is 1023
#define JOY_RIGHT_Y 2
#define JOY_RIGHT_X 3

#define JOY_LEFT_IDLE 504.0 //Idling ADC value of Joystick
#define JOY_RIGHT_IDLE 502.0
#define JOY_HALF_MAX 511.5
#define MAX_JOY_VALUE 1023

//Drivebaord Controlls
double LEFT_VEL;      //(-1000,1000)
double RIGHT_VEL;

//Define ESP SD Ports (read as digitalRead 9/10)
int SD3 = 10;
int SD2 = 9;

//LCD Setup
int lcdColumns = 16;
int lcdRows = 2;
LiquidCrystal_I2C lcd(0x38,2,1,0,4,5,6,7,3,POSITIVE);

void setup() {
  Serial.begin(115200);
  
  //LCD and PIN Setup
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
  #define STAPSK "test1234"
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

void loop() {
  //MainDisplay(lcd,adc);
  //DisplayTest(lcd,adc);
  menu(lcd,adc,SD3,SD2);
  
  if(WiFi.status() == WL_CONNECTED)
    digitalWrite(D0,HIGH);
  else
    digitalWrite(D0,LOW);


  //Tank Drive for Valkyrie (2019)
  int LEFTRIGHT_VEL[2];
  tankDrive(JOY_LEFT_Y, JOY_RIGHT_Y, JOY_LEFT_IDLE, JOY_RIGHT_IDLE, JOY_HALF_MAX, adc,LEFTRIGHT_VEL);
    
  if(adc.readADC(TANK) > 100)
  {
   RoveComm.write(RC_DRIVEBOARD_DRIVELEFTRIGHT_DATAID,RC_DRIVEBOARD_DRIVELEFTRIGHT_DATACOUNT,LEFTRIGHT_VEL);
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
  delay(100);
  return;

}
