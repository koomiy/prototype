#include "../include/Adafruit_ServoDriver.h"
#include "../include/servo_driver.h"

// PCA9685のアドレス
#define PCA9685_ADDRESS 0x40

// サーボモータのパラメータ
#define SERVO_CONTROL_FREQUENCY 50  // 一応PCA9685のPWM周波数は50Hzと書かれている
#define SERVO_CENTER_PULSE_WIDTH_US 1520
#define SERVO_CENTER_PULSE_WIDTH_US_FUTABA_OLD  1310
#define SERVO_RANGE_PULSE_WIDTH_US 1600

ServoDriver::ServoDriver(int pwm_channel) : 
pwm_channel(pwm_channel) 
{
    // サブスクライバの立ち上げ
    sub_pwm = nh.subscribe("/pwm_command", 10, &ServoDriver::pwmCallback, this);
    
    // パブリッシャの立ち上げ
    pub_pwm = nh.advertise<std_msgs::Float64>("/pwm", 10);

    int i2c = 0;    // ファイルディスクリプタ
    char *i2cFileName = (char*)"/dev/i2c-1"; // I2Cデバイスのパス（古いものはi2c-0）
    int driverAddress = PCA9685_ADDRESS;

    // I2Cのデバイスをオープン
    if ((i2c = open(i2cFileName, O_RDWR)) < 0) {
        printf("Faild to open i2c port\n");
        exit(1);
    }

    // PCA9685のアドレスを指定する
    if (ioctl(i2c, I2C_SLAVE, driverAddress) < 0) {
        printf("Unable to get bus access to talk to slave\n");
        exit(1);
    }

    driver._i2c = i2c;

    driver.reset();

    usleep(1000000); // 1秒間待機

    // サーボ制御パルス周波数の設定。
    driver.setPWMFreq(SERVO_CONTROL_FREQUENCY);  // PWMの周波数を50Hzに指定する

    // サーボをセンタ位置へ。
    driver.setServoPulse(0, 1500);    // センタ位置のパルス幅は1500us
    driver.setServoPulse(1, 1500);    // センタ位置のパルス幅は1500us
    driver.setServoPulse(2, 1500);    // センタ位置のパルス幅は1500us
    driver.setServoPulse(3, 1500);    // センタ位置のパルス幅は1500us
    driver.setServoPulse(4, 1500);    // センタ位置のパルス幅は1500us
    driver.setServoPulse(5, 1500);    // センタ位置のパルス幅は1500us
//
    usleep(2000000); // 2秒間待機

}

void ServoDriver::setPWM(double duty_cycle) 
{
    int pulse_length = int(duty_cycle * 4096); // 4096 is the resolution of PCA9685

    // Write the PWM pulse to the PCA9685
    driver.setPWM(pwm_channel, 0, pulse_length);
}

void ServoDriver::pwmCallback(const std_msgs::Float64& msg) {
    setPWM(msg.data);
}

void ServoDriver::spin(){
    ros::Rate loop_rate(20);
    while (ros::ok()){
        //pwmCallback(sub_pwm);
        driver.setServoPulse(0, 500);
        usleep(5000000);
        driver.setServoPulse(0, 2500);
        usleep(5000000);
        loop_rate.sleep();
    }

}