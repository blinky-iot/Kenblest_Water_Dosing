void settingsMenu() {
  if (pcf.digitalRead(start1)) {
    target++;
    lcdRight.setSettings(target);
  }
  if (!pcf.digitalRead(stop1)) {
    if(target > 1) target--;
    lcdRight.setSettings(target);
  }
  if (pcf.digitalRead(set1)) {
    saveConfig(config_filename);
    newSettings = true;
  }
}

void flowMeter1Read() {
  if (millis() - lastFlowmeterRightFetch >= 500) {
    Get_Resource_Right(4112, 28);
    instanteneousTotal_flowmeterR = ReadArrayR[0];
    cumulativeTotal_flowmeterR = ReadArrayR[4] + ReadArrayR[5];
    Serial.println("Cumulative Total flowR: " + String(cumulativeTotal_flowmeterR) + " Instanteneous Total flowR: " + String(instanteneousTotal_flowmeterR));
    lastFlowmeterRightFetch = millis();
  }
}

void flowMeter1Read(bool state) {
    Get_Resource_Right(4112, 28);
    instanteneousTotal_flowmeterR = ReadArrayR[0];
    cumulativeTotal_flowmeterR = ReadArrayR[4] + ReadArrayR[5];
    Serial.println("Cumulative Total flowR: " + String(cumulativeTotal_flowmeterR) + " Instanteneous Total flowR: " + String(instanteneousTotal_flowmeterR));
}