#include <Adafruit_NeoPixel.h>
#include "smart_led.h"
#include "config.h"
#include "udp_sync_client.h"


Adafruit_NeoPixel strip;
static uint32_t sync_timestamp = 0;

const static uint8_t SEGMENT[] = {
  //abcdefg 
  0b1111110,
  0b0110000,
  0b1101101,
  0b1111001,
  0b0110011,
  0b1011011,
  0b1011111,
  0b1110000,
  0b1111111,
  0b1111011
};

uint32_t daylight_color = 0;
uint32_t black_color = 0;

void setOff(){  
  for(uint16_t i = 0; i < NUM_OF_PIXELS; ++i){    
    strip.setPixelColor(i, black_color);    
  }
  
  strip.show();
}

void setNumber(int num){
  setOff();
  int i;
  uint8_t first = num / 10;
  uint8_t second = SEGMENT[num % 10];

  for(i = 0; i < 7; ++i){
    if((SEGMENT[first] >> i) & 1){
      strip.setPixelColor(i, daylight_color);
    }

    if((SEGMENT[second] >> i) & 1){
      strip.setPixelColor(i, daylight_color);
    }
  }  
}

void SL_init(){
  pinMode(LED_STRIP_PIN, OUTPUT);
  daylight_color = strip.Color(0, 0, 255);
  black_color = strip.Color(0, 0, 0);
  
  // Parameter 1 = number of pixels in strip
  // Parameter 2 = pin number (most are valid)
  // Parameter 3 = pixel type flags, add together as needed:
  //   NEO_KHZ800  800 KHz bitstream (most NeoPixel products w/WS2812 LEDs)
  //   NEO_KHZ400  400 KHz (classic 'v1' (not v2) FLORA pixels, WS2811 drivers)
  //   NEO_GRB     Pixels are wired for GRB bitstream (most NeoPixel products)
  //   NEO_RGB     Pixels are wired for RGB bitstream (v1 FLORA pixels, not v2)
  strip = Adafruit_NeoPixel(NUM_OF_PIXELS, LED_STRIP_PIN, NEO_GRB + NEO_KHZ800);
  strip.begin();
  strip.show(); // Initialize all pixels to 'off'
}

void SL_process(){
  if((millis() - sync_timestamp) > SYNC_TIMEOUT){
    sync_timestamp = millis();

    uint32_t seconds = UDP_getCurrentSeconds();
    /*  hours = seconds / 3600
     *  remaining_seconds =  MAX_SECONDS_PER_DAY % 3600
     *  minutes = remaining_seconds / 60 
     */
    int minutes = (seconds % 3600) / 60;
    setNumber(minutes);
  }
}
