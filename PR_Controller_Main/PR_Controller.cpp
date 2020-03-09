#include "PR_Controller.h"
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
	return;
}

String RoverSelectMenu(LiquidCrystal_I2C lcd, MCP3008 adc, int SD3, int SD2)
{
  int OptSelected = 0;
  String NetworkName = "Rover 2020";
  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print("  Select Rover  ");
  lcd.setCursor(0,1);
  lcd.print(":ICRS:");
  lcd.setCursor(9,1);
  lcd.print(":VALK:");
  lcd.setCursor(6,1);
  lcd.print("*");

  while(1)
  {
    yield();
    if(digitalRead(D3) == LOW)
    {
      lcd.setCursor(8,1);
      lcd.print(" ");
      lcd.setCursor(6,1);
      lcd.print("*");
      NetworkName = "Rover 2020";
      
    }
    if(digitalRead(SD3) == LOW)
    {
      lcd.setCursor(6,1);
      lcd.print(" ");
      lcd.setCursor(8,1);
      lcd.print("*");
      NetworkName = "MRDT Valkyrie";
    }
    if(adc.readADC(5) < 100)
    {
      lcd.clear();
      lcd.setCursor(0,0);
      lcd.print(NetworkName);
      lcd.setCursor(0,1);
      lcd.print("Selected");
      delay(1500);
      lcd.clear();
      lcd.setCursor(2,0);
      lcd.print("Connecting To");
      lcd.setCursor(4,1);
      lcd.print("RoveComm");
      return NetworkName;
    }
  }
  return NetworkName;
}

void DisplayTest(LiquidCrystal_I2C lcd, MCP3008 adc)
{
  double LEFT_VEL =  (((adc.readADC(0) - 504.0)/504)*(1000));
  double RIGHT_VEL = (((adc.readADC(2) - 502.0)/502)*(1000));
  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print("LX " + String(adc.readADC(1)));
  lcd.setCursor(8,0);
  lcd.print("LY " + String(adc.readADC(0)));
  lcd.setCursor(0,1);
  lcd.print("RX " + String(adc.readADC(3)));
  lcd.setCursor(8,1);
  lcd.print("RY " + String(adc.readADC(2)));
  delay(100);
  return;
}

void MainDisplay(LiquidCrystal_I2C lcd, MCP3008 adc, int LEFTRIGHT_VEL[])
{
  lcd.setCursor(0,0);
  lcd.print("STR:");
  lcd.print(WiFi.RSSI());         //Signal strength above -85 may be unusable or too weak
  lcd.print(" TANK:");
  if(adc.readADC(6) > 100)
    lcd.print("ON ");
  else
    lcd.print("OFF");

  lcd.setCursor(0,1);
  lcd.print("LV: " + LEFTRIGHT_VEL[0]);
  lcd.setCursor(8,1);
  lcd.print("RV: " + LEFTRIGHT_VEL[1]);
  return;
}

void menu(LiquidCrystal_I2C lcd, MCP3008 adc, int SD3, int SD2)
{
  if(adc.readADC(5) == LOW)
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
      if((adc.readADC(5) < 100)&&(curSel == 0)){
        exitMenu = true;
        lcd.clear();
        delay(200);
      }
    }
  }
  return;
}
void tankDrive(MCP3008 adc,int LeftRight_Vel[],int MAX_SPEED)
{
  
  int leftVelocity =  (((adc.readADC(JOY_LEFT_Y) - JOY_LEFT_Y_IDLE)/JOY_HALF_MAX)*(MAX_SPEED));      //(-1000,1000)when max speed is 1000
  int rightVelocity = (((adc.readADC(JOY_RIGHT_Y) - JOY_RIGHT_Y_IDLE)/JOY_HALF_MAX)*(MAX_SPEED));

  if((leftVelocity < 5)&&(leftVelocity > -5))
    leftVelocity = 0;
  if((rightVelocity < 5)&&(rightVelocity > -5))
    rightVelocity = 0;
  
  if(leftVelocity > MAX_SPEED)
    leftVelocity = MAX_SPEED;
  if(rightVelocity > MAX_SPEED)
    rightVelocity = MAX_SPEED;

  LeftRight_Vel[0] = leftVelocity;
  LeftRight_Vel[1] = rightVelocity;
  return;

}

void safeDrive(MCP3008 adc,int LeftRight_Vel[], int MAX_SPEED)
{
  
  ////////////////////////////////////DETERMINE MAX VELOCITY AND DIRECTION////////////////////////////////////
  int leftVelocity = 0;
  int rightVelocity = 0;
  
  leftVelocity =  (((adc.readADC(JOY_LEFT_Y) - JOY_LEFT_Y_IDLE)/JOY_HALF_MAX)*(MAX_SPEED));      //(-1000,1000) when MAX_SPEED is 1000
  rightVelocity = leftVelocity;  //match velocity across motors
  
  int dir_RY = (((adc.readADC(JOY_RIGHT_Y) - JOY_RIGHT_Y_IDLE)/JOY_HALF_MAX)*(MAX_SPEED));   
  int dir_RX = (((adc.readADC(JOY_RIGHT_X) - JOY_RIGHT_X_IDLE)/JOY_HALF_MAX)*(MAX_SPEED));    
  
  ////////////////////////////////////ADJUST VELOCITY TO MATCH GIVEN DIRECTION////////////////////////////////////

  if(leftVelocity > 50)
  {
    if((adc.readADC(JOY_RIGHT_X)) > (JOY_RIGHT_X_IDLE + 5)) //Directional joystick turning left (+5 is used for buffer)
    {
      leftVelocity = rightVelocity - (dir_RX * .5);
    }
    if((adc.readADC(JOY_RIGHT_X)) < (JOY_RIGHT_X_IDLE - 5)) //Directional joystick turning right (-5 is used for buffer)
    {
      rightVelocity = leftVelocity - (dir_RX * -.5);
    }
  }
  
  ////////////////////////////////////ADJUST VELOCITY AND APPLY SAFEGUARDS////////////////////////////////////
   
  if(leftVelocity < 5)
    leftVelocity = 0;
  if(rightVelocity < 5)
    rightVelocity = 0;
  
  if(leftVelocity > MAX_SPEED)
    leftVelocity = MAX_SPEED;
  if(rightVelocity > MAX_SPEED)
    rightVelocity = MAX_SPEED;

  LeftRight_Vel[0] = leftVelocity;
  LeftRight_Vel[1] = rightVelocity;
  
  return;
}

void maxSpeed(MCP3008 adc, int & MAX_SPEED, int SD2)
{
  if(digitalRead(SD2) == LOW)
  {
    if((MAX_SPEED - 100) > 0)
      MAX_SPEED = (MAX_SPEED - 100);
    delay(20);
  }
  if(digitalRead(D4) == LOW)
  {
    if((MAX_SPEED  + 100) <= 1000)
      MAX_SPEED = (MAX_SPEED + 100);
    delay(20);
  }
  return;
}
