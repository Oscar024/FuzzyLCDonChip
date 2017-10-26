/*
 * File:   motor.c
 * Author: Dell
 *
 * Created on October 6, 2017, 12:51 AM
 */

#include "motor.h"


void motor_forward1(void)
{
    INPUT1 = 1;
    INPUT2 = 0;
    
    
    return;    
}

void motor_Backforward1(void)
{
    INPUT1 = 0;
    INPUT2 = 1;
   
    
    return;
}

void motor_forward2(void)
{
   
    INPUT3 = 1;
    INPUT4 = 0;
    
    return;    
}

void motor_Backforward2(void)
{
   
    INPUT3 = 0;
    INPUT4 = 1;
    
    return;
}

void motor_forward(void)
{
    INPUT1 = 1;
    INPUT2 = 0;
    INPUT3 = 1;
    INPUT4 = 0;    
    
    return;    
}

void motor_Backforward(void)
{
    INPUT1 = 0;
    INPUT2 = 1;
    INPUT3 = 0;
    INPUT4 = 1;
       
    return;
}