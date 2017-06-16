#include <stdlib.h>
#include <ros/ros.h>
#include <geometry_msgs/Twist.h>

int main(int argc, char **argv){
	ros::init(argc, argv, "asdf");
	ros::NodeHandle nh;

	ros::Publisher pub = nh.advertise<geometry_msgs::Twist>("cmd_vel_mux/input/teleop", 1000);
	geometry_msgs::Twist msg;
	msg.linear.x = 0;
	msg.angular.z = 0;
	ros::Rate rate(2);
	while(ros::ok()){
		ROS_INFO_STREAM("asdf");
		pub.publish(msg);
		rate.sleep();
	}
	return 0;
}
		
