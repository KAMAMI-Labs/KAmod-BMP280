//example code for KAmodESP32 POW RS485 and KAmod BMP280
//https://wiki.kamamilabs.com/index.php?title=KAmodESP32_POW_RS485_(PL)

//ino board: ESP32-WROOM-DA Module

//additional wires:
//BMP280 SDO -> GND
//BMP280 CSB -> VDD (3,3V)

#include <Wire.h>
#include <SPI.h>
#include <Adafruit_BMP280.h>

//LED
#define LED_PIN       2 
#define MY_DELAY      2000

//I2C
#define I2C_SDA       33
#define I2C_SCL       32

//SPI
#define SPI_MOSI      13
#define SPI_MISO      12
#define SPI_SCK       14    //no a 11 - a small mistake in the description on the pcb
#define SPI_CS        15

TwoWire I2CBMP = TwoWire(0);
Adafruit_BMP280 bmp280(&I2CBMP);

int status;
int i;

void setup() {
  Serial.begin(115200);
  Serial.println("\r\r\rHello. KAmod BMP280 test start");

  pinMode(LED_PIN, OUTPUT);
  digitalWrite(LED_PIN, HIGH);

  I2CBMP.begin(I2C_SDA, I2C_SCL, 100000);

  status = 0;
  while (status == 0){
    status = bmp280.begin(0x76);
    
    Serial.print("SensorID was: 0x"); Serial.println(bmp280.sensorID(),16); 
    if (!status) {
      Serial.println(F("Something wrong..."));
      delay(3000);
    }
  }

  bmp280.setSampling(Adafruit_BMP280::MODE_NORMAL,  /* Operating Mode. */
                  Adafruit_BMP280::SAMPLING_X2,     /* Temp. oversampling */
                  Adafruit_BMP280::SAMPLING_X16,    /* Pressure oversampling */
                  Adafruit_BMP280::FILTER_X16,      /* Filtering. */
                  Adafruit_BMP280::STANDBY_MS_500); /* Standby time. */
}

void loop() {
  i++;
  digitalWrite(LED_PIN, (i&1));

  Serial.print(F("Temperature = "));
  Serial.print(bmp280.readTemperature());
  Serial.print(" *C;  ");

  Serial.print(F("Pressure = "));
  Serial.print(bmp280.readPressure());
  Serial.println(" Pa");

  Serial.println();
  delay(MY_DELAY);
}
