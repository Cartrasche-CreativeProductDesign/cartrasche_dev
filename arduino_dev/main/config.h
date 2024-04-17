#ifndef CONFIG_H
#define CONFIG_H

////////////// BLDC MOTOR //////////////
#define    SPEED_IN1   5    // ORANGE  6
#define    SPEED_IN2   6    // ORANGE  8
#define         DIR1  10    //  BROWN  2
#define  START_STOP1  11    //   PINK  4
#define         DIR2  12    //  BROWN 16
#define  START_STOP2  13    //   PINK 17
////////////////////////////////////////

////////////// SCREW STEP //////////////
#define STEP_DIR 22  // CW+  2
#define STEP_STEP 24 // CLK+ 5
#define STEP_EN 26   // EN+  8
/////////////////////////////////////////

////////////// ROTATION STEP //////////////
#define STEP_DIR_TOP 28  // CW+  2
#define STEP_STEP_TOP 30 // CLK+ 5
#define STEP_EN_TOP 32   // EN+  8

#define STEP_DIR_BOT 34  // CW+  2
#define STEP_STEP_BOT 36 // CLK+ 5
#define STEP_EN_BOT 38   // EN+  8
/////////////////////////////////////////

#define MID2TOP 50
#define BOT2TOP 52
const int upcount = 10;

#endif