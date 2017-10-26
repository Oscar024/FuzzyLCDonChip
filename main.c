/*******************************************************************************
 * Archivo: main.c
 * Autores: Ing. Oscar Rigoberto Carvajal Ortiz
 * Fecha: 28 de Osctubre de 2016, 07:03 PM
 * Versión: 1.0
 * IDE: MPLAB XC8
 * Empresa: Maestría en Ciencias de la Computación ITT
 * MCU: PIC18F4550

 ******************************************************************************/


#include <xc.h>
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include "pic18f4550config.h"
#include "funciones.h"
#include <pic18f4550.h>
#include "fuzzy.h"
#include "pwm.h"
#include "cny70.h"
#include "motor.h"

int main()
{

  mcu_init();
  
  
  while(1){
      double a, b;
      
//      temperatura=temp_sense(0);
//      duty=fuzzy_system_single(temperatura);
//      duty=(float)duty;
//      Lcd_Set_Cursor(2,1);
//      Lcd_Write_String("%PWM: ");
//      Lcd_Write_Float(duty);
//      PWM_DutyCycle(duty);
      a = fuzzy_system_single1(getCNY70Value());
      b = fuzzy_system_single2(a);
      
      if(SL2 == 1  && SL1 == 1 && SM == 1 && SR1 == 1 && SR2 == 1){
            go_back(100,100);
       }       
      else{
          motor_forward();
          PWM_DutyCycle1(a);
          PWM_DutyCycle1(b);
      }
       
      
      
  }
  
  return 0;
}
 


