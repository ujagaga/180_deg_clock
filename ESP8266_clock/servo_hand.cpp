#include <Servo.h>
#include "servo_hand.h"
#include "udp_sync_client.h"
#include "config.h"

#define MOVE_TIMEOUT    (15)

Servo hourServo;
Servo minuteServo;
static uint32_t servo_timestamp = 0;
static uint32_t move_timestamp = 0;
static int m_angle = 0;
static int h_angle = 0;
static int targetHourAngle = 0;
static int targetMinuteAngle = 0;

void SERVO_init(){
  pinMode(HOUR_SERVO_PIN, OUTPUT);
  pinMode(MINUTE_SERVO_PIN, OUTPUT);
  hourServo.attach(HOUR_SERVO_PIN);
  minuteServo.attach(MINUTE_SERVO_PIN);
}

void SERVO_process(){
  if((millis() - servo_timestamp) > SYNC_TIMEOUT){
    servo_timestamp = millis();

    int seconds = UDPSYNC_getCurrentSeconds();
    targetHourAngle = map(seconds, 0, SECONDS_PER_12_H, 0, 180);    

    int secondsInLastHour = seconds % SECONDS_PER_HOUR;
    targetMinuteAngle = map(secondsInLastHour, 0, SECONDS_PER_HOUR, 0, 180);        

#ifndef KEEP_TIME
    Serial.print("S in 12h :");
    Serial.print(seconds);
    Serial.print(", H Angle:");
    Serial.println(targetHourAngle);
    
    Serial.print("S in h:");
    Serial.print(secondsInLastHour);
    Serial.print(", M Angle:");
    Serial.println(targetMinuteAngle);
    Serial.println("");
#endif 
  }else if((millis() - move_timestamp) > MOVE_TIMEOUT){
    if(targetHourAngle > h_angle){
      h_angle++;
    }else if(targetHourAngle < h_angle){
      h_angle--;
    }

    if(targetMinuteAngle > m_angle){
      m_angle++;
    }else if(targetMinuteAngle < m_angle){
      m_angle--;
    }

    hourServo.write(h_angle);
    minuteServo.write(m_angle);
      
    move_timestamp = millis();
  }
}
