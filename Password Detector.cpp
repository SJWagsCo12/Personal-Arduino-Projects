// C++ code
//
#include <LiquidCrystal.h>

LiquidCrystal lcd(12, 11, 5, 4, 3, 2);
bool active = false;
int column = 0;
int count = 0;
String combo = "";

void setup()
{
  lcd.begin(16, 2);
  lcd.setCursor(0, 0);
  lcd.print("Enter Password:");
  
  Serial.begin(9600);
}

void loop()
{
  lcd.setCursor(column,1);
  lcd.print('_');
  lcd.setCursor(column,1);
  delay(500);
  lcd.print(' ');
  lcd.setCursor(column,1);
  delay(500);
  
  if (digitalRead(10) == HIGH){
    while (digitalRead(10) == HIGH){
      active = true;
      Serial.println("Button is Held");
    }
  }
  
  while (active == true){
    lcd.setCursor(column,1);
    lcd.print(count);
    
    if (digitalRead(10) == HIGH){
      count += 1;
      if (count > 9){
        count = 0;
      }
      while (digitalRead(10) == HIGH){
        Serial.print(count);
        Serial.println("   Button is Held");
      }
    }
    
    if (digitalRead(9) == HIGH){
      combo = combo + String(count);
      while (digitalRead(9) == HIGH){
        active = false;
        Serial.print(combo);
        Serial.println("   Next Line");
      }
      count = 0;
      column += 1;
    }
  }
  if (digitalRead(9) == HIGH){
    while (digitalRead(9) == HIGH){
      Serial.println("Next Line");
    }
    column += 1;
  }
  if (column > 15){
    column = 0;
  }
  
  if (digitalRead(8) == HIGH){
    while (digitalRead(8) == HIGH){
      Serial.println("Code Entered");
    }
    if (combo.toInt() == 7508){
      lcd.clear();
      String granted = "Access";
      lcd.setCursor(8 - (granted.length() / 2), 0);
      lcd.print(granted);
      granted = "Granted";
      lcd.setCursor(8 - (granted.length() / 2), 1);
      lcd.print(granted);
    }else {
      lcd.clear();
      String granted = "Access";
      lcd.setCursor(8 - (granted.length() / 2), 0);
      lcd.print(granted);
      granted = "Denied";
      lcd.setCursor(8 - (granted.length() / 2), 1);
      lcd.print(granted);
    }
    delay(5000);
    lcd.clear();
    lcd.setCursor(0,0);
    lcd.print("Enter Password:");
    column = 0;
  }
}