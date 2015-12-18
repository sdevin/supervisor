#ifndef ACTIONEXECUTOR_H
#define ACTIONEXECUTOR_H

#include "supervisor_msgs/ActionExecutorAction.h"
#include "supervisor_msgs/ActionState.h"
#include "action_executor/virtual_action.h"
#include "action_executor/Actions/action_pkg.h"

#include <actionlib/server/simple_action_server.h>
#include <actionlib/client/terminal_state.h>

#include <iostream>
#include <string>
#include <vector>
#include <ros/ros.h>


typedef actionlib::SimpleActionServer<supervisor_msgs::ActionExecutorAction> Server;
using namespace std;

class ActionExecutor{
public:
	ActionExecutor(string name);
protected:
	ros::NodeHandle node_;
	supervisor_msgs::ActionExecutorFeedback feedback_;
	supervisor_msgs::ActionExecutorResult result_;
	Server action_server_;

private:
	void execute(const supervisor_msgs::ActionExecutorGoalConstPtr& goal);
	VirtualAction* initializeAction(supervisor_msgs::Action action);


};

#endif // ACTIONEXECUTOR_H

