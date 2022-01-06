#include <Arduino.h>
#include "pendulum.h"
#include "config.h"

#define TRIGGER_TIME    (100)
#define SENSE_TIMEOUT   (3000)

static uint32_t sense_timestamp = 0;
static uint32_t trigger_timestamp = 0;

void PENDULUM_init(){
  pinMode(PENDULUM_TRIGGER_PIN, OUTPUT);
  pinMode(PENDULUM_SENSE_PIN, INPUT);
}

void PENDULUM_process(){
  uint32_t timeSinceSense = millis() - sense_timestamp;
  bool sense = (digitalRead(PENDULUM_SENSE_PIN) == HIGH);

  if(sense){
    digitalWrite(PENDULUM_TRIGGER_PIN, HIGH);
    sense_timestamp = millis(); 
    
    if(trigger_timestamp == 0){
      trigger_timestamp = millis();
    }
  }else{
    if(timeSinceSense > SENSE_TIMEOUT){
      // No sense pin change detected for a long time. Try to trigger the pendulum to start swinging.
      digitalWrite(PENDULUM_TRIGGER_PIN, HIGH);
      sense_timestamp = millis(); 
    }else if(timeSinceSense > TRIGGER_TIME){
      digitalWrite(PENDULUM_TRIGGER_PIN, LOW);
      trigger_timestamp = 0;
    }else{
      // Trigger time not yet passed, so keep it up.
      digitalWrite(PENDULUM_TRIGGER_PIN, HIGH);
    }
  }

}
