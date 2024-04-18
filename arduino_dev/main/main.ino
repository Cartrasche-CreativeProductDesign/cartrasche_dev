#include <SoftwareSerial.h>
#include <ros.h>
#include <std_msgs/UInt8.h>
#include <std_msgs/String.h>
#include <std_msgs/Empty.h>
#include <geometry_msgs/Twist.h>

#include "config.h"
#include "_step_control.h"
// #include "_motor_control.h"
#include "_ros_control.h"

// SUbscriber Declaration
ros::Subscriber<geometry_msgs::Twist> subCmdVel("cmd_vel", &cmdvelCallback );
// Publisher Declaration
ros::Publisher rosduino("rosduino", &cmd_vel);
ros::Publisher testcon("testcon", &mstr_msg)

void setupMotors()
{
  // BLDC
  initialize_bldc();
  // STEPPER
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

void setupPheris()
{
  pinMode(MID2TOP, INPUT);
  pinMode(BOT2TOP, INPUT);
}

void setup()
{
  // Serial.begin(57600); 
  setupMotors();  
  setupPheris();
  // ROSSERIAL with Jetson
  n.initNode();
  n.advertise(testcon); // to be removed
  n.advertise(rosduino);
  n.subscribe(subCmdVel);
}

void loop()
{ 
  str_msg.data = heartbeat;
  testcon.publish(&str_msg);
  n.spinOnce();
  delay(1000);

  M2T_bs = digitalRead(MID2TOP);
  B2T_bs = digitalRead(BOT2TOP);

  if(M2T_bs == HIGH){
    mid2top();
  }
  if(B2T_bs == HIGH){
    bot2top();
  }
}
