#!/usr/bin/env python3

import rospy
from geometry_msgs.msg import PoseStamped, PointStamped, Quaternion
from sensor_msgs.msg import LaserScan
from tf.transformations import quaternion_from_euler
import math


class HumanFollower:
    def __init__(self):
        rospy.init_node('human_follower')

        # Subscribers
        self.center_pixel_sub = rospy.Subscriber('/aruco_single/pixel', PointStamped, self.center_pixel_callback) # aruco marker center pixel
        # self.scan_sub = rospy.Subscriber('/scan', LaserScan, self.scan_callback) # LiDAR raw scan data
        self.scan_sub = rospy.Subscriber('/scan_filtered', LaserScan, self.scan_callback) # LiDAR filtered scan data

        # Publisher
        # move_base uses /move_base_simple/goal topic to receive goal poses
        self.goal_pub = rospy.Publisher('/move_base_simple/goal', PoseStamped, queue_size=1)

        # State
        self.current_center_pixel = None
        self.current_scan = None
        
        self.focal_length_x = rospy.get_param('~human_follower/focal_length_x', 0.80803844)
        self.image_width = rospy.get_param('~human_follower/image_width', 640)
        self.camera_fov = 2 * math.atan2(self.image_width / 2, self.focal_length_x)  # Field of view of the camera


    def center_pixel_callback(self, data):
        """Callback for the center pixel of the bounding box."""
        self.current_center_pixel = data


    def scan_callback(self, data):
        self.current_scan = data


    def compute_goal(self):
        if not self.current_center_pixel or not self.current_scan:
            rospy.loginfo("Waiting for data...")
            return

        angle_radians = self.estimate_angle(self.current_center_pixel) # Compute angle from bounding box center
        distance = self.estimate_distance(angle_radians, self.current_scan) # Find the distance(m) from the LiDAR data at this angle
        
        # Compute the goal position (maintaining 1 meter distance from the human)
        goal_pose = PoseStamped()
        goal_pose.header.frame_id = "base_link"
        goal_pose.header.stamp = rospy.Time.now()
        goal_pose.pose.position.x = (distance - 1.0) * math.cos(angle_radians)
        goal_pose.pose.position.y = (distance - 1.0) * math.sin(angle_radians)
        goal_pose.pose.orientation = Quaternion(*quaternion_from_euler(0, 0, angle_radians))

        self.goal_pub.publish(goal_pose)
        rospy.loginfo("Published new goal pose")


    def estimate_distance(self, angle_radians, scan_data):
        angle_index =  int(908 * (math.pi + angle_radians) / (2 * math.pi)) # Calculate the desired index
        distance = scan_data.ranges[angle_index] # Get distance using angle_index

        return distance


    def estimate_angle(self, center_pixel):
        # width difference from center
        pixel_offset_from_center = (self.image_width / 2) - center_pixel.point.x

        # Convert pixel offset to angle using the camera's field of view
        angle_radians = (pixel_offset_from_center / (self.image_width / 2)) * (self.camera_fov / 2.0)
        return angle_radians


    def run(self):
        """Main loop of the node."""
        rate = rospy.Rate(10)  # 10 Hz
        while not rospy.is_shutdown():
            self.compute_goal()
            rate.sleep()


if __name__ == '__main__':
    follower = HumanFollower()
    follower.run()
