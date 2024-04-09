# cartrasche_dev

prerequisitories
add these at the end of '~/.bashrc'
```
source /opt/ros/noetic/setup.bash
export TURTLEBOT3_MODEL=waffle_pi
source /home/minjun/cartrasche_dev/devel/setup.bash
```

## How to Run
Open three terminals
```
roscore

# md_robot_node feeds /cmd_vel
roslaunch md md_robot_node

roslaunch turtlebot3_teleop turtlebot3_teleop_key.launch
```