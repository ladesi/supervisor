// =============================================================================
// Program:        Medidor de Energia
// Hardware Model: PIC18F4520
// Description:    Aferir medidas de tensão e corrente
// Software/Tool:  MPLABX_v5.50/XC8_v2.32/Pickit3
// =============================================================================

/*
* Hardware Pin Out
*                --------
*  MRCLR'/RE3 >>| 1   40 |-- RB7/PGD
* (IS)RA0/AN0 >>| 2   39 |-- RB6/PGC
* (VR)RA1/AN1 >>| 3   38 |-- RB5
* (VS)RA2/AN2 >>| 4   37 |-- RB4
* (IR)RA3/AN3 >>| 5   36 |-- RB3/PGM
*         RA4 --| 6   35 |-- RB2
*     RA5/AN4 --| 7   34 |>> RB1(TIME_OUT)
*  (V)RE0/AN5 >>| 8   33 |<< RB0/INT(TIME_IN)
*  (I)RE1/AN6 >>| 9   32 |-- VDD
* (VR)RE2/AN7 >>| 10  31 |-- VSS
*         VDD >>| 11  30 |-- RD7
*         VSS >>| 12  29 |-- RD6
*    OSC1/RA7 >>| 13  28 |-- RD5
*    OSC2/RA6 >>| 14  27 |-- RD4
*         RC0 --| 15  26 |-- RC7/RX
*   (LED1)RC1 <<| 16  25 |>> RC6/TX(RX esp01)
*         RC2 --| 17  24 |-- RC5
*         RC3 --| 18  23 |-- RC4
*         RD0 --| 19  22 |-- RD3
*         RD1 --| 20  21 |-- RD2
*                --------
*/

#include "config.h"
#include "serial.h"

uint8_t i=0x00, j=0x00, k=0x00, select=0x01, current=0x00;
uint16_t out=0x00, time_phase=0x00, vref=0x00;
unsigned int amost=0x00;
float sample[STORE]={0.0}, mean_out[STORE]={0.0};
float RMS=0.0, PHASE=0.0, temp=0.0;
float VO=0.00, IO=0.00;


void main(void){
    GLOBAL_INT = 0;
    config();
    serial_config();
    __delay_ms(50);
    GLOBAL_INT = 1;

    while(1){
        if(amost && select){
            amost = 0x00;
            // get voltage value from AN0
            out = (uint16_t)adc_read(5);
            sample[j] = (float)(out*5/AD_RES);
            j++;

            if(j == STORE){
                TMR0_INT = 0x00;

                for (i = 0 ; i < STORE; i++){
                    temp += (float)sample[i]*sample[i];
                }
                RMS = (float)sqrt((2*temp)/STORE);
                temp = 0.00;
                mean_out[k] = RMS;
                k++;
                if(k == AVG){
                    for (i = 0 ; i < AVG; i++){
                        temp += (float)mean_out[i];
                    }
                    VO = temp/AVG;
                    temp = 0.00;
                    k = 0x00;
                    if(current){
                        select = 0x00;
                    }
                    else if(!current){
                        json_data(VO, 0.00, 0.00);
                        __delay_ms(250);
                        LED1 = 1;
                        __delay_ms(250);
                        LED1 = 0;
                    }
                }
                j = 0x00;
                TMR0_INT = 0x01;
            }
        }

        if(amost && !select){
            amost = 0x00;
            // get value from VDD/2 in AN2
            vref = (float)adc_read(7);
            // get current value in AN1
            out = (uint16_t)adc_read(6);
            sample[j] = (float)(out*0.0264 - vref*0.0264);
            j++;

            if(j == STORE){
                TMR0_INT = 0x00;

                for (i = 0 ; i < STORE; i++){
                    temp += (float)sample[i]*sample[i];
                }
                RMS = (float)sqrt((temp)/STORE);
                temp=0;
                mean_out[k] = RMS;
                k++;
                if(k == AVG){
                    for (i = 0 ; i < AVG; i++){
                        temp += (float)mean_out[i];
                    }
                    IO = temp/AVG;
                    temp = 0.00;
                    PHASE = (float)(time_phase*FIX_ANGLE);
                    // send data
                    json_data(VO, IO, PHASE);
                    __delay_ms(250);
                    LED1 = 1;
                    __delay_ms(250);
                    LED1 = 0;
                    select = 0x01;
                    k = 0x00;
                }
                j = 0x00;
                current = 0x00;
                TMR0_INT = 0x01;
            }
        }
    }
}


void __interrupt() intr(){
    // time to sync 60Hz wave with 16 samples
    if(TMR0_FLAG){
        TMR0_FLAG = 0x00;
        TMR0 = REC_TMR0;
        OUT_TMR0 = ~OUT_TMR0;
        amost = 0x01;
    }

    // for initialize external interrupt
    if (CM_FLAG){
        // inductive load
        if(C1_OUT && !C2_OUT){
            RB1 = 1;
            current = 0x01;
        }
        else if(C2_OUT && C1_OUT){
            RB1 = 0;
        }
        // capacitive load
        if(!C1_OUT && C2_OUT){
            RB1 = 1;
            current = 0x01;
        }
        else if(!C1_OUT && !C2_OUT){
            RB1 = 0;
        }
        CM_FLAG = 0x00;
    }

    // to calculate time between square waves from comparators
    if (INT0_FLAG){
        if(INT0_EDGE){
            TMR1 = 0;
            TMR1_EN = 1;
            INT0_EDGE = 0x00;
        }
        else if(!INT0_EDGE){
            time_phase = (uint16_t)TMR1;
            TMR1_EN = 0;
            INT0_EDGE = 0x01;
        }
        INT0_FLAG = 0x00;
    }
}
