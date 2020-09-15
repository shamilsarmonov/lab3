#include "ros/ros.h"
#include "std_msgs/Float64.h"

#include <math.h>

float X;
float previous_value;

void joint4angleCallback(const std_msgs::Float64 msg)
{
    X = msg.data;
    if (previous_value < X || (previous_value == 0 && X == 0))
    {
        ROS_INFO("X Changed to: %f", X);
        //ROS_INFO(" ");
        previous_value = X;
    }

}



int main(int argc, char **argv) {
    ros::init(argc, argv, "rotate");
    X = 0;
    previous_value = 0;
    ros::NodeHandle nh;

    ros::Publisher pub3 = nh.advertise<std_msgs::Float64>("/robot/joint1_position_controller/command", 100);
    ros::Publisher pub4 = nh.advertise<std_msgs::Float64>("/robot/joint5_position_controller/command", 100);
    ros::Subscriber sub = nh.subscribe("Change", 1000, joint4angleCallback);

    ros:: Rate loop_rate(10);

    ros::Time startTime = ros::Time::now();

        while (ros::ok()) {
            std_msgs::Float64 msg_to_send;


            msg_to_send.data = previous_value;

            pub3.publish(msg_to_send);
            pub4.publish(msg_to_send);

            ROS_INFO("X: %f", previous_value);

            ros::spinOnce();

            loop_rate.sleep();
        }
}