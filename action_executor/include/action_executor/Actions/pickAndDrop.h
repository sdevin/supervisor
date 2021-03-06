#ifndef PICKANDDROP_H
#define PICKANDDROP_H

#include "action_executor/virtual_action.h"
#include "action_executor/Actions/pick.h"
#include "action_executor/Actions/drop.h"

class PickAndDrop: public VirtualAction{
public:
    PickAndDrop(supervisor_msgs::Action action, Connector* connector);
    virtual bool preconditions();
    virtual bool plan();
    virtual bool exec(Server* action_server);
    virtual bool post();
protected:

private:
    Pick pickAction_; /**< pick part of the action*/
    Drop dropAction_; /**< drop part of the action*/
    std::string container_; /**< container where to drop the object*/
    std::string initialContainer_; /**< given high level container when there is one*/
    int pickId_; /**< gtp id of the pick action*/
    int dropId_; /**< gtp id of the drop action*/


};

#endif // PICKANDDROP_H
