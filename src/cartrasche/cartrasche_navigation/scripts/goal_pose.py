#!/usr/bin/env python3

import rospy
import actionlib
from move_base_msgs.msg import MoveBaseAction, MoveBaseGoal
from geometry_msgs.msg import PoseStamped, Quaternion
from tf.transformations import quaternion_from_euler

class GoalPoseActionClient:
    def __init__(self):
        rospy.init_node('goal_pose_action_client')

        self.action_client = actionlib.SimpleActionClient('move_base', MoveBaseAction)
        # self.action_client.wait_for_server()

        rospy.loginfo("Connected to move_base action server")
        print("done")
        # Subscribe to a topic where goals are published or get them from parameters
        self.goal_sub = rospy.Subscriber('/goal_pose', PoseStamped, self.handle_new_goal)

    def handle_new_goal(self, msg):
        """Handle new goal pose and send it to the move_base action server."""
        goal = MoveBaseGoal()
        goal.target_pose.header.frame_id = "map"
        goal.target_pose.header.stamp = rospy.Time.now()
        goal.target_pose.pose = msg.pose

        self.send_goal(goal)

    def send_goal(self, goal):
        """Send a goal to the move_base action server and handle the response."""
        self.action_client.send_goal(goal, done_cb=self.done_cb, active_cb=self.active_cb, feedback_cb=self.feedback_cb)

        rospy.loginfo("Goal sent to move_base: x=%f, y=%f", goal.target_pose.pose.position.x, goal.target_pose.pose.position.y)

    def active_cb(self):
        rospy.loginfo("Goal pose is now being processed by the action server.")

    def feedback_cb(self, feedback):
        rospy.loginfo("Current location: x=%.2f, y=%.2f", feedback.base_position.pose.position.x, feedback.base_position.pose.position.y)

    def done_cb(self, status, result):
        if status == 3:
            rospy.loginfo("Goal reached")
        elif status in [2, 8]:
            rospy.loginfo("Goal cancelled or rejected by action server")
        elif status == 4:
            rospy.loginfo("Goal aborted by the action server")
        elif status == 1:
            rospy.loginfo("Goal is pending")
        elif status == 0:
            rospy.loginfo("Goal is waiting to be processed")


if __name__ == '__main__':
    try:
        goal_pose_action_client = GoalPoseActionClient()
        rospy.spin()
    except rospy.ROSInterruptException:
        rospy.loginfo("Goal pose action client node terminated.")