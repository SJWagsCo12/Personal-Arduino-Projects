#include <Wire.h>
#include <RTClib.h>
#include <DHT.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#define DHTPIN 2
#define DHTTYPE DHT11

#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64
#define OLED_ADDR 0x3C

RTC_DS3231 rtc;
DHT dht(DHTPIN, DHTTYPE);
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, -1);

const int buttonPin = 3;
volatile bool buttonPressed = false;

const int textSize = 2;

unsigned long previousMillis = 0;
const long interval = 1000;

const int clockButton = 22;

void setup() {
  pinMode(buttonPin, INPUT_PULLUP);
  pinMode(DHTPIN, INPUT);
  pinMode(clockButton, INPUT_PULLUP);

  Serial.begin(9600);
  delay(100);

  if (!rtc.begin()){
    Serial.println("No RTC Module Found");
  }

  dht.begin();

  if (!display.begin(SSD1306_SWITCHCAPVCC, OLED_ADDR)) {
    Serial.println(F("SSD1306 allocation failed"));
    for (;;);
  }
  display.clearDisplay();
  display.display();

  attachInterrupt(digitalPinToInterrupt(buttonPin), buttonPressISR, FALLING);
}

void loop() {
  if(buttonPressed){
    buttonPressed = false;
    handleButtonPress();
  }

  unsigned long currentMillis = millis();

  if (currentMillis - previousMillis >= interval) {
    previousMillis = currentMillis;

    handleTimeDisplay();
  }

  if (digitalRead(clockButton) == LOW){
    Serial.println("Setting Time on RTC Module");
    rtc.adjust(DateTime(F(__DATE__), F(__TIME__)));
  }
  while (digitalRead(clockButton) == LOW){
    continue;
  }
}

void buttonPressISR(){
  buttonPressed = true;
}

void handleButtonPress(){
  display.clearDisplay();
  float humidity = dht.readHumidity();
  float temp = dht.readTemperature();

  if (!isnan(humidity) && !isnan(temp)){
    temp = (temp * (9.0/5.0)) + 32.0;

    humidity = round(humidity);
    temp = round(temp);

    Serial.print("Temp: ");
    Serial.print(temp);
    Serial.print("°F   Humidity: ");
    Serial.print(humidity);
    Serial.println("%");
    
    display.setTextSize(textSize);
    display.setTextColor(SSD1306_WHITE);
    display.setCursor(0, 0); // Top-left corner
    display.print("Temp:");
    display.setCursor((textSize * 5) * 3, ((textSize * 8) * 1) + 1);
    display.print(temp);
    display.print("F");
    
    display.setCursor(0, ((textSize * 8) * 2) + 1); // Adjust y-coordinate for the next line
    display.print("Humidity:");
    display.setCursor((textSize * 5) * 3, ((textSize * 8) * 3) + 1);
    display.print(humidity);
    display.print("%");
  }else{
    Serial.println("Error: Failed to read from DHT Sensor");
    display.setTextSize(1); // Use a smaller size for error messages
    display.setCursor(0, 0);
    display.print("Error reading DHT");
  }
  display.display();
  while (digitalRead(buttonPin) == LOW){
    continue;
  }
  display.clearDisplay();
  display.display();
  delay(500);
  return;
}

void handleTimeDisplay() {
  display.clearDisplay();
  DateTime now = rtc.now();

  now = now + TimeSpan(0, 0, 0, 9);

  display.setTextSize(1);
  display.setTextColor(SSD1306_WHITE);
  display.setCursor(0, 0);

  String monthNames[] = {"January", "February", "March", "April", "May", "June", 
                         "July", "August", "September", "October", "November", "December"};

  // Display the date
  display.print(monthNames[now.month() - 1]);
  display.print(" ");
  display.print(now.day(), DEC);
  display.print(", ");
  display.print(now.year(), DEC);

  // Time display (centered)
  int timeX = (SCREEN_WIDTH - (textSize * 6 * 8)) / 2;
  int timeY = 28;  // Adjust this value as needed

  display.setTextSize(textSize);  // Use a larger size for the time
  display.setCursor(timeX, timeY);

  // Format the time with leading zeros
  char timeStr[9];  // Format: "hh:mm:ss"
  sprintf(timeStr, "%02d:%02d:%02d", now.hour(), now.minute(), now.second());

  display.print(timeStr);  // Display the formatted time

  display.display();
}