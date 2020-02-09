
#ifndef PR_Controller_Header
#define PR_Controller_Header
#include <LiquidCrystal_I2C.h>
#include <MCP3008.h>

void RoverWelcome(LiquidCrystal_I2C lcd);                             //Displays on Start-Up

void DisplayTest(LiquidCrystal_I2C lcd, MCP3008 adc);                 //Displays all ADC Values on screen

void menu(LiquidCrystal_I2C lcd, MCP3008 adc,int SD3,int SD2);        //Displays menu with 4 available sub-menus

void MainDisplay(LiquidCrystal_I2C lcd, MCP3008 adc);                  //idling display after connection to RoveComm

#endif
