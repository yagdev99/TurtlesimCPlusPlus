#include "ros/ros.h"
#include "turtlesim/Pose.h"
#include "geometry_msgs/Twist.h"
#include "math.h"

#include <sstream>

ros::Subscriber sub;
ros::Publisher pub;

float range(const float theta){
    if(theta > M_PI){
        return (theta - M_PI_2);
    }
    else if(theta < -1*M_PI_2){
        return (theta + M_PI);
    }

    return theta;
}


void sendVel(const turtlesim::Pose::ConstPtr& data){
    ros::NodeHandle n;

    pub = n.advertise<geometry_msgs::Twist>("/turtle1/cmd_vel",100);

    int goal_x = 2;
    int goal_y = 2;

    float curr_x = data->x;
    float curr_y = data->y;
    float curr_ang = data->theta;

    float dist = sqrt(pow(goal_x-curr_x,2) + pow(goal_y-curr_y,2));
    std::cout << "Distance = " << dist << std::endl;

    if(dist > 0.1){
        double ang = atan2((float)(curr_y-goal_y),(float)(curr_x-goal_x));

        std::cout << "Curr_ang = " << curr_ang << " | ang = " << ang << " | difference = " << 2*range(curr_ang + M_PI_2 - ang) << std::endl;

        geometry_msgs::Twist t_msg;

        t_msg.linear.x = 0.75*(dist);
        t_msg.angular.z = 2*range(curr_ang + M_PI_2 - ang);

        pub.publish(t_msg);
    }

}

int main(int argc, char **argv){
    ros::init(argc,argv,"goToGoal");

    ros::NodeHandle n;

    sub = n.subscribe("/turtle1/pose",10,sendVel);

    ros::spin();


    return 0;
}