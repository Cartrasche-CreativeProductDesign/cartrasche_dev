#ifndef _ROS_CONTROL_H
#define _ROS_CONTROL_H
#include <ros.h>
#include <std_msgs/Int32.h>
#include <std_msgs/String.h>
#include <std_msgs/Empty.h>
#include <geometry_msgs/Twist.h>
#include "config.h"
#include "_motor_control.h"

// ROS usage
ros::NodeHandle n;
std_msgs::String str_msg;
std_msgs::Int32 int_msg;
ros::Publisher rosduino("rosduino", &str_msg);
ros::Publisher velocity("velocity", &int_msg);
char cmdvelcallback[18] = "rcvd cmdvel";
char stcallback[18] = "rcvd st";


// Subscriber Callbacks
void cmdvelCallback(const geometry_msgs::Twist& cmd_vel){

  float linx = cmd_vel.linear.x;
  float angz = cmd_vel.angular.z;
  str_msg.data = cmdvelcallback;
  rosduino.publish(&str_msg);

  int spd = calculateSPeed(abs(linx));
  int ang = calculateAngle(abs(angz));
  int_msg.data = spd;
  velocity.publish(&int_msg);
  
  if(linx == 0.0){
    turn_off_motor();
  }
  else if(linx > 0.0){
    fb_control(0, spd);
  }
  else if(linx < 0.0){
    fb_control(1, spd);
  }

  if(angz == 0.0){
    turn_off_motor();
  }
  else if(angz > 0.0){
    lr_control(0, ang);
  }
  else if(angz < 0.0){
    lr_control(1, ang);
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
