#include <ros.h>
#include <std_msgs/UInt8.h>
#include <std_msgs/String.h>
#include <std_msgs/Empty.h>
#include <geometry_msgs/Twist.h>
#include "config.h"
#include "_motor_control.h"

// ROS usage
ros::NodeHandle n;
std_msgs::String str_msg;
char callback[18] = "rcvd topic";

// Subscriber Callbacks
void cmdvelCallback(const geometry_msgs::Twist& cmd_vel){
  // Serial.println(cmdVel.linear.x);
  // Serial.println(cmdVel.angular.z);

  double RPM = cmd_vel.linear.x / (2*PI*WHEEL_RAD);
  str_msg.data = callback;
  testcon.publish(&str_msg);
  
  if(cmdVel.linear.x == 0){
    turn_off_motor();
  }
}
