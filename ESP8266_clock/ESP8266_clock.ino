#include <ESP8266WiFi.h>
#include <ESP8266WiFiMulti.h>
#include <Servo.h>
#include "udp_sync_client.h"
#include "smart_led.h"
#include "servo_hand.h"
#include "config.h"
#include "pendulum.h"

ESP8266WiFiMulti WiFiMulti;

void setup()
{
  Serial.begin(115200);
   
  WiFi.mode(WIFI_STA);
  WiFiMulti.addAP(SSID_1, PASS_1);
  WiFiMulti.addAP(SSID_2, PASS_2);
  
  Serial.print( "\n\nConnecting" );
  while ( WiFiMulti.run() != WL_CONNECTED ) {
    delay ( 500 );
    ESP.wdtFeed();
    Serial.print ( "." );
  }
  String IP =  WiFi.localIP().toString();
  String wifi_statusMessage = "\nConnected to: " + WiFi.SSID() + String(". IP address: ") + IP;   
  Serial.println(wifi_statusMessage);  

  UDPPING_init();
  SL_init();
  SH_init();
  PENDULUM_init();
}

void loop() {
  UDPPING_process();
  SH_process();
  SL_process();
  PENDULUM_process();
}
