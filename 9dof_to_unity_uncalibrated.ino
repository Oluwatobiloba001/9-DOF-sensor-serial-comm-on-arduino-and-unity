// SPDX-FileCopyrightText: 2022 Liz Clark for Adafruit Industries
//
// SPDX-License-Identifier: MIT
#include <Wire.h> // Include the Wire library for I2C communication
#include <Adafruit_LSM6DSOX.h>


int x;
int y;
int z;

// For SPI mode, we need a CS pin
#define LSM_CS 17
// For software-SPI mode we need SCK/MOSI/MISO pins
#define LSM_SCK 18
#define LSM_MISO 5
#define LSM_MOSI 19

Adafruit_LSM6DSOX lsm6ds;



void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);

  if (!lsm6ds.begin_I2C()) {
    // if (!lsm6ds.begin_SPI(LSM_CS)) {
    // if (!lsm6ds.begin_SPI(LSM_CS, LSM_SCK, LSM_MISO, LSM_MOSI)) {
    // Serial.println("Failed to find LSM6DSOX chip");
    while (1) {
      delay(10);
    }
  }
  lsm6ds.setAccelRange(LSM6DS_ACCEL_RANGE_2_G);
  lsm6ds.setGyroRange(LSM6DS_GYRO_RANGE_250_DPS);

  lsm6ds.setAccelDataRate(LSM6DS_RATE_104_HZ);
  lsm6ds.setGyroDataRate(LSM6DS_RATE_104_HZ);

}

void loop() {
  // put your main code here, to run repeatedly:

  sensors_event_t accel;
  sensors_event_t gyro;
  sensors_event_t temp;
  lsm6ds.getEvent(&accel, &gyro, &temp);

  x = map(accel.acceleration.x, -12, 11, 180, -180); 
  y = map(accel.acceleration.y, -19, 20, -180, 180); 
  z = map(accel.acceleration.z, -17, 15, 180, -180); 

  Serial.print("|");
  Serial.print(x);
  Serial.print("|");
  Serial.print(y);
  Serial.print("|");
  Serial.print(z);
  Serial.println();
  delay(50);
}
