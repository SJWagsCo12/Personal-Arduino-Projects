// C++ code
//
#include <LiquidCrystal.h>

bool ButPres = false;
bool gameOver = false;

LiquidCrystal lcd_1(12, 11, 5, 4, 3, 2);

void setup()
{
  lcd_1.begin(16, 2); // Set up the number of columns and rows on the LCD.
}

void loop()
{
  int num = random(10, 200);
  num = num * 100;
  int sec = num / 1000;
  int mil = num % 1000;
  String disTim = String(sec) + "." + String(mil) + "s";
  
  // Print a message to the LCD
  lcd_1.print("Stop at ");
  lcd_1.print(disTim);
  
  // set the cursor to column 0, line 1
  lcd_1.setCursor(0, 1);
  
  // Run game until button is pressed
  delay(3000);
  int counter = 0;
  int seconds = 0;
  int milliseconds = 0;
  
  while (ButPres == false){
    counter += 100;
    seconds = counter / 1000;
    milliseconds = counter % 1000;
    delay(100);
    String displayTime = String(seconds) + "." + String(milliseconds) + "s";
    lcd_1.print(displayTime);
    lcd_1.setCursor(0, 1);
    if (digitalRead(8) == HIGH){
      	ButPres = true;
    }
  }
  delay(1000);
  if (counter == num and gameOver == false){
    lcd_1.clear();
    String win = "Winner";
    lcd_1.setCursor(8 - (win.length() / 2), 0);
    lcd_1.print(win);
    String comp = "Congrats";
    lcd_1.setCursor(8 - (comp.length() / 2), 1);
    lcd_1.print(comp);
    gameOver = true;
  } else if (counter != num and gameOver == false){
    lcd_1.clear();
    String win = "Better Luck";
    lcd_1.setCursor(8 - (win.length() / 2), 0);
    lcd_1.print(win);
    String comp = "Next Time";
    lcd_1.setCursor(8 - (comp.length() / 2), 1);
    lcd_1.print(comp);
    gameOver = true;
  }
  delay(5000);
  ButPres = false;
  lcd_1.clear();
  gameOver = false;
}