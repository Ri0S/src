#include <ros/ros.h>
#include <sensor_msgs/LaserScan.h>
#include <geometry_msgs/Twist.h>
#include <iostream>
#include <std_msgs/Int32.h>
#include <sys/time.h>
#include <stdio.h>

using namespace std;

ros::Publisher pub;

template<typename T>
double isnan(T value){
	if(value != value)
		return 10;
	else
		return value;
}
int status = 0;
void cb(const sensor_msgs::LaserScan& msg){
	geometry_msgs::Twist aa;
	int count = 0;
	for(int i = 196; i < 445; i++){
		if(msg.ranges[i] < 1)
			count++;
	}
	if(count > 0){
		aa.linear.x = 0;
		aa.angular.z = 0.1;
		struct timeval stop, start;

		gettimeofday(&start, NULL);
		
		while(1){
			pub.publish(aa);
			gettimeofday(&stop, NULL);
			if(stop.tv_usec - start.tv_usec > 15000)
				break;
		}
		status = 1;
	}
	else{
		if(status == 1){
			aa.linear.x = 0;
			aa.angular.z = 0;
			pub.publish(aa);
			status = 0;
		}
	}
	count = 0;
}
int main(int argc, char **argv){
	ros::init(argc, argv, "obstacle");
	ros::NodeHandle nh;

	ros::Subscriber sub = nh.subscribe("/scan", 10, &cb);
	pub = nh.advertise<geometry_msgs::Twist>("cmd_vel_mux/input/teleop", 1000);
	ros::spin();

	return 0;
}
