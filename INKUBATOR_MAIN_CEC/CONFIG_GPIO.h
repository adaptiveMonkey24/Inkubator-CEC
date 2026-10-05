#ifndef CONFIG_GPIO_H
#define CONFIG_GPIO_H

#define DIMMER1_PIN 2
#define DIMMER2_PIN 3
#define DIMMER3_PIN 4
#define DIMMER4_PIN 5

#define ZC_PIN 18

volatile unsigned long waktuZC = 0;

int powerDimmer[4] = {0, 0, 0, 0};
bool triggerDimmer[4] = {false, false, false, false};

void zeroCross() {
  waktuZC = micros();

  for (int i = 0; i < 4; i++) {
    triggerDimmer[i] = false;
  }
}

void dimmerInit() {
  pinMode(DIMMER1_PIN, OUTPUT);
  pinMode(DIMMER2_PIN, OUTPUT);
  pinMode(DIMMER3_PIN, OUTPUT);
  pinMode(DIMMER4_PIN, OUTPUT);

  pinMode(ZC_PIN, INPUT);

  digitalWrite(DIMMER1_PIN, LOW);
  digitalWrite(DIMMER2_PIN, LOW);
  digitalWrite(DIMMER3_PIN, LOW);
  digitalWrite(DIMMER4_PIN, LOW);

  attachInterrupt(
    digitalPinToInterrupt(ZC_PIN),
    zeroCross,
    RISING
  );
}

void setDimmer(int channel, int power) {

  power = constrain(power, 0, 100);

  if (channel >= 1 && channel <= 4) {
    powerDimmer[channel - 1] = power;
  }
}

void setDimmer1(int power) {
  setDimmer(1, power);
}

void setDimmer2(int power) {
  setDimmer(2, power);
}

void setDimmer3(int power) {
  setDimmer(3, power);
}

void setDimmer4(int power) {
  setDimmer(4, power);
}

void dimmerUpdate() {

  unsigned long sekarang = micros();
  unsigned long elapsed = sekarang - waktuZC;

  for (int i = 0; i < 4; i++) {

    if (powerDimmer[i] == 0) {
      continue;
    }

    int delayTrigger = map(
      powerDimmer[i],
      0, 100,
      9000, 0
    );

    if (!triggerDimmer[i] && elapsed >= delayTrigger) {

      int pin;

      if (i == 0) pin = DIMMER1_PIN;
      if (i == 1) pin = DIMMER2_PIN;
      if (i == 2) pin = DIMMER3_PIN;
      if (i == 3) pin = DIMMER4_PIN;

      digitalWrite(pin, HIGH);
      delayMicroseconds(100);
      digitalWrite(pin, LOW);

      triggerDimmer[i] = true;
    }
  }
}

#endif