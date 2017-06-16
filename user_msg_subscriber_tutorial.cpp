#include <ros/ros.h>
#include <knu_ros_lecture/knuRosLecture.h>

void msgCallback(const knu_ros_lecture::knuRosLecture &msg){
	ROS_INFO("Received Msg : %s / %.2lf / %.2f / %d", msg.stringData.c_str(), msg.float64Data, msg.float32Data, msg.int32Data);
}

int main(int argc, char **argv){
	ros::init(argc, argv, "user_msg_subscriber_tutorial");
	ros::NodeHandle nh;

	ros::Subscriber sub = nh.subscribe("user_msg_tutorial", 10, &msgCallback);
	ros::spin();

	return 0;
}
