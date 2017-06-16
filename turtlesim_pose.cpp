#include <ros/ros.h>
#include <turtlesim/Pose.h>
#include <nav_msgs/Odometry.h>
#include <iomanip>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <opencv/cv.h>
#include <opencv/highgui.h>
#include <cv_bridge/cv_bridge.h>

using namespace cv;

typedef struct pos{
	double x;
	double y;
};

pos position[11];
Mat display;

int condition = 1;
void poseMessageReceived(const nav_msgs::Odometry& msg){
	printf("%2.2lf, %2.2lf\n", msg.pose.pose.position.x, msg.pose.pose.position.y);
	if( (msg.pose.pose.position.x > position[condition].x-0.2) &&
		(msg.pose.pose.position.x < position[condition].x + 0.2) &&
		(msg.pose.pose.position.y > position[condition].y-0.2) &&
		(msg.pose.pose.position.y < position[condition].y + 0.2)){
		
		line(display, Point(250 + (position[condition-1].x)*200, 250 - (position[condition-1].y)*200), Point(250 + (position[condition].x)*200, 250 - (position[condition].y)*200), CV_RGB(255, 0, 255), 2, CV_AA);
		circle(display, Point(250 + (position[condition].x)*200, 250 - (position[condition].y)*200), 7, CV_RGB(255, 255, 0), 2, CV_AA);
		condition++;
	}
	int nCount = 0;

	imshow("ROS_OpenCV Preview", display);
	int nKey = waitKey(30) % 255;
	if(nKey == 27){
		exit(0);
	}
	else if(nKey == ' '){
		printf("Count = %d\n", nCount++);
	}
}

int main(int argc, char **argv){
	int i = 0;
	FILE *f;
	f = fopen("/home/turtle/move.txt", "r");
	position[0].x = 0;
	position[0].y = 0;
	for(i = 1; i < 8; i++){
		fscanf(f, "%lf %lf", &(position[i].x), &(position[i].y));
	}
	ros::init(argc, argv, "turtlesim_pose");
	ros::NodeHandle nh;

	ros::Subscriber sub = nh.subscribe("odom", 1000, &poseMessageReceived);
	
	display = Mat::zeros(500, 500, CV_8UC3);
	
	line(display, Point(250, 0), Point(250, 500), CV_RGB(255, 255, 255), 2, CV_AA);
	line(display, Point(0, 250), Point(500, 250), CV_RGB(255, 255, 255), 2, CV_AA);
	
	ros::spin();
	return 0;
}
