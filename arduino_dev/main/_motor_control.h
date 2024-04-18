#ifndef _MOTOR_CONTROL_H
#define _MOTOR_CONTROL_H

#include "config.h"

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
  for (int i = 150; i <= speed; i += 5) {
    analogWrite(SPEED_IN1, i);
    delay(250);
  }
}

// 0 ~ 100 : left
// 100 ~ 150 : stop
// 150 ~250 : right 
void lr_control(int dir, int speed)
{
  // Turn motor on
  if(speed>250){
    speed = 250;
  }
  current_lr_speed = speed;

  // 0 : left, 1 : right
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

  for (int i = 150; i <= speed; i += 5) {
    analogWrite(SPEED_IN2, i);
    delay(250);
  }
}

void turn_off_motor()
{
  // Slowly decrease motor speed
  if(current_fb_speed > 150){
    for (int i = current_fb_speed; i >= 150; i -= 5) {
      analogWrite(SPEED_IN1, i);
      delay(250);
      }
    }
  if(current_lr_speed > 150){
    for (int i = current_lr_speed; i >= 150; i -= 5) {
      analogWrite(SPEED_IN2, i);
      delay(250);
      }
    }
  // Turn motor off
  digitalWrite(START_STOP1, HIGH);
  digitalWrite(START_STOP2, HIGH);
}

// 직진신호, 1초 대기, 회전신호 중첩
void test_case1()
{
  fb_control(0,190);
  delay(1000);
  digitalWrite(LED_BUITIN, HIGH);
  lr_control(0,170); // left : 190 - 30 , right : 190 + 30
  delay(3000);
  turn_off_motor();
}

// 회전신호, 1초 대기, 직진신호 중첩
void test_case2()
{
  fb_control(0,190);
  // delay(1000);
  digitalWrite(LED_BUITIN, HIGH);
  lr_control(0,170); // left : 190 - 30 , right : 190 + 30
  delay(3000);
  turn_off_motor();
}

// 직진신호, 무대기, 회전신호 중첩
void test_case1()
{
  fb_control(0,190);
  digitalWrite(LED_BUITIN, HIGH);
  lr_control(0,170); // left : 190 - 30 , right : 190 + 30
  delay(3000);
  turn_off_motor();
}

// 회전신호, 무대기, 직진신호 중첩
void test_case4()
{
  fb_control(0,190);
  digitalWrite(LED_BUITIN, HIGH);
  lr_control(0,170); // left : 190 - 30 , right : 190 + 30
  delay(3000);
  turn_off_motor();
}
#endif
