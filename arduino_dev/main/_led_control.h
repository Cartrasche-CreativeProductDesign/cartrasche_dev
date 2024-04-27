#ifndef _LED_CONTROL_H
#define _LED_CONTROL_H

#include "config.h"

Adafruit_NeoPixel ring(LED_CNT, LED_PIN, NEO_RGBW + NEO_KHZ800);

void initializeLED(){
  ring.begin();           
  ring.show();            
  ring.setBrightness(250); 
  for(int i = 0; i < ring.numPixels(); i++){
    ring.setPixelColor(i, random(255), random(255), random(255), 0);
    ring.show();
    delay(50);
  }
}

#endif
