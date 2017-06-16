#include <ros/ros.h>
#include <turtlesim/Pose.h>
#include <iomanip>
#include <geometry_msgs/Twist.h>
#include <stdlib.h>
#include <iostream>
#include <unistd.h>
#include <sys/types.h>

using namespace std;
int fd[2];
int condition = 0;
int x = 5;
int y = 5;
int q = 1;
double sr = 3.14159265358/4;
void poseMessageReceived(const turtlesim::Pose& msg){
//	ROS_INFO_STREAM(std::setprecision(2) << std::fixed <<
//		"position = (" << msg.x << "," << msg.y << ")" <<
//		" direction = " << msg.theta);
	if(condition == 0 && msg.x > x+1.95 && msg.x < x+2.05 && msg.y > y-1.95 && msg.y < y + 2.05){
		condition = 1;
		char str[2] = {'0'+condition, 0};
		cout << "contidion" << str << endl;
		write(fd[1], str, 2);
		x = msg.x;
		y = msg.y;
	}
}

int main(int argc, char **argv){
	pipe(fd);

	ros::init(argc, argv, "turtlesim_pose");
	ros::NodeHandle nh;

	ros::Subscriber sub = nh.subscribe("turtle1/pose", 1000, &poseMessageReceived);
	ros::Publisher asdf = nh.advertise<geometry_msgs::Twist>("turtle1/cmd_vel", 1000);
	ros::Rate rate(2);
	geometry_msgs::Twist msg;
	msg.linear.x = 2;
	msg.angular.z = 0;
	asdf.publish(msg);
	rate.sleep();
	asdf.publish(msg);
	rate.sleep();
	write(fd[1], "0", 2);
		
	int pid;
	if((pid = fork()) == 0){
		ros::NodeHandle nh2;
		ros::Publisher pub = nh2.advertise<geometry_msgs::Twist>("turtle1/cmd_vel", 1000);
		//ros::Rate rate(2);
		geometry_msgs::Twist msg;
		msg.linear.x = 2;
		msg.angular.z = 0;
		//asdf.publish(msg);
		pub.publish(msg);
		rate.sleep();
		pub.publish(msg);
		//asdf.publish(msg);
		rate.sleep();
		while(1){
			char con[2];
			read(fd[0], con, 2);
			cout << con[0] << endl;
			sleep(1);
			switch(con[0] - '0'){
				case 0:
					cout << condition << endl;
					msg.linear.x = 0;
					msg.angular.z = sr;
					pub.publish(msg);
					rate.sleep();
					sleep(1);
					msg.linear.x = 10;
					msg.angular.z = 0;
					pub.publish(msg);
					rate.sleep();
					sleep(1);
					break;
				case 1:
					msg.linear.x = 0;
					msg.angular.z = -3*sr;
					pub.publish(msg);
					rate.sleep();
					sleep(1);
					msg.linear.x = 10;
					msg.angular.z = 0;
					pub.publish(msg);
					rate.sleep();
					sleep(1);
					break;
				case 2:
					break;
				case 3:
					break;
				case 4:
					break;
				case 5:
					break;
				case 6:
					break;
				case 7:
					break;
				case 8:
					break;
			}
		}
	}
	cout << pid << endl;
	close(fd[0]);
	ros::spin();

	return 0;
}
