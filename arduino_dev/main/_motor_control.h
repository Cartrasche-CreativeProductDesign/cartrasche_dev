#ifndef _MOTOR_CONTROL_H
#define _MOTOR_CONTROL_H

#include "config.h"

int current_speed;

void initialize_bldc()
{
  pinMode(DIR1, OUTPUT);
  pinMode(START_STOP1, OUTPUT);
  pinMode(DIR2, OUTPUT);
  pinMode(START_STOP2, OUTPUT);
    
  pinMode(SPEED_IN1, OUTPUT);
  pinMode(SPEED_IN2, OUTPUT);

  analogWrite(SPEED_IN1, 125);
  analogWrite(SPEED_IN2, 125);
  digitalWrite(DIR1, LOW);
  digitalWrite(DIR2, HIGH);
  digitalWrite(START_STOP1, HIGH); //stop
  digitalWrite(START_STOP2, HIGH); //stop

  Serial.println("BLDC Initialization Done");

}


void fb_control(int dir, int speed)
{
  // Turn motor on
  if(speed>255){
    speed = 255;
  }
  current_speed = speed;

  // 0 : fwd, 1 : bwd
  if(dir == 0){
    digitalWrite(DIR1, LOW);
    digitalWrite(DIR2, HIGH);
  }
  else if(dir == 1){
    digitalWrite(DIR1, HIGH);
    digitalWrite(DIR2, LOW);
  }
  digitalWrite(START_STOP1, LOW);
  digitalWrite(START_STOP2, LOW);

  // Slowly increase motor speed
  for (int i = 0; i <= speed; i += 5) {
    Serial.println(i);
    analogWrite(SPEED_IN1, i);
    delay(250);
    if(i==85)
    {
      delay(5000);
    }
  }
}


void lr_control(int dir, int speed)
{
  // Turn motor on
  if(speed>255){
    speed = 255;
  }
  current_speed = speed;

  // 0 : fwd, 1 : bwd
  if(dir == 0){
    digitalWrite(DIR1, LOW);
    digitalWrite(DIR2, HIGH);
  }
  else if(dir == 1){
    digitalWrite(DIR1, HIGH);
    digitalWrite(DIR2, LOW);
  }
  digitalWrite(START_STOP1, LOW);
  digitalWrite(START_STOP2, LOW);

  Serial.println("SPD2");
  analogWrite(SPEED_IN1, 200);
  delay(5000);
  Serial.println("start");
  for (int i = 0; i <= 250; i += 5) {
    Serial.println(i);
    analogWrite(SPEED_IN2, i);
    delay(1000);
  }
}


void turn_off_motor()
{
  // Slowly decrease motor speed
  for (int i = current_speed; i >= 150; i -= 5) {
    analogWrite(SPEED_IN1, i);
    delay(250);
  }
  // Turn motor off
  digitalWrite(START_STOP1, HIGH);
  digitalWrite(START_STOP2, HIGH);
}

#endif
