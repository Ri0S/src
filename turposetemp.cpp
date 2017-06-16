#include <ros/ros.h>
#include <turtlesim/Pose.h>
#include <iomanip>
#include <stdlib.h>
#include <geometry_msgs/Twist.h>
#include <iostream>
#include <signal.h>
#include <knu_ros_lecture/srvKnuRosLecture.h>

using namespace std;
double x = 5.544445;
double y = 5.544445;

int q = 1;
int condition = 0;

ros::ServiceClient client;
ros::ServiceClient reset;

void poseMessageReceived(const turtlesim::Pose& msg){
//	reset = nh.serviceClient("reset");
	knu_ros_lecture::srvKnuRosLecture srv;
	ROS_INFO_STREAM(std::setprecision(2) << std::fixed <<
		"position = (" << msg.x << "," << msg.y << ")" <<
		" direction = " << msg.theta);
	switch(condition){
		case 0:
			x = 5.544445;
			y = 5.544445;
			if(condition !=9)
				system("rossevice call reset");
			if(msg.x > x)
				condition = 9;
			else
				condition = 1;
			sleep(1);
			break;
		case 1:
			if(msg.x > x+1.95){
                              	srv.request.a = 0;
				srv.request.b = 0;
				client.call(srv);
				srv.request.a = 0;
				srv.request.b = 2.3561944;
				client.call(srv);
				sleep(2);

				x = msg.x;
				y = msg.y;

				condition = 2;
				q = 1;
			}
			else{
				srv.request.a = 1;
				srv.request.b = 0;
				client.call(srv);
			}
			break;
		case 2:
			if(msg.x < x-1.95){
                                srv.request.a = 0;
                                srv.request.b = 0;
                                client.call(srv);
                                srv.request.a = 0;
                                srv.request.b = -2.3561944;
                                client.call(srv);
                                sleep(2);
	
                                x = msg.x;
                                y = msg.y;

                                condition = 3;
                                q = 1;
			}
			else{
				srv.request.a = 1;
				srv.request.b = 0;
				client.call(srv);
			}		
			break;
		
                case 3:
                        if(msg.x > x+1.95){
				        srv.request.a = 0;
                                srv.request.b = 0;
                                client.call(srv);
                                srv.request.a = 0;
                                srv.request.b = 2.3561944;
                                client.call(srv);
                                sleep(2);

                                x = msg.x;
                                y = msg.y;

                                condition = 4;
                                q = 1;
                        }
                        else{
                                srv.request.a = 1;
                                srv.request.b = 0;
                                client.call(srv);
                        }
                        break;
               
                case 4:
                        if(msg.x < x-0.95){
			        srv.request.a = 0;
                                srv.request.b = 0;
                                client.call(srv);
                                srv.request.a = 0;
                                srv.request.b = 1.57079632679;
                                client.call(srv);
                                sleep(2);

                                x = msg.x;
                                y = msg.y;

                                condition = 5;
                                q = 1;
                        }
                        else{
                                srv.request.a = 1;
                                srv.request.b = 0;
                                client.call(srv);
                        }
                        break;
                
                case 5:
                        if(msg.x < x-0.95){
                                srv.request.a = 0;
                                srv.request.b = 0;
                                client.call(srv);
                                srv.request.a = 0;
                                srv.request.b = 0.785298163395;
                                client.call(srv);
                         
                                x = msg.x;
                                y = msg.y;

                                condition = 6;
                                q = 1;
                                sleep(2);
                        }
                        else{
                                srv.request.a = 1;
                                srv.request.b = 0;
                                client.call(srv);
                        }
		case 6:
                        if(msg.y < y-1.95){
                                srv.request.a = 0;
                                srv.request.b = 0;
                                client.call(srv);
                                srv.request.a = 0;
                                srv.request.b = 2.3561944;
                                client.call(srv);
                                sleep(2); 
                         
                                x = msg.x;
                                y = msg.y;

                                condition = 7;
                                q = 1;
                        }
                        else{
                                srv.request.a = 1;
                                srv.request.b = 0;
                                client.call(srv);
                        }
                        break;
		case 7:
                        if(msg.x > x+1.95){
                                srv.request.a = 0;
                                srv.request.b = 0;
                                client.call(srv);
                                srv.request.a = 0;
                                srv.request.b = -2.3561944;
                                client.call(srv);
                                sleep(2); 
                         
                                x = msg.x;
                                y = msg.y;

                                condition = 8;
                                q = 1;
                        }
                        else{
                                srv.request.a = 1;
                                srv.request.b = 0;
                                client.call(srv);
                        }
                        break;
		case 8:
			if(msg.y < y-1.95){
				srv.request.a = 0;
				srv.request.b = 0;
				client.call(srv);
				condition = 0;
			}
			else{
				srv.request.a = 1;
				srv.request.b = 0;
				client.call(srv);
			}
            }


}

int main(int argc, char ** argv){
	ros::init(argc, argv, "turtlesim_pose");
	ros::NodeHandle nh;
	ros::Subscriber sub = nh.subscribe("turtle1/pose", 1000, &poseMessageReceived);
	client = nh.serviceClient<knu_ros_lecture::srvKnuRosLecture>("knu_ros_lecture_srv_tutorial");

	ros::spin();

	return 0;
}
