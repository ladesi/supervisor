#include "serial.h"
#include "config.h"

void serial_config(void){
    //USART bits (TXSTA: TRANSMIT STATUS AND CONTROL REGISTER)
    TXSTA = 0b00100100;
    /*        |CSRC: Clock Source Select bit/ Asynchronous mode: Don?t care.
               |TX9: 9-bit Transmit Enable bit/ 0 = Selects 8-bit transmission
                |TXEN: Transmit Enable bit/ 1 = Transmit enabled
                 |SYNC: USART Mode Select bit/ 0 = Asynchronous mode
                  |Unimplemented: Read as '0'
                   |BRGH: High Baud Rate Select bit/ 1 = High speed
                    |TRMT: Transmit Shift Register Status bit (1 = TSR empty/ 0 = TSR full)
                     |TX9D: 9th bit of Transmit Data, can be Parity bit
   */

    //USART bits (RCSTA: RECEIVE STATUS AND CONTROL REGISTER)
    RCSTA = 0b10010000;
    /*        |SPEN: Serial Port Enable bit/ 1 = Serial port enabled (configures RC7/RX/DT and RC6/TX/CK pins as serial port pins)
               |RX9: 9-bit Receive Enable bit/ 0 = Selects 8-bit reception
                |SREN: Single Receive Enable bit/ Asynchronous mode: Don?t care
                 |CREN: Continuous Receive Enable bit/ 1 = Enables continuous receive
                  |ADDEN: Address Detect Enable bit/ 0 = Disables address detection
                   |FERR: Framing Error bit/ 0 = No framing error
                    |OERR: Overrun Error bit/ 0 = No overrun error
                     |RX9D: 9th bit of Received Data (can be parity bit but must be calculated by user firmware)
    */

    //USART Baud Rate Generator (BRG)
    SPBRG = 129;
    /*
        Baud Rate = FOSC/(16(x+1))
        x = value in SPBRG (0 to 255)
        Baud Rate = 9.6k, FOSC = 20MHz
    */
}


void tx_data(unsigned char data){
    TXREG = data;
    __delay_ms(10);
}

void float_send(float aux){
    unsigned int var = (unsigned int)100*aux;
    char cent, dez, unit, dec_1, dec_2;
    cent =  (var/10000);
    dez =   (var%10000/1000);
    unit =  (var%1000/100);
    dec_1 = (var%100/10);
    dec_2 = (var%10);

    if (var >= 10000){
        tx_data(cent+48);
        tx_data(dez+48);
        tx_data(unit+48);
        tx_data(46);
        tx_data(dec_1+48);
        tx_data(dec_2+48);
    }

    if (var < 10000 && var >= 1000){
        tx_data(dez+48);
        tx_data(unit+48);
        tx_data(46);
        tx_data(dec_1+48);
        tx_data(dec_2+48);
    }

    if (var < 1000){
        tx_data(unit+48);
        tx_data(46);
        tx_data(dec_1+48);
        tx_data(dec_2+48);
    }
}

void json_data(float v, float i, float p){
    tx_obraces
    tx_quotes
    tx_data('v');
    tx_quotes
    tx_colon
    float_send(v);
    tx_comma
    tx_space
    tx_quotes
    tx_data('i');
    tx_quotes
    tx_colon
    float_send(i);
    tx_comma
    tx_space
    tx_quotes
    tx_data('z');
    tx_quotes
    tx_colon
    float_send(p);
    tx_cbraces
    tx_data('\n');
    tx_data('\r');
}
