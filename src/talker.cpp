#include "ros/ros.h"
#include "std_msgs/String.h"
#include<sstream>

int main(int argc, char **argv){
  ros::init(argc,argv,"yagnesh_talker");

  ros::NodeHandle n;

  ros::Publisher pub = n.advertise<std_msgs::String>("talk",1000);

  ros::Rate loop_rate(10);

  while(ros::ok()){
    std_msgs::String msg;
    msg.data = "Hello World";

    ROS_INFO("%s",msg.data.c_str());

    pub.publish(msg);

    ros::spinOnce();

    loop_rate.sleep();
  }
}