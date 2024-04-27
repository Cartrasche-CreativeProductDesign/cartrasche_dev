#ifndef CONFIG_H
#define CONFIG_H

///////////// INCLUDE CONFIG /////////////
#include <Arduino.h>
#include <ros.h>
#include <std_msgs/Int32.h>
#include <std_msgs/String.h>
#include <std_msgs/Empty.h>
#include <geometry_msgs/Twist.h>
#include <SoftwareSerial.h>
////////////////////////////////////////

///////////// ROBOT CONFIG /////////////
#define WHEEL_RAD     0.056 // m
#define PI            3.1415926535897932384626433832795
#define TWOPIRAD      0.352
#define WHEELBASE     0.3228
#define VEL_MAX       30 // m/s
#define ANG_MAX       30 // deg
#define EPSILON       0.000001
////////////////////////////////////////

////////////// BLDC MOTOR //////////////
// 50 ~ 3000 RPM 
// 0.03V per 1 analogOut 
// 29RPM per 1 analog Output
// Vol  : analog  RPM
// 3.0V : 153 -> 50 RPM  
// 4.9V : 250 -> 2855 RPM
// 5.0V : 255 -> 3000 RPM 
// linvel || Analog = (((linVel*300)/(TWOPIRAD)-50)/29)+153
#define    SPEED_IN1   5    // ORANGE  6
#define    SPEED_IN2   6    // ORANGE  8
#define         DIR1  10    //  BROWN  2
#define  START_STOP1  11    //   PINK  4
#define         DIR2  12    //  BROWN 16
#define  START_STOP2  13    //   PINK 17
////////////////////////////////////////

////////////// SCREW STEP //////////////
#define STEP_DIR   22  // CW+  2
#define STEP_STEP  24 // CLK+ 5
#define STEP_EN    26   // EN+  8
/////////////////////////////////////////

////////////// ROTATION STEP //////////////
#define STEP_DIR_TOP   28  // CW+  2
#define STEP_STEP_TOP  30 // CLK+ 5
#define STEP_EN_TOP    32   // EN+  8

#define STEP_DIR_BOT   34  // CW+  2
#define STEP_STEP_BOT  36 // CLK+ 5
#define STEP_EN_BOT    38   // EN+  8

#define MID2TOP          50
#define BOT2TOP          52
#define upcount           1
#define STEPS_PER_REV  1000 // 1/8 step mode shall be 
/////////////////////////////////////////

//////////// ARDUINO CONFIG /////////////
#define RELAY        23
#define LED_BUILTIN  13
#define LED_UNO      25
#define LED_DOS      27
#define LED_TRES     29
/////////////////////////////////////////

#endif
