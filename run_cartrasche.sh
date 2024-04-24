#!/bin/sh

sudo chmod 777 /dev/ttyACM0 &
roscore &
rosrun rosserial_python serial_node _baud:=57600 _port:=/dev/ttyACM0 &
rostopic echo /heartbeat