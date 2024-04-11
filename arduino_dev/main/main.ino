#include <SoftwareSerial.h>
#include <ros.h>
#include <std_msgs/UInt8.h>
#include <std_msgs/String.h>
#include <std_msgs/Empty.h>
#include <geometry_msgs/Twist.h>

// ROS usage
ros::NodeHandle n;
std_msgs::String str_msg;
char heartbeat[18] = "arduino heartbeat";

// Subscriber Callbacks
void numberCallback(const std_msgs::UInt8& msg){
  n.loginfo(msg.data);
}
void cmdvelCallback(onst geometry_msgs::Twist& cmdVel){
  n.loginfo(cmdVel.linear.x);
  n.loginfo(cmdVel.angular.z);
}

// SUbscriber Declaration
ros::Subscriber<geometry_msgs::Twist> subCmdVel("cmd_vel", &cmdvelCallback );
ros::Subscriber<std_msgs::UInt8> sub("hex", &numberCallback); //Empty

// Publisher Declaration
ros::Publisher rosduino("rosduino", &str_msg);


void setup()
{
  Serial.begin(9600); 
  Serial.println("Arduino is ready");
  initialize_bldc();

  // ROSSERIAL with Jetson
  n.initNode();
  n.advertise(rosduino);
  n.subscribe(sub);
  n.subscribe(subCmdVel);

  // Initial Motor Check should be removed for action
  fb_control(0, 250);
  delay(10000);
  turn_off_motor();
}


void loop()
{
  str_msg.data = heartbeat;
  rosduino.publish(&str_msg);
  n.spinOnce();
  delay(1000);
}
