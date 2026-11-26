#ifndef CONFIG_GPIO_H
#define CONFIG_GPIO_H



#define DIMMER1_PIN 19 //4
#define DIMMER2_PIN 23 //16
#define DIMMER3_PIN 16
#define DIMMER4_PIN 4
#define DIMMER5_PIN 5

#define ZC_PIN1 17
#define ZC_PIN2 18

// Definisi Pin Relay
#define RELAY1_PIN 21
#define RELAY2_PIN 22

volatile unsigned long waktuZC1 = 0;
volatile unsigned long waktuZC2 = 0;



int powerDimmer[5] = {0, 0, 0, 0, 0};
bool triggerDimmer[5] = {false, false, false, false, false};

// Interrupt Zero Crossing untuk Modul 4-Channel (Channel 1-4)

void zeroCross1() {
  waktuZC1 = micros();
  for (int i = 0; i < 4; i++) {
  triggerDimmer[i] = false;
  }
}



// Interrupt Zero Crossing untuk Modul 1-Channel (Channel 5)

void zeroCross2() {
  waktuZC2 = micros();
  triggerDimmer[4] = false;
}



void dimmerInit() {
  pinMode(DIMMER1_PIN, OUTPUT);
  pinMode(DIMMER2_PIN, OUTPUT);
  pinMode(DIMMER3_PIN, OUTPUT);
  pinMode(DIMMER4_PIN, OUTPUT);
  pinMode(DIMMER5_PIN, OUTPUT);

  pinMode(RELAY1_PIN, OUTPUT);
  pinMode(RELAY2_PIN, OUTPUT);

  pinMode(ZC_PIN1, INPUT);
  pinMode(ZC_PIN2, INPUT);

  digitalWrite(DIMMER1_PIN, LOW);
  digitalWrite(DIMMER2_PIN, LOW);
  digitalWrite(DIMMER3_PIN, LOW);
  digitalWrite(DIMMER4_PIN, LOW);
  digitalWrite(DIMMER5_PIN, LOW);

  attachInterrupt(digitalPinToInterrupt(ZC_PIN1), zeroCross1, RISING);
  attachInterrupt(digitalPinToInterrupt(ZC_PIN2), zeroCross2, RISING);
}



void setDimmer(int channel, int power) {
  power = constrain(power, 0, 100);

  if (channel >= 1 && channel <= 5) {
  powerDimmer[channel - 1] = power;
  }
}



void setDimmer1(int power) { setDimmer(1, power); }
void setDimmer2(int power) { setDimmer(2, power); }
void setDimmer3(int power) { setDimmer(3, power); }
void setDimmer4(int power) { setDimmer(4, power); }
void setDimmer5(int power) { setDimmer(5, power); }



// Fungsi untuk mengontrol Relay (relayNum: 1 atau 2, state: HIGH/LOW atau 1/0)

void setRelay(int relayNum, int state) {
  if (relayNum == 1) {
  digitalWrite(RELAY1_PIN, state);
  Serial.print("Relay 1 diubah ke: ");
  Serial.println(state == HIGH ? "HIGH" : "LOW");
  } else if (relayNum == 2) {
  digitalWrite(RELAY2_PIN, state);
  Serial.print("Relay 2 diubah ke: ");
  Serial.println(state == HIGH ? "HIGH" : "LOW");
  } else {
  Serial.println("Error: Relay tidak valid! Gunakan R1 atau R2.");
  }
}

void dimmerUpdate() {
  unsigned long sekarang = micros();

  // 1. Logika Trigger untuk Modul 4-Channel (Channel 1-4)
  unsigned long elapsed1 = sekarang - waktuZC1;
  for (int i = 0; i < 4; i++) {
    if (powerDimmer[i] == 0) {
      triggerDimmer[i] = false;
      continue;
    }

    int delayTrigger = map(powerDimmer[i], 0, 100, 9000, 0);
    if (!triggerDimmer[i] && elapsed1 >= delayTrigger) {
    int pin;
    if (i == 0) pin = DIMMER1_PIN;
    else if (i == 1) pin = DIMMER2_PIN;
    else if (i == 2) pin = DIMMER3_PIN;
    else pin = DIMMER4_PIN;

    digitalWrite(pin, HIGH);
    delayMicroseconds(200);
    digitalWrite(pin, LOW);

    triggerDimmer[i] = true;
    }
  }



// 2. Logika Trigger untuk Modul 1-Channel (Channel 5)

  unsigned long elapsed2 = sekarang - waktuZC2;
  if (powerDimmer[4] == 0) {
    triggerDimmer[4] = false;
  } else {
  int delayTrigger2 = map(powerDimmer[4], 0, 100, 9000, 0);
  if (!triggerDimmer[4] && elapsed2 >= delayTrigger2) {
    digitalWrite(DIMMER5_PIN, HIGH);
    delayMicroseconds(200);
    digitalWrite(DIMMER5_PIN, LOW);
    triggerDimmer[4] = true;
  }
  }
}

#endif