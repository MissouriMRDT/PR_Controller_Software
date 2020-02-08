
#ifndef PR_Controller_Header
#define PR_Controller_Header
#include <LiquidCrystal_I2C.h>
#include <MCP3008.h>

void RoverWelcome(LiquidCrystal_I2C lcd);
void DisplayTest(LiquidCrystal_I2C lcd, MCP3008 adc); //Displays all ADC Values on screen
void menu(LiquidCrystal_I2C lcd, MCP3008 adc,int SD3,int SD2);
#endif
