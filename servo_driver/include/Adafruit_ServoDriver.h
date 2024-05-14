#pragma once

#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <math.h>
#include <linux/i2c-dev.h>
#include <fcntl.h>
#include <sys/ioctl.h>
#include <unistd.h>

class Ada_ServoDriver
{
public:
    uint8_t _i2cAddr;
    int _i2c;

public: 
    Ada_ServoDriver();
    void reset(void);
    void setPWMFreq(float frea);
    void setPWM(uint8_t srvNo, uint16_t onTime, uint16_t offTime);
    void setServoPulse(uint8_t ch, double pulseWidth_us);   // 500us(-90度)~2500us(+90度)のパルス幅を設定する
    uint8_t read8(uint8_t addr);
    void write8(uint8_t addr, uint8_t d);
 
};