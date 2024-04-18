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

  double RPM = cmd_vel.linear.x / (2*PI*WHEEL_RAD);
  str_msg.data = callback;
  rosduino.publish(&str_msg);
  
  if(cmd_vel.linear.x == 0){
    turn_off_motor();
  }
}
