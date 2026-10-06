#include "CONFIG_GPIO.h"
#include "SENSOR_HANDLER.h"
#include "PID_CONTROLLER.h"

void setup() {
  dimmerInit();
}

void loop() {
  for (int daya = 0; daya <= 100; daya++) {
    setDimmer2(daya);

    for (int i = 0; i < 20; i++) {
      dimmerUpdate();
      delay(1);
    }
  }

  for (int daya = 100; daya >= 0; daya--) {
    setDimmer2(daya);

    for (int i = 0; i < 20; i++) {
      dimmerUpdate();
      delay(1);
    }
  }
}
