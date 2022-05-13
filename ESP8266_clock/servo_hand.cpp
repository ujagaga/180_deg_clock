#include <Servo.h>
#include "servo_hand.h"
#include "udp_sync_client.h"
#include "config.h"

#define MOVE_TIMEOUT    (100)
#define H_SRV_MIN       (490)
#define H_SRV_MAX       (2460)


Servo hourServo;
Servo minuteServo;
static uint32_t servo_timestamp = 0;
static uint32_t move_timestamp = 0;
static int m_angle = 180;
static int h_angle = 0;
static int targetHourAngle = 0;
static int targetMinuteAngle = 0;

#ifdef DETACH_HOUR_SERVO
static bool hourServoAttached = false;
#endif

void SERVO_init(){
  pinMode(HOUR_SERVO_PIN, OUTPUT);
  pinMode(MINUTE_SERVO_PIN, OUTPUT);
  hourServo.attach(HOUR_SERVO_PIN, H_SRV_MIN, H_SRV_MAX);
  minuteServo.attach(MINUTE_SERVO_PIN, 500, 2500);
  minuteServo.write(m_angle);  

#ifdef DETACH_HOUR_SERVO
  hourServoAttached = true;
#endif
}

int calc_m_angle(int seconds){
  if(seconds >= SECONDS_PER_HOUR){
    seconds = SECONDS_PER_HOUR - 1;
  }else if(seconds < 0){
    seconds = 0;
  }

  int ratio = SECONDS_PER_HOUR / 180;
  int result = seconds / ratio;

  return (180 - result);
}

int calc_h_angle(int seconds){
  if(seconds >= SECONDS_PER_12_H){
    seconds = SECONDS_PER_12_H - 1;
  }else if(seconds < 0){
    seconds = 0;
  }

  int ratio = SECONDS_PER_12_H / 180;
  int result = seconds / ratio;

  float current = (float)result;
  if(result > 135){
    result = (int)(current * 1.01);
  }else if(result > 90){
    result = (int)(current * 1.01);
  }else if(result > 45){
    result = (int)(current * 0.98);
  }

  return result;
}

#ifdef TEST_SWEEP
  int angle = 1;
  int increment = 1;
#endif

void SERVO_process(){
#ifdef TEST_SWEEP
  if((millis() - servo_timestamp) > MOVE_TIMEOUT){
    servo_timestamp = millis();
    
    if((angle >= 180) || (angle <= 0)){      
      increment = -increment;
    }

    angle += increment;    
    hourServo.write(angle);    
  }
#else
  
  if((millis() - servo_timestamp) > SYNC_TIMEOUT){
    servo_timestamp = millis();

    int seconds = UDPSYNC_getCurrentSeconds();
    targetHourAngle = calc_h_angle(seconds);    

    int secondsInLastHour = seconds % SECONDS_PER_HOUR;
    targetMinuteAngle = calc_m_angle(secondsInLastHour);        

  }else if((millis() - move_timestamp) > MOVE_TIMEOUT){
    if(targetHourAngle > h_angle){
      h_angle++;
      
#ifdef DETACH_HOUR_SERVO
      if(!hourServoAttached){
        hourServo.attach(HOUR_SERVO_PIN, H_SRV_MIN, H_SRV_MAX);
        hourServoAttached = true;
      }
#endif      
    }else if(targetHourAngle < h_angle){
      h_angle--;
      
#ifdef DETACH_HOUR_SERVO
      if(!hourServoAttached){
        hourServo.attach(HOUR_SERVO_PIN, H_SRV_MIN, H_SRV_MAX);
        hourServoAttached = true;
      }
#endif      
    }else{
#ifdef DETACH_HOUR_SERVO
      if(hourServoAttached){
        hourServo.detach();
        hourServoAttached = false;
      }      
#endif 
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

#endif // TEST_SWEEP
}
