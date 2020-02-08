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
#define STASSID "test"
#define STAPSK "test"
#endif

RoveCommWifiUdp RoveComm;


//ADC Setup
#define CLK D5
#define Dout D6
#define Din D7
#define CS D8
MCP3008 adc(CLK,Din,Dout,CS);

//Define SD Ports
int SD3 = 10;
int SD2 = 9;

//LCD Setup
int lcdColumns = 16;
int lcdRows = 2;
LiquidCrystal_I2C lcd(0x38,2,1,0,4,5,6,7,3,POSITIVE);

void setup() {
  Serial.begin(115200);
  
  //WiFi Setup
  IPAddress ip(192,168,1,141);
  IPAddress gateway(192,168,1,1);
  IPAddress subnet(255,255,255,0);
  WiFi.config(ip,gateway,subnet);
  WiFi.begin(STASSID, STAPSK);
  Serial.print("Connecting to Network");
  while(WiFi.status() != WL_CONNECTED){
    Serial.print(".");
    delay(500);
  }
  Serial.println();
  Serial.print("Connected! IP address: ");
  Serial.println(WiFi.localIP());

  //LCD and PIN Setup
  lcd.begin(lcdColumns,lcdRows);
  pinMode(D0,OUTPUT);
  pinMode(D3,INPUT);
  pinMode(D6,INPUT);
  pinMode(D4,INPUT);
  pinMode(SD2,INPUT);
  pinMode(SD3,INPUT);

  RoverWelcome(lcd);

}

void loop() {
  DisplayTest(lcd,adc);
  menu(lcd,adc,SD3,SD2);
  if(WiFi.status() == WL_CONNECTED)
    digitalWrite(D0,HIGH);
  else
    digitalWrite(D0,LOW);

}
