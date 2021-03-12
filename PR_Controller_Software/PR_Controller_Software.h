#ifndef PR_CONTROLLER_SOFTWARE
#define PR_CONTROLLER_SOFTWARE

#include <MCP3008.h>
#include <ESP8266WiFi.h>
#include <SPI.h>
#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include "RoveComm.h"
#include "lcd.h"

////////////////////////////
//  DRIVEBOARD CONTROLS
////////////////////////////
const int MAX_SPEED = 1000;
uint8_t wheelSpeeds[4];     //FL,RL,FR,RR
uint8_t wheelAngles[4];     //FL,RL,FR,RR

////////////////////////////
//  LCD INITIALIZATION
////////////////////////////
const int lcdColumns = 16;
const int lcdRows = 2;
bool lcdBacklight = false;
LiquidCrystal_I2C lcd(0x38,2,1,0,4,5,6,7,3,POSITIVE);
//NOTE: 0x38 is the I2C address for the specific PCF chip on this board, use an
//      I2C address scanner for future iterations to determine which address is 
//      appropriate for I2C bus. I2C scanner in folder "Test Code"

////////////////////////////
//  ESP SD PINS
////////////////////////////
const int SD3 = 10;
const int SD2 = 9;

////////////////////////////
//  ADC PINS
////////////////////////////
#define CLK     D5
#define Dout    D6
#define Din     D7
#define CS      D8
#define TANK    6

////////////////////////////
//  JOYSTICK VALUES
////////////////////////////
#define JOY_LEFT_Y      0       //adc.readADC(0) to read Y value
#define JOY_LEFT_X      1
#define JOY_RIGHT_Y     2
#define JOY_RIGHT_X     3

#define JOY_LEFT_Y_IDLE     504.0 //Idling ADC value of Joystick
#define JOY_RIGHT_Y_IDLE    502.0
#define JOY_HALF_MAX        511.5
#define MAX_JOY_VALUE       1023
#define JOY_RIGHT_X_IDLE    513.0
#define JOY_LEFT_X_IDLE     499.0

////////////////////////////
//  CUSTOM CHARACTERS
////////////////////////////

//Print as -->  TL TM TR
//              BL BM
byte roveLogoBL[] = {
B11110,
B11100,
B11001,
B00011,
B00111,
B00000,
B00000,
B00000
};

byte roveLogoBM[] = {
B01111,
B11111,
B11111,
B11110,
B11100,
B00000,
B00000,
B00000
};

byte roveLogoTL[] = {
B00000,
B00000,
B00000,
B00111,
B01111,
B11111,
B11111,
B11111
};

byte roveLogoTM[] = {
B00000,
B00000,
B00000,
B11110,
B11100,
B11001,
B11011,
B10011
};

byte roveLogoTR[] = {
B00100,
B01100,
B11000,
B10000,
B00000,
B00000,
B00000,
B00000 
};

void lcdPrintCenter(String text, int row) 
{
  uint newColumn = (lcdColumns/2) - (text.length()/2);
  lcd.setCursor(newColumn,row);
  lcd.print(text);
}

//Centers based on offset given
void lcdPrintCenter(String text, int row, int columnOffset)
{
  uint newColumn = (lcdColumns/2) - (text.length()/2);
  if(text.length() % 2 != 0)
    newColumn--;
  newColumn += columnOffset - 1; //Column starts at zero
  lcd.setCursor(newColumn,row);
  lcd.print(text);
}

void lcdPrintLogo()
{
    lcd.createChar(0, roveLogoBL);
    lcd.createChar(1, roveLogoBM);
    lcd.createChar(2, roveLogoTL);
    lcd.createChar(3, roveLogoTM);
    lcd.createChar(4, roveLogoTR);

    lcd.clear();
    lcd.home();
    lcd.write(2);
    lcd.setCursor(1,0);
    lcd.write(3);
    lcd.setCursor(0,1);
    lcd.write(0);
    lcd.setCursor(1,1);
    lcd.write(1);
    lcd.setCursor(2,0);
    lcd.write(4);
}

void lcdStartupScreen()
{
    lcdPrintLogo();
    lcdPrintCenter("Mars Rover", 0, 3);
    lcd.setCursor(8,1);
    for(int i=0; i<3; i++)
    {
      delay(500);
      lcd.print(".");
    }
    delay(500);
    lcd.clear();
}

void lcdMenu()
{

}

#endif