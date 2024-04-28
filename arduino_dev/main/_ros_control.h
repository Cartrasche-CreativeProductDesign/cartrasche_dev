#ifndef _ROS_CONTROL_H
#define _ROS_CONTROL_H
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

  float linx = cmd_vel.linear.x;
  float angz = cmd_vel.angular.z;
 
  int spd = calculateSPeed(abs(linx));
  int ang = calculateAngle(angz);
  
  String velstring2 = String(spd);
  // n.loginfo(velstring2.c_str());  
  String velstring3 = String(ang);
  // n.loginfo(velstring3.c_str());
  
  if(linx > 0.0){
    n.loginfo("linear fwd");
    fb_control(0, spd);
    delay(10);
    if(abs(angz) > 0.0){
      n.loginfo("angular_1");
      lr_control(ang);
      delay(10);
    }
  }
  else if(linx < 0.0){
    n.loginfo("linear bwd");
    fb_control(1, spd);
    delay(10);
    if(abs(angz) > 0.0){
      n.loginfo("angular_2");
      lr_control(ang);
      delay(10);
    }
  }
  else{
    n.loginfo("linear zero");
    if(abs(angz) > 0.0){
      n.loginfo("angular_3");
      lr_control(ang);
      delay(10);
    }
    else{
      n.loginfo("stop");
      turn_off_motor();
      delay(10);
    }
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
