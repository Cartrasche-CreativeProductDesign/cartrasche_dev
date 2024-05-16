#!/usr/bin/env python3

import rospy
from geometry_msgs.msg import Twist


def straight(pub, speed=0.5, duration=4.0):
    twist_msg = Twist()
    twist_msg.linear.x = speed  # Set linear velocity in the x-axis
    twist_msg.angular.z = 0.0  # Set angular velocity in the z-axis
    rate = rospy.Rate(2)  # Set the publishing rate to 0.5 Hz
    start_time = rospy.get_time()  # Get the current time
    while rospy.get_time() - start_time < duration:  # Run for 2 seconds
        pub.publish(twist_msg)
        print(f"Publishing straight {speed} m/s")
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


def right_turn(pub, speed=4.0, duration=4.0):
    twist_msg = Twist()
    twist_msg.linear.x = 0.0  # Set linear velocity in the x-axis
    twist_msg.angular.z = speed  # Set angular velocity in the z-axis
    rate = rospy.Rate(2)  # Set the publishing rate to 0.5 Hz
    start_time = rospy.get_time()  # Get the current time
    while rospy.get_time() - start_time < duration:  # Run for 2 seconds
        pub.publish(twist_msg)
        print(f"Publishing right turn {speed} rad/s")
        rate.sleep()

def combined(pub, linear, angular, duration=5.0):
    twist_msg = Twist()
    twist_msg.linear.x = linear  # Set linear velocity in the x-axis
    twist_msg.angular.z = angular  # Set angular velocity in the z-axis
    rate = rospy.Rate(2)  # Set the publishing rate to 0.5 Hz
    start_time = rospy.get_time()  # Get the current time
    while rospy.get_time() - start_time < duration:  # Run for 2 seconds
        pub.publish(twist_msg)
        print(f"Publishing combined {linear} m/s , {angular} rad/s")
        rate.sleep()



def scenario():
    rospy.init_node('scenario_1')
    pub = rospy.Publisher('/cmd_vel', Twist, queue_size=10)
    rospy.sleep(0.1)  # Sleep for 0.1 seconds to allow the publisher to initialize

    # scenario_1
    straight(pub, speed=0.4, duration=4.0)
    stop(pub)
    right_turn(pub, speed=2.0, duration=3.0)
    stop(pub)
    straight(pub, speed=0.4, duration=4.0)
    stop(pub)

    # # acceleration
    # straight(pub, speed=1.0, duration=3.0)
    # straight(pub, speed=1.0, duration=4.0)
    # straight(pub, speed=1.5, duration=4.0)
    # straight(pub, speed=2.0, duration=4.0)
    # straight(pub, speed=2.5, duration=4.0)
    # straight(pub, speed=3.0, duration=4.0)

    # # deceleration
    # straight(pub, speed=2.5, duration=4.0)
    # straight(pub, speed=2.0, duration=4.0)
    # straight(pub, speed=1.5, duration=4.0)
    # straight(pub, speed=1.0, duration=4.0)
    # straight(pub, speed=0.5, duration=4.0)

    # right turn
    # right_turn(pub, speed=10.0, duration=4.0)
    # stop(pub)
    # right_turn(pub, speed=-10.0, duration=4.0)
    # right_turn(pub, speed=10.0, duration=4.0)
    # right_turn(pub, speed=5.0, duration=4.0)

    # combined
    # combined(pub, linear=1.0, angular=0.0)
    # combined(pub, linear=1.0, angular=5.0)
    # combined(pub, linear=1.0, angular=10.0)
    # combined(pub, linear=1.0, angular=15.0)

    # combined(pub, linear=1.0, angular=10.0)
    # combined(pub, linear=1.5, angular=10.0)
    # combined(pub, linear=2.0, angular=10.0)
    # combined(pub, linear=2.5, angular=10.0)


    # stop
    stop(pub)


if __name__ == "__main__":
    scenario()
    print("end")
