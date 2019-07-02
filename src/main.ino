#define OLED_RESET D3
#define SERIAL_SPEED 74880

//#define DEBUG

#include <SPI.h>
#include <Wire.h>
#include <Adafruit_SSD1306.h>
#include <BME280I2C.h>

Adafruit_SSD1306 display(OLED_RESET);
BME280I2C bme;

void setup()
{
  #ifdef DEBUG
  Serial.begin(SERIAL_SPEED);
  Serial.println("init display");
  #endif

  display.begin(SSD1306_SWITCHCAPVCC, 0x3D);
  display.clearDisplay();
  display.display();
  display.setTextColor(WHITE);

  #ifdef DEBUG
  Serial.println("display done. searching sensor");
  #endif

  #ifndef DEBUG
  bme.begin();
  #else
  while(!bme.begin())
  {
    Serial.println("no sensor found");
    delay(1000);
  }
  #endif

  #ifndef DEBUG
  bme.chipModel();
  #else
  switch(bme.chipModel())
  {
    case BME280::ChipModel_BME280:
      Serial.println("found bme280 sensor.");
      break;
    case BME280::ChipModel_BMP280:
      Serial.println("found bmp280 sensor.");
      break;
    default:
      Serial.println("found unknown sensor.");
  }
  #endif
}

void loop()
{
  delay(500);
  printBME280Data();
}

void printBME280Data()
{
  float temp(NAN), hum(NAN), pres(NAN);

  BME280::TempUnit tempUnit(BME280::TempUnit_Celsius);
  BME280::PresUnit presUnit(BME280::PresUnit_hPa);

  bme.read(pres, temp, hum, tempUnit, presUnit);

  display.clearDisplay();

  display.setCursor(0,0);
  display.setTextSize(2);
  display.print(temp);
  display.setTextSize(1);
  display.print(" ");
  display.println((char)247 + String(tempUnit == BME280::TempUnit_Celsius ? 'C' :'F'));

  display.setCursor(0,25);
  display.setTextSize(2);
  display.print(hum);
  display.setTextSize(1);
  display.println(" % RH");

  display.setCursor(0,50);
  display.setTextSize(2);
  display.print(pres);
  display.setTextSize(1);
  display.println(" hPa");
  display.display();

  delay(1000);
}
