#include <ros/ros.h>
#include <knu_ros_lecture/srvKnuRosLecture.h>
#include <cstdlib>

int main(int argc, char **argv){
	ros::init(argc, argv, "client_srv_tutorial");
	if(argc != 3){
		ROS_INFO("cmd : rosrun knu_Ros_lecture client_srv_tutorial arg0 arg1");
		ROS_INFO("arg0: integer number ,arg1: integer number");

		return 1;
	}

	ros::NodeHandle nh;	
	ros::ServiceClient client = nh.serviceClient<knu_ros_lecture::srvKnuRosLecture>("knu_ros_lecture_srv_tutorial");

	knu_ros_lecture::srvKnuRosLecture srv;
	srv.request.a = atoll(argv[1]);
	srv.request.b = atoll(argv[2]);

	if(client.call(srv)){
		ROS_INFO("send srv, srv.Request.a and b: %ld, %ld", (long int)srv.request.a, (long int)srv.request.b);
		ROS_INFO("recieve srv, srv.Response.result: %ld", (long int)srv.response.result);
	}
	else{
		ROS_ERROR("Failed to call service knu_ros_lecture_srv_tutorial");
		return 1;
	}

	ROS_INFO("Succeed to call service knu_Ros_lecture_srv_tutorial");

	return 1;
}
