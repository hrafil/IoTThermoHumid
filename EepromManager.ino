void writeSsidAndPasswordToEEPROM(String ssid, String password)
{
  String stringToWrite = ssid + "$" + password;
  Serial.println("string to write " + stringToWrite);
  writeStringToEEPROM(0, stringToWrite);
  EEPROM.commit();
}

String readSsidAndPasswordFromEEPROM()
{
  readStringFromEEPROM(0);
}

String getSSIDFromString(String ssidAndPassword)
{
  return getSplittedStringValue(ssidAndPassword, '$', 0);
}

String getPasswordFromString(String ssidAndPassword)
{
  return getSplittedStringValue(ssidAndPassword, '$', 1);
}

void writeStringToEEPROM(int addrOffset, const String &strToWrite)
{
  byte len = strToWrite.length();
  EEPROM.write(addrOffset, len);
  for (int i = 0; i < len; i++)
  {
    EEPROM.write(addrOffset + 1 + i, strToWrite[i]);
  }
}

String readStringFromEEPROM(int addrOffset)
{
  int newStrLen = EEPROM.read(addrOffset);
  String result;
  for (int i = 0; i < newStrLen; i++)
  {
    result += char(EEPROM.read(addrOffset + 1 + i));
  }
  return result;
}

String getSplittedStringValue(String data, char separator, int index)
{
    int found = 0;
    int strIndex[] = { 0, -1 };
    int maxIndex = data.length() - 1;

    for (int i = 0; i <= maxIndex && found <= index; i++) {
        if (data.charAt(i) == separator || i == maxIndex) {
            found++;
            strIndex[0] = strIndex[1] + 1;
            strIndex[1] = (i == maxIndex) ? i+1 : i;
        }
    }
    return found > index ? data.substring(strIndex[0], strIndex[1]) : "";
}
