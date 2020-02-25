//#include <Wire.h>

String result = "", oldresult = "";
String tx = "", oldtx = "";

int bat =0, oldBat = -1; //bat
String rate="" , oldRate = "";

#include "blepart.h"
#include "bitmaps.h"
#include "capacitive.h";
#include "eeprom.h";
//#include "wifipart.h"
#include "displaypart.h";



void setup() {
  Serial.begin(115200);
  startDisplay();

  pinMode(34, INPUT);

  createBle();
  display.drawBitmap(55, 0,  ble_on , 8, 8 , WHITE); // ble on
  displayString(64, 0 , 1, "!", ""); //display oled
  // displayString(5, 50, 1, "Wait to connect..", ""); //display oled

  //  setwificode("codewifi213", "21254efrt");
  //  Serial.print("code  ");
  //  Serial.println(getlenght()[0] + " , " + getlenght()[1]);
  //  Serial.println(getwifi()[0] + " , " + getwifi()[1]);
  //
  // if(connectToNetwork()){
  // display.drawBitmap(48, 0,  wifi_on , 8, 8 , WHITE);
  // }else{
  //   display.drawBitmap(44, 0,  wifi_on , 8, 8 , WHITE);
  //   displayString(53,0 , 1, "!", "");  //display oled
  // }

  //Serial.println(result);
}


void loop() {
  result = res();
  detectSajda();
  countSajda();
  countRaqa();
  reset();
  /**/
  if (sajda > 0 && raqa <= maxraqa ) {
    if(raqa != oldRaqa || sajda != oldSajda){
    tx = String(raqa) + '~' + String(sajda) + '~' + String(timesajda) + '~' + counter;
    }
  }

  if (deviceConnected) {
    displayString(64, 0 , 1, " ", "!"); //ble off
    
    int len = result.length();
    if (len > 0) {
      if (result == "salam" ) {
        initialize();
        delay(50);
        sendMsg("salam");
        
      }

      if (result == "none" && result != oldresult) {
      //  sendMsg("none");
        delay(1000);
        sendMsg("none");
        oldresult = "none";
      }

      if (result.charAt(0) == 'n' && result.charAt(len - 1) == 'r') {
        initialize();
        String v = "";
        for (int i = 0; i < len; i++) {
          if (isDigit(result[i])) {
              v += (char)result[i]; }
        maxraqa = v.toInt(); }
        delay(50);
        raqa = 0;
        sajda = 0;
        timesajda = 0;
        result = "";
      }
    }

   if (tx != oldtx && timesajda != 0 && sajda != 0 ) {
      sendMsg(tx);
      Serial.println(tx);
    }

 }

  if (!deviceConnected && oldDeviceConnected) {
    delay(500); // give the bluetooth stack the chance to get things ready
    pServer->startAdvertising(); // restart advertising
    displayString(64, 0 , 1, "!", ""); //display oled
    sendMsg("ble_off");
   
    oldDeviceConnected = deviceConnected;
  }

  // connecting
  if (deviceConnected && !oldDeviceConnected) {
    // do stuff here on connecting
    displayString(64, 0 , 1, "!", ""); //display oled
    sendMsg("ble_off");
    initialize();
    oldDeviceConnected = deviceConnected;
  }

  diplayinLoop(); //

  if (timesajda == 0) {
    timesajda = oldtheTime;
  }
  
  oldresult = result;
  oldtheTime = timesajda;
  oldRaqa = raqa;
  oldMax = maxraqa;
  oldtx = tx;
  oldBat = bat;
  oldRate = rate;
  oldSajda = sajda; 

  display.display();
  delay(100);

}


void diplayinLoop(){
  int a34 = analogRead(34);

  bat = int(a34 * (3.3 / 4095.0));
  rate = String(int(100 * a34 / 4095.0)) + "%";

  displayInt(5, 0, 1, int( a34 * (3.3 / 4095.0)), oldBat); //display oled Battery Status
  displayString(25, 0, 1, String(int(100 * a34 / 4095.0)) + "%", oldRate); //display oled Battery Status

  displayInt(5, 17, 4, sajda, oldSajda);
  displayInt(80, 17, 4, raqa, oldRaqa);

  if (maxraqa > 0) {
    displayString(50, 50, 1, String(timesajda) , String(oldtheTime) );
    displayInt(100, 0, 1, maxraqa, oldMax);
    displayString(110, 0, 1, "R", "");
  }
}
