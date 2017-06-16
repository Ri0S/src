#include <ros/ros.h>
#include <knu_ros_lecture/srvKnuRosLecture.h>
#include <geometry_msgs/Twist.h>
#include <stdlib.h>
#include <iostream>

using namespace std;

ros::Publisher pub;

bool publ(knu_ros_lecture::srvKnuRosLecture::Request &req, knu_ros_lecture::srvKnuRosLecture::Response &res){
	geometry_msgs::Twist msg;
	
	msg.linear.x = req.a;
	msg.angular.z = req.b;
	pub.publish(msg);
	pub.publish(msg);
}

int main(int argc, char **argv){
	ros::init(argc, argv, "server_srv_tutorial");
	ros::NodeHandle nh;
	ros::ServiceServer server = nh.advertiseService("knu_ros_lecture_srv_tutorial", publ);
	pub = nh.advertise<geometry_msgs::Twist>("turtle1/cmd_vel", 1000);
	ROS_INFO("ready srv server:");
	ros::spin();

	return 0;
}
