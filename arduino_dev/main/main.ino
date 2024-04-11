#include <SoftwareSerial.h>
#include <ros.h>
#include <std_msgs/UInt8.h>
#include <std_msgs/String.h>
#include <std_msgs/Empty.h>

ros::NodeHandle n;

void numberCallback(const std_msgs::UInt8& msg){
  n.loginfo(msg.data);
}

ros::Subscriber<std_msgs::UInt8> sub("hex", &numberCallback); //Empty
std_msgs::String str_msg;
ros::Publisher rosduino("rosduino", &str_msg);
char heartbeat[18] = "arduino heartbeat";


void setup()
{
  Serial.begin(9600); 
  Serial.println("Arduino is ready");
  initialize_bldc();

  // ROSSERIAL with Jetson
  n.initNode();
  n.advertise(rosduino);
  n.subscribe(sub);

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
