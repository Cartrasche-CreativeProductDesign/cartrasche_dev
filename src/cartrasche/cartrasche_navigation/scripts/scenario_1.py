#!/usr/bin/env python3

import rospy
from geometry_msgs.msg import Twist


def straight(pub):
    twist_msg = Twist()
    twist_msg.linear.x = 0.5  # Set linear velocity in the x-axis
    twist_msg.angular.z = 0.0  # Set angular velocity in the z-axis
    rate = rospy.Rate(2)  # Set the publishing rate to 0.5 Hz
    start_time = rospy.get_time()  # Get the current time
    while rospy.get_time() - start_time < 4.0:  # Run for 2 seconds
        pub.publish(twist_msg)
        print("Publishing straight")
        rate.sleep()


def stop(pub):
    twist_msg = Twist()
    twist_msg.linear.x = 0.0  # Set linear velocity in the x-axis
    twist_msg.angular.z = 0.0  # Set angular velocity in the z-axis
    rate = rospy.Rate(2)  # Set the publishing rate to 0.5 Hz
    start_time = rospy.get_time()  # Get the current time
    while rospy.get_time() - start_time < 1.0:  # Run for 2 seconds
        pub.publish(twist_msg)
        print("Publishing stop")
        rate.sleep()


def right_turn(pub):
    twist_msg = Twist()
    twist_msg.linear.x = 0.0  # Set linear velocity in the x-axis
    twist_msg.angular.z = 4.0  # Set angular velocity in the z-axis
    rate = rospy.Rate(2)  # Set the publishing rate to 0.5 Hz
    start_time = rospy.get_time()  # Get the current time
    while rospy.get_time() - start_time < 4.0:  # Run for 2 seconds
        pub.publish(twist_msg)
        print("Publishing right turn")
        rate.sleep()



def scenario():
    rospy.init_node('scenario_1')
    pub = rospy.Publisher('/cmd_vel', Twist, queue_size=10)
    rospy.sleep(0.1)  # Sleep for 0.1 seconds to allow the publisher to initialize

    straight(pub)
    stop(pub)
    right_turn(pub)
    stop(pub)


if __name__ == "__main__":
    scenario()
    print("end")
