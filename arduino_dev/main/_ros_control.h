#ifndef _ROS_CONTROL_H
#define _ROS_CONTROL_H
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
ros::Publisher rosduino("rosduino", &str_msg);
char callback[18] = "rcvd topic";

// Subscriber Callbacks
void cmdvelCallback(const geometry_msgs::Twist& cmd_vel){

  str_msg.data = callback;
  rosduino.publish(&str_msg);
  
  int spd = calculateSPeed(abs(cmd_vel.linear.x));
  if(cmd_vel.linear.x == 0){
    turn_off_motor();
  }
  else if(cmd_vel.linear.x > 0){
    fb_control(0, spd);
  }
  else if(cmd_vel.linear.x < 0){
    fb_control(1, spd);
  }
}

#endif
