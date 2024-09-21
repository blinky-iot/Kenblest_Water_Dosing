// void LCDsetup() {
//   lcdLeft.init();
//   lcdLeft.backlight();

//   lcdRight.init();
//   lcdRight.backlight();
// }

// void clearLCDLineRight(int line) {
//   for (int n = 0; n < 20; n++) {  // 20 indicates symbols in line. For 2x16 LCD write - 16
//     lcdRight.setCursor(n, line);
//     lcdRight.print(" ");
//   }
//   lcdRight.setCursor(0, line);  // set cursor in the beginning of deleted line
// }

// void clearLCDLineRight(int line, int startCell) {
//   for (int n = startCell; n < 20; n++) {  // 20 indicates symbols in line. For 2x16 LCD write - 16
//     lcdRight.setCursor(n, line);
//     lcdRight.print(" ");
//   }
//   lcdRight.setCursor(0, line);  // set cursor in the beginning of deleted line
// }

// void clearLCDLineRight(int line, int startCell,int stopCell) {
//   for (int n = startCell; n < stopCell; n++) {  // 20 indicates symbols in line. For 2x16 LCD write - 16
//     lcdRight.setCursor(n, line);
//     lcdRight.print(" ");
//   }
//   lcdRight.setCursor(0, line);  // set cursor in the beginning of deleted line
// }

// void clearLCDLineLeft(int line) {
//   for (int n = 0; n < 20; n++) {  // 20 indicates symbols in line. For 2x16 LCD write - 16
//     lcdLeft.setCursor(n, line);
//     lcdLeft.print(" ");
//   }
//   lcdLeft.setCursor(0, line);  // set cursor in the beginning of deleted line
// }

// void clearLCDLineLeft(int line, int startCell) {
//   for (int n = startCell; n < 20; n++) {  // 20 indicates symbols in line. For 2x16 LCD write - 16
//     lcdLeft.setCursor(n, line);
//     lcdLeft.print(" ");
//   }
//   lcdLeft.setCursor(0, line);  // set cursor in the beginning of deleted line
// }

// void clearLCDLineLeft(int line, int startCell,int stopCell) {
//   for (int n = startCell; n < stopCell; n++) {  // 20 indicates symbols in line. For 2x16 LCD write - 16
//     lcdLeft.setCursor(n, line);
//     lcdLeft.print(" ");
//   }
//   lcdLeft.setCursor(0, line);  // set cursor in the beginning of deleted line
// }

// void startScreenRight() {

//   lcdRight.clear();
//   lcdRight.setCursor(0, 0);
//   lcdRight.print("MODE:");
//   lcdRight.setCursor(0, 1);
//   lcdRight.print("TOTAL:");
//   lcdRight.setCursor(0, 2);
//   lcdRight.print("CURRENT:");
//   lcdRight.setCursor(0, 3);
//   lcdRight.print("STATUS:");
// }
// void startScreenLeft() {
//   lcdLeft.clear();
//   lcdLeft.setCursor(0, 0);
//   lcdLeft.print("MODE:");
//   lcdLeft.setCursor(0, 1);
//   lcdLeft.print("TOTAL:");
//   lcdLeft.setCursor(0, 2);
//   lcdLeft.print("CURRENT:");
//   lcdLeft.setCursor(0, 3);
//   lcdLeft.print("STATUS:");
// }

// void displayStatusRight()
// {
//   clearLCDLineRight(0,6);
//   lcdRight.setCursor(6,0);
//   if(!manualMode) lcdRight.print("AUTO");
//   else lcdRight.print("MAN");

//   clearLCDLineRight(1,7);
//   lcdRight.setCursor(7,1);
//   lcdRight.print(980);
//   lcdRight.print(" L");

//   clearLCDLineRight(2,9);
//   lcdRight.setCursor(9,2);
//   lcdRight.print(20);
//   lcdRight.print(" L");

//   clearLCDLineRight(3,8);
//   lcdRight.setCursor(8,3);
//   if(meter1running) lcdRight.print("RUNNING");
//   else lcdRight.print("STOPPED");


// }

// void displayStatusLeft(){}

