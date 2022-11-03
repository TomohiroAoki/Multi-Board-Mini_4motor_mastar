#include "mbed.h"
#include "math.h"
#include "MotorDriver.h"
#include <PS3BT.h>
#include <usbhub.h>

#include "math.h"

#define MAX_DUTY 0.3
 
Serial pc(USBTX, USBRX, 115200);

//Nucleo f303k8用
USB Usb(D11, D12, D13, A3, A2); // mosi, miso, sclk, ssel, intr
BTD Btd(&Usb);
PS3BT PS3(&Btd);



int Stick_vel_converter(int dead_band,int max_vel,int stick_input){    
    int dead_band_min;
    int dead_band_max;
    int output_data;

    double slope,intercept;

    dead_band_min = 127 - dead_band/2 - 1; 
    dead_band_max = 128 + dead_band/2 - 1;

    slope = max_vel / (255 - dead_band_max);
    intercept = max_vel - slope * 255;

    if(stick_input < dead_band_min){
        output_data = slope * stick_input - max_vel;
    }else if(stick_input > dead_band_max){
        output_data = slope * stick_input + intercept;
    }else{
        output_data = 0;
    }

    return output_data;    
}

void single_stick_mode(){
                 
    float x,y;
                 
    x = (float)PS3.getAnalogHat(RightHatX)/128-1;
    y = 1-(float)PS3.getAnalogHat(RightHatY)/128;
                
    //m(-(x+y)*MAX_DUTY,(y-x)*MAX_DUTY),-(x+y)*MAX_DUTY,(y-x)*MAX_DUTY);
    //M1.pulsewidth_us(1500);
    //M2.pulsewidth_us(1500);

}
/*
void motor_double_stick_mode(float max_duty){
    
    int stick_L,stick_R;
    double duty_L,duty_R;
    
    A_PWM.period_us(50);
    B_PWM.period_us(50);
    
    stick_L = PS3.getAnalogHat(LeftHatY);
    stick_R = PS3.getAnalogHat(RightHatY);
    
    duty_L = fabsf(((double)stick_L/255-0.5)*2*max_duty);
    duty_R = fabsf(((double)stick_R/255-0.5)*2*max_duty);
    
    printf("%f %f\r\n",duty_L,duty_R);
    
    A_PWM = duty_L;
    B_PWM = duty_R;
    //LED_1 = duty_R;
    
    if(stick_L >= 128){
        A_IN1 = 1;
        A_IN2 = 0;
    }else{
        A_IN1 = 0;
        A_IN2 = 1;
    }
    
    if(stick_R >= 128){
        B_IN1 = 1;
        B_IN2 = 0;
    }else{
        B_IN1 = 0;
        B_IN2 = 1;
    }
    
}
*/

int main(){


float up;
float down;
float right;
float left,l1,r1; 




    if (Usb.Init() == -1)
    {
        pc.printf("\r\nOSC did not start");
        while (1); // Halt
    }
    pc.printf("\r\nPS3 USB Library Started");
    
    while(1){
        Usb.Task();
        up = (float)PS3.getAnalogButton(UP)/255;
        down = (float)PS3.getAnalogButton(DOWN)/255;
        right = (float)PS3.getAnalogButton(RIGHT)/255;
        left = (float)PS3.getAnalogButton(LEFT)/255;
        l1 = (float)PS3.getAnalogButton(L1)/255;
        r1 = (float)PS3.getAnalogButton(R1)/255;


        if (PS3.PS3Connected || PS3.PS3NavigationConnected) {
            //single_stick_mode();
            printf("%f\r\n",MAX_DUTY*left);
            if(PS3.getAnalogButton(UP) > 0){
                m(MAX_DUTY*up, MAX_DUTY*up, MAX_DUTY*up ,MAX_DUTY*up);
            }else if(PS3.getAnalogButton(DOWN) > 0){
                m(-MAX_DUTY*down, -MAX_DUTY*down, -MAX_DUTY*down, -MAX_DUTY*down);
            }else if(PS3.getAnalogButton(LEFT) > 0){
                m(-MAX_DUTY*left, MAX_DUTY*left, -MAX_DUTY*left, MAX_DUTY*left);
            }else if(PS3.getAnalogButton(RIGHT) > 0){
                m(MAX_DUTY*right, -MAX_DUTY*right, MAX_DUTY*right, -MAX_DUTY*right);
            }else if(PS3.getAnalogButton(L1) > 0){
                m(-MAX_DUTY*l1, -MAX_DUTY*l1, MAX_DUTY*l1 ,MAX_DUTY*l1);
            }else if(PS3.getAnalogButton(R1) > 0){
                m(MAX_DUTY*r1, MAX_DUTY*r1, -MAX_DUTY*r1 ,-MAX_DUTY*r1);
            }else{
               m(0,0,0,0);
            }
            
        }else{
            m(0,0,0,0);
            pc.printf("not connect\r\n");
        }
    }
    //*/
}
