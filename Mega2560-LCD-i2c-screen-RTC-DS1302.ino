#include <virtuabotixRTC.h>
#include <Wire.h>
#include <LiquidCrystal_I2C.h>
// Creation of the Real Time Clock Object
virtuabotixRTC myRTC(6, 7, 8);
LiquidCrystal_I2C lcd(0x27,16,2);

void setup()  {
  lcd.init();
  lcd.backlight();
  // Set the current date, and time in the following format:
  // seconds, minutes, hours, day of the week, day of the month, month, year
  myRTC.setDS1302Time(23, 37, 15, 7, 23, 6, 2022);
}

void loop()  {
  // This allows for the update of variables for time or accessing the individual elements.
  myRTC.updateTime();

  // Start printing elements as individuals
  lcd.print("NI ILE MASAA");
  delay(700);
  lcd.clear();
  delay(500);
  lcd.print("Date:");
  lcd.print(myRTC.dayofmonth);
  lcd.print("-");
  lcd.print(myRTC.month);
  lcd.print("-");
  lcd.print(myRTC.year);
  delay(500);
  lcd.setCursor(0,1);
  lcd.print("Time: ");
  lcd.print(myRTC.hours);
  lcd.print(":");
  lcd.print(myRTC.minutes);
  lcd.print(":");
  lcd.print(myRTC.seconds);
  // Delay so the program doesn't print non-stop
  delay(4200);
  lcd.clear();
  delay(500);
  lcd.setCursor(2,0);
  lcd.print("Butasi is ");
  lcd.setCursor(4,1);
  lcd.print("Awesome");
  delay(500);
  lcd.clear();
}
