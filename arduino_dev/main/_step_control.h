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

// button state
int M2T_bs = 0;
int B2T_bs = 0;

void initialize_steppers(){
  pinMode(STEP_DIR, OUTPUT);
  pinMode(STEP_STEP, OUTPUT);
  pinMode(STEP_EN, OUTPUT);
  digitalWrite(STEP_EN, LOW);
  pinMode(STEP_DIR_TOP, OUTPUT);
  pinMode(STEP_STEP_TOP, OUTPUT);
  pinMode(STEP_EN_TOP, OUTPUT);
  digitalWrite(STEP_EN_TOP, LOW);
  pinMode(STEP_DIR_BOT, OUTPUT);
  pinMode(STEP_STEP_BOT, OUTPUT);
  pinMode(STEP_EN_BOT, OUTPUT);
  digitalWrite(STEP_EN_BOT, LOW);
}

// push up the link
void spinUp(){
    digitalWrite(STEP_DIR, LOW);
    for(int i  = 0; i < upcount*stepsPerRevolution; i++){
      digitalWrite(STEP_STEP, HIGH);
      delayMicroseconds(stepDelay);
      digitalWrite(STEP_STEP, LOW);
      delayMicroseconds(stepDelay);
    }
}

// let down the link
void spinDown(){
    digitalWrite(STEP_DIR, HIGH);
    for(int i  = 0; i < upcount*stepsPerRevolution; i++){
      digitalWrite(STEP_STEP, HIGH);
      delayMicroseconds(stepDelay);
      digitalWrite(STEP_STEP, LOW);
      delayMicroseconds(stepDelay);
    }
}

// rotate top stepper once
void rotateTop(){
    digitalWrite(STEP_DIR_TOP, HIGH); // direction check later
    for(int i  = 0; i < stepsPerRevolution; i++){
      digitalWrite(STEP_STEP_TOP, HIGH);
      delayMicroseconds(stepDelay);
      digitalWrite(STEP_STEP_TOP, LOW);
      delayMicroseconds(stepDelay);
    }
}

// rotate bottom stepper once
void rotateBot(){
    digitalWrite(STEP_DIR_BOT, HIGH);
    for(int i  = 0; i < stepsPerRevolution; i++){
      digitalWrite(STEP_STEP_BOT, HIGH);
      delayMicroseconds(stepDelay);
      digitalWrite(STEP_STEP_BOT, LOW);
      delayMicroseconds(stepDelay);
    }
}

void mid2top(){
  spinUp();
  delay(500);
  rotateTop();
  delay(500);
  spinDown();
}

void bot2top(){
  rotateBot();
  delay(500);
  mid2top();
}


void STEP_TEST(){
  if (checkAngle == 0) {a = +1; }
  if (checkAngle == 360) {a = -1; }

  angle = angle + a;
  a = angle;
  step = map(a, 0, 360, 0, stepsPerRevolution);

    digitalWrite(STEP_DIR, LOW);
    for(int i  = 0; i < 5*stepsPerRevolution; i++){
      digitalWrite(STEP_STEP, HIGH);
      delayMicroseconds(stepDelay);
      digitalWrite(STEP_STEP, LOW);
      delayMicroseconds(stepDelay);
    }

    digitalWrite(STEP_DIR, HIGH);
    for(int i  = 0; i < 5*stepsPerRevolution; i++){
      digitalWrite(STEP_STEP, HIGH);
      delayMicroseconds(stepDelay);
      digitalWrite(STEP_STEP, LOW);
      delayMicroseconds(stepDelay);
    }
}

#endif
