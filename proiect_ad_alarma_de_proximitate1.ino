#include<LiquidCrystal.h>

int pirPin = 13;
int buzzerPin = 2;
int switchPin = 0;
int state = LOW;
unsigned long previousTime;
LiquidCrystal lcd(12, 11, 6, 5, 4, 3);

void setup()
{
  	// Initializare
	pinMode(pirPin, INPUT);
	pinMode(buzzerPin, OUTPUT);
  	lcd.begin(16, 2);
}

void loop()
{
  int motion = 0;
  motion = digitalRead(pirPin);
  state = digitalRead(switchPin);
  	
  /*
  Daca switch-ul se afla pe pozitia ON
  */
  if (state == HIGH) {
    
    /* 
  	Daca senzorul PIR detecteaza miscare,
  	atunci buzzerul se activeaza si ecranul
  	lcd va afisa durata acestei detectari
  	*/
    if (motion == HIGH){
      digitalWrite(buzzerPin, HIGH);
      lcd.setCursor(0, 0);
      lcd.print("Alarma activata");
      lcd.setCursor(0, 1);
      lcd.print("Durata: ");
      lcd.setCursor(8, 1);
      lcd.print((millis() - previousTime) / 1000);
      
      if ((millis() - previousTime) / 1000 < 10) {
        lcd.setCursor(9, 1);
        lcd.print('.');
        lcd.setCursor(10, 1);
        lcd.print(((millis() - previousTime) / 100) % 10);
        lcd.setCursor(11, 1);

      } else {
        lcd.setCursor(10, 1);
        lcd.print('.');
        lcd.setCursor(11, 1);
        lcd.print(((millis() - previousTime) / 100) % 10);
        lcd.setCursor(12, 1);
      }
      lcd.print("s            ");
    }
    
    /*
    Cand senzorul nu detecteaza nimic,
    ecranul lcd va afisa faptul ca este in
    Stand by
    */
    else {
      digitalWrite(buzzerPin, LOW);
      lcd.setCursor(0, 0);
      lcd.print("   Stand by     ");
      lcd.setCursor(0, 1);
      lcd.print("                ");
      previousTime = millis();
    }
    delay(100);
    
  /*
  Daca switch-ul se afla pe pozitia OFF
  */
  } else {
    digitalWrite(buzzerPin, LOW);
    lcd.setCursor(0, 0);
    lcd.print("   System OFF   ");
    lcd.setCursor(0, 1);
    lcd.print("                  ");
    previousTime = millis();
  }
}