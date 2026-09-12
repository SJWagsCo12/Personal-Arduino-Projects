// This program is designed as a representation of how to show values on Serial Monitor
// The monitor is located in the Tools section if the IDE

// This program was run with a basic Pull-Down Button

void setup() {
  // Begins output to Serial Monitor at 9600 bits per second
  Serial.begin(9600);
}

void loop() {
  if (digitalRead(2) == HIGH){
    Serial.println("Button is Pressed");
  }else {
    Serial.println("Button is not Pressed");
  }
}