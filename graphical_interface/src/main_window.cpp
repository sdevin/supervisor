/**
 **/
#include "../include/graphical_interface/main_window.hpp"

MainWindow::MainWindow(int argc, char** argv, QWidget *parent)
    : QMainWindow(parent),
      actionClient_("supervisor/action_executor", true)
{
    ui.setupUi(this);
    setWindowTitle("PR2 supervisor");
    node_.getParam("/robot/name", robotName_);

    //we retrieve the possible actions from param of the .yaml file
    vector<string> actionNames;
    node_.getParam("/highLevelActions/names", actionNames);
    for(vector<string>::iterator it = actionNames.begin(); it != actionNames.end(); it++){
        ui.comboBoxActionName->addItem(it->c_str());
    }

    //we retrieve the possible objects from param of the .yaml file
    vector<string> objects;
    node_.getParam("/entities/objects", objects);
    for(vector<string>::iterator it = objects.begin(); it != objects.end(); it++){
        ui.comboBoxActionObject->addItem(it->c_str());
    }


    //we retrieve the possible supports from param of the .yaml file
    vector<string> supports;
    node_.getParam("/entities/supports", supports);
    for(vector<string>::iterator it = supports.begin(); it != supports.end(); it++){
        ui.comboBoxActionSupport->addItem(it->c_str());
    }

    actionClient_.waitForServer();


}

MainWindow::~MainWindow() {}


/*
Send an action to the action executor (simple non aware execution without head control)
*/
void MainWindow::on_pushButtonExecuteAction_clicked()
{
    //Getting parameters
    string actionName = ui.comboBoxActionName->currentText().toStdString();
    string actionObject = ui.comboBoxActionObject->currentText().toStdString();
    string actionSupport = ui.comboBoxActionSupport->currentText().toStdString();

    //creating the action with the good parameters coming from higl level actions
    supervisor_msgs::ActionExecutorGoal goal;
    goal.action.name = actionName;
    goal.action.id = -1;
    goal.action.actors.push_back(robotName_);
    string paramTopic = "highLevelActions/";
    paramTopic = paramTopic + actionName + "_param";
    vector<string> params;
    node_.getParam(paramTopic, params);
    for(vector<string>::iterator it = params.begin(); it != params.end(); it++){
        if(*it == "mainObject"){
             goal.action.parameters.push_back(actionObject);
        }else if(*it == "supportObject"){
            goal.action.parameters.push_back(actionSupport);
       }
    }

    //Sending the actions
    actionClient_.sendGoal(goal);
}

/*
Ask an action: send the action to the mental state manager (complete execution)
*/
void MainWindow::on_pushButtonAskAction_clicked()
{
    //Getting parameters
    string actionName = ui.comboBoxActionName->currentText().toStdString();
    string actionObject = ui.comboBoxActionObject->currentText().toStdString();
    string actionSupport = ui.comboBoxActionSupport->currentText().toStdString();

    //creating the action
    ros::ServiceClient action_state = node_.serviceClient<supervisor_msgs::ActionState>("mental_state/action_state");
    supervisor_msgs::ActionState srv_astate;
    srv_astate.request.action.name = actionName;
    srv_astate.request.action.id = -1;
    srv_astate.request.action.actors.push_back(robotName_);
    string paramTopic = "highLevelActions/";
    paramTopic = paramTopic + actionName + "_param";
    vector<string> params;
    node_.getParam(paramTopic, params);
    for(vector<string>::iterator it = params.begin(); it != params.end(); it++){
        if(*it == "mainObject"){
             srv_astate.request.action.parameters.push_back(actionObject);
        }else if(*it == "supportObject"){
            srv_astate.request.action.parameters.push_back(actionSupport);
       }
    }

    srv_astate.request.state = "ASKED";

    //Sending the action
    if (!action_state.call(srv_astate)) {
       ROS_ERROR("Failed to call service mental_state/action_state");
       return;
    }
}
