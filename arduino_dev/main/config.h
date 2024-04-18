#ifndef CONFIG_H
#define CONFIG_H

///////////// ROBOT CONFIG /////////////
#define WHEEL_RAD     0.1 // m
#define PI            3.1415926535897932384626433832795
#define VEL_MAX       30 // m/s
#define ANG_MAX       30 // deg
////////////////////////////////////////

////////////// BLDC MOTOR //////////////
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

#define MID2TOP     50
#define BOT2TOP     52
#define upcount     10
/////////////////////////////////////////

//////////// ARDUINO CONFIG /////////////
#define RELAY        23
#define LED_BUILTIN  13
/////////////////////////////////////////

#endif