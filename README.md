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
- Subscribe : /cmd_vel  [geometry_msgs::Twist] -> linear.x, angular.z
- Subscribe : /switch_tray [std_msgs::Int32] -> 1 or 2
- Publish   : /rosduino [std_msgs::String] -> callback msg for received topic
- Publish   : /heartbeat [std_msgs::String] -> heartbeat

## LED INDEX
- WHITE : DEFAULT
- BLUE : MID to TOP
- GREEN : BOTTOM to TOP
- MAGENTA : On Drive Mode
- YELLOW : On Manual Mode