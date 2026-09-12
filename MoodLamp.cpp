int red_int = 0;
int green_int = 0;
int blue_int = 0;

int red_pin = 11;
int green_pin = 9;
int blue_pin = 10;

void setup()
{
  Serial.begin(9600);
  pinMode(red_pin, OUTPUT);
  pinMode(green_pin, OUTPUT);
  pinMode(blue_pin, OUTPUT);
}

void loop()
{
  int pot_In = analogRead(A0);
  if (pot_In <= 341){
    red_int = 341 - pot_In;
    green_int = pot_In;
    blue_int = 0;
  }else if (pot_In > 341 and pot_In < 682){
    red_int = 0;
    green_int = 682 - pot_In;
    blue_int = pot_In - 341;
  }else if (pot_In >= 682){
    red_int = pot_In - 682;
    green_int = 0;
    blue_int = 1023 - pot_In;
  }
  int red_out = map(red_int, 0, 341, 0, 255);
  int green_out = map(green_int, 0, 341, 0, 255);
  int blue_out = map(blue_int, 0, 341, 0, 255);
  
  Serial.println(pot_In);
  analogWrite(red_pin, red_out);
  analogWrite(green_pin, green_out);
  analogWrite(blue_pin, blue_out);
}