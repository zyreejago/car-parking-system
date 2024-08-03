#include <Wire.h>
#include <LiquidCrystal_I2C.h>
LiquidCrystal_I2C lcd(0x27, 16, 2); // Ubah alamat HEX jika perlu
#include <Servo.h>

Servo inGateServo;
Servo outGateServo;

int inIR = 2;
int outIR = 3;

int availableSlots = 4; // Jumlah total slot parkir

int inFlag = 0;
int outFlag = 0;

void setup() {
  lcd.init();
  lcd.begin(16, 2);
  lcd.backlight();
  pinMode(inIR, INPUT);
  pinMode(outIR, INPUT);

  inGateServo.attach(4);
  outGateServo.attach(5);

  inGateServo.write(100);
  outGateServo.write(100);

  lcd.setCursor(0, 0);
  lcd.print("    ARDUINO    ");
  lcd.setCursor(0, 1);
  lcd.print("PARKING SYSTEM ");
  delay(2000);
  lcd.clear();
}

void loop() {
  if (digitalRead(inIR) == LOW && inFlag == 0) {
    if (availableSlots > 0) {
      inFlag = 1;
      inGateServo.write(180);
      availableSlots--;
      delay(3000); // Delay sebelum menutup gate
      inGateServo.write(100); // Menutup gate setelah delay
      inFlag = 0; // Reset flag setelah membuka gate
    } else {
      lcd.setCursor(0, 0);
      lcd.print("    SORRY :(    ");
      lcd.setCursor(0, 1);
      lcd.print("  Parking Full  ");
      delay(3000);
      lcd.clear();
    }
  }

  if (digitalRead(outIR) == LOW && outFlag == 0) {
    if (availableSlots < 4) { // Ganti dengan jumlah maksimum slot parkir
      outFlag = 1;
      outGateServo.write(0);
      availableSlots++;
      delay(3000); // Delay sebelum menutup gate
      outGateServo.write(100); // Menutup gate setelah delay
      outFlag = 0; // Reset flag setelah membuka gate
    }
  }

  lcd.setCursor(0, 0);
  lcd.print("    WELCOME!    ");
  lcd.setCursor(0, 1);
  lcd.print("Slot Left: ");
  lcd.print(availableSlots);
}
