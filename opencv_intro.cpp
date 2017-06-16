#include <ros/ros.h>
#include <opencv/cv.h>
#include <opencv/highgui.h>
#include <cv_bridge/cv_bridge.h>
using namespace cv;
int main(int argc, char **argv)
{
// Ros initialization
	ros::init(argc, argv, "opencv_intro");
// Initialize a buffer image
	Mat display = Mat::zeros(500, 500, CV_8UC3);
// Draw a line
	line(display, Point(250, 250), Point(350, 350), CV_RGB(255, 0, 0), 2, CV_AA);
	circle(display, Point(350, 350), 4, CV_RGB(255, 255, 0), 2, CV_AA);
// Counter
	int nCount = 0;
// main loop
	while(ros::ok()) {
// draw the images
		imshow("ROS-OpenCV Preview", display);
// wait a user message
		int nKey = waitKey(30) % 255;
		if(nKey == 27) {
// escape
			break;
		}
		else if(nKey == ' ') {
			printf("Count = %d\n", nCount++);
		}
		else {
		}
	}	
	return 0;
}
