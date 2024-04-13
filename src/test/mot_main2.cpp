#include "kf_tracker/CKalmanFilter.h"
#include "kf_tracker/featureDetection.h"
#include "opencv2/video/tracking.hpp"
#include "pcl_ros/point_cloud.h"
#include <algorithm>
#include <fstream>
#include <geometry_msgs/Point.h>
#include <iostream>
#include <iterator>
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/video/video.hpp>
#include <pcl/io/pcd_io.h>
#include <pcl/point_types.h>
#include <ros/ros.h>
#include <std_msgs/Float32MultiArray.h>
#include <std_msgs/Int32MultiArray.h>
#include <string.h>
#include <pcl/common/centroid.h>
#include <pcl/common/geometry.h>
#include <pcl/features/normal_3d.h>
#include <pcl/filters/extract_indices.h>
#include <pcl/filters/voxel_grid.h>
#include <pcl/kdtree/kdtree.h>
#include <pcl/point_cloud.h>
#include <pcl/point_types.h>
#include <pcl/sample_consensus/method_types.h>
#include <pcl/sample_consensus/model_types.h>
#include <pcl/segmentation/extract_clusters.h>
#include <pcl/segmentation/sac_segmentation.h>
#include <pcl_conversions/pcl_conversions.h>
#include <sensor_msgs/PointCloud2.h>
#include <limits>
#include <utility>
#include <visualization_msgs/Marker.h>
#include <visualization_msgs/MarkerArray.h>

using namespace std;
using namespace cv;

ros::Publisher objID_pub;
ros::Publisher pub_cluster0;
ros::Publisher pub_cluster1;
ros::Publisher markerPub;

// KF initialization for two clusters
int stateDim = 4;  // [x,y,v_x,v_y]
int measDim = 2;   // [z_x,z_y]
int ctrlDim = 0;
cv::KalmanFilter KF[2];

std::vector<geometry_msgs::Point> prevClusterCenters;

cv::Mat state(stateDim, 1, CV_32F);
cv::Mat_<float> measurement(measDim, 1);

std::vector<int> objID; // Output of the data association using KF

bool firstFrame = true;

// Calculate Euclidean distance of two points
double euclidean_distance(const geometry_msgs::Point& p1, const geometry_msgs::Point& p2) {
    return sqrt(pow(p1.x - p2.x, 2) + pow(p1.y - p2.y, 2) + pow(p1.z - p2.z, 2));
}

// Find the index of the minimum value in a distance matrix
std::pair<int, int> findIndexOfMin(const std::vector<std::vector<float>>& distMat) {
    std::pair<int, int> minIndex;
    float minEl = std::numeric_limits<float>::max();
    for (int i = 0; i < distMat.size(); i++) {
        for (int j = 0; j < distMat[i].size(); j++) {
            if (distMat[i][j] < minEl) {
                minEl = distMat[i][j];
                minIndex = {i, j};
            }
        }
    }
    return minIndex;
}

void KFT(const std_msgs::Float32MultiArray& ccs) {
    std::vector<cv::Mat> pred;
    for (auto& kf : KF) {
        pred.push_back(kf.predict());
    }

    std::vector<geometry_msgs::Point> clusterCenters;
    for (auto it = ccs.data.cbegin(); it != ccs.data.cend(); it += 3) {
        clusterCenters.push_back({*it, *(it + 1), *(it + 2)});
    }

    std::vector<std::vector<float>> distMat;
    for (int filterN = 0; filterN < 2; ++filterN) {
        std::vector<float> distVec;
        for (const auto& center : clusterCenters) {
            distVec.push_back(euclidean_distance(pred[filterN], center));
        }
        distMat.push_back(distVec);
    }

    for (int clusterCount = 0; clusterCount < 2; ++clusterCount) {
        auto minIndex = findIndexOfMin(distMat);
        objID[minIndex.first] = minIndex.second;

        for (auto& row : distMat) {
            row[minIndex.second] = std::numeric_limits<float>::max();
        }
        std::fill(distMat[minIndex.first].begin(), distMat[minIndex.first].end(), std::numeric_limits<float>::max());
    }

    visualization_msgs::MarkerArray clusterMarkers;
    for (int i = 0; i < 2; ++i) {
        visualization_msgs::Marker m;
        m.id = i;
        m.type = visualization_msgs::Marker::CUBE;
        m.header.frame_id = "map";
        m.scale.x = m.scale.y = m.scale.z = 0.3;
        m.action = visualization_msgs::Marker::ADD;
        m.color.a = 1.0;  // Don't forget to set the alpha!
        m.color.r = static_cast<float>(i % 2);
        m.color.g = static_cast<float>(i % 2);
        m.color.b = static_cast<float>(i % 2);

        m.pose.position = clusterCenters[objID[i]];
        clusterMarkers.markers.push_back(m);
    }

    markerPub.publish(clusterMarkers);

    std_msgs::Int32MultiArray obj_id;
    for (int id : objID) {
        obj_id.data.push_back(id);
    }
    objID_pub.publish(obj_id);
}

void cloud_cb(const sensor_msgs::PointCloud2ConstPtr& input) {
    pcl::PointCloud<pcl::PointXYZ>::Ptr input_cloud(new pcl::PointCloud<pcl::PointXYZ>);
    pcl::fromROSMsg(*input, *input_cloud);

    pcl::search::KdTree<pcl::PointXYZ>::Ptr tree(new pcl::search::KdTree<pcl::PointXYZ>);
    tree->setInputCloud(input_cloud);

    pcl::EuclideanClusterExtraction<pcl::PointXYZ> ec;
    ec.setClusterTolerance(0.3); // Adjust the tolerance based on your scenario
    ec.setMinClusterSize(10);
    ec.setMaxClusterSize(600);
    ec.setSearchMethod(tree);
    ec.setInputCloud(input_cloud);

    std::vector<pcl::PointIndices> cluster_indices;
    ec.extract(cluster_indices);

    std::vector<pcl::PointCloud<pcl::PointXYZ>::Ptr> cluster_vec;
    for (auto& indices : cluster_indices) {
        pcl::PointCloud<pcl::PointXYZ>::Ptr cloud_cluster(new pcl::PointCloud<pcl::PointXYZ>);
        for (int index : indices.indices) {
            cloud_cluster->points.push_back(input_cloud->points[index]);
        }
        cluster_vec.push_back(cloud_cluster);
    }

    std_msgs::Float32MultiArray cc;
    for (auto& cluster : cluster_vec) {
        pcl::PointXYZ centroid;
        pcl::computeCentroid(*cluster, centroid);
        cc.data.push_back(centroid.x);
        cc.data.push_back(centroid.y);
        cc.data.push_back(centroid.z);
    }

    KFT(cc);

    // Publish the clusters
    if (!cluster_vec.empty()) {
        pub_cluster0.publish(cluster_vec[0]);
        if (cluster_vec.size() > 1) {
            pub_cluster1.publish(cluster_vec[1]);
        }
    }
}

int main(int argc, char** argv) {
    ros::init(argc, argv, "kf_tracker");
    ros::NodeHandle nh;

    pub_cluster0 = nh.advertise<sensor_msgs::PointCloud2>("cluster_0", 1);
    pub_cluster1 = nh.advertise<sensor_msgs::PointCloud2>("cluster_1", 1);
    objID_pub = nh.advertise<std_msgs::Int32MultiArray>("obj_id", 1);
    markerPub = nh.advertise<visualization_msgs::MarkerArray>("cluster_markers", 1);

    ros::Subscriber sub = nh.subscribe("input_cloud", 1, cloud_cb);

    ros::spin();
}
