#include <Wire.h>
#include <MCP3008.h>
#include <SPI.h>
#include <LiquidCrystal_I2C.h>

#define CS_PIN 12
#define CLOCK_PIN 9
#define MOSI_PIN 11
#define MISO_PIN 10

MCP3008 adc(D5,D7,D6,D8);
int lcdColumns = 16;
int lcdRows = 2;
int SD3 = 10;
int SD2 = 9;
LiquidCrystal_I2C lcd(0x20,2,1,0,4,5,6,7,3,POSITIVE);

void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
  lcd.begin(16,2);
  pinMode(D0,OUTPUT);
  pinMode(D3,INPUT);
  pinMode(D6,INPUT);
  pinMode(D4,INPUT);
  pinMode(SD2,INPUT);
  pinMode(SD3,INPUT);
}

void loop() {
  // put your main code here, to run repeatedly:
  Serial.println("--------------------------");
  Serial.println("Y-Value:" + String(adc.readADC(0)));
  Serial.println("X-Value:" + String(adc.readADC(1)));
  Serial.println("Select:" + String(adc.readADC(5)));
   Serial.println("Select:" + String(adc.readADC(2)));
    Serial.println("Select2:" + String(adc.readADC(3)));
     Serial.println("Select3:" + String(adc.readADC(4)));
      Serial.println("Select4:" + String(adc.readADC(6)));
       Serial.println("Select5:" + String(adc.readADC(7)));
       delay(500);
}
