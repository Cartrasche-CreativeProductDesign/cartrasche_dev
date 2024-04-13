#!/usr/bin/env python
import rospy
from sensor_msgs.msg import LaserScan, PointCloud2
from laser_geometry import LaserProjection

class ScanToPointCloud:
    def __init__(self):
        self.node_name = "scan_to_cloud"
        rospy.init_node(self.node_name)

        self.laser_projection = LaserProjection()
        self.laser_sub = rospy.Subscriber("/scan", LaserScan, self.scan_callback)
        self.cloud_pub = rospy.Publisher("/PointCloud2", PointCloud2, queue_size=1)

    def scan_callback(self, scan):
        try:
            cloud = self.laser_projection.projectLaser(scan)
            self.cloud_pub.publish(cloud)
        except Exception as e:
            rospy.logerr("Error when converting LaserScan to PointCloud2: %s", e)

if __name__ == '__main__':
    converter = ScanToPointCloud()
    rospy.spin()
