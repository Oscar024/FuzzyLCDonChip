/*
 * File:   funciones.c
 * Author: OSCAR
 *
 * Created on October 28, 2016, 9:31 PM
 */


#include <xc.h>
#include "funciones.h"
#include "pwm.h"


void mcu_init(void){
    //Inicialización MCU PIC18F4550
    TRISA=TRISB=TRISC=TRISD=TRISE=0;                          //Pines como salidas
    PORTA=PORTB=PORTC=PORTD=PORTE=0;
    
    
    
    int i = 0;
    __delay_ms(40);
    OSCCONbits.IRCF = 0b111; // Oscilador Interno a 8 Mhz
//            OSCTUNEbits.PLLEN = 1; // PLL Activado (8 Mhz x 4 = 32 Mhz)_
//            __delay_ms(40);
    //        ODCON2bits.U2OD = 1; // Activa Open Drain en USART2
    //        TRISGbits.TRISG1 = 0; // USART2 TX
    TRISA = TRISB = TRISC = TRISD = TRISE = 0;
    PORTA =  PORTB =  PORTC =  PORTD = PORTE = 0;
    TRISCbits.TRISC7 = 1;
    TRISCbits.TRISC6 = 0;
//    for (i = 1; i <= 50; i++)
//      __delay_ms(20);
    PORTE = 0;
    PORTB = 0;
    TRISBbits.TRISB0 = 1;
    TRISBbits.TRISB1 = 1;
    TRISBbits.TRISB2 = 1;
    TRISBbits.TRISB3 = 1;
    TRISBbits.TRISB4 = 1;
//    external_interrupt_init();
   
    //        CheckTX(INICIO);  
    
    
     PWM_init1(0xff);
     PWM_init2(0xff);
     PWM_DutyCycle1(0);
     PWM_DutyCycle2(0);
    

    return;

}
