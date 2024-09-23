void LittleFsSetup() {
  if (!LittleFS.begin(FORMAT_LITTLEFS_IF_FAILED)) {
    Serial.println("setup -> LITTLEFS Mount Failed");
  } else {
    Serial.println("setup -> LITTLEFS mounted successfully");
    if (readConfig(config_filename) == false) {
      Serial.println("setup -> Could not read Config file -> initializing new file");
      // if not possible -> save new config file
      if (saveConfig(config_filename)) {
        Serial.println("setup -> Config file saved");
      }
    }
  }
}

bool saveConfig(String file_name) {
  StaticJsonDocument<1024> doc;

  // write variables to JSON file
  doc["total"] = total;
  doc["target"] = target;
  
  // write config file
  String tmp = "";
  serializeJson(doc, tmp);
  writeFile(config_filename, tmp);

  return true;
}

bool readConfig(String file_name) {
  String file_content = readFile(file_name);

  int config_file_size = file_content.length();
  Serial.println("Config file size: " + String(config_file_size));

  if (config_file_size > 1024) {
    Serial.println("Config file too large");
    return false;
  }
  StaticJsonDocument<1024> doc;
  auto error = deserializeJson(doc, file_content);
  if (error) {
    Serial.println("Error interpreting config file");
    return false;
  }

  float _value1 = doc["total"];
  float  _value2 = doc["target"];
 
  total = _value1;
  target = _value2;

  return true;
}

void writeFile(String filename, String message) {
  Serial.println("writeFile -> Writing file: " + filename);

  File file = LittleFS.open(filename, "w");
  if (!file) {
    Serial.println("writeFile -> failed to open file for writing");
    return;
  }
  if (file.print(message)) {
    Serial.println("writeFile -> file written");
  } else {
    Serial.println("writeFile -> write failed");
  }
  file.close();
}

String readFile(String filename) {
  Serial.println("readFile -> Reading file: " + filename);

  File file = LittleFS.open(filename);
   if(!file){
        Serial.println("Failed to open file for reading");
        return "";
    }
    

  String fileText = "";
  while (file.available()) {
    fileText = file.readString();
  }

  file.close();
  return fileText;
}

void deleteFile(fs::FS &fs, String filename){
  Serial.println("Deleting file: " + filename);
  if(fs.remove(filename)){
    Serial.println("- file deleted");
  } else {
    Serial.println("- delete failed");
  }
}


