void inputSetup() {
  Serial.println("Adafruit PCF8574 Initiallization...");

  if (!pcf.begin(0x3E, &Wire)) {
    Serial.println("Couldn't find PCF8574");
    while (1);
  }
  for (uint8_t p=0; p<8; p++) {
    pcf.pinMode(p, INPUT_PULLUP);
  }
}

void outputSetup(){
  shift.setBitCount(8);
  shift.setPins(23, 18, 5, 19);

    for(int i=0; i < 8; i++){
    shift.writeBit(i, LOW);
  } 

}