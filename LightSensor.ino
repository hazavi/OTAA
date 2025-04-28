#include <TheThingsNetwork.h>

// Set your AppEUI and AppKey
const char *appEui = "0004A30B001C5968";
const char *appKey = "f6d713263ef80c76fbe39bb34438e8d4";

#define loraSerial Serial1
#define debugSerial Serial

// Replace REPLACE_ME with TTN_FP_EU868 or TTN_FP_US915
#define freqPlan TTN_FP_EU868

TheThingsNetwork ttn(loraSerial, debugSerial, freqPlan);

void setup()
{
  loraSerial.begin(57600);
  debugSerial.begin(9600);

  // Wait a maximum of 10s for Serial Monitor
  while (!debugSerial && millis() < 10000)
    ;

  pinMode(LED_BUILTIN, OUTPUT);

  debugSerial.println("-- STATUS");
  ttn.showStatus();

  debugSerial.println("-- JOIN");
  ttn.join(appEui, appKey);

  ttn.showStatus();
  debugSerial.println("Setup for The Things Network complete");
}

void loop()
{
  digitalWrite(LED_BUILTIN, HIGH);
  delay(500);
  ttn.sendBytes("1", sizeof("1"));
  digitalWrite(LED_BUILTIN, LOW);
  delay(1000);
  ttn.sendBytes("0", sizeof("0"));
}
