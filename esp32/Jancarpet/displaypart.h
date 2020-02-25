#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#define SCREEN_WIDTH 128 // OLED display width, in pixels
#define SCREEN_HEIGHT 64 // OLED display height, in pixels

//#define I2C_SDA 15
//#define I2C_SCL 2

// Declaration for an SSD1306 display connected to I2C (SDA, SCL pins)
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, -1);

void displayString(int i, int j, int txtSize , String str, String old) {
  display.setCursor(i, j);
  display.setTextSize(txtSize);
  if (old != str) {
    display.setTextColor(BLACK);
    display.print(old);
    display.setCursor(i, j);
    display.setTextColor(WHITE);
    display.print(str);
  } else { }

}

void displayInt(int i, int j, int txtSize , int str, int old) {
  display.setCursor(i, j);
  display.setTextSize(txtSize);
  if (old != str) {
    display.setTextColor(BLACK);
    display.print(old);
    display.setCursor(i, j);
    display.setTextColor(WHITE);
    display.print(str);
  } else { }

}
void startDisplay() {
  // Wire.begin( I2C_SDA, I2C_SCL, 1000000);
  // Invert Display
  //display.invertDisplay(1);

  if (!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) { // Address 0x3D for 128x64
    Serial.println(F("SSD1306 allocation failed"));
    for (;;);
  }
  delay(2000);
  display.clearDisplay();
  display.display();
}
