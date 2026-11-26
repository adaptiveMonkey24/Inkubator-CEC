<<<<<<< HEAD
#include "CONFIG_GPIO.h"
#include "SENSOR_HANDLER.h"
#include "PID_CONTROLLER.h"

int currentPower[5] = {0, 0, 0, 0, 0};

unsigned long previousMillis = 0;
const long interval = 2000;

void setup() {
  Serial.begin(115200);
  dimmerInit();
  dhtInit(); // Inisialisasi sensor DHT
  Serial.println("Sistem Inkubator Siap.");
  Serial.println("Format Dimmer: Dx, PWM (Contoh: D1, 75)");
  Serial.println("Format Relay : Rx, STATUS (Contoh: R1, HIGH atau R2, LOW)");
  digitalWrite(RELAY1_PIN, HIGH);
  digitalWrite(RELAY2_PIN, HIGH);
}



void loop() {
  // Selalu jalankan update dimmer agar zero-cross interrupt tidak terganggu
  dimmerUpdate();

  // Membaca dan menampilkan sensor secara berkala setiap 2 detik tanpa blocking
  unsigned long currentMillis = millis();
  if (currentMillis - previousMillis >= interval) {
  previousMillis = currentMillis;

  updateSensors();
  printSensorData(currentPower);
  }

  // Membaca perintah dari Serial Monitor
  if (Serial.available() > 0) {
    String data = Serial.readStringUntil('\n');
    data.trim();

    // 1. Kontrol Dimmer (Format: Dx, PWM)
    if (data.startsWith("D") || data.startsWith("d")) {
      int commaIndex = data.indexOf(',');

      if (commaIndex > 0) {
        String channelStr = data.substring(1, commaIndex);
        String valueStr = data.substring(commaIndex + 1);
        channelStr.trim();
        valueStr.trim();

        int channel = channelStr.toInt();
        int targetPower = valueStr.toInt();

        if (channel >= 1 && channel <= 5) {
        targetPower = constrain(targetPower, 0, 100);

        int chIdx = channel - 1;

        Serial.print("Perintah -> Channel ");
        Serial.print(channel);
        Serial.print(": ");
        Serial.print(currentPower[chIdx]);
        Serial.print(" -> ");
        Serial.println(targetPower);

        if (currentPower[chIdx] < targetPower) {
        for (int p = currentPower[chIdx]; p <= targetPower; p++) {
          setDimmer(channel, p);
          for (int i = 0; i < 10; i++) {
            dimmerUpdate();
            delay(1);
          }
        }

        } else if (currentPower[chIdx] > targetPower) {
          for (int p = currentPower[chIdx]; p >= targetPower; p--) {
            setDimmer(channel, p);
            for (int i = 0; i < 10; i++) {
            dimmerUpdate();
            delay(1);
            }
          }
        }

        currentPower[chIdx] = targetPower;
        } else {
        Serial.println("Error: Channel dimmer tidak valid! Gunakan D1 sampai D5.");
        }
      }
    }

    // 2. Kontrol Relay (Format: Rx, HIGH/LOW)
    else if (data.startsWith("R") || data.startsWith("r")) {
      int commaIndex = data.indexOf(',');
      if (commaIndex > 0) {
      String relayStr = data.substring(1, commaIndex);
      String stateStr = data.substring(commaIndex + 1);
      relayStr.trim();
      stateStr.trim();
      stateStr.toUpperCase(); // Ubah ke huruf besar agar mudah dicocokkan

      int relayNum = relayStr.toInt();
      int state = LOW;

      if (stateStr == "HIGH" || stateStr == "1") {
      state = HIGH;
      } else if (stateStr == "LOW" || stateStr == "0") {
      state = LOW;
      } else {

      Serial.println("Error: Status relay tidak valid! Gunakan HIGH atau LOW.");
      return;
      }

      // Panggil fungsi kontrol relay dari CONFIG_GPIO.h
      setRelay(relayNum, state);
      }
    }
  }
}

=======
#include "CONFIG_GPIO.h"
#include "SENSOR_HANDLER.h"
#include "PID_CONTROLLER.h"

int currentPower[5] = {0, 0, 0, 0, 0};

unsigned long previousMillis = 0;
const long interval = 2000;

void setup() {
  Serial.begin(115200);
  dimmerInit();
  dhtInit(); // Inisialisasi sensor DHT
  Serial.println("Sistem Inkubator Siap.");
  Serial.println("Format Dimmer: Dx, PWM (Contoh: D1, 75)");
  Serial.println("Format Relay : Rx, STATUS (Contoh: R1, HIGH atau R2, LOW)");
  digitalWrite(RELAY1_PIN, HIGH);
  digitalWrite(RELAY2_PIN, HIGH);
}



void loop() {
  // Selalu jalankan update dimmer agar zero-cross interrupt tidak terganggu
  dimmerUpdate();

  // Membaca dan menampilkan sensor secara berkala setiap 2 detik tanpa blocking
  unsigned long currentMillis = millis();
  if (currentMillis - previousMillis >= interval) {
  previousMillis = currentMillis;

  updateSensors();
  printSensorData(currentPower);
  }

  // Membaca perintah dari Serial Monitor
  if (Serial.available() > 0) {
    String data = Serial.readStringUntil('\n');
    data.trim();

    // 1. Kontrol Dimmer (Format: Dx, PWM)
    if (data.startsWith("D") || data.startsWith("d")) {
      int commaIndex = data.indexOf(',');

      if (commaIndex > 0) {
        String channelStr = data.substring(1, commaIndex);
        String valueStr = data.substring(commaIndex + 1);
        channelStr.trim();
        valueStr.trim();

        int channel = channelStr.toInt();
        int targetPower = valueStr.toInt();

        if (channel >= 1 && channel <= 5) {
        targetPower = constrain(targetPower, 0, 100);

        int chIdx = channel - 1;

        Serial.print("Perintah -> Channel ");
        Serial.print(channel);
        Serial.print(": ");
        Serial.print(currentPower[chIdx]);
        Serial.print(" -> ");
        Serial.println(targetPower);

        if (currentPower[chIdx] < targetPower) {
        for (int p = currentPower[chIdx]; p <= targetPower; p++) {
          setDimmer(channel, p);
          for (int i = 0; i < 10; i++) {
            dimmerUpdate();
            delay(1);
          }
        }

        } else if (currentPower[chIdx] > targetPower) {
          for (int p = currentPower[chIdx]; p >= targetPower; p--) {
            setDimmer(channel, p);
            for (int i = 0; i < 10; i++) {
            dimmerUpdate();
            delay(1);
            }
          }
        }

        currentPower[chIdx] = targetPower;
        } else {
        Serial.println("Error: Channel dimmer tidak valid! Gunakan D1 sampai D5.");
        }
      }
    }

    // 2. Kontrol Relay (Format: Rx, HIGH/LOW)
    else if (data.startsWith("R") || data.startsWith("r")) {
      int commaIndex = data.indexOf(',');
      if (commaIndex > 0) {
      String relayStr = data.substring(1, commaIndex);
      String stateStr = data.substring(commaIndex + 1);
      relayStr.trim();
      stateStr.trim();
      stateStr.toUpperCase(); // Ubah ke huruf besar agar mudah dicocokkan

      int relayNum = relayStr.toInt();
      int state = LOW;

      if (stateStr == "HIGH" || stateStr == "1") {
      state = HIGH;
      } else if (stateStr == "LOW" || stateStr == "0") {
      state = LOW;
      } else {

      Serial.println("Error: Status relay tidak valid! Gunakan HIGH atau LOW.");
      return;
      }

      // Panggil fungsi kontrol relay dari CONFIG_GPIO.h
      setRelay(relayNum, state);
      }
    }
  }
}

>>>>>>> 419d3b3d6f9b66bdee48352775cbf4c94c64a7d8
