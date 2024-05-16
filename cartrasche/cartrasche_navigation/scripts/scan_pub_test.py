#!/usr/bin/env python3

import rospy
from sensor_msgs.msg import LaserScan

def scan_pub():
    # Initialize the ROS node
    rospy.init_node('scan_test_publisher')

    # Create a publisher for the pixel topic
    pub = rospy.Publisher('/scan', LaserScan, queue_size=1)

    # Set the rate at which the message will be published (in Hz)
    rate = rospy.Rate(10)

    while not rospy.is_shutdown():
        scan_msg = LaserScan()
        scan_msg.header.frame_id = 'scan_base'
        scan_msg.header.stamp = rospy.Time.now()
        scan_msg.ranges = [2.0] * 909  # Assign a valid value to scan_msg.ranges

        # Publish the message
        pub.publish(scan_msg)

        # Sleep to maintain the desired publishing rate
        rate.sleep()

if __name__ == '__main__':
    try:
        scan_pub()
    except rospy.ROSInterruptException:
        pass