#include "ros/ros.h"
#include "std_msgs/Float64.h"

//for sin()
#include <math.h>

float X;
float P;

void joint4angleCallback(const std_msgs::Float64 msg)
{
    X = msg.data;
}



int main(int argc, char **argv) {
    ros::init(argc, argv, "rotate");
    X = 0;
    P = 0;
    ros::NodeHandle nh;

    ros::Publisher pub3 = nh.advertise<std_msgs::Float64>("/robot/joint1_position_controller/command", 100);
    ros::Publisher pub4 = nh.advertise<std_msgs::Float64>("/robot/joint5_position_controller/command", 100);
    ros::Subscriber sub = nh.subscribe("sin_wave", 1000, joint4angleCallback);

    ros:: Rate loop_rate(10);

    ros::Time startTime = ros::Time::now();

        while (ros::ok()) {
            std_msgs::Float64 msg_to_send;

            if ((sin(X) <= 0.5 && sin(X) >= 0)|| (sin(X) > -0.5 && sin(X) <= 0))
            {
                P = 0;
            } else {
                P = 1;
            }
            msg_to_send.data = P;
            X = X + 0.1;
            pub3.publish(msg_to_send);
            pub4.publish(msg_to_send);

            ROS_INFO("X: %f", P);

            ros::spinOnce();

            loop_rate.sleep();
        }
}