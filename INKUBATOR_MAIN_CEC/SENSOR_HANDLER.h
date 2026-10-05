#ifndef SENSOR_HANDLER_H
#define SENSOR_HANDLER_H

#include <DHT.h>

#define DHT_PIN 7
#define DHT_TYPE DHT22

DHT dht(DHT_PIN, DHT_TYPE);

void dhtInit() {
  dht.begin();
}

float getTemperature() {
  return dht.readTemperature();
}

float getHumidity() {
  return dht.readHumidity();
}

#endif