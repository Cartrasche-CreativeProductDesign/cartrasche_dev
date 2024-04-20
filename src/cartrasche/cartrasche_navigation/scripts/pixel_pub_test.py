#!/usr/bin/env python3

import rospy
from geometry_msgs.msg import PointStamped


def pixel_pub():
    # Initialize the ROS node
    rospy.init_node('pixel_test_publisher')

    # Create a publisher for the pixel topic
    pub = rospy.Publisher('/aruco_single/pixel', PointStamped, queue_size=1)

    # Set the rate at which the message will be published (in Hz)
    rate = rospy.Rate(10)

    while not rospy.is_shutdown():
        # Create a message with x value of 160
        pixel_msg = PointStamped()
        pixel_msg.header.frame_id = 'usb_cam'
        pixel_msg.header.stamp = rospy.Time.now()
        pixel_msg.point.x = 160
        pixel_msg.point.y = 0
        pixel_msg.point.z = 0

        # Publish the message
        pub.publish(pixel_msg)

        # Sleep to maintain the desired publishing rate
        rate.sleep()

if __name__ == '__main__':
    try:
        pixel_pub()
    except rospy.ROSInterruptException:
        pass