#include<xc.h>
#define _XTAL_FREQ 1000000
#pragma config FOSC=INTOSC_EC
#pragma config WDT=OFF
unsigned int a=125;
void interrupt ISR(void);
void main(void){
    TRISC2=0;      
    TMR1=60536;        //Precarga del Timer1 que asegura los 20 ms mas el tiempo del pulso
    T1CON=0b10000000;
    CCPR1=60536+125;    //Servomotor a 0°
    CCP1CON=0b00001001; //Establece modo de comparación para generación de pulso
    TMR1IF=0;
    TMR1IE=1;
    PEIE=1;
    GIE=1;
    TMR1ON=1;
    while(1){
      a=125;        //Servomotor a 0°
      __delay_ms(2000);  
      a=375;        //Servomotor a 90°
      __delay_ms(2000);
      a=625;        //Servomotor a 180°
      __delay_ms(2000);
    }
}
void interrupt ISR(void){
    TMR1IF=0;
    TMR1=60536;        //Precarga del Timer1 que asegura los 20 ms mas el tiempo del pulso
    CCPR1=60536+a;    //Varia la duración del púlso y a su vez del angulo del servo
    CCP1CON=0b00001001; //Establece modo de comparación para generación de pulso  
}
