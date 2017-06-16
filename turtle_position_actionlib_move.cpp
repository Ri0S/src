#include <ros/ros.h>
#include <turtlebot_actions/TurtlebotMoveAction.h>
#include <actionlib/client/simple_action_client.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#define toRadian(degree) ((degree) * (M_PI / 180.))
typedef struct pos{
        double x;
        double y;
};
int main(int argc, char **argv)	{
	printf("asdf");
	ros::init(argc, argv, "turtle_position_move");
	
// 파라미터 받아오기
	pos position[11];
	FILE *f;
	f = fopen("/home/turtle/move.txt", "r");
	position[0].x = 0;
	position[0].y = 0;

	for(int i = 1; i < 8; i++)
		fscanf(f, "%lf %lf", &(position[i].x), &(position[i].y));
	for(int i = 0; i < 6; i++)
		printf("%lf %lf\n", position[i].x, position[i].y);
	actionlib::SimpleActionClient<turtlebot_actions::TurtlebotMoveAction> client("turtlebot_move");
// 서버가 준비될 때까지 대기
	double before2[7] = {0, 0.235, -0.235, 0.235, 0.235, -0, 0.235};
	double before = 0;
	client.waitForServer();
	for(int i = 1; i < 7; i++){
//		client.waitForServer();
// 이동을 지시!
		turtlebot_actions::TurtlebotMoveGoal goal;
		goal.forward_distance = 0;
		goal.turn_distance = atan2(position[i].y - position[i-1].y, position[i].x - position[i-1].x) - before2[i] - before;
		before = before + goal.turn_distance + before2[i];
		printf("num%d. current: %0.2lf dis: %0.2lf, turn: %0.2lf ", i, before, goal.forward_distance, goal.turn_distance);
		if(client.sendGoalAndWait(goal, ros::Duration(50), ros::Duration(50)) == actionlib::SimpleClientGoalState::SUCCEEDED) {
			printf("Call to action server succeeded!\n");
		} else {
			printf("Call to action server failed!\n");
		}
		goal.turn_distance = 0;
                goal.forward_distance = sqrt((position[i].x - position[i-1].x) * (position[i].x - position[i-1].x) + (position[i].y - position[i-1].y) * (position[i].y - position[i-1].y));
		printf("num%d. current: %0.2lf dis: %0.2lf, turn: %0.2lf ", i, before, goal.forward_distance, goal.turn_distance);
		ros::Duration(1.0).sleep();
		if(client.sendGoalAndWait(goal, ros::Duration(50), ros::Duration(50)) == actionlib::SimpleClientGoalState::SUCCEEDED) {
                        printf("Call to action server succeeded!\n");
                } else {
                        printf("Call to action server failed!\n");
                }
	}
	return 0;
}
