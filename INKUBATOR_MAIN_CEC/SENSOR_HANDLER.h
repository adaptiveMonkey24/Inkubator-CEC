#ifndef SENSOR_HANDLER_H
#define SENSOR_HANDLER_H

#include <DHT.h>

#define DHT_TYPE DHT22

// Penyesuaian pin sensor per lantai
#define DHT1_PIN 13 // Lantai 1
#define DHT2_PIN 25 // Lantai 2
#define DHT3_PIN 27 // Lantai 3
#define DHT4_PIN 14 // Lantai 4
#define DHT5_PIN 26 // Lantai 5

DHT dht1(DHT1_PIN, DHT_TYPE);
DHT dht2(DHT2_PIN, DHT_TYPE);
DHT dht3(DHT3_PIN, DHT_TYPE);
DHT dht4(DHT4_PIN, DHT_TYPE);
DHT dht5(DHT5_PIN, DHT_TYPE);

float temp[5] = {0.0, 0.0, 0.0, 0.0, 0.0};
float hum[5] = {0.0, 0.0, 0.0, 0.0, 0.0};

void dhtInit() {
  dht1.begin();
  dht2.begin();
  dht3.begin();
  dht4.begin();
  dht5.begin();
}

void updateSensors() {
  float t1 = dht1.readTemperature(); float h1 = dht1.readHumidity();
  if (!isnan(t1)) temp[0] = t1; if (!isnan(h1)) hum[0] = h1;
  float t2 = dht2.readTemperature(); float h2 = dht2.readHumidity();
  if (!isnan(t2)) temp[1] = t2; if (!isnan(h2)) hum[1] = h2;
  float t3 = dht3.readTemperature(); float h3 = dht3.readHumidity();
  if (!isnan(t3)) temp[2] = t3; if (!isnan(h3)) hum[2] = h3;
  float t4 = dht4.readTemperature(); float h4 = dht4.readHumidity();
  if (!isnan(t4)) temp[3] = t4; if (!isnan(h4)) hum[3] = h4;
  float t5 = dht5.readTemperature(); float h5 = dht5.readHumidity();
  if (!isnan(t5)) temp[4] = t5; if (!isnan(h5)) hum[4] = h5;
}

// Fungsi cetak dengan format per lantai menyertakan nilai PWM dimmer
void printSensorData(int dimmerPower[]) {
for (int i = 0; i < 5; i++) {
Serial.print("Lantai ");
Serial.print(i + 1);
Serial.print(" >> Suhu ");
Serial.print(i + 1);
Serial.print(" : ");
Serial.print(temp[i]);
Serial.print(", Kelembapan ");
Serial.print(i + 1);
Serial.print(" ");
Serial.print(hum[i]);
Serial.print("%, Dimmer ");
Serial.print(i + 1);
Serial.print(" : ");
Serial.print(dimmerPower[i]);
Serial.println("%");
}

Serial.println("--------------------------------------------------");
}

#endif