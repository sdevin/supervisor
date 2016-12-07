/**
author Sandra Devin
Class allowing the execution of a pick action
**/

#include "action_executor/Actions/pick.h"

/**
 * \brief Construction of the class
 * @param action the definition of the pick action to execute
 * @param connector pointer to the connector structure
 * */
Pick::Pick(supervisor_msgs::Action action, Connector* connector) : VirtualAction(connector){

    bool found = false;
    for(int i=0; i<=action.parameter_keys.size();i++){
        if(action.parameter_keys[i] == "object"){
            object_ = action.parameter_values[i];
            found = true;
            break;
        }
    }
    if(!found){
        ROS_WARN("[action_executor] Missing parameter: object to pick");
    }
}

/**
 * \brief Precondition of the pick action:
 *    - the object should be a manipulable object
 *    - the object should be reachable by the agent
 *    - the agent should not have any object in hand
 * @return true if the preconditions are checked
 * */
bool Pick::preconditions(){

    //First we check if the object is a known manipulable object
    if(!isManipulableObject(object_)){
      ROS_WARN("[action_executor] The object to pick (%s) is not a known manipulable object", object_.c_str());
      return false;
    }

    //Then we check if the robot has the hands free and if the object is reachable
    std::vector<toaster_msgs::Fact> precsTocheck;
    toaster_msgs::Fact fact;
    fact.subjectId = "NULL";
    fact.property = "isHoldBy";
    fact.targetId = connector_->robotName_;
    precsTocheck.push_back(fact);
    fact.subjectId = object_;
    fact.property = "isReachableBy";
    fact.targetId = connector_->robotName_;
    precsTocheck.push_back(fact);

    return ArePreconditionsChecked(precsTocheck);

}

/**
 * \brief Planning the pick action:
 *    - ask a gtp plan
 * @return true if the planning succeed
 * */
bool Pick::plan(){

    //FOR TESTS ONLY
    //connector_->previousId_  = -1;

   std::vector<gtp_ros_msgs::Role> agents;
   gtp_ros_msgs::Role role;
   role.role = "mainAgent";
   role.name = connector_->robotName_;
   agents.push_back(role);
   std::vector<gtp_ros_msgs::Role> objects;
   role.role = "mainObject";
   role.name = object_;
   objects.push_back(role);
   std::vector<gtp_ros_msgs::Point> points;
   std::vector<gtp_ros_msgs::MiscData> datas;

   if(connector_->shouldUseRightHand_){
       gtp_ros_msgs::MiscData data;
       data.key = "hand";
       data.value = "right";
       datas.push_back(data);
   }

   std::pair<int, std::vector<gtp_ros_msgs::SubSolution> > answer = planGTP("pick", agents, objects, datas, points);
   gtpActionId_ = answer.first;

   if(gtpActionId_ == -1){
       return false;
    }

   subSolutions_ = answer.second;
   return true;
}

/**
 * \brief Execution of the pick action:
 *    - execute gtp plan
 * @return true if the execution succeed
 * */
bool Pick::exec(Server* action_server){

   return execAction(gtpActionId_, subSolutions_, true, action_server);

}

/**
 * \brief Post conditions of the pick action:
 *    - chek if the gripper is not empty
 * @return true if the post-conditions are ok
 * */
bool Pick::post(){

    //Check gripper position (completly close or not)
    if(gripperEmpty_  && !connector_->simu_){
        ROS_WARN("[action_executor] Robot failed to pick (gripper empty)");
        return false;
    }

    return true;
}
