// Full Feature Weather Station v0.1
// By Bora Akbay
// https://github.com/boraakbay

#include <LiquidCrystal_I2C.h>
#include <DHT.h>
#include <Wire.h>
#include <Adafruit_BMP085.h>

#define DHTPIN 2
#define DHTTYPE DHT11
DHT dht(DHTPIN, DHTTYPE);
LiquidCrystal_I2C lcd(0x3F, 20, 4); // Set the LCD I2C address
Adafruit_BMP085 bmp;
void setup() {
  dht.begin();
  bmp.begin();
  lcd.begin(16, 2);
  
  ////Defining custom chars////
byte thermo[8] = //icon for termometer
{
    B00100,
    B01010,
    B01010,
    B01010,
    B01110,
    B11111,
    B11111,
    B01110
};

byte droplet[8] = //icon for water droplet
{
    B00100,
    B01110,
    B01110,
    B11111,
    B11111,
    B11111,
    B01110,
};
byte degreecel[8] = //icon for degree celcius
{
    B11000,
    B11000,
    B00011,
    B00100,
    B00100,
    B00100,
    B00011  
};
/////////END Definition////

  lcd.createChar(1,thermo);
  lcd.createChar(2,droplet);
  lcd.createChar(3,degreecel);
}


void loop() {
  float tempsum = bmp.readTemperature () + dht.readTemperature();
  float t = tempsum / 2;
  float h = dht.readHumidity();
  float p = bmp.readPressure();
  float hpa;
  float bar = bmp.readPressure() * 0.0002952998751;
  float inhg = bmp.readPressure() * 0.0002953337;
  float mmhg = bmp.readPressure() * 0.254 * 0.02953337;
  float atm = bmp.readPressure() * 0.0000098692;

  lcd.clear();
  lcd.backlight();
  lcd.setCursor(0, 0);
  lcd.write(1);
  lcd.print(t, 2);
  lcd.write(3);

  lcd.setCursor(10, 0);
  lcd.write(2);
  lcd.print(h, 1);
  lcd.print("%");

  hpa = p / 100;    //convert pascals to hectopascals

  lcd.setCursor(0, 1);
  lcd.print("Pressure:");
  lcd.print(hpa, 0);
  lcd.print("hPa");
  delay (2000);
}
