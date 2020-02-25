// include library to read and write from flash memory
#include <EEPROM.h>

void setwificode(String ssii, String code) {
  // Convert to array
  int len_ssii = ssii.length();
  int len_code = code.length();

  EEPROM.begin(512);
  for (int i = 0; i < len_ssii; ++i) {
    int j = 10 + i;
    EEPROM.write(j, ssii[i]);
  }

  for (int i = 0; i < len_code; ++i) {
    int j = 30 + i;
    EEPROM.write(j, code[i]);
  }

  EEPROM.write(0, len_ssii);
  EEPROM.write(5, len_code);
  EEPROM.commit();
}


int *getlenght() {
  int code[2];
  code[0] = char(EEPROM.read(0));
  code[1] = char(EEPROM.read(5));
  return code;
}

String *getwifi() {
  int lenssii = getlenght()[0];
  int lencode = getlenght()[1];
  String ssii, code;

  EEPROM.begin(512);
  for (int i = 0; i < lenssii; ++i) {
    int j = 10 + i;
    ssii += char(EEPROM.read(j));
  }
  for (int i = 0; i < lencode; ++i) {
    int j = 30 + i;
    code += char(EEPROM.read(j));
  }

  String wifi[2];
  wifi[0] = ssii;
  wifi[1] = code;
  return wifi;
}
