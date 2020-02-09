#include "PR_Controller_Header.h"
#include <ESP8266WiFi.h>

void RoverWelcome(LiquidCrystal_I2C lcd)
{
	lcd.setCursor(0,0);
	lcd.print("   Mars Rover   ");
	for(int i = 0; i<3; i++)
	{
		lcd.setCursor(i+6,1);
    delay(100);
		lcd.print(".");
		delay(400);
	}
	lcd.clear();
  lcd.setCursor(2,0);
  lcd.print("Connecting To");
  lcd.setCursor(4,1);
  lcd.print("RoveComm");
	return;
}

void DisplayTest(LiquidCrystal_I2C lcd, MCP3008 adc)
{
  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print("LX " + String(adc.readADC(0)));
  lcd.setCursor(8,0);
  lcd.print("LY " + String(adc.readADC(1)));
  lcd.setCursor(0,1);
  lcd.print("RX " + String(adc.readADC(2)));
  lcd.setCursor(8,1);
  lcd.print("RY " + String(adc.readADC(5)));
  delay(100);
  return;
}

void MainDisplay(LiquidCrystal_I2C lcd, MCP3008 adc)
{
  lcd.setCursor(0,0);
  lcd.print("NW_STR: ");
  lcd.print(WiFi.RSSI());
}

void menu(LiquidCrystal_I2C lcd, MCP3008 adc, int SD3, int SD2)
{
  if(digitalRead(D4) == LOW)
  {
    int curSel = 0;               //tracks current menu selecttion. 0-BR 1-BL 2-TR 3-TL
    int cursorX1 = 8;              //Moves cursor around LCD
    int cursorX2 = 6;
    int cursorY1 = 1;
    int cursorY2 = 0;
    int cursor_CurX;             
    int cursor_CurY;
    bool exitMenu = false;
    String optionTL = ":OPT4:";
    String optionTR = ":OPT3:";
    String optionBL = ":OPT2:";
    String optionBR = ":EXIT:";
    lcd.clear();
    lcd.setCursor(0,0);
    lcd.print(optionTL);
    lcd.setCursor(9,0);
    lcd.print(optionTR);
    lcd.setCursor(0,1);
    lcd.print(optionBL);
    lcd.setCursor(cursorX1,cursorY2);
    cursor_CurX = cursorX1; cursor_CurY = cursorY2;
    lcd.print("*");
    lcd.setCursor(9,1);
    lcd.print(optionBR);
    while(exitMenu == false)
    {
      yield();
      if(digitalRead(D3)==LOW){
        lcd.setCursor(cursor_CurX,cursor_CurY);
        lcd.print(" ");
        lcd.setCursor(cursorX2,cursor_CurY);
        cursor_CurX = cursorX2;
        lcd.print("*");
      }
      if(digitalRead(SD2)==LOW){
        lcd.setCursor(cursor_CurX,cursor_CurY);
        lcd.print(" ");
        lcd.setCursor(cursor_CurX, cursorY1);
        cursor_CurY = cursorY1;
        lcd.print("*");
      }
      if(digitalRead(SD3)==LOW){
        lcd.setCursor(cursor_CurX,cursor_CurY);
        lcd.print(" ");
        lcd.setCursor(cursorX1,cursor_CurY);
        cursor_CurX = cursorX1;
        lcd.print("*");
      }
      if(digitalRead(D4)==LOW){
        lcd.setCursor(cursor_CurX,cursor_CurY);
        lcd.print(" ");
        lcd.setCursor(cursor_CurX,cursorY2);
        cursor_CurY = cursorY2;
        lcd.print("*");
      }
      if((cursor_CurX == cursorX2)&&(cursor_CurY == cursorY2))
        curSel = 3;
      if((cursor_CurX == cursorX1)&&(cursor_CurY == cursorY2))
        curSel = 2;
      if((cursor_CurX == cursorX2)&&(cursor_CurY == cursorY1))
        curSel = 1;
      if((cursor_CurX == cursorX1)&&(cursor_CurY == cursorY1))
        curSel = 0;
      if((adc.readADC(5) < 100)&&(curSel == 0))
        exitMenu = true;
    }
  }
  return;
}
