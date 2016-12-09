/**
author Sandra Devin
Class allowing the execution of a pick and place action
**/

#include "action_executor/Actions/pickAndPlace.h"

/**
 * \brief Constructor of the class
 * @param action the definition of the action to execute
 * @param connector pointer to the connector structure
 * */
PickAndPlace::PickAndPlace(supervisor_msgs::Action action, Connector* connector) : VirtualAction(connector){

    //we construct the pick action, then the place action
    Pick* pick = new Pick(action, connector);
    pickAction_ = *pick;
    Place* place = new Place(action, connector);
    placeAction_ = *place;

    bool foundObj = false;
    bool foundSup = false;
    for(int i=0; i<=action.parameter_keys.size();i++){
        if(action.parameter_keys[i] == "object"){
            object_ = action.parameter_values[i];
            foundObj = true;
        }
        if(action.parameter_keys[i] == "support"){
            support_ = action.parameter_values[i];
            foundSup = true;
        }
        if(foundObj && foundSup){
            break;
        }
    }
    if(!foundObj){
        ROS_WARN("[action_executor] Missing parameter: object to place");
    }
    if(!foundSup){
        ROS_WARN("[action_executor] Missing parameter: support where to place");
    }
}

/**
 * \brief Precondition of the pick and place action:
 *    - look for an object refinment if needed
 *    - the object should be a manipulable object
 *    - the support should be a support object
 *    - the object should be reachable by the agent
 *    - the support should be reachable by the agent
 * @return true if the preconditions are checked
 * */
bool PickAndPlace::preconditions(){

    if(!isRefined(object_)){
        //we look for a refinment
        std::vector<toaster_msgs::Fact> conditions;
        toaster_msgs::Fact fact;
        fact.subjectId = "NULL";
        fact.property = "isOn";
        fact.targetId = "OBJECT";
        conditions.push_back(fact);
        fact.subjectId = "OBJECT";
        fact.property = "isReachableBy";
        fact.targetId = connector_->robotName_;
        conditions.push_back(fact);
        std::string newObject  = findRefinment(object_, conditions, "NULL");
        //we update the current action
        if(newObject != "NULL"){
            initialObject_ = object_;
            std::replace (connector_->currentAction_.parameter_values.begin(), connector_->currentAction_.parameter_values.end(), object_, newObject);
            object_ = newObject;
        }
    }

    //First we check if the object is a known manipulable object
    if(!isManipulableObject(object_)){
       ROS_WARN("[action_executor] The object to place is not a known manipulable object");
      return false;
    }

    //Then we check if the support is a known support object
    if(!isSupportObject(support_)){
       ROS_WARN("[action_executor] The support is not a known support object");
      return false;
    }

    //Then we check if the object and the support are reachable
    std::vector<toaster_msgs::Fact> precsTocheck;
    toaster_msgs::Fact fact;
    fact.subjectId = object_;
    fact.property = "isReachableBy";
    fact.targetId = connector_->robotName_;
    precsTocheck.push_back(fact);
    fact.subjectId = support_;
    fact.property = "isReachableBy";
    fact.targetId = connector_->robotName_;
    precsTocheck.push_back(fact);

    return ArePreconditionsChecked(precsTocheck);

}

/**
 * \brief Planning the pick and place action:
 *    - plan for pick action then for place
 * @return true if the planning succeed
 * */
bool PickAndPlace::plan(){

    if(pickAction_.plan()){
        pickId_ = connector_->previousId_;
        if(!isRefined(support_)){
            //we postpone the support decision
           return true;
        }
        return placeAction_.plan();
    }

    return false;
}

/**
 * \brief Execution of the pick and place place action:
 *    - look for a support refinment if needed
 *    - execute the pick action then the place
 * @return true if the execution succeed
 * */
bool PickAndPlace::exec(Server* action_server){

    placeId_ = connector_->previousId_;
    connector_->previousId_  = pickId_;
    if(pickAction_.exec(action_server) && pickAction_.post()){
        //look for a support
        if(!isRefined(support_)){
            //we look for a refinment
            std::vector<toaster_msgs::Fact> conditions;
            toaster_msgs::Fact fact;
            if(isManipulableObject(support_) || isUniqueSupport(support_)){
                fact.subjectId = "NULL";
                fact.property = "isOn";
                fact.targetId = "OBJECT";
                conditions.push_back(fact);
            }
            fact.subjectId = "OBJECT";
            fact.property = "isReachableBy";
            fact.targetId = connector_->robotName_;
            conditions.push_back(fact);
            std::string newObject  = findRefinment(support_, conditions, "NULL");
            //we update the current action
            if(newObject != "NULL"){
                initialSupport_ = support_;
                std::replace (connector_->currentAction_.parameter_values.begin(), connector_->currentAction_.parameter_values.end(), support_, newObject);
                support_ = newObject;
                if(placeAction_.plan()){
                    return placeAction_.exec(action_server);
                }
            }
            return false;
        }
        connector_->previousId_  = placeId_;
        return placeAction_.exec(action_server);
    }

    return false;

}

/**
 * \brief Post conditions of the pick and place action:
 *    - post condition of the place action
 * @return true if the post-conditions are ok
 * */
bool PickAndPlace::post(){

    return placeAction_.post();
}
