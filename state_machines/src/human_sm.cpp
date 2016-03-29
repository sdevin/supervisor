/**
author Sandra Devin

State machine for the robot
**/

#include <state_machines/human_sm.h>



HumanSM::HumanSM(string humanName)
 {
	humanName_ = humanName;
	node_.getParam("/robot/name", robotName_);
	node_.getParam("/timeNoAction", timeToWait_);
  	node_.getParam("/simu", simu_);
	timerStarted_ = false;
}

/*
State where the human is IDLE
*/
string HumanSM::idleState(){

	//TODO if human ACTING
	//TODO if human PRESENT
	//We look if the human thinks he has an action to do
    ros::ServiceClient client = node_.serviceClient<supervisor_msgs::GetInfo>("mental_state/get_info");
  	ros::ServiceClient client_db = node_.serviceClient<supervisor_msgs::SolveDivergentBelief>("mental_state/solve_divergent_belief");
    supervisor_msgs::GetInfo srv_info;
    supervisor_msgs::SolveDivergentBelief srv_db;
    srv_info.request.info ="ACTIONS_TODO";
    srv_info.request.agent = humanName_;
    srv_info.request.actor = humanName_;
	srv_db.request.agent = humanName_;
    if (client.call(srv_info)){
     if(srv_info.response.state == "READY"){//the human thinks he has an action to do
        //we look if the robot also thinks the human should do the action
        srv_info.request.info ="ACTION_STATE";
        srv_info.request.agent = robotName_;
        srv_info.request.action = srv_info.response.action;
        if (client.call(srv_info)){
         if(srv_info.response.state == "READY"){//the state is the same in the robot knowledge, the human SOULD ACT
			ROS_INFO("[state_machines] %s goes to SHOULD ACT", humanName_.c_str());
			return "SHOULDACT";
		 }else{//it is necessary to solve the divergent belief
            srv_db.request.action = srv_info.response.action;
			if (!client_db.call(srv_db)){
				ROS_ERROR("[state_machines] Failed to call service mental_state/solve_divergent_belief");
			}
		  }
		}else{
	 	 ROS_ERROR("[state_machines] Failed to call service mental_state/get_action_state");
		}
     }else if(srv_info.response.state == "NEEDED"){//the human thinks he has an action to do but no possible
        //we look if the robot also thinks the human should do the action and that the action is not possible
        srv_info.request.info ="ACTION_STATE";
        srv_info.request.agent = robotName_;
        srv_info.request.action = srv_info.response.action;
        if (client.call(srv_info)){
         if(srv_info.response.state == "NEEDED"){//the state is the same in the robot knowledge, the human has to WAIT
			ROS_INFO("[state_machines] %s goes to WAITING", humanName_.c_str());
			return "WAITING";
         }else if(srv_info.response.state == "READY"){//the robot thinks the human can act, it is necessary to solve the divergent belief
            srv_db.request.action = srv_info.response.action;
			if (!client_db.call(srv_db)){
				ROS_ERROR("[state_machines] Failed to call service mental_state/solve_divergent_belief");
			}
		  }
		}else{
         ROS_ERROR("[state_machines] Failed to call service mental_state/get_info");
		}
	 }else{//the human thinks he has no action, we check if the robot thinks he has an action to do	
        srv_info.request.agent = robotName_;
        srv_info.request.info ="ACTIONS_TODO";
        srv_info.request.actor = humanName_;
        if (client.call(srv_info)){
          if(srv_info.response.state == "READY"){//the robot thinks the human should act, it is necessary to solve the divergent belief
            srv_db.request.action = srv_info.response.action;
			if (!client_db.call(srv_db)){
				ROS_ERROR("[state_machines] Failed to call service mental_state/solve_divergent_belief");
			}
		  }
		}else{
         ROS_ERROR("[state_machines] Failed to call service mental_state/get_info");
		}
	  }
	}else{
     ROS_ERROR("[state_machines] Failed to call service mental_state/get_info");
	}

	return "IDLE";
}

/*
State where the human is ACTING
*/
string HumanSM::actingState(){

	//TODO sill ACTING?
	//TODO if human PRESENT
	

	return "ACTING";
}

/*
State where the human is WAITING
*/
string HumanSM::absentState(){

	//TODO if human PRESENT
	
	
	return "ABSENT";
}

/*
State where the human is WAITING
*/
string HumanSM::waitingState(){

	//TODO if human ACTING
	//TODO if human PRESENT
	
	//We look if the human still thinks he has an action to do
    ros::ServiceClient client = node_.serviceClient<supervisor_msgs::GetInfo>("mental_state/get_info");
    ros::ServiceClient client_db = node_.serviceClient<supervisor_msgs::SolveDivergentBelief>("mental_state/solve_divergent_belief");
    supervisor_msgs::GetInfo srv_info;
    supervisor_msgs::SolveDivergentBelief srv_db;
    srv_info.request.info ="ACTIONS_TODO";
    srv_info.request.agent = humanName_;
    srv_info.request.actor = humanName_;
	srv_db.request.agent = humanName_;
    if (client.call(srv_info)){
     if(srv_info.response.state == "NEEDED"){
        //we verify that the robot also thinks the action is NEEDED
        srv_info.request.info ="ACTION_STATE";
        srv_info.request.agent = robotName_;
        srv_info.request.action = srv_info.response.action;
        if (client.call(srv_info)){
         if(srv_info.response.state == "NEEDED"){
			//the state is the same in the robot knowledge, the human continue to WAIT
			return "WAITING";
		 }else{//there is a divergent belief, we solve it and return to IDLE
            srv_db.request.action = srv_info.response.action;
			if (!client_db.call(srv_db)){
				ROS_ERROR("[state_machines] Failed to call service mental_state/solve_divergent_belief");
			}
			ROS_INFO("[state_machines] %s goes to IDLE", humanName_.c_str());
			return "IDLE";
		  }
		}else{
         ROS_ERROR("[state_machines] Failed to call service mental_state/get_info");
		}
	 }else{//we return to IDLE to look for other actions
		ROS_INFO("[state_machines] %s goes to IDLE", humanName_.c_str());
		return "IDLE";
	  }
	}else{
     ROS_ERROR("[state_machines] Failed to call service mental_state/get_info");
	}
	
	return "WAITING";
}

/*
State where the human SHOULD ACT
*/
string HumanSM::shouldActState(){
	
	//TODO if human ACTING
	//TODO if human PRESENT

    ros::ServiceClient client = node_.serviceClient<supervisor_msgs::GetInfo>("mental_state/get_info");
    ros::ServiceClient action_state = node_.serviceClient<supervisor_msgs::ChangeState>("mental_state/change_state");
    supervisor_msgs::GetInfo srv_info;
    supervisor_msgs::ChangeState srv_action;
    srv_info.request.info ="ACTIONS_TODO";
    srv_info.request.agent = humanName_;
    srv_info.request.actor = humanName_;

	if(!timerStarted_){//we we just enter the state, we start the timer
		start_ = clock();
		timerStarted_ = true;
	}else{
		double duration = (clock() - start_ ) / (double) CLOCKS_PER_SEC;
		if(duration >= timeToWait_){
            if (client.call(srv_info)){
                srv_info.request.info ="ACTION_STATE";
                srv_info.request.agent = robotName_;
                srv_info.request.action = srv_info.response.action;
                if (client.call(srv_info)){
                 if(srv_info.response.state != "ASKED"){//if the action is not already ASKED, the robot asks to do the action
					  if(simu_){
                        srv_action.request.type = "action";
                        srv_action.request.action = srv_info.response.action;
					 	srv_action.request.state = "ASKED";
					  	if (!action_state.call(srv_action)){
                         ROS_ERROR("Failed to call service mental_state/change_state");
					 	}
					  }else{
						//TODO: ask action
					  }
				  }else{//else, we consider the action failed
                     srv_action.request.type = "action";
                     srv_action.request.action = srv_info.response.action;
					 srv_action.request.state = "FAILED";
					  if (!action_state.call(srv_action)){
                        ROS_ERROR("Failed to call service mental_state/change_state");
					  }
		           ROS_INFO("[state_machines] %s goes to IDLE", humanName_.c_str());
		           return "IDLE";
				  }
				}else{
                 ROS_ERROR("[state_machines] Failed to call service mental_state/get_info");
				}
			}else{
             ROS_ERROR("[state_machines] Failed to call service mental_state/get_info");
			}
		}
	}
	
	
	return "SHOULDACT";
}
