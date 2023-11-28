#include <WiFiManager.h> // https://github.com/tzapu/WiFiManager
// select which pin will trigger the configuration portal when set to LOW
#define TRIGGER_PIN 1

int timeout = 60; // seconds to run for
bool wmTriggered = 0;
const char *apName = "Aini Display Lights";
void startWM() {
  startMemory();
  WiFi.mode(WIFI_STA); // explicitly set mode, esp defaults to STA+AP
  // put your setup code here, to run once:

  Serial.println("\n Starting");

  WiFiManager wm;

  //wm.resetSettings();
  bool res;
  res = wm.autoConnect(apName);
  if (!res) {
    Serial.println("Failed to connect");
    // ESP.restart();
  }
}

void checkWM() {
  if (wmTriggered) {
    wmTriggered = false;
    WiFiManager wm;
    //reset settings - for testing
    //wm.resetSettings();

    // set configportal timeout
    wm.setConfigPortalTimeout(timeout);

    if (!wm.startConfigPortal(apName)) {
      Serial.println("failed to connect and hit timeout");
      delay(3000);
      //reset and try again, or maybe put it to deep sleep
      ESP.restart();
      delay(5000);
    }
    Serial.println("connected...yeey :)");
  }
}
