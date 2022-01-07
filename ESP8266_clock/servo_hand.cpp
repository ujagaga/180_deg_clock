#include <Servo.h>
#include "servo_hand.h"
#include "udp_sync_client.h"
#include "config.h"

Servo hourServo;
Servo minuteServo;
static uint32_t servo_timestamp = 0;

void SERVO_init(){
  pinMode(HOUR_SERVO_PIN, OUTPUT);
  pinMode(MINUTE_SERVO_PIN, OUTPUT);
  hourServo.attach(HOUR_SERVO_PIN);
  minuteServo.attach(MINUTE_SERVO_PIN);
}

void SERVO_process(){
  if((millis() - servo_timestamp) > SYNC_TIMEOUT){
    servo_timestamp = millis();

    uint32_t seconds = UDPSYNC_getCurrentSeconds();

    uint32_t secInLast12h = seconds % SECONDS_PER_12_H;    
    int hourAngle = map(secInLast12h, 0, SECONDS_PER_12_H, 0, 180);
    hourServo.write(hourAngle);

    uint32_t secondsInLastHour = seconds % SECONDS_PER_HOUR;
    uint32_t minutes = secondsInLastHour / SECONDS_PER_MINUTE;
    int minuteAngle = map(minutes, 0, MINUTES_PER_HOUR, 0, 180);
    minuteServo.write(minuteAngle);
  }
}
