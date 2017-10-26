
#include <xc.h>
#include <plib/spi.h>
#include<stdio.h>
#include<stdlib.h>
#include"Bluetooth.h"
#include<string.h>
#include"Funciones.h"
#include "lcd.h"



char FinComandB;
char FinComandT;
char                  CheckSum              = 0;
int                   TamanhoTrama          = 0;
unsigned char     num_med_low           = 0;
unsigned char     num_med_medium        = 0;
unsigned char     num_med_hi            = 0;
int                   Med_msb               = 0;
int                   Med_lsb               = 0;
unsigned char         dato[14];
unsigned char         packet                = 0;
unsigned char         contador              = 0;
unsigned char         contador2             = 0;
unsigned char         TramaTablet[20];
extern unsigned char  BluetoothDato[20];
extern unsigned char  cad;
extern unsigned char  cleanBfer,Timer1;
char array[20];
unsigned char j=0;






//Estados del Bluetooth Bee
void EstadoBluetooth(void)
{

      if(strcmp(BluetoothDato,READY)==0){
            Pause_seg(4);

            BT_Init();

            CheckTX(CONECTING);

            CheckTX(CONECTEDOK);
            CheckTX(CONECTED);
            Pause_seg(7);
            cad=0;
            clrBufferUSART();
 
            Led_Blanco=0;
            Led_Azul=0;

            
    }
            UART1_Init(51);
            return;

}


//******************************************************************************
//Función Que inicializa el Drive By
void Inicializa_Driveby(void)
{
        TRISA=TRISB=TRISC=TRISD=0;
        INTCON=0b11000000;
//        PIE1bits.RCIE=1;
        //Inicialización del MCU
        int i = 0;
        __delay_ms(40);
        OSCCONbits.IRCF = 0b111; // Oscilador Interno a 8 Mhz
//        OSCTUNEbits.PLLEN = 1; // PLL Activado (8 Mhz x 4 = 32 Mhz)_
//        __delay_ms(40);
//        ODCON2bits.U2OD = 1; // Activa Open Drain en USART2
//        TRISGbits.TRISG1 = 0; // USART2 TX
        TRISA=0;
        PORTA=0;
        TRISCbits.TRISC7 = 1;
        TRISCbits.TRISC6 = 0;
            for (i = 1; i <= 50; i++)
            __delay_ms(20);
        PORTE = 0;
        PORTB = 0;
        Lcd_Clear();
        Lcd_Set_Cursor(2,1);
        Lcd_Write_String("INICIO");
//        CheckTX(INICIO);
        BT_Init();
        Lcd_Clear();
        Lcd_Set_Cursor(1,1);
        Lcd_Write_String("BT INICIALIZADO");
//        Lcd_Clear();
//        Lcd_Set_Cursor(1,1);
//        Lcd_Write_String("BT inicializado");
//        Lcd_Set_Cursor(2,1);
//        Lcd_Clear();
//        Lcd_Set_Cursor(1,1);
//        Lcd_Write_String("CONENCTANDO");
//        CheckTX(CONECTEDOK);
//        Lcd_Clear();
//        Lcd_Set_Cursor(1,1);
//        Lcd_Write_String("Conectando ok");
//        CheckTX(CONECTED);
//        Lcd_Clear();
//        Lcd_Set_Cursor(1,1);
//        Lcd_Write_String("Conectado");
        Pause_seg(7);
        cad=0;
        clrBufferUSART();

        Led_Blanco=0;
        Led_Azul=0;
        
 
        return;
}

//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
// Configuración del CC1101 para transmitir la trama  Solicitud % RF de la función Arma Cadena

//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//Función que transmite a la Tablet
void Mandar_Tablet(void) {

        UART1_Init(51);
        putcBluetoothString(TamanhoTrama);
        PantallaPrin();
        Pause_seg(1);

        return;
}

//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
void PantallaPrin(void) {
        UART1_Init(51);
//        LCD_Pos_Cursor(1, 1);
//        LCD_Escribe((char*) "      DRIVE-BY     ", 19);
//        LCD_Pos_Cursor(1, 2);
//        LCD_Escribe((char*) "  TABLET Conectada  ", 20);

        cad = 0;
        clrBufferUSART();

        return;
}

//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

void ConecBatteria(int Off_On_BAt) {
        int x;
         CheckSum = BluetoothDato[1] + BluetoothDato[2];
         if (BluetoothDato[3] != CheckSum) {

                for (x = 0; x <= 7; x++)
                    dato[x] = 0;

                //Conectar batería/Error
                dato[0] = '#';
                dato[1] = BluetoothDato[1];
                dato[2] = 2;
                dato[3] = 0x45;
                dato[4] = 0;
                dato[5] = dato[1] + dato[2] + dato[3] + dato[4];
                dato[6] = '#';
                TamanhoTrama = 7; // Se cambió de 6 a 7
//                Mandar_Tablet();
                PantallaPrin();

                return;
          }



          if (Off_On_BAt == 1) {

                 for (x = 0; x <= 7; x++)
                      dato[x] = 0;

                 //Conectar batería/Exitoso
                 TRISBbits.RB5=0;
                 CHRG_EN=1;

                 dato[0] = '#';
                 dato[1] = 1;
                 dato[2] = 1;
                 dato[3] = 1;
                 //        dato[4] = dato[1] + dato[2] + dato[3] + dato[4];
                 dato[4] = dato[1] + dato[2] + dato[3] ;//Se le quitó + dato[4]
                 dato[5] = '#';
                 TamanhoTrama = 6;  //Secambió de 5 a 6
//                 Mandar_Tablet();
                 PantallaPrin();
            }

            if (Off_On_BAt == 0) {

                    for (x = 0; x <= 7; x++)
                        dato[x] = 0;

                 //Desconectar bactería/Exitoso
                 TRISBbits.RB5=0;
                 CHRG_EN=0;

                 dato[0] = '#';
                 dato[1] = 2;
                 dato[2] = 1;
                 dato[3] = 1;
                 dato[4] = dato[1] + dato[2] + dato[3];
                 dato[5] = '#';
                 TamanhoTrama = 6; //Secambio de 5 a 6
//                 Mandar_Tablet();
//                 PantallaPrin();

             }
         return;
}

//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//Limpia el Buffer de datos
void clrBufferDato(void) {

        for (int i = 0; i < 14; i++)
             dato[i] = 0;

       return;
}

//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

void PONGBT(void) {

        int i = 0;
        clrBufferDato();
        PantallaPrin();

       //Respuesta PING BT
       dato[0] = '#';
       dato[1] = 4;
       dato[2] = 1;
       dato[3] = 1;
       dato[4] = dato[1] + dato[2] + dato[3];
       dato[5] = '#';

            putcBluetoothString(6);
       return;
}
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++


//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//Comando Tablet con ACK
//Verifico que trama recibo de la tablet por medio de los comandos



void DelayCommands()
{
      for(int j=0;j<10;j++){
                Led_Azul=1;
                for(int i=0;i<20;i++)
                    __delay_ms(20);
                Led_Azul=0;
                for(int i=0;i<20;i++)
                    __delay_ms(20);
      }
             Led_Azul=0;

      return;
}

//Estados del Bluetooth Bee
void BT_ModoVisible(void)
{
      
      UART1_Init(51);

      if(strcmp(BluetoothDato,CONECTING)==0||strcmp(BluetoothDato,READY )==0||strcmp(BluetoothDato,BT_DISCONECT )==0 ){
//            Pause_seg(4);
//            DelayCommands();
//            SendBlueToothCommand("\r\n+INQ=1\r\n",10);                                  //Lo pone visible
//            Pause_seg(4);

            clrBufferUSART();

                    
    }
           

     return;
}

void Comando_Tablet() {

    int i = 0, x;


    //Verifico si es Solicitud % BT
    if (BluetoothDato[1] == SOLIPORC)
    {
//
//        clrBufferDato();
//        CheckSum = BluetoothDato[1] + BluetoothDato[2];
//        CheckSum=CheckSum&0X0000FF;
        Lcd_Clear();
        Lcd_Set_Cursor(1,1);
        Lcd_Write_String("Alto");
        PORTAbits.RA0=0;
        PORTAbits.RA1=0;
        PORTAbits.RA2=0;
        PORTAbits.RA3=0;
        clrBufferUSART();

        //Se verifica si el CheckSum es correcto
//        if (BluetoothDato[3] != CheckSum)
//        {
//            DelayCommands();
//            for (x = 0; x <= 20; x++)
//                dato[x] = 0;
//            //Respuesta % BT/Error
//            dato[0] = '#';
//            dato[1] = 3;
//            dato[2] = 2;
//            dato[3] = 0x45;
//            dato[4] = 0;
//            dato[5] = dato[1] + dato[2] + dato[3] + dato[4];
//            dato[6] = '#';
//            TamanhoTrama = 7; //Se cambio de 6 a 7
////            Mandar_Tablet();
//            return;
//        }
        return;
        
    }

    //Verifico si es desconectar batería
    else if (BluetoothDato[1] == SOLIBATOFF) {
//             DelayCommands();
            Lcd_Clear();
            Lcd_Set_Cursor(1,1);
            Lcd_Write_String("Arriba");
            PORTAbits.RA0=1;
            PORTAbits.RA1=0;
            PORTAbits.RA2=1;
            PORTAbits.RA3=0;
            clrBufferUSART();
//            ConecBatteria(0);
            
            return;
    }
    //Verifico si es conectar batería
    else if (BluetoothDato[1] == SOlIBATON) {
//             DelayCommands();
//            ConecBatteria(1);
            Lcd_Clear();
            Lcd_Set_Cursor(1,1);
            Lcd_Write_String("Abajo");
            PORTAbits.RA0=0;
            PORTAbits.RA1=1;
            PORTAbits.RA2=0;
            PORTAbits.RA3=1;
            clrBufferUSART();
            return;
    }
    //Verifico si es PING BT
    else if (BluetoothDato[1] == PINGBT) {
//            DelayCommands();
//            PONGBT();
            Lcd_Clear();
            Lcd_Set_Cursor(1,1);
            Lcd_Write_String("Izquierda");
            PORTAbits.RA0=1;
            PORTAbits.RA1=0;
            PORTAbits.RA2=0;
            PORTAbits.RA3=0;
            clrBufferUSART();
            return;
    }
    //Verifico si es ACK
     else if (BluetoothDato[1] == ACK ) {
//            UART1_Init(25);
//            DelayCommands();
              Lcd_Clear();
              Lcd_Set_Cursor(1,1);
              Lcd_Write_String("Derecha");
              PORTAbits.RA0=0;
              PORTAbits.RA1=0;
              PORTAbits.RA2=1;
              PORTAbits.RA3=0;
              clrBufferUSART();
            return;
    }
        //////////////////////////////
    //Si no coincide ningún comando, comando inválido
    else {

//         DelayCommands();
        for (x = 0; x <= 20; x++)
                dato[x] = 0;
            //Respuesta % BT/Error
            dato[0] = '#';
            dato[1] = 3;
            dato[2] = 2;
            dato[3] = 0x45;
            dato[4] = 2;
            dato[5] = dato[1] + dato[2] + dato[3] + dato[4];
            dato[6] = '#';
            TamanhoTrama = 7; //Se cambio de 6 a 7
//        Mandar_Tablet();

        return;
    }
}

