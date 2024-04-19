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
char heartbeat[18] = "arduino heartbeat";
ros::Publisher testcon("testcon", &str_msg);

void setupMotors()
{
  // BLDC
  initialize_bldc();
  // STEPPER
  initialize_steppers();
}

void setupPheris()
{
  pinMode(MID2TOP, INPUT);
  pinMode(BOT2TOP, INPUT);
  pinMode(LED_BUILTIN, OUTPUT);
}

void setup()
{
  setupMotors();  
  setupPheris();
  // ROSSERIAL with Jetson
  n.initNode();
  n.advertise(testcon); // to be removed
  n.advertise(rosduino);
  n.subscribe(subCmdVel);

  // fb_control(0,170);
  mid2top();
  delay(3000);
  bot2top();
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
