// Interfacing Arduino with NEO-6M GPS module
// #include <sstream>
#include <TinyGPS++.h>           // Include TinyGPS++ library
#include <SoftwareSerial.h>      // Include software serial library

#include <Wire.h> 
#include <LiquidCrystal_I2C.h>

LiquidCrystal_I2C lcd(0x27, 20, 4);

TinyGPSPlus gps;

#define S_RX    4                // Define software serial RX pin
#define S_TX    3                // Define software serial TX pin

SoftwareSerial SoftSerial(S_RX, S_TX);    // Configure SoftSerial library

void setup(void) {
  Serial.begin(9600);
  SoftSerial.begin(9600);

  // Initialize the LCD
  lcd.init();
  
  // Turn on the backlight
  lcd.backlight();
}

void loop() {

  while (SoftSerial.available() > 0) {

    if (gps.encode(SoftSerial.read())) {

      if (gps.location.isValid()) {
        Serial.print("Latitude   = ");
        Serial.println(gps.location.lat(), 6);
        // Print a message to the LCD
        lcd.setCursor(0, 0); // First line
        lcd.print("Latitude =");
        lcd.print(gps.location.lat(), 6);
        Serial.print("Longitude  = ");
        Serial.println(gps.location.lng(), 6);
        lcd.setCursor(0, 1); // second line
        lcd.print("Longitude=");
        lcd.print(gps.location.lng(), 6);
      }
      else
        Serial.println("Location Invalid");

      if (gps.speed.isValid()) {
        Serial.print("Speed      = ");
        Serial.print(gps.speed.kmph());
        Serial.println(" kmph");
        lcd.setCursor(0, 2); // third line
        lcd.print("Speed    =");
        lcd.print(gps.speed.kmph());
        lcd.print(" kmph");
      }
      else
        Serial.println("Speed Invalid");

      if (gps.time.isValid()) {
        Serial.print("Time (GMT) : ");
        if(gps.time.hour() < 10)     Serial.print("0");
        Serial.print(gps.time.hour());
        Serial.print(":");
        if(gps.time.minute() < 10)   Serial.print("0");
        Serial.print(gps.time.minute());
        Serial.print(":");
        if(gps.time.second() < 10)   Serial.print("0");
        Serial.println(gps.time.second());
      }
      else
        Serial.println("Time Invalid");

      if (gps.date.isValid()) {
        Serial.print("Date       : ");
        lcd.setCursor(0, 3); // forth line
        lcd.print("Date     :");
        if(gps.date.day() < 10)      Serial.print("0");
        Serial.print(gps.date.day());
        Serial.print("/");
        lcd.print(gps.date.day());
        lcd.print("/");
        if(gps.date.month() < 10)    Serial.print("0");
        Serial.print(gps.date.month());
        Serial.print("/");
        Serial.println(gps.date.year());
        lcd.print(gps.date.month());
        lcd.print("/");
        lcd.print(gps.date.year());
      }
      else
        Serial.println("Date Invalid");

    }

  }
}
