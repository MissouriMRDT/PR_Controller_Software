#ifndef PR_Controller
#define PR_Controller
#include <LiquidCrystal_I2C.h>
#include <MCP3008.h>

/////////ADC SETUP/////////
#define CLK D5
#define Dout D6
#define Din D7
#define CS D8
#define TANK 6

/////////JOYSTICK VALUES/////////
#define JOY_LEFT_Y 0  //adc.readADC(0) to read value 
#define JOY_LEFT_X 1  //Max JOY value is 1023
#define JOY_RIGHT_Y 2
#define JOY_RIGHT_X 3

#define JOY_LEFT_Y_IDLE 504.0 //Idling ADC value of Joystick
#define JOY_RIGHT_Y_IDLE 502.0
#define JOY_HALF_MAX 511.5
#define MAX_JOY_VALUE 1023
#define JOY_RIGHT_X_IDLE 513.0
#define JOY_LEFT_X_IDLE 499.0


//Displays on Start-Up
void RoverWelcome(LiquidCrystal_I2C lcd);
                             
//Menu start-up to select which rover to connect to. Returns string of network name.
String RoverSelectMenu(LiquidCrystal_I2C lcd, MCP3008 adc,int SD3, int SD2);    

//Displays all ADC Values on screen. ONLY FOR TESTING!
void DisplayTest(LiquidCrystal_I2C lcd, MCP3008 adc);

//Displays menu with 4 available sub-menus. Availalbe after network connection.
//contains funtions that call additional testing variable from TIVAs
void menu(LiquidCrystal_I2C lcd, MCP3008 adc,int SD3,int SD2, bool &backlight);

//idling display after connection to RoveComm. Displays network connection strength
void MainDisplay(LiquidCrystal_I2C lcd, MCP3008 adc, int LEFTRIGHT_VEL[]);

//Returns matrix with left and right velocity values between (-1000,1000). Activated through on-board jumper.
void tankDrive(MCP3008 adc, int LeftRight_Vel[],int MAX_SPEED);

//Returns matrix with left and right velocity values between (-1000,1000). Activated through on-baord jumper.
//Auto activated by default when no jumper is dectected. 
//Modifies joystick values to drive within a controlled fashion safe for the Rover.
//LeftJoystick = Speed    RightJoystick = Direction
void safeDrive(MCP3008 adc,int LeftRight_Vel[], int MAX_SPEED);

//adjusts max speed value to be passed to TankDrive and SafeDrive
void maxSpeed(MCP3008 adc, int & MAX_SPEED, int SD2);

//MENU FUNCTION: toggles LCD backlight normal operating mode
bool Menu_Backlight(MCP3008 adc,LiquidCrystal_I2C lcd, int SD2);

#endif
