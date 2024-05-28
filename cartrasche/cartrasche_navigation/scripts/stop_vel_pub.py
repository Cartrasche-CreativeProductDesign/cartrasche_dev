#!/usr/bin/env python3

import rospy
from geometry_msgs.msg import Twist
from std_msgs.msg import Int32

class StopVel:
    def __init__(self):
        rospy.init_node('stop_vel_node')
        self.cmd_vel_sub = rospy.Subscriber("/cmd_vel", Twist, self.stop_vel_callback)
        self.stop_vel_pub = rospy.Publisher("/stop_vel", Int32, queue_size=1)

    def stop_vel_callback(self, data):
        if data.linear.x == 0.0 and data.angular.z == 0.0:
            rate = rospy.Rate(10)  # 5 Hz
            stop_vel = Int32(1)
            for _ in range(10):
                self.stop_vel_pub.publish(stop_vel)
                rate.sleep()

    def run(self):
        rospy.spin()

if __name__ == "__main__":
    stop_vel = StopVel()
    stop_vel.run()
