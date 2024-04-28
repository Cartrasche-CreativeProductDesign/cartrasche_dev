#ifndef _LED_CONTROL_H
#define _LED_CONTROL_H

#include "config.h"
#ifdef __AVR__
 #include <avr/power.h> // Required for 16 MHz Adafruit Trinket
#endif

Adafruit_NeoPixel pixels = Adafruit_NeoPixel(NUMPIXELS, LED_PIN, NEO_GRBW + NEO_KHZ800);

void initializeLED(){
  pixels.begin();
  for(int i=0;i<NUMPIXELS;i++){
    pixels.setPixelColor(i,pixels.Color(200,200,200)); 
  }        
  pixels.show();
  delay(PIXEL_DELAY);
}

void show_red(int brightness){
  for(int i=0;i<NUMPIXELS;i++){
    pixels.setPixelColor(i,pixels.Color(brightness,0,0)); 
  }
  pixels.show(); //update hardware with RGB color set
  delay(PIXEL_DELAY);
  return;
}

void show_yellow(int brightness){
  for(int i=0;i<NUMPIXELS;i++){
    pixels.setPixelColor(i,pixels.Color(brightness,brightness,0)); 
  }
  pixels.show(); //update hardware with RGB color set
  delay(PIXEL_DELAY);
  return;
}

void show_green(int brightness){
  for(int i=0;i<NUMPIXELS;i++){
    pixels.setPixelColor(i,pixels.Color(0,brightness,0)); 
  }
  pixels.show(); //update hardware with RGB color set
  delay(PIXEL_DELAY);
  return;
}

void show_blue(int brightness){
  for(int i=0;i<NUMPIXELS;i++){
    pixels.setPixelColor(i,pixels.Color(0,0,brightness)); 
  }
  pixels.show(); //update hardware with RGB color set
  delay(PIXEL_DELAY);
  return;
}

void show_violet(int brightness){
  for(int i=0;i<NUMPIXELS;i++){
    pixels.setPixelColor(i,pixels.Color(brightness,0,brightness)); 
  }
  pixels.show(); //update hardware with RGB color set
  delay(PIXEL_DELAY);
  return;
}

void show_white(int brightness){
  for(int i=0;i<NUMPIXELS;i++){
    pixels.setPixelColor(i,pixels.Color(brightness,brightness,brightness)); 
  }
  pixels.show(); //update hardware with RGB color set
  delay(PIXEL_DELAY);
  return;
}

void turn_off_led(){
  for(int i=0;i<NUMPIXELS;i++){
      pixels.setPixelColor(i,pixels.Color(0,0,0)); 
    }
  pixels.show();
  delay(PIXEL_DELAY);
  return;
}

#endif
