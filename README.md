# cartrasche_dev

prerequisitories
add these at the end of '~/.bashrc'
```
source /opt/ros/noetic/setup.bash
export TURTLEBOT3_MODEL=waffle_pi
source /home/minjun/cartrasche_dev/devel/setup.bash
```

## How to Run
Open two terminals
```
roscore

rosrun rosserial_python serial_node.py _port:=/dev/ttyACM0 _baud:=57600
```

## ROSSERIAL-ATMEGA
ARDUINO
- Subscribe : /cmd_vel  [geometry_msgs::Twist]
- Publish   : /rosduino [std_msgs::String]