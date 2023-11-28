#include "AdafruitIO_WiFi.h"

//AdafruitIO_WiFi io(IO_USERNAME, IO_KEY, "", "");
//AdafruitIO_Group *group = io.group(FEED_GROUP_NAME);
class MyAdafruitIO : public AdafruitIO_ESP32 {
public:
  using AdafruitIO_ESP32::_disconnect;
  using AdafruitIO_ESP32::_connect;
  
  // Correct the constructor to match the base class
  MyAdafruitIO(const char *user, const char *key, const char *ssid, const char *pass)
    : AdafruitIO_ESP32(user, key, ssid, pass) {}
};
MyAdafruitIO io(IO_USERNAME, IO_KEY, "", "");
AdafruitIO_Group *group = io.group(FEED_GROUP_NAME);
#define IO_LOOP_DELAY 500
unsigned long lastUpdate = 0;
int flag = 0;
unsigned long lastSent = 0;
int prevMode = 0;

void handleSecondsPerMode(AdafruitIO_Data *data);
void handleTwinkleDensity(AdafruitIO_Data *data);
void handleTwinkleSpeed(AdafruitIO_Data *data);
void handleBrightness(AdafruitIO_Data *data);
void handlePalette(AdafruitIO_Data *data);
void handleMode(AdafruitIO_Data *data);
void handlecolour1(AdafruitIO_Data *data);
void handlecolour2(AdafruitIO_Data *data);
void handlecolour3(AdafruitIO_Data *data);
void handlecolour4(AdafruitIO_Data *data);
void UpdateDataIO();
void updateData() ;

void updateIOCredentials(const char *username, const char *key, const char *ssid, const char *pass) {
  // Create a new AdafruitIO_WiFi instance with updated credentials
  Serial.println("z");
  //io._disconnect();
  delay(1000);
  Serial.println("a");
  //AdafruitIO_WiFi newIO(username, key, ssid, pass);
  MyAdafruitIO newIO(username, key, ssid, pass);
  Serial.println("b");
  // Replace the existing io instance with the new one
  io = newIO;
  Serial.println("c");
  
  io.connect();
  io._connect();
  Serial.println("d");
  Serial.println("Connecting to Adafruit IO...");
  group->onMessage("secondspermode", handleSecondsPerMode);
  group->onMessage("twinkledensity", handleTwinkleDensity);
  group->onMessage("twinklespeed", handleTwinkleSpeed);
  group->onMessage("brightness", handleBrightness);
  group->onMessage("palette", handlePalette);
  group->onMessage("mode", handleMode);
  group->onMessage("colour1", handlecolour1);
  group->onMessage("colour2", handlecolour2);
  group->onMessage("colour3", handlecolour3);
  group->onMessage("colour4", handlecolour4);
  while(io.status() < AIO_CONNECTED) {
    Serial.print(".");
    delay(500);
  }
  group->get();
  if (io.status() == 21) {
    Serial.println(io.status());
    UpdateDataIO();
    updateData();
    Serial.println(io.status());
  }
}

void AdafruitIOStart() {
  io.connect();
  Serial.println("Connecting to Adafruit IO...");
  group->onMessage("secondspermode", handleSecondsPerMode);
  group->onMessage("twinkledensity", handleTwinkleDensity);
  group->onMessage("twinklespeed", handleTwinkleSpeed);
  group->onMessage("brightness", handleBrightness);
  group->onMessage("palette", handlePalette);
  group->onMessage("mode", handleMode);
  group->onMessage("colour1", handlecolour1);
  group->onMessage("colour2", handlecolour2);
  group->onMessage("colour3", handlecolour3);
  group->onMessage("colour4", handlecolour4);
  group->get();
}


void handleSecondsPerMode(AdafruitIO_Data *data) {
  SECONDS_PER_PALETTE = data->toInt();
  if (SECONDS_PER_PALETTE < 1)
  {
    SECONDS_PER_PALETTE = 1;
  }
  preferences.putInt("palettetimer", SECONDS_PER_PALETTE);
}
void handleTwinkleDensity(AdafruitIO_Data *data) {
  TWINKLE_DENSITY = data->toInt();
  preferences.putInt("twinkledensity", TWINKLE_DENSITY);
}
void handleTwinkleSpeed(AdafruitIO_Data *data) {
  TWINKLE_SPEED = data->toInt();
  preferences.putInt("twinklespeed", TWINKLE_SPEED);
}
void handleBrightness(AdafruitIO_Data *data) {
  Serial.println("Brightness Changed");
  BRIGHTNESS = data->toInt();
  preferences.putInt("brightness", BRIGHTNESS);
}
void handlePalette(AdafruitIO_Data *data) {
  MODE = data->toInt();
  preferences.putInt("mode", MODE);
  flag = 1;
}

void handleMode(AdafruitIO_Data *data) {
}

void handlecolour1(AdafruitIO_Data *data) {
  uint8_t r = data->toRed();
  uint8_t g = data->toGreen();
  uint8_t b = data->toBlue();
  set_custom_gradient_palette(0, r, g, b);
  customPal.loadDynamicGradientPalette(custom_gp);
  c1r = preferences.putUChar("c1r", r);
  c1g = preferences.putUChar("c1g", g);
  c1b = preferences.putUChar("c1b", b);
}
void handlecolour2(AdafruitIO_Data *data) {
  uint8_t r = data->toRed();
  uint8_t g = data->toGreen();
  uint8_t b = data->toBlue();
  set_custom_gradient_palette(1, r, g, b);
  customPal.loadDynamicGradientPalette(custom_gp);
  c2r = preferences.putUChar("c2r", r);
  c2g = preferences.putUChar("c2g", g);
  c2b = preferences.putUChar("c2b", b);
}
void handlecolour3(AdafruitIO_Data *data) {
  uint8_t r = data->toRed();
  uint8_t g = data->toGreen();
  uint8_t b = data->toBlue();
  set_custom_gradient_palette(2, r, g, b);
  customPal.loadDynamicGradientPalette(custom_gp);
  c3r = preferences.putUChar("c3r", r);
  c3g = preferences.putUChar("c3g", g);
  c3b = preferences.putUChar("c3b", b);
}
void handlecolour4(AdafruitIO_Data *data) {
  uint8_t r = data->toRed();
  uint8_t g = data->toGreen();
  uint8_t b = data->toBlue();
  set_custom_gradient_palette(3, r, g, b);
  customPal.loadDynamicGradientPalette(custom_gp);
  c4r = preferences.putUChar("c4r", r);
  c4g = preferences.putUChar("c4g", g);
  c4b = preferences.putUChar("c4b", b);
}

void customColourStart(){
  TRGBGradientPaletteEntryUnion* grad_entry = (TRGBGradientPaletteEntryUnion*) custom_gp;
  grad_entry[0].r = c1r;
  grad_entry[0].g = c1g;
  grad_entry[0].b = c1b;
  grad_entry[1].r = c2r;
  grad_entry[1].g = c2g;
  grad_entry[1].b = c2b; 
  grad_entry[2].r = c3r;
  grad_entry[2].g = c3g;
  grad_entry[2].b = c3b; 
  grad_entry[3].r = c4r;
  grad_entry[3].g = c4g;
  grad_entry[3].b = c4b;  
  customPal.loadDynamicGradientPalette(custom_gp);
}

void UpdateDataIO() {
  if (millis() > (lastUpdate + IO_LOOP_DELAY)) {
    io.run();
    Serial.println("IO run succeed");
    lastUpdate = millis();
  }
}

void updateData() {
  if (flag == 1 && lastSent + 4000 < millis() && MODE != prevMode)
  {
    prevMode = MODE;
    lastSent = millis();
    group->set("mode", modes[MODE]);
    group->save();
    flag = 0;
  }
}
