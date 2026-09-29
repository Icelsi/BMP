#include <Arduino.h> 
#include <Wire.h> 
#include <Adafruit_Sensor.h> 
#include <Adafruit_BMP280.h> 
#include <SPI.h> 
#include <Adafruit_GFX.h> 
#include <Adafruit_SSD1306.h> 

Adafruit_BMP280 bmp; 
float temperature; 
float altitude; 
float pressure;
#define SCREEN_WIDTH 128 
#define SCREEN_HEIGHT 64 
#define OLED_MOSI 11 
#define OLED_CLK 13 
#define OLED_DC 9 
#define OLED_CS 10 
#define OLED_RST 8 

 

Adafruit_SSD1306 display( 
  SCREEN_WIDTH, 
  SCREEN_HEIGHT, 
  OLED_MOSI, 
  OLED_CLK, 
  OLED_DC, 
  OLED_RST, 
  OLED_CS 
); 

void setup(){ 
 
  Serial.begin(9600); 
  Wire.begin(); 

  Serial.println("I2C Started"); 

  Serial.println("Program Started"); 
  if(bmp.begin(0x76)){
    Serial.println("BMP280 Found at 0x76");
  }
    else if(bmp.begin(0x77)){
      Serial.println("BMP280 Found at 0x77");
    }
    else {
      Serial.println("BMP280 Not Found");
    }

  display.begin(
    SSD1306_SWITCHCAPVCC
  );
  display.clearDisplay();
  display.setTextSize(1);
  display.setTextColor(SSD1306_WHITE);
  display.display();
} 

void loop(){ 
  temperature = bmp.readTemperature();
  Serial.print("Temperature:");
  Serial.print(temperature);
  Serial.println(" C");
  delay(1000);

  altitude = bmp.readAltitude(1013.25);
  Serial.print("Altitude: ");
  Serial.print(altitude);
  Serial.println("%");

  pressure = bmp.readPressure()/100; 
  Serial.print("Pressure: ");
  Serial.print(pressure);
  Serial.println("hPa");

  display.clearDisplay();
  display.setCursor(0,0);
  display.println("Hello Dawson!");

  display.print("Temp: ");
  display.print(temperature);
  display.println(" C");

  display.print("Hum: ");
  display.print(altitude);
  display.println(" %");


  display.print("Pres: ");
  display.print(pressure);
  display.print(" hPa");


  display.display();
  delay(1000);
} 