#include <Wire.h>
#include <MCP3008.h>
#include <SPI.h>
#include <LiquidCrystal_I2C.h>

MCP3008 adc(D5, D7, D6, D8);
int lcdColumns = 16;
int lcdRows = 2;
int SD3 = 10;
int SD2 = 9;
LiquidCrystal_I2C lcd(0x38,2,1,0,4,5,6,7,3,POSITIVE);

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
  lcd.setCursor(0,0);
  lcd.print("   Mars Rover   ");
  lcd.setCursor(0,1);
  lcd.print("  Design  Team  ");
  delay(4000);
  lcd.clear();
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
  lcd.setCursor(0,0);
  lcd.print("Y-Value: " + String(adc.readADC(0))+ "   ");
  lcd.setCursor(0,1);
  lcd.print("X-Value: " + String(adc.readADC(1))+ "   ");
  delay(500);
  if((digitalRead(D3) == LOW) || (digitalRead(D4) == LOW) || (digitalRead(9) == LOW) || (digitalRead(10) == LOW))
    digitalWrite(D0,HIGH);

  else
    digitalWrite(D0,LOW);
    
  Serial.println("Button:" + String(adc.readADC(6)));
  if(digitalRead(D3) == LOW)
    {
      lcd.clear();
      lcd.print("D3 Button On");
      delay(2000);
    }
    
}
