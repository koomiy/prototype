#include "../include/Adafruit_ServoDriver.h"
#include "../include/servo_driver.h"

int main(int argc, char **argv)
{
    ros::init(argc, argv, "servo_driver_node");

    int pwm_channel = 0;
    ServoDriver servo_driver(pwm_channel);

    servo_driver.spin();
    std::cout << "\next program\n" << std::endl;
    
    return 0;
}
