#include <Arduino.h>
#include "LCDsettings.h"
#include <LiquidCrystal_I2C.h>


LCDsettings::LCDsettings(uint8_t address)
  : lcd(address, lcdColumns, lcdRows) {
}

void LCDsettings::LCDsetup() {
  lcd.init();
  lcd.backlight();
}

void LCDsettings::clearLCDLine(int line) {
  for (int n = 0; n < 20; n++) {  // 20 indicates symbols in line. For 2x16 LCD write - 16
    lcd.setCursor(n, line);
    lcd.print(" ");
  }
  lcd.setCursor(0, line);  // set cursor in the beginning of deleted line
}

void LCDsettings::clearLCDLine(int line, int startCell) {
  for (int n = startCell; n < 20; n++) {  // 20 indicates symbols in line. For 2x16 LCD write - 16
    lcd.setCursor(n, line);
    lcd.print(" ");
  }
  lcd.setCursor(0, line);  // set cursor in the beginning of deleted line
}

void LCDsettings::clearLCDLine(int line, int startCell, int stopCell) {
  for (int n = startCell; n < stopCell; n++) {  // 20 indicates symbols in line. For 2x16 LCD write - 16
    lcd.setCursor(n, line);
    lcd.print(" ");
  }
  lcd.setCursor(0, line);  // set cursor in the beginning of deleted line
}

void LCDsettings::startScreen() {
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("MOD:");
  lcd.setCursor(9, 0);
  lcd.print("TRG:");
  lcd.setCursor(0, 1);
  lcd.print("TOT:");
  lcd.setCursor(0, 2);
  lcd.print("BCH:");
  lcd.setCursor(0, 3);
  lcd.print("STS:");
  lcd.setCursor(12, 3);
  lcd.print("SEN:");
}

void LCDsettings::displayStatus(bool manualMode, bool meterRunning, int target, float total, bool modbusOK,float batchAmount,bool update) {
  if (!update) this->startScreen();
  clearLCDLine(0, 5, 2);
  lcd.setCursor(5, 0);
  if (!manualMode) lcd.print("AUT");
  else lcd.print("MAN");

  clearLCDLine(0, 14);
  lcd.setCursor(14, 0);
  lcd.print(target);
  lcd.print(" L");

  clearLCDLine(1, 5);
  lcd.setCursor(5, 1);
  lcd.print(total,1);
  lcd.print(" L");

  clearLCDLine(2, 5);
  lcd.setCursor(5, 2);
  lcd.print(batchAmount,1);
  lcd.print(" L");

  clearLCDLine(3, 5, 11);
  lcd.setCursor(5, 3);
  if (meterRunning) lcd.print("RUN");
  else lcd.print("STOP");

  clearLCDLine(3, 17);
  lcd.setCursor(17, 3);
  if (modbusOK) lcd.print("OK");
  else lcd.print("NO");

}

void LCDsettings::setSettings(int target) {
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("SET BATCH QTY");
  lcd.setCursor(0, 1);
  lcd.print("BATCH: ");
  lcd.print(target);
  lcd.print(" L");
  lcd.setCursor(0, 3);
  lcd.print("STOP->DEC");
  lcd.setCursor(10, 3);
  lcd.print("START->INC");
}

void LCDsettings::batchUpdater(float batch, float total) {
  clearLCDLine(1, 5);
  lcd.setCursor(5, 1);
  lcd.print(total,1);
  lcd.print(" L");

  clearLCDLine(2, 5);
  lcd.setCursor(5, 2);
  lcd.print(batch,1);
  lcd.print(" L");
}

void LCDsettings::manualDisplayStatus(bool manualMode, bool meterRunning, float total, bool modbusOK,float batchAmount) {
  clearLCDLine(0, 5);
  lcd.setCursor(5, 0);
  if (!manualMode) lcd.print("AUT");
  else lcd.print("MAN");

  clearLCDLine(1, 5);
  lcd.setCursor(5, 1);
  lcd.print(total,1);
  lcd.print(" L");

  clearLCDLine(2, 5);
  lcd.setCursor(5, 2);
  lcd.print(batchAmount,1);
  lcd.print(" L");

  clearLCDLine(3, 5, 11);
  lcd.setCursor(5, 3);
  if (meterRunning) lcd.print("RUN");
  else lcd.print("STOP");

  clearLCDLine(3, 17);
  lcd.setCursor(17, 3);
  if (modbusOK) lcd.print("OK");
  else lcd.print("NO");
}
