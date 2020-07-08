#include <LiquidCrystal.h>
#include <stdio.h>
#include <math.h>
LiquidCrystal lcd(12, 11, 5, 4, 3, 2);
char rxBuff[64];
int ValueA = 0, ValueB = 0;
char operation[16];
void setup()
{
  lcd.begin(16, 2);
  Serial.begin(9600);
  Serial.setTimeout(500);
  for (int i = 0; i < 24; i++)
  {
    lcd.setCursor(i, 0);
    lcd.print("Kalkulator");
    lcd.setCursor(i, 1);
    lcd.print("by Mateusz");
    delay(200);
    lcd.clear();
  }
  lcd.clear();
}
void loop()
{
  memset(rxBuff, 0, sizeof(rxBuff));
  Serial.readBytesUntil('\r', rxBuff, sizeof(rxBuff) - 1);
  sscanf(rxBuff, "%i%[^1234567890]%i", &ValueA, operation, &ValueB);
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print(ValueA);
  lcd.print(operation);
  lcd.print(ValueB);
  lcd.setCursor(0, 1);
  if (*operation == '+')
  {
    lcd.print(ValueA + ValueB);
  }
  else if (*operation == '-')
  {

    lcd.print(ValueA - ValueB);
  }
  else if (*operation == '*')
  {

    lcd.print(ValueA * ValueB);
  }
  else if (*operation == '/')
  {
    if (ValueB != 0)
    {
      float result = float(ValueA) / float(ValueB);
      lcd.print(result);
    }
    else
    {
      lcd.print("NIE DZIELP P. 0");
    }
  }
  else if (*operation == '%')
  {
    lcd.print("REST = ");
    lcd.print(ValueA % ValueB);
  }
  else if (*operation == '^')
  {
    lcd.print(pow(ValueA, ValueB));
  }
  else if (*operation == '!')
  {
    long int silnia = 1;
    for (int i = ValueA; i > 1; i--)
    {
      silnia *= i;
    }
    lcd.print(silnia);
  }
  else
  {
    lcd.print("Error");
  }
  Serial.print("ValueA:");
  Serial.print(ValueA);
  Serial.print(" ValueB:");
  Serial.print(ValueB);
  Serial.print(" operation:");
  Serial.println(operation);
}