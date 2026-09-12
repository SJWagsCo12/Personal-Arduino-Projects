int i = 0;
int LEDState = 0;

void setup() {
  // put your setup code here, to run once:
  pinMode(8, OUTPUT);
  pinMode(2, INPUT);
  pinMode(13, OUTPUT);
  pinMode(12, OUTPUT);

  LEDState = 1;
  digitalWrite(8, HIGH);
}

void loop() {
  // put your main code here, to run repeatedly:
  if (LEDState == 1) {
    while (digitalRead(2) == HIGH) {
      digitalWrite(8, LOW);
      digitalWrite(13, LOW);
      digitalWrite(12, HIGH);
      LEDState = 2;
    }
  }
  if (LEDState == 2) {
    while (digitalRead(2) == HIGH) {
      digitalWrite(12, LOW);
      digitalWrite(8, LOW);
      digitalWrite(13, HIGH);
      LEDState = 3;
    }
  }
  if (LEDState == 3) {
    while (digitalRead(2) == HIGH) {
      digitalWrite(13, LOW);
      digitalWrite(12, LOW);
      digitalWrite(8, HIGH);
      LEDState = 1;
    }
  }
  delay(1);
}