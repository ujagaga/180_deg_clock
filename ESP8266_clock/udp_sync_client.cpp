#include <WiFiUdp.h>
#include <ESP8266WiFi.h>
#include "udp_sync_client.h"
#include "config.h"
#include "ota.h"

static WiFiUDP Udp;                             /* UDP object used for receiving the ping message. */
static char incomingPacket[10];                 /* buffer for incoming packets */
uint32_t sync_timestamp = 0;                    /* Timestamp of the last sync. */
uint32_t sync_result = 0;

void UDPSYNC_init(){
  Udp.begin(UDP_PORT);
}

void UDPSYNC_process(){
  int packetSize = Udp.parsePacket();
  
  if((packetSize > 0) && (packetSize < 10)){
    // receive incoming UDP packets
    int len = Udp.read(incomingPacket, 10);
    
    incomingPacket[len] = 0;

    String msg = String(incomingPacket);  
    Serial.println(msg);
    if(msg == "ota"){
      OTA_init();
    }else{    
    
      uint32_t rx = msg.toInt();
      
      if((rx >= 0) && (rx < MAX_SECONDS_PER_DAY)){
        sync_result = rx;
        sync_timestamp = millis();
      }    
    }
  }
}

int UDPSYNC_getCurrentSeconds(){ 

  uint32_t passedSinceSync = millis() - sync_timestamp;
  uint32_t total = (passedSinceSync / 1000) + sync_result;
  uint32_t seconds = total % SECONDS_PER_12_H;
  
  return (int)seconds;
}
