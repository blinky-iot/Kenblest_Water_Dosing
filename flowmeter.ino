#include <Shifty.h>
#include "SPI.h"
#include <Arduino.h>
#include <Adafruit_PCF8574.h>
#include "LCDsettings.h"
#include "pinouts.h"

//LittleFs Handler
#include "FS.h"
#include <LittleFS.h>
#include <ArduinoJson.h>

#define FORMAT_LITTLEFS_IF_FAILED true
const String config_filename = "/waterBatcher.json";

Adafruit_PCF8574 pcf;
Shifty shift;


unsigned long previousCounter = 0;

int target = 100;
float total;

LCDsettings lcdRight(0x26);
LCDsettings lcdLeft(0x27);

bool meter1running = false;
bool meter2running = false;

bool manualMode = true;
bool previousManualMode = false;
bool previousMode = false;
bool previousmeter1running = true;

long LastUpdate;
bool newSettings;

bool newTotal = false;
bool modbusOK = false;

uint32_t requiredPulses;


void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
  RS485.begin(9600, SWSERIAL_8N1);
  flowMeterRight.begin(SLAVE_ID_R, RS485);
  //flowMeterLeft.begin(SLAVE_ID_L, RS485);

  LittleFsSetup();

  inputSetup();
  outputSetup();

  for (int i = 0; i < 8; i++) {
    shift.writeBit(i, LOW);
  }

  LCDsetups();

  LastUpdate = millis();
}

void loop() {
  // put your main code here, to run repeatedly:
  modeChange();      // check for mode change
  flowMeter1Read();  // modbus Read instanteneous and total flow

  if (!manualMode) automaticModeOperation();  // Automatic mode
  else manualModeOperation();                 // Manual mode

  if (millis() - LastUpdate >= 2000) {
    LastUpdate = millis();
    if (newSettings) {
      lcdRight.displayStatus(manualMode, meter1running, target, total, batchBuffer, false);
      newSettings = false;
    }
    if (manualMode) {
      lcdRight.manualDisplayStatus(manualMode, meter1running, cumulativeTotal_flowmeterR, batchBuffer);
    } else
      lcdRight.displayStatus(manualMode, meter1running, target, total, batchBuffer);
  }
}


void modeChange() {
  if (pcf.digitalRead(modeSetter1)) manualMode = false;
  else manualMode = true;
  if (manualMode == false && previousManualMode == true) {
    lcdRight.displayStatus(manualMode, meter1running, target, total, batchBuffer, false);
    previousManualMode = manualMode;
  } else if (manualMode == true && previousManualMode == false) {
    previousCumulativeTotalR = cumulativeTotal_flowmeterR;
    batchBuffer = 0;
    previousManualMode = manualMode;
  }
}

void startTap1() {
  shift.writeBit(valve1, HIGH);
}

void stopTap1() {
  shift.writeBit(valve1, LOW);
}

void updateTotals() {
  //flowMeter1Read(true);
  total = cumulativeTotal_flowmeterR;
  saveConfig(config_filename);
}

void automaticModeOperation() {
  if (pcf.digitalRead(start1) == true && pcf.digitalRead(stop1) == true) {  // Start sequence and Wait for full batch, Stop with bitton

    previousCumulativeTotalR = cumulativeTotal_flowmeterR;
    meter1running = true;
    lcdRight.displayStatus(manualMode, meter1running, target, total, batchBuffer);
    startTap1();
    displayCumulativeTotalR = cumulativeTotal_flowmeterR;
    batchBuffer = 0.00;
    lcdRight.batchUpdater(batchBuffer, cumulativeTotal_flowmeterR);

    while (true) {
      flowMeter1Read();
      batchBuffer = cumulativeTotal_flowmeterR - previousCumulativeTotalR;
      meter1running = true;

      if (batchBuffer >= target) {
        stopTap1();
        meter1running = false;
        displayBatch();
        if (instanteneousTotal_flowmeterR == 0) {
          updateTotals();
          break;
        }
      } else {
        displayBatch();
      }

      if (!pcf.digitalRead(stop1)) {
        stopTap1();
        meter1running = false;
        updateTotals();
        break;
      }
    }
  } else {
    stopTap1();
    meter1running = false;
    updateTotals();
  }

  if (pcf.digitalRead(set1)) {
    lcdRight.setSettings(target);
    newSettings = false;
    for (;;) {
      if (!newSettings) settingsMenu();
      else break;
    }
  }
}

void manualModeOperation() {
  if (pcf.digitalRead(start1) && pcf.digitalRead(stop1) == true) {
    startTap1();
    meter1running = true;
    batchBuffer = cumulativeTotal_flowmeterR - previousCumulativeTotalR;
    displayBatch();
    newTotal = true;

  } else {
    stopTap1();
    batchBuffer = cumulativeTotal_flowmeterR - previousCumulativeTotalR;
    displayBatch();
    meter1running = false;

    if (instanteneousTotal_flowmeterR == 0.00) {
      if (newTotal) {
        updateTotals();
        newTotal = false;
      }
      previousCumulativeTotalR = cumulativeTotal_flowmeterR;
    }
  }
}



// bool checkPulses(uint32_t pulses) {
//   if (meter1running == true && counter_A >= pulses) {
//     stopTap1();
//     meter1running = false;
//     total += (counter_A * 0.5);
//     saveConfig(config_filename);
//     lcdRight.displayStatus(manualMode, meter1running, target, total);
//     *p1 = 0;
//     counter_A = 0;
//     return false;
//   } else {
//     if (counter_A != previousCounter) {
//       lcdRight.batchUpdater(counter_A);
//       previousCounter = counter_A;
//     }
//     return true;
//   }
// }

// void checkPulses() {
//   if (counter_A != previousCounter) {
//     lcdRight.batchUpdater(counter_A);
//     previousCounter = counter_A;
//   }
// }

// void pulseToLiter() {
//   requiredPulses = target / 0.5;
// }

// void saveTotals() {
//   if (meter1running == false && previousmeter1running == true) {
//     saveConfig(config_filename);
//     previousmeter1running = false;
//   }
// }
