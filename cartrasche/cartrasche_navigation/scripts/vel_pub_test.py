#!/usr/bin/env python3

import rospy
from geometry_msgs.msg import Twist


def publish_cmd_vel():
    # Initialize the ROS node
    rospy.init_node('cmd_vel_publisher')

    # Create a publisher for the cmd_vel topic
    pub = rospy.Publisher('/cmd_vel', Twist, queue_size=1)
    rospy.sleep(0.1)

    cmd_vel_msg = Twist()
    cmd_vel_msg.linear.x = 0.5  # linear velocity in the x-axis
    cmd_vel_msg.angular.z = 0.0  # angular velocity in the z-axis

    pub.publish(cmd_vel_msg)

if __name__ == '__main__':
    publish_cmd_vel()
