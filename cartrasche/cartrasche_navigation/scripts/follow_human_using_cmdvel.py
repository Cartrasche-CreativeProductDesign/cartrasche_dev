#!/usr/bin/env python3

import rospy
from std_msgs.msg import Float32, Int32
from geometry_msgs.msg import PoseStamped, PointStamped, Quaternion, Twist, TransformStamped
from sensor_msgs.msg import LaserScan
from tf.transformations import quaternion_from_euler
import math


class HumanFollower:
    def __init__(self):
        rospy.init_node('human_follower')

        # Subscribers
        self.center_pixel_sub = rospy.Subscriber('/aruco_single/pixel', PointStamped, self.center_pixel_callback)  # Aruco marker center pixel
        self.aruco_tf_sub = rospy.Subscriber('/aruco_single/transform', TransformStamped, self.aruco_tf_callback)  # Aruco marker transform

        # Publisher
        self.vel_pub = rospy.Publisher('/cmd_vel', Twist, queue_size=1)
        self.stop_vel_pub = rospy.Publisher("/stop_vel", Int32, queue_size=1)

        # State
        self.current_center_pixel = None
        self.current_aruco_tf = None

        self.last_center_pixel_time = rospy.Time.now()
        self.timeout_duration = rospy.Duration(1.5)  # 1.5 second timeout

        self.focal_length_x = rospy.get_param('~human_follower/focal_length_x', 1036.51263)
        self.image_width = rospy.get_param('~human_follower/image_width', 1280)
        self.camera_fov = 2 * math.atan2(self.image_width / 2, self.focal_length_x)  # Field of view of the camera

    def center_pixel_callback(self, data):
        """Callback for the center pixel of the bounding box."""
        self.current_center_pixel = data
        self.last_center_pixel_time = rospy.Time.now()
        

        if not self.current_center_pixel or not self.current_aruco_tf:
            rospy.loginfo("Waiting for data...")
            return

        angle_radians = self.estimate_angle(self.current_center_pixel)  # Compute angle(rad) from bounding box center
        angle_degrees = angle_radians * 180 / math.pi
        # distance = self.estimate_distance(angle_radians, self.current_scan)  # Find the distance(m) from the LiDAR data at this angle
        distance = self.estimate_distance()

        # Compute the linear and angular velocities
        cmd_vel = Twist()
        linear_abs_vel = min(1.0, 0.1 + 0.5 * (distance - 1.5))
        cmd_vel.linear.x = linear_abs_vel if distance > 1.5 else 0.0
        angular_abs_vel = min(1.0, 0.2 + 1.0 * (abs(angle_radians) - 0.2))
        cmd_vel.angular.z = angular_abs_vel if angle_radians > 0.2 else -angular_abs_vel if angle_radians < -0.2 else 0.0

        self.vel_pub.publish(cmd_vel)
        # stop signal publish
        if cmd_vel.linear.x == 0 and cmd_vel.angular.z == 0:
            stop_vel = Int32(1)
            self.stop_vel_pub.publish(stop_vel)
        rospy.loginfo(f"distance : {distance}")

    def scan_callback(self, data):
        self.current_scan = data

    def aruco_tf_callback(self, data):
        self.current_aruco_tf = data
    
    def estimate_distance(self):
        x = self.current_aruco_tf.transform.translation.x
        y = self.current_aruco_tf.transform.translation.y
        z = self.current_aruco_tf.transform.translation.z
        distance = math.sqrt(x**2 + y**2 + z**2)

        return distance

    def estimate_angle(self, center_pixel):
        # Width difference from center
        pixel_offset_from_center = (self.image_width / 2) - center_pixel.point.x

        # Convert pixel offset to angle using the camera's field of view
        angle_radians = (pixel_offset_from_center / (self.image_width / 2)) * (self.camera_fov / 2.0)
        # angle_radians /= 3.0
        return angle_radians

    def run(self):
        """Main loop of the node."""
        rate = rospy.Rate(10)  # 5 Hz
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
