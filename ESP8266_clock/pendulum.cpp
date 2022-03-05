#include <Arduino.h>
#include "pendulum.h"
#include "config.h"

#define DURATION      (100)
#define TRIGGER_TIME  (100)
#define MIN_PERIOD    (500)

volatile uint32_t sense_timestamp = 0;
volatile bool sense_flag = false;
bool magnet_active_flag = false;

ICACHE_RAM_ATTR void sense(){ 
  if(!sense_flag){
    // Magnet just detected
    sense_timestamp = millis();  
    sense_flag = true; 
  } 
}

void PENDULUM_init(){
  pinMode(PENDULUM_TRIGGER_PIN, OUTPUT);
  pinMode(PENDULUM_SENSE_PIN, INPUT_PULLUP);
  digitalWrite(PENDULUM_TRIGGER_PIN, LOW);
  digitalWrite(LED_PIN, HIGH);
  magnet_active_flag = false;
  attachInterrupt(digitalPinToInterrupt(PENDULUM_SENSE_PIN), sense, FALLING);
}

void PENDULUM_process(){ 
  if(sense_flag){ 
    uint32_t passed = millis() - sense_timestamp;     
    
    if(passed < TRIGGER_TIME){
      // Wait for the right time to trigger the magnet     
      magnet_active_flag = false;   
    }else if(passed < (TRIGGER_TIME + DURATION)){
      // Keep repelling the magnet
      magnet_active_flag = true;
    }else if(passed < MIN_PERIOD){
      magnet_active_flag = false;      
    }else{
      magnet_active_flag = false;
      sense_flag = false;
    }
  }else{
    magnet_active_flag = false;
  }

  if(magnet_active_flag){
    digitalWrite(PENDULUM_TRIGGER_PIN, HIGH);
    digitalWrite(LED_PIN, LOW);    
  }else{
    digitalWrite(PENDULUM_TRIGGER_PIN, LOW);
    digitalWrite(LED_PIN, HIGH);
  } 

}
