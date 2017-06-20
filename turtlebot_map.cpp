#include <ros/ros.h>
#include <opencv/cv.h>
#include <iomanip>
#include <opencv/highgui.h>
#include <cv_bridge/cv_bridge.h>
#include <nav_msgs/OccupancyGrid.h>
#include <nav_msgs/MapMetaData.h>
#include <ros/callback_queue.h>
#include <ros/duration.h>

using namespace cv;

Mat display;

void occupancyGrid_Callback(const nav_msgs::OccupancyGrid& msg){
	printf("%d %d", msg.info.width, msg.info.height);
	display = Mat(msg.info.width, msg.info.height, CV_8UC1, cv::Scalar());

	for(int i = 0; i < msg.info.height; i++){
		for(int j = 0; j < msg.info.width; j++){
			if(msg.data[i * msg.info.width + j] == 0)
				display.at<Vec3b>(j, i) = Vec3b(80, 80, 80);
			else if(msg.data[i * msg.info.width + j] > 0)
				display.at<Vec3b>(j, i) = Vec3b(255, 255, 255);
		}
	}	

	imshow("Map", display);
}

int main(int argc, char **argv){
	ros::init(argc, argv, "turtlebot_map");
	ros::NodeHandle nh;

	ros::Subscriber sub = nh.subscribe("map", 131072, occupancyGrid_Callback);
	
	display = cv::Mat(1, 1, CV_8UC1, cv::Scalar());


	while(ros::ok()){
		ros::getGlobalCallbackQueue()->callAvailable(ros::WallDuration(0.1));

		imshow("Map", display);
		waitKey(30);
	}

	return 0;
}
