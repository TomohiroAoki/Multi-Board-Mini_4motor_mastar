#ifndef MOTORDRIVER_H
#define MOTORDRIVER_H

#include "math.h"

//MDA
DigitalOut A_IN1(PB_0),A_IN2(PB_1);
PwmOut A_PWM(PA_8);

//MDB
DigitalOut B_IN1(PB_6),B_IN2(PB_7);
PwmOut B_PWM(PA_9);


DigitalOut C_IN(PA_0),D_IN(PA_1);
AnalogOut C_PWM(PA_5),D_PWM(PA_6);

void m(float mb,float mc,float md,float ma){ //MotorDriver PWM function
    
    float Peri;
    float Freq = 10000;        //frequency(Hz)
    Peri =  1/Freq;
    A_PWM.period(Peri);
    B_PWM.period(Peri);
    
    A_PWM = fabsf(ma);
    B_PWM = fabsf(mb);
    C_PWM = fabsf(mc);
    D_PWM = fabsf(md);

    if(ma == 0){
        A_IN1 = 0;
        A_IN2 = 0;
    }else if(ma == 2){ //brake
        A_IN1 = 1;
        A_IN2 = 1;
    }else if(ma > 0){
        A_IN1 = 1;
        A_IN2 = 0;
    }else if(ma < 0){
        A_IN1 = 0;
        A_IN2 = 1;
    }
    
    
    if(mb == 0){
        B_IN1 = 0;
        B_IN2 = 0;
    }else if(mb == 2){ //brake
        B_IN1 = 1;
        B_IN2 = 1;
    }else if(mb > 0){
        B_IN1 = 0;
        B_IN2 = 1;
    }else if(mb < 0){
        B_IN1 = 1;
        B_IN2 = 0;
    }    

    if(mc > 0){
        C_IN = 1;
    }else{
        C_IN = 0;
    }

    if(md > 0){
        D_IN = 0;
    }else{
        D_IN = 1;
    }

}
#endif