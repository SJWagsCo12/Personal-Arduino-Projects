#include <LedControl.h>

LedControl dmat = LedControl(48, 52, 50, 1);

int randNum;

byte dice_1[] = 
{
  B00000000,
  B00000000,
  B00000000,
  B00011000,
  B00011000,
  B00000000,
  B00000000,
  B00000000
};
byte dice_2[] = 
{
  B11000000,
  B11000000,
  B00000000,
  B00000000,
  B00000000,
  B00000000,
  B00000011,
  B00000011
};
byte dice_3[] = 
{
  B11000000,
  B11000000,
  B00000000,
  B00011000,
  B00011000,
  B00000000,
  B00000011,
  B00000011
};
byte dice_4[] = 
{
  B11000011,
  B11000011,
  B00000000,
  B00000000,
  B00000000,
  B00000000,
  B11000011,
  B11000011
};
byte dice_5[] = 
{
  B11000011,
  B11000011,
  B00000000,
  B00011000,
  B00011000,
  B00000000,
  B11000011,
  B11000011
};
byte dice_6[] = 
{
  B11000011,
  B11000011,
  B00000000,
  B11000011,
  B11000011,
  B00000000,
  B11000011,
  B11000011
};

void setup() {
  Serial.begin(9600);
  pinMode(22, INPUT_PULLUP);

  dmat.shutdown(0, false);
  dmat.setIntensity(0,8);
  dmat.clearDisplay(0);
}

void loop() {
  while (digitalRead(22) == HIGH){
    Serial.println("Button is NOT Pressed");
  }
  if (digitalRead(22) == LOW){
    Serial.print("Button is Pressed   ");
    randNum = rand() % 6;
    Serial.println(randNum);
    dmat.clearDisplay(0);
  }

  if (randNum == 0){
    for (int i = 0; i < 8; i++){
      dmat.setRow(0, i, dice_1[i]);
    }
  }else if (randNum == 1){
    for (int i = 0; i < 8; i++){
      dmat.setRow(0, i, dice_2[i]);
    }
  }else if (randNum == 2){
    for (int i = 0; i < 8; i++){
      dmat.setRow(0, i, dice_3[i]);
    }
  }else if (randNum == 3){
    for (int i = 0; i < 8; i++){
      dmat.setRow(0, i, dice_4[i]);
    }
  }else if (randNum == 4){
    for (int i = 0; i < 8; i++){
      dmat.setRow(0, i, dice_5[i]);
    }
  }else if (randNum == 5){
    for (int i = 0; i < 8; i++){
      dmat.setRow(0, i, dice_6[i]);
    }
  }
}