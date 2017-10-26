#include <xc.h> // include processor files - each processor file is guarded.  


#define PWM2 PORTCbits.RC1
#define PWM1 PORTCbits.RC2
#define INPUT1 PORTDbits.RD7
#define INPUT2 PORTDbits.RD4
#define INPUT3 PORTDbits.RD2
#define INPUT4 PORTDbits.RD3

void motor_forward(void);
void motor_Backforward(void);
void motor_forward1(void);
void motor_forward2(void);
void motor_Backforward1(void);
void motor_Backforward2(void);