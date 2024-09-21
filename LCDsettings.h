#ifndef LCDsettings_h
#define LCDsettings_h

#include <Arduino.h>
#include <LiquidCrystal_I2C.h> 

class LCDsettings{
private:
  int lcdColumns = 20;
  int lcdRows = 4;
  LiquidCrystal_I2C lcd;
  void clearLCDLine(int line);
  void clearLCDLine(int line, int startCell);
  void clearLCDLine(int line, int startCell, int stopCell);

public:
  LCDsettings(uint8_t address);
  void startScreen();
  void displayStatus(bool manualMode, bool meterRunning, int target, float total, float batchAmount, bool update = true);
  void setSettings(int target);
  void batchUpdater(float batch, float total);
  void manualDisplayStatus(bool manualMode, bool meterRunning, float total, float batchAmount);
  void LCDsetup();
};

#endif