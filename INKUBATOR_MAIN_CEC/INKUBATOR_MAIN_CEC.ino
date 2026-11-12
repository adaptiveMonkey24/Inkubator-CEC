#include "CONFIG_GPIO.h"
#include "SENSOR_HANDLER.h"
#include "PID_CONTROLLER.h"

int currentPower[6] = {0, 0, 0, 0, 0, 0};

void setup() {
  Serial.begin(9600);
  dimmerInit();
  Serial.println("Sistem Dimmer 6 Channel Siap. Format: Dx, PWM (Contoh: D2, 80)");
}

void loop() {
  dimmerUpdate();

  if (Serial.available() > 0) {
    String data = Serial.readStringUntil('\n');
    data.trim();

    if (data.startsWith("D") || data.startsWith("d")) {
      int commaIndex = data.indexOf(',');
      
      if (commaIndex > 0) {
        String channelStr = data.substring(1, commaIndex);
        String valueStr = data.substring(commaIndex + 1);
        channelStr.trim();
        valueStr.trim();

        int channel = channelStr.toInt();
        int targetPower = valueStr.toInt();

        if (channel >= 1 && channel <= 6) {
          targetPower = constrain(targetPower, 0, 100);
          int chIdx = channel - 1;

          Serial.print("Channel ");
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
          } else {
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
          Serial.println("Error: Channel tidak valid! Gunakan D1 sampai D6.");
        }
      }
    }
  }
}