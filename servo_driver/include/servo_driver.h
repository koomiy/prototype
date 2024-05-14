#pragma once

#include <ros/ros.h>
#include <std_msgs/Float64.h>

class ServoDriver
{
private: 
    ros::NodeHandle nh;
    ros::Subscriber sub_pwm;
    ros::Publisher pub_pwm;

    Ada_ServoDriver driver;

    int pwm_channel;

public: 
    ServoDriver(int pwm_channel);
    void setPWM(double duty_cycle);
    void pwmCallback(const std_msgs::Float64& msg);
    void spin();

};