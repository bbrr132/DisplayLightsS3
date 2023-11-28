#include "memory.h"
#include "lightPalettes.h"
#include "adafruitjp.h"
#include "wifi_manager_8266.h"
#include "JigglyPuff.h"

bool touchReleased = true;  // Initialize to true assuming touch is released initially
bool stateTouch = true;

unsigned long previousHoldTimer = 0;
void checkTouchState();
void setup() {
  Serial.begin(115200);
  startMemory();
  startWM();
  AdafruitIOStart();
  startLED();
  customColourStart();
}

void loop()
{
  //Serial.println(io.status());
  if(io.status() == 2){
    AdafruitIOStart();
  }
  //Serial.println(io.status());
  //Serial.println(io.statusText());
  if (io.status() == 21) {
    //Serial.println(io.status());
    UpdateDataIO();
    updateData();
  }
  drawLED();
  checkTouchState();
  checkWM();
  if (io.status() != 21) {
    updateIOCredentials("ainimoonlight", "aio_QXCB29GeVKybtwHlKVlWHkScP3Kd", "", "");
  }
  Serial.println(io.statusText());
  Serial.println(io.status());
}

void checkTouchState() {
  if (touchReleased && touchRead(1) > 40000) {
    Serial.println("Touched");
    previousHoldTimer = millis();
    Serial.println(previousHoldTimer);
    touchReleased = false;
    if (!stateTouch) {
      Serial.println("Turning On");
      BRIGHTNESS = preferences.getInt("brightness", 255);
      stateTouch = true;  // Update state
    } else {
      Serial.println("Turning Off");
      BRIGHTNESS = 0;
      stateTouch = false; // Update state
    }
    FastLED.show();  // Update LED
  }
  if (!touchReleased && touchRead(1) > 40000 && previousHoldTimer + 5000 < millis()) {
    Serial.println(millis());
    Serial.println("WM Triggered");
    wmTriggered = true;
  }
  if (!touchReleased && touchRead(T1) < 40000) {
    touchReleased = true;
  }
}
