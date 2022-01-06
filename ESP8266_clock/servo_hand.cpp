#include <Servo.h>
#include "servo_hand.h"
#include "udp_sync_client.h"
#include "config.h"



Servo clockServo;
static uint32_t servo_timestamp = 0;

void SH_init(){
  pinMode(SERVO_PIN, OUTPUT);
  clockServo.attach(SERVO_PIN);
}

void SH_process(){
  if((millis() - servo_timestamp) > SYNC_TIMEOUT){
    servo_timestamp = millis();

    uint32_t seconds = UDP_getCurrentSeconds();
    int angle = map(seconds, 0, SECONDS_PER_12_H, 0, 180);
    clockServo.write(angle);
  }
}
