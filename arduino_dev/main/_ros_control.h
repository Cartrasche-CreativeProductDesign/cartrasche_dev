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
char cmdvelcallback[18] = "rcvd cmdvel";
char stcallback[18] = "rcvd st";

// Subscriber Callbacks
void cmdvelCallback(const geometry_msgs::Twist& cmd_vel){
  str_msg.data = cmdvelcallback;
  rosduino.publish(&str_msg);
  
  int spd = calculateSPeed(abs(cmd_vel.linear.x));
  int ang = calculateAngle(abs(cmd_vel.angular.z));
  if(cmd_vel.linear.x == 0){
    turn_off_motor();
  }
  else if(cmd_vel.linear.x > 0){
    fb_control(0, spd);
  }
  else if(cmd_vel.linear.x < 0){
    fb_control(1, spd);
  }

  if(cmd_vel.angular.z == 0){
    turn_off_motor();
  }
  else if(cmd_vel.angular.z > 0){
    lr_control(0, spd);
  }
  else if(cmd_vel.angular.z < 0){
    lr_control(1, spd);
  }
}

void stCallback(const std_msgs::Int32& switch_tray){
  str_msg.data = stcallback;
  rosduino.publish(&str_msg);

  if(switch_tray.data == 1){
    mid2top();
  }
  if(switch_tray.data == 2){
    bot2top();
  }
}

#endif
