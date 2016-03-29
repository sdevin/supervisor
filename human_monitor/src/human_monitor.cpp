/**
author Sandra Devin

**/

#include <human_monitor/human_monitor.h>

/*
Function to call when a human picks an object
	@agent: the human who does the action
	@object: the object picked
*/
void HumanMonitor::humanPick(string agent, string object){
	
	ROS_INFO("[human_monitor] %s has picked %s", agent.c_str(), object.c_str());
	
	ros::NodeHandle node;
    ros::ServiceClient action_state = node.serviceClient<supervisor_msgs::ChangeState>("mental_state/change_state");
	ros::ServiceClient put_in_hand = node.serviceClient<toaster_msgs::PutInHand>("pdg/put_in_hand");

	//put the object in the hand of the agent
	string humanHand;
	node.getParam("/humanRightHand", humanHand);
	toaster_msgs::PutInHand srv_putInHand;
   srv_putInHand.request.objectId = object;
   srv_putInHand.request.agentId = agent;
   srv_putInHand.request.jointName = humanHand;
   if (!put_in_hand.call(srv_putInHand)){
   	 ROS_ERROR("Failed to call service pdg/put_in_hand");
 	}
 	
	//we create the corresponding action
	supervisor_msgs::Action action;
	action.name = "pick";
	action.parameters.push_back(object);
	action.actors.push_back(agent);

	//send the action to the mental state manager
    supervisor_msgs::ChangeState srv_astate;
    srv_astate.request.type = "action";
    srv_astate.request.action = action;
 	srv_astate.request.state = "DONE";
  	if (!action_state.call(srv_astate)){
     ROS_ERROR("Failed to call service mental_state/change_state");
 	}

}

/*
Function to call when a human place an object
	@agent: the human who does the action
	@object: the object placed
	@support: the support where the object is placed
*/
void HumanMonitor::humanPlace(string agent, string object, string support){
	
	ROS_INFO("[human_monitor] %s has placed %s on %s", agent.c_str(), object.c_str(), support.c_str());
	
	ros::NodeHandle node;
    ros::ServiceClient action_state = node.serviceClient<supervisor_msgs::ChangeState>("mental_state/change_state");
	ros::ServiceClient remove_from_hand = node.serviceClient<toaster_msgs::RemoveFromHand>("pdg/remove_from_hand");
	ros::ServiceClient set_entity_pose = node.serviceClient<toaster_msgs::SetEntityPose>("toaster_simu/set_entity_pose");

	//remove the object from the hand of the agent
	toaster_msgs::RemoveFromHand srv_rmFromHand;
   srv_rmFromHand.request.objectId = object;
   if (!remove_from_hand.call(srv_rmFromHand)){
   	 ROS_ERROR("Failed to call service pdg/remove_from_hand");
 	}

	//put the object on the placement
	double objectHeight, supportHeight;
	string objectHeightTopic = "/objectsHeight/bottom/";
	objectHeightTopic = objectHeightTopic + object;
	string supportHeightTopic = "/objectsHeight/top/";
	supportHeightTopic = supportHeightTopic + support;
	node.getParam(objectHeightTopic, objectHeight);
	node.getParam(supportHeightTopic, supportHeight);
	toaster_msgs::ObjectList objectList;
	double x,y,z;
   try{
       objectList  = *(ros::topic::waitForMessage<toaster_msgs::ObjectList>("pdg/objectList",ros::Duration(1)));
       for(vector<toaster_msgs::Object>::iterator it = objectList.objectList.begin(); it != objectList.objectList.end(); it++){
         if(it->meEntity.id == support){
            x = it->meEntity.positionX;
            y = it->meEntity.positionY;
            z = it->meEntity.positionZ;
            break;
         }
       }
       z = z + objectHeight + supportHeight;
       toaster_msgs::SetEntityPose srv_setPose;
       srv_setPose.request.id = object;
       srv_setPose.request.type = "object";
       srv_setPose.request.x = x;
       srv_setPose.request.y = y;
       srv_setPose.request.z = z;
       srv_setPose.request.roll = 0.0;
       srv_setPose.request.pitch = 0.0;
       srv_setPose.request.yaw = 0.0;
       if (!set_entity_pose.call(srv_setPose)){
      	 ROS_ERROR("Failed to call service toaster_simu/set_entity_pose");
    	 }
   }
   catch(const std::exception & e){
       ROS_WARN("Failed to read %s pose from toaster", support.c_str());
   }
	

	//we create the corresponding action
	supervisor_msgs::Action action;
	action.name = "place";
	action.parameters.push_back(object);
	action.parameters.push_back(support);
	action.actors.push_back(agent);

	//send the action to the mental state manager
    supervisor_msgs::ChangeState srv_astate;
    srv_astate.request.type = "action";
 	srv_astate.request.action = action;
 	srv_astate.request.state = "DONE";
  	if (!action_state.call(srv_astate)){
     ROS_ERROR("Failed to call service mental_state/change_state");
 	}

	//we also consider a pick and place action
	supervisor_msgs::Action action2;
	action2.name = "pickandplace";
	action2.parameters.push_back(object);
	action2.parameters.push_back(support);
	action2.actors.push_back(agent);
	
	//send the action to the mental state manager
 	srv_astate.request.action = action2;
 	srv_astate.request.state = "DONE";
  	if (!action_state.call(srv_astate)){
     ROS_ERROR("Failed to call service mental_state/change_state");
 	}
}

/*
Function to call when a human drop an object
	@agent: the human who does the action
	@object: the object droped
	@support: the container where the object is droped
*/
void HumanMonitor::humanDrop(string agent, string object, string container){
	
	ROS_INFO("[human_monitor] %s has droped %s in %s", agent.c_str(), object.c_str(), container.c_str());
	
	ros::NodeHandle node;
    ros::ServiceClient action_state = node.serviceClient<supervisor_msgs::ChangeState>("mental_state/change_state");
	ros::ServiceClient remove_from_hand = node.serviceClient<toaster_msgs::RemoveFromHand>("pdg/remove_from_hand");
	ros::ServiceClient set_entity_pose = node.serviceClient<toaster_msgs::SetEntityPose>("toaster_simu/set_entity_pose");

	//remove the object from the hand of the agent
	toaster_msgs::RemoveFromHand srv_rmFromHand;
   srv_rmFromHand.request.objectId = object;
   if (!remove_from_hand.call(srv_rmFromHand)){
   	 ROS_ERROR("Failed to call service pdg/remove_from_hand");
 	}

	//put the object in the container
	toaster_msgs::ObjectList objectList;
	double x,y,z;
   try{
       objectList  = *(ros::topic::waitForMessage<toaster_msgs::ObjectList>("pdg/objectList",ros::Duration(1)));
       for(vector<toaster_msgs::Object>::iterator it = objectList.objectList.begin(); it != objectList.objectList.end(); it++){
         if(it->meEntity.id == container){
            x = it->meEntity.positionX;
            y = it->meEntity.positionY;
            z = it->meEntity.positionZ;
            break;
         }
       }
       toaster_msgs::SetEntityPose srv_setPose;
       srv_setPose.request.id = object;
       srv_setPose.request.type = "object";
       srv_setPose.request.x = x;
       srv_setPose.request.y = y;
       srv_setPose.request.z = z;
       srv_setPose.request.roll = 0.0;
       srv_setPose.request.pitch = 0.0;
       srv_setPose.request.yaw = 0.0;
       if (!set_entity_pose.call(srv_setPose)){
      	 ROS_ERROR("Failed to call service toaster_simu/set_entity_pose");
    	 }
   }
   catch(const std::exception & e){
       ROS_WARN("Failed to read %s pose from toaster", container.c_str());
   }

	//we create the corresponding action
	supervisor_msgs::Action action;
	action.name = "drop";
	action.parameters.push_back(object);
	action.parameters.push_back(container);
	action.actors.push_back(agent);

	//send the action to the mental state manager
    supervisor_msgs::ChangeState srv_astate;
    srv_astate.request.type = "action";
 	srv_astate.request.action = action;
 	srv_astate.request.state = "DONE";
  	if (!action_state.call(srv_astate)){
     ROS_ERROR("Failed to call service mental_state/change_state");
 	}

	//we also consider a pick and drop action
	supervisor_msgs::Action action2;
	action2.name = "pickanddrop";
	action2.parameters.push_back(object);
	action2.parameters.push_back(container);
	action2.actors.push_back(agent);
	
	//send the action to the mental state manager
 	srv_astate.request.action = action2;
 	srv_astate.request.state = "DONE";
  	if (!action_state.call(srv_astate)){
     ROS_ERROR("Failed to call service mental_state/change_state");
 	}
}

