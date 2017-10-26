/*
 * File:   funciones.h
 * Author: L
 *
 * Created on 11 de septiembre de 2014, 07:15 PM
 */

#ifndef FUNCIONES_H
#define	FUNCIONES_H
#define _XTAL_FREQ 8000000


        // DIRECCIONES //

#define DIR_MAE                 0
#define DIR_ESC                 1
#define DIR_TEL                 2                                               //direccion del esclavo
#define Drive_by                4
#define TABLET                  5					                // Número del medidor

#define SOlIBATON               1
#define SOLIBATOFF              2
#define SOLIPORC                3
#define PINGBT                  4
#define ACK                     5
#define NAME                    41
#define SOLIPORC_LOW_POWER      7


#define NUM_SOLICITUD           2
#define Led_Blanco  LATBbits.LATB5
#define Led_Azul   LATBbits.LATB1
#define Led_Verde    LATBbits.LATB0
#define Led_Rojo   LATBbits.LATB2
#define BT_DISCONN PORTCbits.RC0
#define CHRG_EN    PORTBbits.RB5


void PantallaPrin(void);
void PONGBT(void);
void clrBufferDato(void);
void ConecBatteria(int Off_On_BAt);
void EstadoBluetooth(void);
void Comando_Tablet(void);
void Inicializa_Driveby(void);
void Mandar_Tablet(void);
char Tecla(void);
void Teclado(void);
void DelayCommands();
void BT_ModoVisible(void);
#endif	/* FUNCIONES_H */

