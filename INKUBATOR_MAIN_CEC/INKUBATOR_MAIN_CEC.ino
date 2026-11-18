#include "CONFIG_GPIO.h"
#include "SENSOR_HANDLER.h"
#include "PID_CONTROLLER.h"

int currentPower[5] = {0, 0, 0, 0, 0};

void setup() {
  Serial.begin(115200);
  dimmerInit();
  Serial.println("Sistem Dimmer 5 Channel (2 Modul) Siap. Format: Dx, PWM (Contoh: D5, 80)");
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

        // Validasi channel 1 sampai 5
        if (channel >= 1 && channel <= 5) {
          targetPower = constrain(targetPower, 0, 100);
          int chIdx = channel - 1;

          Serial.print("Channel ");
          Serial.print(channel);
          Serial.print(": ");
          Serial.print(currentPower[chIdx]);
          Serial.print(" -> ");
          Serial.println(targetPower);

          // Transisi bertahap (for) naik atau turun
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

          // Simpan posisi terakhir dengan pasti
          currentPower[chIdx] = targetPower;
        } else {
          Serial.println("Error: Channel tidak valid! Gunakan D1 sampai D5.");
        }
      }
    }
  }
}