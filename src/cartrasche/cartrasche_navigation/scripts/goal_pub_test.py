#!/usr/bin/env python3

import rospy
from geometry_msgs.msg import PoseStamped, Quaternion
from tf.transformations import quaternion_from_euler


def goal_pub():
    # Initialize the ROS node
    rospy.init_node('goal_publisher')

    # Create a publisher for the goal_pose topic
    goal_pub = rospy.Publisher('goal_pose', PoseStamped, queue_size=1)

    # Create a PoseStamped message
    goal_msg = PoseStamped()

    # Set the position and orientation of the goal
    goal_msg.pose.position.x = 0.0
    goal_msg.pose.position.y = 2.0
    goal_msg.pose.position.z = 0.0
    goal_msg.pose.orientation = Quaternion(*quaternion_from_euler(0, 0, 0))

    # Set the header information of the goal message
    goal_msg.header.frame_id = 'map'

    # Set the publishing rate to 10Hz
    rate = rospy.Rate(1)

    while not rospy.is_shutdown():
        # Set the timestamp of the goal message
        goal_msg.header.stamp = rospy.Time.now()

        # Publish the goal message
        goal_pub.publish(goal_msg)

        # Sleep to maintain the publishing rate
        rate.sleep()

if __name__ == '__main__':
    try:
        goal_pub()
    except rospy.ROSInterruptException:
        pass