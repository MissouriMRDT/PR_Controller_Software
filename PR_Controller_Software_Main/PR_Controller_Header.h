#ifndef PR_Controller_Header
#define PR_Controller_Header
#include <LiquidCrystal_I2C.h>
#include <MCP3008.h>

//Displays on Start-Up
void RoverWelcome(LiquidCrystal_I2C lcd);
                             
//Menu start-up to select which rover to connect to. Returns string of network name.
String RoverSelectMenu(LiquidCrystal_I2C lcd, MCP3008 adc,int SD3, int SD2);    

//Displays all ADC Values on screen. ONLY FOR TESTING!
void DisplayTest(LiquidCrystal_I2C lcd, MCP3008 adc);

//Displays menu with 4 available sub-menus. Availalbe after network connection.
//contains funtions that call additional testing variable from TIVAs
void menu(LiquidCrystal_I2C lcd, MCP3008 adc,int SD3,int SD2);

//idling display after connection to RoveComm. Displays network connection strength
void MainDisplay(LiquidCrystal_I2C lcd, MCP3008 adc);

//Returns matrix with left and right velocity values between (-1000,1000). Activated through on-board jumper.
void tankDrive(int joyLeftY, int joyRightY, float joyLeftIdle, float joyRightIdle, float joyHalfMax, MCP3008 adc, int LeftRight_Ve[],int MAX_SPEED);

//Returns matrix with left and right velocity values between (-1000,1000). Activated through on-baord jumper.
//Auto activated by default when no jumper is dectected. 
//Modifies joystick values to drive within a controlled fashion safe for the Rover.
//LeftJoystick = Speed    RightJoystick = Direction
void safeDrive(int joyLeftY, int joyRightY, int joyLeftX, int joyRightX, float joyLeftIdle, float joyRightIdle, float joyHalfMax, MCP3008 adc, int leftRight_Ve[]);

//adjusts max speed value to be passed to TankDrive and SafeDrive
void maxSpeed(MCP3008 adc, int & MAX_SPEED, int SD2);

#endif
