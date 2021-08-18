#include "ros/ros.h"
#include "std_msgs/String.h"

#include<sstream>

void chatterCB(const std_msgs::String::ConstPtr& msg){
    ROS_INFO("Heard");
}

int main(int argc, char **argv){
    ros::init(argc,argv, "yagnesh_listener");

    ros::NodeHandle n;

    ros::Subscriber sub = n.subscribe("talk",1000,chatterCB);

    ros::spin();

}