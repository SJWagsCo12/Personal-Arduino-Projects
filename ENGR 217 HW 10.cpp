// C++ code
//

// Initialize 6 variables that are constants that
// are used throughout the program

// Establish a digital pin for each of the LEDs used
const int redLED = 10;
const int yellowLED = 9;
const int greenLED = 8;

// Create a "dead zone" where the motor will be at 0
// rpm. The deadzone determines how many values in
// the middle of the potentiometer path result in 0 rpm
const int deadZone = 55;
const float lowerBound = (1023 / 2) - (deadZone / 2);
const float upperBound = (1023 / 2) + (deadZone / 2) + 1;

// Set up the arduino with a serial monitor used to
// display the value being read from the potentiometer
void setup()
{
  // Begine the Serial Monitor at 9600 bits per second
  Serial.begin(9600);
  
  // Establish the LED pins as output pins to ensure
  // the Arduino outputs 5V
  pinMode(redLED, OUTPUT);
  pinMode(yellowLED, OUTPUT);
  pinMode(greenLED, OUTPUT);
}

// Reads the potentiometer as a 'throttle' where the value
// from the potentiometer controls the speed of the motor.
// The LEDs are used to represent 'throttle intensity',
// where they turn on sequentially depending on the
// potentiometer angle.
void loop()
{
  // Read the pin the potentiometer is connected to and
  // re-map the values to be outputed on the PWM pins.
  // Analog, max 1023. Digital PWM, 255
  int reading = analogRead(A0);
  int motorForward = map(reading, upperBound, 1023, 0, 255);
  int motorBackward = map(reading, 0, lowerBound, 255, 0);
  // Mapping is made to leave a 'deadzone' in the middle
  
  // Determine which side the potentiometer is on and rotate
  // the motor in that direction at a scaling rpm based off
  // of the distance the potentiometer is rotated
  if (reading <= lowerBound){
    analogWrite(3, motorBackward);
  }else if (reading > lowerBound and reading < upperBound){
    analogWrite(3, 0);
    analogWrite(5, 0);
  }else if (reading >= upperBound){
    analogWrite(5, motorForward);
  }
  // Write reading to serial monitor to check if values
  // are reading correctly
  Serial.println(reading);
  
  // Determine if the motor is going in the positive or
  // negative direction. Then Determine by how much in
  // order to turn on the corresponding LEDs
  if (reading <= lowerBound){
    // If the potentiometer is on the lower end
    if (motorBackward <= 85){
      // If the speed of the motor is slow
      digitalWrite(redLED, HIGH);
      digitalWrite(yellowLED, LOW);
      digitalWrite(greenLED, LOW);
    }else if (motorBackward > 85 and motorBackward <= 170){
      // If the speed of the motor is moderate
      digitalWrite(redLED, HIGH);
      digitalWrite(yellowLED, HIGH);
      digitalWrite(greenLED, LOW);
    }else if (motorBackward > 170){
      //If the speed of the motor is fast
      digitalWrite(redLED, HIGH);
      digitalWrite(yellowLED, HIGH);
      digitalWrite(greenLED, HIGH);
    }
  }else if (reading > lowerBound and reading < upperBound){
    // If the potentiometer is in the deadzone
    digitalWrite(redLED, LOW);
    digitalWrite(yellowLED, LOW);
    digitalWrite(greenLED, LOW);
  }else if (reading >= upperBound){
    if (motorForward <= 85){
      // If the speed of the motor is slow
      digitalWrite(redLED, HIGH);
      digitalWrite(yellowLED, LOW);
      digitalWrite(greenLED, LOW);
    }else if (motorForward > 85 and motorForward <= 170){
      // If the speed of the motor is moderate
      digitalWrite(redLED, HIGH);
      digitalWrite(yellowLED, HIGH);
      digitalWrite(greenLED, LOW);
    }else if (motorForward > 170){
      // If the speed of the motor is fast
      digitalWrite(redLED, HIGH);
      digitalWrite(yellowLED, HIGH);
      digitalWrite(greenLED, HIGH);
    }
  }
}