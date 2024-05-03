# cartrasche_dev

![cartrasche_logo](https://github.com/Cartrasche-CreativeProductDesign/cartrasche_dev/assets/68832065/74af2a03-79aa-4e0f-a699-e39b201d271c)

prerequisitories

add these at the end of '~/.bashrc'
```
source /opt/ros/noetic/setup.bash
export TURTLEBOT3_MODEL=waffle_pi
source /home/{$YOUR_DIR}/cartrasche_dev/devel/setup.bash
```

## Set as On-Boot Service
```
cd cartrasche_dev
sudo sh set_service.sh
```
cartrasche service will run on-boot after reboot

check status with
```
sudo systemctl status cartrasche
```

## How to Run
Open two terminals
```
roscore

sudo chmod 777 /dev/ttyACM0 &
rosrun rosserial_python serial_node.py _port:=/dev/ttyACM0 _baud:=57600
```

## ROSSERIAL-ATMEGA
ARDUINO
- Subscribe : /cmd_vel  [geometry_msgs::Twist] -> linear.x, angular.z
- Subscribe : /switch_tray [std_msgs::Int32] -> 1 or 2
- Publish   : /rosduino [std_msgs::String] -> callback msg for received topic
- Publish   : /heartbeat [std_msgs::String] -> heartbeat

JESTSON
- Publish : /cmd_vel  [geometry_msgs::Twist] -> linear.x, angular.z
- Publish : /switch_tray [std_msgs::Int32] -> 1 or 2
- NODE : Serial_Node

## LED INDEX
- WHITE : DEFAULT
- BLUE : MID to TOP
- YELLOW : BOTTOM to TOP
- GREEN : On Drive Mode
- RED : On STOP
