#include <Preferences.h>
int BRIGHTNESS;                   // Brightness 0 - 255, but won't exceed current specified above
int buttonPushCounter;
int TWINKLE_SPEED;
int TWINKLE_DENSITY;
int SECONDS_PER_PALETTE;
int MODE;
const char *IO_USERNAME = "ainimoonlighta";
const char *IO_KEY = "aio_QXCB29GeVKybtwHlKVlWHkScP3Kd";
const char *FEED_GROUP_NAME = "moon";

uint8_t c1r;
uint8_t c2r;
uint8_t c3r;
uint8_t c4r;
uint8_t c1g;
uint8_t c2g;
uint8_t c3g;
uint8_t c4g;
uint8_t c1b;
uint8_t c2b;
uint8_t c3b;
uint8_t c4b;
Preferences preferences;

void startMemory() {
  preferences.begin("my-app", false);
  BRIGHTNESS = preferences.getInt("brightness", 255);
  MODE = preferences.getInt("mode", 10);
  TWINKLE_SPEED = preferences.getInt("twinklespeed", 5);
  TWINKLE_DENSITY = preferences.getInt("twinkledensity", 8);
  SECONDS_PER_PALETTE = preferences.getInt("palettetimer", 5);
  c1r = preferences.getUChar("c1r", 255);
  c2r = preferences.getUChar("c2r", 255);
  c3r = preferences.getUChar("c3r", 255);
  c4r = preferences.getUChar("c4r", 255);
  c1g = preferences.getUChar("c1g", 255);
  c2g = preferences.getUChar("c2g", 255);
  c3g = preferences.getUChar("c3g", 255);
  c4g = preferences.getUChar("c4g", 255);
  c1b = preferences.getUChar("c1b", 255);
  c2b = preferences.getUChar("c2b", 255);
  c3b = preferences.getUChar("c3b", 255);
  c4b = preferences.getUChar("c4b", 255);
  
  
}
