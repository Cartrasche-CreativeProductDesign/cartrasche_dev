#ifndef _STEP_CONTROL_H
#define _STEP_CONTROL_H

#include "config.h"
// #define STEP_DIR 22  // CW+  2
// #define STEP_STEP 24 // CLK+ 5
// #define STEP_EN 26   // EN+  8

const int stepsPerRevolution = 1600;

int angle = 0;
int step = 0;
int stepDelay = 500;
int checkAngle = 0;
int a = 0;

void spinUp(){
    digitalWrite(STEP_DIR, LOW);
    for(int i  = 0; i < 5*stepsPerRevolution; i++){
      Serial.println(i);
      digitalWrite(STEP_STEP, HIGH);
      delayMicroseconds(stepDelay);
      digitalWrite(STEP_STEP, LOW);
      delayMicroseconds(stepDelay);
    }

}

void spinDown(){
    digitalWrite(STEP_DIR, HIGH);
    for(int i  = 0; i < 5*stepsPerRevolution; i++){
      Serial.println(i);
      digitalWrite(STEP_STEP, HIGH);
      delayMicroseconds(stepDelay);
      digitalWrite(STEP_STEP, LOW);
      delayMicroseconds(stepDelay);
    }
}

void STEP_TEST(){
  if (checkAngle == 0) {a = +1; }
  if (checkAngle == 360) {a = -1; }

  angle = angle + a;
  a = angle;
  step = map(a, 0, 360, 0, stepsPerRevolution);

    digitalWrite(STEP_DIR, LOW);
    for(int i  = 0; i < 5*stepsPerRevolution; i++){
      Serial.println(i);
      digitalWrite(STEP_STEP, HIGH);
      delayMicroseconds(stepDelay);
      digitalWrite(STEP_STEP, LOW);
      delayMicroseconds(stepDelay);
    }

    digitalWrite(STEP_DIR, HIGH);
    for(int i  = 0; i < 5*stepsPerRevolution; i++){
      Serial.println(i);
      digitalWrite(STEP_STEP, HIGH);
      delayMicroseconds(stepDelay);
      digitalWrite(STEP_STEP, LOW);
      delayMicroseconds(stepDelay);
    }
}

#endif