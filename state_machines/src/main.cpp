/**
author Sandra Devin

Main class of the state_machines manager.

The state machines manager keeps trace of the activity of each agent.

**/

#include <state_machines/robot_sm.h>
#include <state_machines/human_sm.h>
#include "supervisor_msgs/GetInfo.h"
#include "supervisor_msgs/AgentActivity.h"
#include "supervisor_msgs/Focus.h"
#include "supervisor_msgs/HumanAction.h"
#include "supervisor_msgs/Knowledge.h"
#include "supervisor_msgs/ActionMSList.h"

string robotState;
string robotName;
ros::NodeHandle* node;

vector<string> objectsRobot_;
double weightRobot_ = 0.0;
bool actionPerformed = false;
supervisor_msgs::Action performedAction;
string agentAction;
vector<string> allAgents;
vector<string> partners;

vector<supervisor_msgs::AgentKnowledge> knowledge;
vector<supervisor_msgs::ActionMS> actions;

/*
Main function of the robot state machine
*/
void robotStateMachine(){
  	ros::Rate loop_rate(30);
	robotState = "IDLE";
    RobotSM rsm(node);

    string topicName = "supervisor/activity_state/";
    topicName = topicName + robotName;
    ros::Publisher robot_pub = node->advertise<supervisor_msgs::AgentActivity>(topicName, 1000);
	
	while(true){
        rsm.knowledge_ = knowledge;
        rsm.actions_ = actions;
        supervisor_msgs::AgentActivity msg;
        vector<string> objects;
        double weight = 0.0;
        string previousState = robotState;
		if(robotState == "IDLE"){
            robotState = rsm.idleState(partners);
		}else if(robotState == "ACTING"){
            robotState = rsm.actingState();
            objects = objectsRobot_;
            weight = weightRobot_;
		}else if(robotState == "WAITING"){
			robotState = rsm.waitingState();
		}else{
			ROS_ERROR("[state_machines] Wrong robot state");	
        }

        //we publish the robot state
        msg.activityState = previousState;
        msg.unexpected = false;
        msg.weight = weight;
        msg.objects = objects;
        robot_pub.publish(msg);
  		loop_rate.sleep();
	}

}

/*
Main function of the human state machine
*/
void humanStateMachine(string human_name){
  	ros::Rate loop_rate(30);
    string humanState = "IDLE";
    string topicName = "supervisor/activity_state/";
    topicName = topicName + human_name;
    ros::Publisher human_pub = node->advertise<supervisor_msgs::AgentActivity>(topicName, 1000);
    HumanSM* hsm = new HumanSM(node, human_name);

	
    while(true){
        //check if no action from the agent
        if(actionPerformed){
            if(agentAction == human_name){
                hsm->humanActs_ = true;
                hsm->PerformedAction_ = performedAction;
                actionPerformed = false;
                humanState == "ACTING";
            }
        }
        supervisor_msgs::AgentActivity msg;
        vector<string> objects;
        double weight = 0.0;
        bool unexpected = false;
        string previousState = humanState;
		if(humanState == "IDLE"){
			humanState = hsm->idleState();
		}else if(humanState == "ACTING"){
            humanState = hsm->actingState(&objects, &unexpected);
            weight = 0.8;
		}else if(humanState == "WAITING"){
			humanState = hsm->waitingState();
		}else if(humanState == "SHOULDACT"){
            humanState = hsm->shouldActState(robotState, &objects);
            weight = 0.8;
		}else if(humanState == "ABSENT"){
			humanState = hsm->absentState();
            unexpected = true;
		}else{
			ROS_ERROR("[state_machines] Wrong human state");	
        }

        //we publish the robot state
        msg.activityState = previousState;
        msg.unexpected = unexpected;
        msg.weight = weight;
        msg.objects = objects;
        human_pub.publish(msg);
  		loop_rate.sleep();
	}

}

void focusCallback(const supervisor_msgs::Focus::ConstPtr& msg){

    objectsRobot_ = msg->objects;
    weightRobot_ = msg->weight;
}

void knowledgeCallback(const supervisor_msgs::Knowledge::ConstPtr& msg){

    knowledge = msg->agentsKnowledge;
}

void actionsCallback(const supervisor_msgs::ActionMSList::ConstPtr& msg){

    actions = msg->actionsList;
}

void partnersCallback(const supervisor_msgs::AgentList::ConstPtr& msg){

    partners = msg->agents;
}


/*
Service call to tell that a human performed an action
*/
bool humanAction(supervisor_msgs::HumanAction::Request  &req, supervisor_msgs::HumanAction::Response &res){

    actionPerformed = true;
    performedAction = req.action;
    agentAction = req.agent;

    return true;
}

int main (int argc, char **argv)
{
  ros::init(argc, argv, "state_machines");
  ros::NodeHandle node_;
  node = &node_;

  ROS_INFO("[state_machines] Init state_machines");

  ros::ServiceServer service = node_.advertiseService("state_machines/human_action", humanAction);
  ros::Subscriber sub = node_.subscribe("action_executor/focus", 1000, focusCallback);
  ros::Subscriber subKnow = node_.subscribe("mental_states/agents_knowledge", 1000, knowledgeCallback);
  ros::Subscriber subAct = node_.subscribe("mental_states/actions", 1000, actionsCallback);
  ros::Subscriber subPartners = node_.subscribe("plan_elaboration/partners", 1000, partnersCallback);

  node_.getParam("/robot/name", robotName);
  ros::service::waitForService("mental_state/get_info", -1);
  ros::ServiceClient client = node->serviceClient<supervisor_msgs::GetInfo>("mental_state/get_info");
  supervisor_msgs::GetInfo srv;
  srv.request.info = "AGENTS";
  if (client.call(srv)){
     allAgents = srv.response.agents;
  }else{
    ROS_ERROR("[state_machines] Failed to call service mental_state/get_all_agents");
  }

  ROS_INFO("[state_machines] state_machines ready");

  boost::thread_group g;
  for(vector<string>::iterator it = allAgents.begin(); it != allAgents.end(); it++){
    if(*it == robotName){
        g.create_thread(robotStateMachine);
    }else{
        g.create_thread(boost::bind(humanStateMachine, *it));
	}
  }

  ros::spin();
  return 0;
}
