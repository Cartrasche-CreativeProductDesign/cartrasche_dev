#!/usr/bin/env python3

import rospy
from std_msgs.msg import Float32
from geometry_msgs.msg import PoseStamped, PointStamped, Quaternion, Twist
from sensor_msgs.msg import LaserScan
from tf.transformations import quaternion_from_euler
import math


class HumanFollower:
    def __init__(self):
        rospy.init_node('human_follower')

        # Subscribers
        self.scan_sub = rospy.Subscriber('/scan', LaserScan, self.scan_callback)  # LiDAR raw scan data
        self.center_pixel_sub = rospy.Subscriber('/aruco_single/pixel', PointStamped, self.center_pixel_callback)  # Aruco marker center pixel

        # Publisher
        self.vel_pub = rospy.Publisher('/cmd_vel', Twist, queue_size=1)

        # State
        self.current_center_pixel = None
        self.current_scan = None
        self.last_center_pixel_time = rospy.Time.now()
        self.timeout_duration = rospy.Duration(1.0)  # 1 second timeout

        self.focal_length_x = rospy.get_param('~human_follower/focal_length_x', 0.80803844)
        self.image_width = rospy.get_param('~human_follower/image_width', 640)
        self.camera_fov = 2 * math.atan2(self.image_width / 2, self.focal_length_x)  # Field of view of the camera

    def center_pixel_callback(self, data):
        """Callback for the center pixel of the bounding box."""
        self.current_center_pixel = data
        self.last_center_pixel_time = rospy.Time.now()

        if not self.current_center_pixel or not self.current_scan:
            rospy.loginfo("Waiting for data...")
            return

        angle_radians = self.estimate_angle(self.current_center_pixel)  # Compute angle from bounding box center
        distance = self.estimate_distance(angle_radians, self.current_scan)  # Find the distance(m) from the LiDAR data at this angle
        rospy.loginfo(f"angle: {angle_radians}, distance: {distance}")

        # Compute the linear and angular velocities
        cmd_vel = Twist()
        cmd_vel.linear.x = 0.2 if distance > 1.5 else 0.0
        cmd_vel.angular.z = -0.1 if angle_radians > 0.1 else 0.1 if angle_radians < -0.1 else 0.0

        self.vel_pub.publish(cmd_vel)
        rospy.loginfo(f"Published new velocity command.")
        rospy.loginfo(f"Linear: {cmd_vel.linear.x}, Angular: {cmd_vel.angular.z}")

    def scan_callback(self, data):
        self.current_scan = data

    def estimate_distance(self, angle_radians, scan_data):
        angle_index = int(908 * (math.pi + angle_radians) / (2 * math.pi))  # Calculate the desired index
        distance = scan_data.ranges[angle_index]  # Get distance using angle_index

        return distance

    def estimate_angle(self, center_pixel):
        # Width difference from center
        pixel_offset_from_center = (self.image_width / 2) - center_pixel.point.x

        # Convert pixel offset to angle using the camera's field of view
        angle_radians = (pixel_offset_from_center / (self.image_width / 2)) * (self.camera_fov / 2.0)
        angle_radians /= 3.0
        return angle_radians

    def run(self):
        """Main loop of the node."""
        rate = rospy.Rate(5)  # 5 Hz
        while not rospy.is_shutdown():
            current_time = rospy.Time.now()
            if (current_time - self.last_center_pixel_time) > self.timeout_duration:
                # No recent center pixel data, publish zero velocity
                cmd_vel = Twist()
                self.vel_pub.publish(cmd_vel)
                rospy.loginfo(f"No center pixel data, published zero velocity.")

            rate.sleep()


if __name__ == '__main__':
    follower = HumanFollower()
    follower.run()
