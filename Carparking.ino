#include<Servo.h>  // Servo library for servo motor control to demonstrate gate open and locked activity.
#include <LiquidCrystal.h> // library file for LCD display
const int rs = 23, en = 22, d4 = 24, d5 = 26, d6 = 28, d7 = 30; // Initiating pins for LCD display
LiquidCrystal lcd(rs, en, d4, d5, d6, d7); // Creating LCD object to access and control LCD display texts
Servo gate; // creating SERVO object to contol servo motor
bool triger=false; 
int front,back;
int sensorValues[7],availableParking[7];
int cars=0;
void setup(void) 
{
  lcd.begin(20, 4);
  for(int i=2;i<9;++i)
      pinMode(i,OUTPUT);

  Serial.begin(9600);  // for Serial monitoring at baud rate 9600 (9600 bits per second)
  pinMode(54,INPUT); // Selecting pin mode for further operations
  pinMode(9,INPUT);
  pinMode(10,INPUT);
  pinMode(11,OUTPUT);  
  gate.attach(8);
  digitalWrite(11,HIGH);
  gate.write(0);
  delay(200);
  digitalWrite(11,LOW);
}
void loop(void)
{
  delay(200);
  senceValues();
  senceDoor();
  countCars();
  if(front==0)
  {
    if(cars<6)
    {
     digitalWrite(11,HIGH);
    gate.write(90);
    delay(400);
    digitalWrite(11,LOW);
    senceDoor();
    lcd.clear();
    lcd.setCursor(0,0);
    lcd.print("|------------------|");
    lcd.setCursor(0,1);
    lcd.print("|       Go to      |");
    lcd.setCursor(0,2);
    lcd.print("|    ");
    lcd.print("Slot No: ");
    lcd.print(allotePlace());
    lcd.print("    |");
    lcd.setCursor(0,3);
    lcd.print("|------------------|");
    while(back!=0)
    {
      senceDoor();
      delay(50);
    }
    digitalWrite(11,HIGH);
    gate.write(0);
    delay(400);
    digitalWrite(11,LOW);
    delay(500);
    triger = true; 
    }
    else
    {
      lcd.clear();
      lcd.setCursor(0,0);
      lcd.print("|------------------|");
      lcd.setCursor(0,1);
      lcd.print("Not Enough Space for");
      lcd.setCursor(0,2);
      lcd.print("      Parking       ");
      lcd.setCursor(0,3);
      lcd.print("|------------------|");
    }
  }
  if(back==0)
  {
    if(!triger){
      digitalWrite(11,HIGH);
    gate.write(90);
    delay(400);
    digitalWrite(11,LOW);
    senceDoor();
    while(front!=0)
    {
      senceDoor();
      delay(5);
    }
    digitalWrite(11,HIGH);
    gate.write(0);
    delay(400);
    digitalWrite(11,LOW);
    delay(500);
    }
    else triger = false;
  }
  lcd.setCursor(1,0);
  lcd.print(" Parking Dash Board ");
  lcd.setCursor(0,1);
  if(availableParking[1]==1) lcd.print("Empty  ");
  else lcd.print("Filled  ");
  lcd.setCursor(7,1);
  if(availableParking[2]==1) lcd.print("Empty  ");
  else lcd.print("Filled  ");
  lcd.setCursor(14,1);
  if(availableParking[3]==1) lcd.print("Empty  ");
  else lcd.print("Filled  ");
  lcd.setCursor(0,2);
  lcd.print("------|------|------");
  lcd.setCursor(0,3);
  if(availableParking[4]==1) lcd.print("Empty  ");
  else lcd.print("Filled  ");
  lcd.setCursor(7,3);
  if(availableParking[5]==1) lcd.print("Empty  ");
  else lcd.print("Filled  ");
  lcd.setCursor(14,3);
  if(availableParking[6]==1) lcd.print("Empty  ");
  else lcd.print("Filled  ");  
  delay(20);
}
void senceDoor(void)
{
  front = digitalRead(9);
  back = digitalRead(10);
}
void countCars(void)
{
  cars =0;
  for(int i=1;i<7;++i)
  {
    if(availableParking[i]==0) ++cars;
  }
}
void senceValues(void)
{
  for(int i=1;i<7;++i)
  {
    digitalWrite(i+1,HIGH);
    sensorValues[i] = analogRead(54);
    digitalWrite(i+1,LOW);
    if(sensorValues[i]<100) 
       availableParking[i] = 0;
    else availableParking[i]=1;
  }
}

int allotePlace(void)
{
  for(int i=1;i<7;++i)
  {
    if(availableParking[i]==1)
        return i;
  }
}
