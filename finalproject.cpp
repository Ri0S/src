#include <ros/ros.h>
#include <turtlebot_actions/TurtlebotMoveAction.h>
#include <actionlib/client/simple_action_client.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define toRadian(degree) ((degree) * (M_PI / 180.))
int main(int argc, char** argv)
{
	ros::init(argc, argv, "finalproject");
	srand(time(0));
	
	while(1)
	{
		// 파라미터 받아오기
		double rotation = (double)(rand() % 180);
		double translation = (double)((rand() % 30)/5.);
		// SimpleActionClient 객체 생성
		// 서버가 준비될 때까지 대기
		actionlib::SimpleActionClient<turtlebot_actions::TurtlebotMoveAction> client("turtlebot_move");
		client.waitForServer();
		// 이동을 지시!
		turtlebot_actions::TurtlebotMoveGoal goal;
		goal.turn_distance = toRadian(rotation);
		goal.forward_distance = translation;
		if(client.sendGoalAndWait(goal, ros::Duration(50.0), ros::Duration(50.0)) == actionlib::SimpleClientGoalState::SUCCEEDED) {
			printf("Call to action server succeeded!\n");
		} 
		else {
			printf("Call to action server failed!\n");
		}
		printf("one more tim\n");
	}	
	return 0;
}
