#include <SoftwareSerial.h>
#include <ros.h>
#include <std_msgs/UInt8.h>
#include <std_msgs/String.h>
#include <std_msgs/Empty.h>
#include <geometry_msgs/Twist.h>

#include "config.h"
#include "_step_control.h"
#include "_motor_control.h"


// ROS usage
ros::NodeHandle n;
std_msgs::String str_msg;
char heartbeat[18] = "arduino heartbeat";

// Subscriber Callbacks
void numberCallback(const std_msgs::UInt8& msg){
}
void cmdvelCallback(const geometry_msgs::Twist& cmdVel){
  Serial.println(cmdVel.linear.x);
}

// SUbscriber Declaration
ros::Subscriber<geometry_msgs::Twist> subCmdVel("cmd_vel", &cmdvelCallback );
ros::Subscriber<std_msgs::UInt8> sub("hex", &numberCallback); //Empty

// Publisher Declaration
ros::Publisher rosduino("rosduino", &str_msg);


void setupMotors()
{
  // BLDC
  initialize_bldc();
  // STEPPER
  pinMode(STEP_DIR, OUTPUT);
  pinMode(STEP_STEP, OUTPUT);
  pinMode(STEP_EN, OUTPUT);
  digitalWrite(STEP_EN, LOW);
}

void setup()
{
  Serial.begin(57600); 
  setupMotors();
  Serial.println("Driver is ready");
  
  
  // ROSSERIAL with Jetson
  n.initNode();
  n.advertise(rosduino);
  n.subscribe(sub);
  n.subscribe(subCmdVel);

  // Initial Motor Check should be removed for action
  
//  Serial.println("--------");
//  lr_control(0, 100);
//  delay(10000);
//  Serial.println("done spd2");
//  turn_off_motor(); 
}


void loop()
{ 
  str_msg.data = heartbeat;
  rosduino.publish(&str_msg);
  n.spinOnce();
  delay(1000);
  lr_control(0, 250);
  delay(5000);
  turn_off_motor();
}
