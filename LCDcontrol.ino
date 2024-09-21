void LCDsetups() {
  lcdRight.LCDsetup();
  lcdLeft.LCDsetup();
  lcdRight.startScreen();
  lcdLeft.startScreen();
}

void displayBatch() {
  if (cumulativeTotal_flowmeterR - displayCumulativeTotalR >= 0.01) {
    lcdRight.batchUpdater(batchBuffer, cumulativeTotal_flowmeterR);
    displayCumulativeTotalR = cumulativeTotal_flowmeterR;
  }
}