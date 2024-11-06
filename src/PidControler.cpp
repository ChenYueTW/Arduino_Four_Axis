#include <PID_v1.h>
#include <MPU6050_light.h>
#include <Wire.h>

double outMin,outMax;
int sampleTime = 1000;
double Setpoint, Input, Output;
double kp = 0;
double ki = 0;
double kd = 0;
bool PIDSwitch = true;
//double OutArray[] = {0,0};


void PidControler(double Input,double Setpoint) {
    PID myPID(&Input, &Output, &Setpoint, kp, ki, kd, DIRECT);
    myPID.SetMode(AUTOMATIC);
    myPID.SetOutputLimits(0,180);
    myPID.SetSampleTime(50);
    myPID.SetTunings(kp,ki,kd);
//    OutArray[0] = myPID.Compute();
//    OutArray[1] = myPID.GetDirection();
//    return OutArray;
//123
    return myPID.Compute();
    
}