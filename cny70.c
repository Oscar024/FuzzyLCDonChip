#include "cny70.h"
#include "pwm.h"

int getCNY70Value(void)
{
//    if(RB1 == 1  && RB0 == 0 && RB2 == 1){
//        go_straight();
//        return 0;
//    }
//    else if(RB1 == 0  && RB0 == 1 && RB2 == 1){
//        right();
//        return -1;
//    }
//    else if(RB1 == 1  && RB0 == 1 && RB2 == 0){
//        left();
//        return -1;
//    }
//    else if(RB2 == 1  && RB0 == 1 && RB1 == 1 && RB3 == 1 && RB4 == 1){
//        go_back();
//        return -1;
//    }
//    
    
    if(SL2 == 1  && SL1 == 1 && SM == 0 && SR1 == 1 && SR2 == 1){
//        go_straight();
        return 0;
    } 
        
    else if(SL2 == 1 && SL1 == 0 && SM == 1 && SR1 == 1 && SR2 == 1){
//        left();
        return -1;
    }
        
    else if(SL2 == 0 && SL1 == 1 && SM == 1 && SR1 == 1 && SR2 == 1){
//        left();
        return -2;
    }
        
    else if(SL2 == 1 && SL1 == 1 && SM == 1 && SR1 == 0 && SR2 == 1){
//        right();
        return 1;
    }
        
    else if(SL2 == 1 && SL1 == 1 && SM == 1 && SR1 == 1 && SR2 == 0){
//        right();
        return 2;
    }
    
        
    else if(SL2 == 1 && SL1 == 1 && SM == 1 && SR1 == 0 && SR2 == 0){
//        right();
        return 2;
    }
        
    else if(SL2 == 0 && SL1 == 0 && SM == 1 && SR1 == 1 && SR2 == 1){
//        left();
        return -2;        
    }
        
    else if(SL2 == 1 && SL1 == 0 && SM == 0 && SR1 == 1 && SR2 == 1){
//        go_straight();
        return -1;
    }
        
    else if(SL2 == 1 && SL1 == 1 && SM == 0 && SR1 == 0 && SR2 == 1){
//        go_straight();
         return 1;
    }  
    
//    else if(SL2 == 1 && SL1 == 1 && SM == 1 && SR1 == 1 && SR2 == 1){
//        go_back();
//         return -10;
//     }
           
    else
        return 0;
//     if(RB0 == 0 && RB1 == 0 && RB2 == 1 && RB3 == 0 && RB4 == 0)
//        return 0;
//    else if(RB0 == 0 && RB1 == 1 && RB2 == 0 && RB3 == 0 && RB4 == 0)
//        return -1;
//    else if(RB0 == 1 && RB1 == 0 && RB2 == 0 && RB3 == 0 && RB4 == 0)
//        return -2;
//    else if(RB0 == 0 && RB1 == 0 && RB2 == 0 && RB3 == 1 && RB4 == 0)
//        return 1;
//    else if(RB0 == 0 && RB1 == 0 && RB2 == 0 && RB3 == 0 && RB4 == 1)
//        return 2;
//    else if(RB0 == 0 && RB1 == 0 && RB2 == 0 && RB3 == 1 && RB4 == 1)
//        return 2;
//    else if(RB0 == 1 && RB1 == 1 && RB2 == 0 && RB3 == 0 && RB4 == 0)
//        return -2;
//    else if(RB0 == 0 && RB1 == 1 && RB2 == 1 && RB3 == 0 && RB4 == 0)
//        return -1;
//    else if(RB0 == 0 && RB1 == 0 && RB2 == 1 && RB3 == 1 && RB4 == 0)
//        return 1;
//    else
//        return 0;
}

void right(unsigned char m_right , unsigned char m_left)
{
    motor_forward2();
    motor_Backforward1();
    PWM_DutyCycle1(m_right);
    PWM_DutyCycle2(m_left);
    return;
}

void left(unsigned char m_rigth, unsigned char m_left)
{
    motor_forward1();
    motor_Backforward2();
    PWM_DutyCycle1(m_rigth);
    PWM_DutyCycle2(m_left);
    return;
}

void go_straight(unsigned char m_right, unsigned char m_left)
{
    motor_forward();
    PWM_DutyCycle1(m_right);
    PWM_DutyCycle2(m_left);
    return;
}

void go_back(unsigned char m_right, unsigned char m_left)
{
    motor_Backforward();
    PWM_DutyCycle1(m_right);
    PWM_DutyCycle2(m_left);
    return;
}