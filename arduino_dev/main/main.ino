
#include "config.h"
#include "_step_control.h"
#include "_led_control.h"
// #include "_motor_control.h"
#include "_ros_control.h"

// SUbscriber Declaration
ros::Subscriber<geometry_msgs::Twist> subCmdVel("cmd_vel", &cmdvelCallback );
ros::Subscriber<std_msgs::Int32> subSwitch("switch_tray", &stCallback );
// Publisher Declaration
char hb[18] = "arduino heartbeat";
ros::Publisher heartbeat("heartbeat", &str_msg);

void setupMotors()
{
  // BLDC
  initialize_bldc();
  // STEPPER
  initialize_steppers();
}

void setupPheris()
{
  pinMode(MID2TOP, INPUT);
  pinMode(BOT2TOP, INPUT);
  pinMode(LED_BUILTIN, OUTPUT);
  initializeLED();
}

void setup()
{
  setupMotors();  
  setupPheris();
  // ROSSERIAL with Jetson
  n.initNode();
  n.advertise(heartbeat);
  n.advertise(rosduino);
  n.subscribe(subCmdVel);
  n.subscribe(subSwitch);
  mid2top();
}

void loop()
{ 
  str_msg.data = hb;
  heartbeat.publish(&str_msg);
  n.spinOnce();
  delay(1000);

  M2T_bs = digitalRead(MID2TOP);
  B2T_bs = digitalRead(BOT2TOP);

  if(M2T_bs == HIGH){
    mid2top();
  }
  if(B2T_bs == HIGH){
    bot2top();
  }
}
