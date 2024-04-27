# Initial Setup 

## Camera 

    sudo apt install ros-noetic-usb-cam
    
    rosdep install camera_calibration 

Before continuing to the next step, you must complete camera calibration:
<http://wiki.ros.org/camera_calibration/Tutorials/MonocularCalibration>

As a result of the calibration, a YAML file, which describes the camera intrinsic parameters, is created at /tmp/.../opt.yml(you should definitely check the log). 

## ArUco

    git clone https://github.com/pal-robotics/aruco_ros

    cd aruco_ros
    mkdir src 
    catkin_make
    
## LiDAR SDK Installation 
<https://github.com/YDLIDAR/ydlidar_ros_driver>
    
    git clone https://github.com/YDLIDAR/ydlidar_ros_driver.git

    chmod 0777 src/ydlidar_ros_driver/startup/*
    sudo sh src/ydlidar_ros_driver/startup/initenv.sh

## Hector Slam 
<https://github.com/tu-darmstadt-ros-pkg/hector_slam>

    git clone https://github.com/tu-darmstadt-ros-pkg/hector_slam.git

    catkin_make 

# Run Launch File 

## Camera + ArUco

    roslaunch vision cam_aruco_bringup.launch
    

## LiDAR + Hector Slam

    roslaunch vision lidar_slam_bringup.launch

# Topics
Only interested in the center coordinates of the marker. It is easily found on the topic /aruco_single/pixel

    /aruco_single/pixel 

    /aruco_single/position


# Trials and Errors 

    serialConfig.cmake not found<https://github.com/wjwwood/serial/issues/89> 

    sudo apt install ros-noetic-serial 
