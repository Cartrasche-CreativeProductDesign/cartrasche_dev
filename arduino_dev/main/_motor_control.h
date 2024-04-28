#ifndef _MOTOR_CONTROL_H
#define _MOTOR_CONTROL_H

#include "config.h"
#include "_led_control.h"

int current_fb_speed;
int current_lr_speed;

void initialize_bldc()
{
  pinMode(DIR1, OUTPUT);
  pinMode(START_STOP1, OUTPUT);
  pinMode(DIR2, OUTPUT);
  pinMode(START_STOP2, OUTPUT);
    
  pinMode(SPEED_IN1, OUTPUT);
  pinMode(SPEED_IN2, OUTPUT);

  analogWrite(SPEED_IN1, 125); //stop
  analogWrite(SPEED_IN2, 125); //stop
  digitalWrite(DIR1, LOW);
  digitalWrite(DIR2, HIGH);
  digitalWrite(START_STOP1, HIGH); //stop
  digitalWrite(START_STOP2, HIGH); //stop
}

// 0 ~ 100 : fwd
// 100 ~ 150 : stop
// 150 ~250 : bwd 
void fb_control(int dir, int speed)
{
  if(speed>250){
    speed = 250;
  }
  current_fb_speed = speed;

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
  analogWrite(SPEED_IN1, speed);

}

// 0 ~ 102 : left
// 103 ~ 152 : stop
// 153 ~250 : right 
void lr_control(int speed)
{
  // Turn motor on
  if(speed>250){
    speed = 250;
  }
  current_lr_speed = speed;

  digitalWrite(DIR1, LOW);
  digitalWrite(DIR2, HIGH);

  digitalWrite(START_STOP1, LOW);
  digitalWrite(START_STOP2, LOW);

  analogWrite(SPEED_IN2, speed);
}

void turn_off_motor()
{ 
  int temp = current_fb_speed;
  if(current_fb_speed>=current_lr_speed){
    temp = current_lr_speed;
  }
  while((current_fb_speed <= 150)&&(current_lr_speed <= 150)){
    if(current_fb_speed > 150){
      current_fb_speed -= 5;
      analogWrite(SPEED_IN1, current_fb_speed);
      }
    if(current_lr_speed > 150){
      current_fb_speed -= 5;
      analogWrite(SPEED_IN1, current_lr_speed);
      }
    delay(10);
  }
  
  digitalWrite(START_STOP1, HIGH);
  digitalWrite(START_STOP2, HIGH);
  turn_off_led();
}

int calculateSPeed(float linVel){
  float calc = ((linVel*300)/(TWOPIRAD)-50)/29+153;
  int AnalogOut = int(trunc(calc));
  return AnalogOut;
}

int calculateAngle(float angVel){
  if(angVel>0){
    // 계산 다시
    float calc = ((300*angVel*WHEELBASE)/(2*TWOPIRAD) - 50)/29 + 153;
    int AnalogOut = int(trunc(calc));
    return AnalogOut;
  }
  else{
    float calc = 102 - ((300*abs(angVel)*WHEELBASE)/(2*TWOPIRAD) - 50)/29;
    int AnalogOut = int(trunc(calc));
    return AnalogOut;
  }
}

#endif
