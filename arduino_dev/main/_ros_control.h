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
char heartbeat[18] = "rosduino heartbeat";

// Subscriber Callbacks
void cmdvelCallback(const geometry_msgs::Twist& cmdVel){
  Serial.println(cmdVel.linear.x);
  Serial.println(cmdVel.angular.z);
  
  if(cmdVel.linear.x == 0){
    turn_off_motor();
  }
}
