#include <ESP8266WiFi.h>
#include <ESP8266WiFiMulti.h>
#include <Servo.h>
#include "udp_sync_client.h"
#include "servo_hand.h"
#include "config.h"
#include "pendulum.h"
#include "ota.h"

ESP8266WiFiMulti WiFiMulti;

void setup()
{
  Serial.begin(115200);
  pinMode(LED_PIN, OUTPUT);
  digitalWrite(LED_PIN, HIGH);
   
  WiFi.mode(WIFI_STA);
  WiFiMulti.addAP(SSID_1, PASS_1);
  WiFiMulti.addAP(SSID_2, PASS_2);

  bool ledTgl = false;
  
  Serial.print( "\n\nConnecting" );
  while ( WiFiMulti.run() != WL_CONNECTED ) {
    delay ( 500 );
    ESP.wdtFeed();
    Serial.print ( "." );
    ledTgl = !ledTgl;
    if(ledTgl){
      digitalWrite(LED_PIN, HIGH);
    }else{
      digitalWrite(LED_PIN, LOW);
    }
  }
  String IP =  WiFi.localIP().toString();
  String wifi_statusMessage = "\nConnected to: " + WiFi.SSID() + String(". IP address: ") + IP;   
  Serial.println(wifi_statusMessage);  
  digitalWrite(LED_PIN, HIGH);

  UDPSYNC_init();
  SERVO_init();
  PENDULUM_init();
}

void loop() {  
  if(OTA_updateInProgress()){
    OTA_process();
  }else{
    UDPSYNC_process();
    PENDULUM_process();
    SERVO_process();
    PENDULUM_process();
  }
}
