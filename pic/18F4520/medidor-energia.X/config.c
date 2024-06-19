#include "config.h"

void config(void){
    //IO setup
    TRISA = 0x0F; // 0000 1111
    PORTA = 0x00;
    LATA = 0x00;
    TRISB = 0x31; // 0011 0001
    PORTB = 0x00;
    LATB = 0x00;
    TRISC = 0x00; // 0000 0000
    PORTC = 0x00;
    LATC = 0x00;
    TRISD = 0x1C; // 0001 1100
    PORTD = 0x00;
    LATD = 0x00;
    TRISE = 0x07; // 0000 0111
    PORTE = 0x00;
    LATE = 0x00;


    // INTERRUPTS
    RCONbits.IPEN = 0; // disable priority
    INTCONbits.PEIE = 1; // enable  peripheral interrupts
    PIE1bits.PSPIE = 0; // disable PSP
    INTCON2bits.RBPU = 1; // RBPU'=0 pull-ups enabled
    INT0_EDGE = 1; // 1=rising
    PORTB_INT = 0;
    INT0 = 1;
    CM_INT = 1;

    // COMPARATORS
    CMCON = 0x03; // 0000 0011 - enable C1 and C2 comparators with outputs
    C1_INV = 1;

    // TMR0
    T0CON = 0xC5; // 1100 0101 - 8-bit no priority, PS=64
    TMR0 = REC_TMR0;
    TMR0_INT = 0;
    // T0 = Tm.PS.(256-TMR0)
    // Examples:
    // 200ns.64.(256-175) = 1.0368 ms (16)
    // 200ns.64.(256-202) = 0.6912 ms (24)
    // 200ns.64.(256-216) = 0.512 ms (32)
    // 200ns.64.(256-229) = 0.3456 ms (48)
    // 200ns.8.(256-152) = 0.0001664 (100) ps=8 010
    // 18-184 | 20-191 | 22-197 | 26-206 | 30-213

    // TMR1
    T1CON = 0xB0; // 1011 0000 - 16-bits PS=8
    TMR1 = 0;

    // AD
    ADCON0 = 0x01; // 0000 0001
    ADCON1 = 0x07; // 0000 0111 - AN0:AN7
    ADCON2 = 0x82; // 1000 0010 - <0:2>, right justified
}

// select analog pin
unsigned int adc_read(int port){
    unsigned int value;
    ADCON0 = ( (port<<2) | (ADCON0 & 0XC3) );
    __delay_us(20);
    init_AD = 0x01;
    while(init_AD);
    value = (unsigned int)( (ADRESH << 8) + (ADRESL) );
    return(value);
}
