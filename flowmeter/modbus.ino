void Get_Resource_Right(int Reg_Address, int offset) {
  uint8_t Reg = flowMeterRight.readInputRegisters(Reg_Address, offset);

  if (Reg == flowMeterRight.ku8MBSuccess) {
    Serial.println("Read successful");
    for (int i = 0, z = 0; i < offset; i += 2, z++) {
      data = flowMeterRight.getResponseBuffer(i);
      data = (data << 16) | flowMeterRight.getResponseBuffer(i + 1);
      if (i != 8) dataArray[z] = *(float *)&data;
      else dataArray[z] = data;
    }

    for (int j = 0; j < offset; j++) {
      ReadArrayR[j] = dataArray[j];
    }

    modbusOK =true;

  } else {
    Serial.println("Read Unsuccesfull");
    modbusOK = false;
  }
}

void Get_Resource_Left(int Reg_Address, int offset) {
  uint8_t Reg = flowMeterLeft.readInputRegisters(Reg_Address, offset);

  if (Reg == flowMeterLeft.ku8MBSuccess) {
    Serial.println("Read successful");
    for (int i = 0, z = 0; i < offset; i += 2, z++) {
      data = flowMeterLeft.getResponseBuffer(i);
      data = (data << 16) | flowMeterLeft.getResponseBuffer(i + 1);
      dataArray[z] = *(float *)&data;
    }

    for (int j = 0; j < offset; j++) {
      ReadArrayL[j] = dataArray[j];
    }

  } else {
    Serial.println("Read Unsuccesfull");
    memset(ReadArrayL, 0, sizeof(ReadArrayL));
  }
}