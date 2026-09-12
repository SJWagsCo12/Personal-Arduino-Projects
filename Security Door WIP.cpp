// ======================= Libraries =======================
//#include <SPI.h>
//#include <MFRC522.h>
#include <LiquidCrystal.h>
#include <Keypad.h>
#include <Servo.h>

// ====================== #define Section =======================
// RFID
//#define RFID_SS_PIN 53
//#define RFID_RST_PIN 9
#define RFID_SCAN 43

// LCD (Parallel)
#define LCD_RS 52
#define LCD_EN 53
#define LCD_D4 51
#define LCD_D5 49
#define LCD_D6 47
#define LCD_D7 45

// Buzzer
#define BUZZER_PIN 12
#define BEEP_DURATION 50           // ms
#define BEEP_GAP_DURATION 125      // ms
#define GRANT_BEEP_DURATION 1000   // ms for access granted
#define BUZZER_PITCH 1000          // Hz

// Keypad
const byte ROWS = 4;
const byte COLS = 4;
char keys[ROWS][COLS] = {
  {'1','2','3','A'},
  {'4','5','6','B'},
  {'7','8','9','C'},
  {'*','0','#','D'}
};
byte rowPins[ROWS] = {23, 25, 27, 29};
byte colPins[COLS] = {31, 33, 35, 37};

// Timing
#define INPUT_TIMEOUT 5000  // how long (ms) user can input code

// Valid Accounts
const byte num_accounts = 2;
const byte acc_cols = 3;
String accounts[num_accounts][acc_cols] = {
  {"Phill", "A1B2C3", "800B5"},
  {"Suzan", "N1G6A5", "ABC123"}
};

#define SERVO_PIN 13
#define UNLOCK_POS 90
#define LOCK_POS 0
#define UNLOCK_DURATION 5000

// ================== Object Initialization ==================
//MFRC522 rfid(RFID_SS_PIN, RFID_RST_PIN);
LiquidCrystal lcd(LCD_RS, LCD_EN, LCD_D4, LCD_D5, LCD_D6, LCD_D7);
Keypad keypad = Keypad(makeKeymap(keys), rowPins, colPins, ROWS, COLS);
Servo doorLock;

// ======================== Variables ========================

unsigned long previousMillis;
bool input_Start = false;
String UID, Code;

// ======================== Structs ========================

struct EntryResult{
  bool isValid;
  bool accExist;
  String reason;
  String name;
};

// ================== Function Prototypes ===================

void buzz_single(){
  tone(BUZZER_PIN, BUZZER_PITCH);
  delay(BEEP_DURATION);
  noTone(BUZZER_PIN);
}

void buzz_double(){
  tone(BUZZER_PIN, BUZZER_PITCH);
  delay(BEEP_DURATION);
  noTone(BUZZER_PIN);
  delay(BEEP_GAP_DURATION);
  tone(BUZZER_PIN, BUZZER_PITCH);
  delay(BEEP_DURATION);
  noTone(BUZZER_PIN);
}

void buzz_long(){
  tone(BUZZER_PIN, BUZZER_PITCH);
  delay(1000);
  noTone(BUZZER_PIN);
}

EntryResult valid_entry(String UID, String Code){
  buzz_double();
  EntryResult result;
  for (int i = 0; i <= num_accounts; i++){
    if (UID == accounts[i][1]){
      result.accExist = true;
	  result.name = accounts[i][0];
      if (result.accExist && Code == accounts[i][2]){
        result.isValid = true;
        result.reason = "Access Granted";
      } else {
        result.isValid = false;
        result.reason = "Incorrect Password";
      }
    } else if(result.accExist != true){
      result.accExist = false;
    }
  }
  return result;
}

void unlock_door() {
  doorLock.write(UNLOCK_POS);
  buzz_long();
  delay(UNLOCK_DURATION);
  doorLock.write(LOCK_POS);
}

// ======================= Setup ===========================
void setup() {
  Serial.begin(9600);

  // RFID Setup
  //SPI.begin();
  //rfid.PCD_Init();

  // LCD Setup
  lcd.begin(16, 2);
  lcd.clear();
  lcd.noDisplay();  // Start with LCD off

  // Buzzer Setup
  pinMode(BUZZER_PIN, OUTPUT);
  digitalWrite(BUZZER_PIN, LOW);

  // Startup Status
  Serial.println("Security system initialized. Waiting for scan...");

  pinMode(RFID_SCAN, INPUT_PULLUP);

  doorLock.attach(SERVO_PIN);
  doorLock.write(LOCK_POS);  // Start locked
}

// ======================== Loop ===========================
void loop() {
  if (digitalRead(RFID_SCAN) == HIGH && !input_Start) {
    previousMillis = millis();
    UID = "";
    return;
  } else if (digitalRead(RFID_SCAN) == LOW && !input_Start){
    input_Start = true;
    Serial.println("RFID Scanned");
    UID = "A1B2C3";   //Change this to become the scanned RFID UID
    Code = "";
    buzz_double();
    lcd.display();
    lcd.setCursor(0,0);
    lcd.print("Enter Passcode:");
  }

  //Update LCD and check keypad
  lcd.setCursor(0,1);

  char key = keypad.getKey();
  if (key){
    buzz_single();
    if (key == '*'){
      EntryResult check = valid_entry(UID, Code);
      lcd.clear();
      lcd.setCursor(0,0);
      if (check.accExist){
        Serial.print (check.name);
        Serial.print (": ");
        Serial.print (check.reason);
        if (check.isValid){
          Serial.println ("");
          unlock_door();
        } else {
          Serial.println (" - Access Denied");
        }
      } else {
        Serial.print ("Unknown UIN: ");
        Serial.print (UID);
        Serial.println (" - Access Denied");
      }
    } else {
      Code += key;
      lcd.print(Code);
    }
  }

  if (millis() - previousMillis >= INPUT_TIMEOUT){
    input_Start = false;
    lcd.noDisplay();
    lcd.clear();
    buzz_single();
  }

}