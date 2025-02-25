#ifndef SERIAL_HEADER
#define SERIAL_HEADER

#define _XTAL_FREQ 20000000

// ASCII characters
#define tx_start     tx_data(2);   // Start of Text
#define tx_enter     tx_data(13);  // Next line
#define tx_space     tx_data(32);  // Space
#define tx_quotes    tx_data(34);  // Quotes
#define tx_plus      tx_data(43);  // Plus sign
#define tx_comma     tx_data(44);  // Comma
#define tx_minus     tx_data(45);  // Minus sign
#define tx_slash     tx_data(47);  // Slash
#define tx_colon     tx_data(58);  // Colon
#define tx_obraces   tx_data(123); // Open Braces
#define tx_cbraces   tx_data(125); // Closing Braces
#define tx_vbar      tx_data(124); // Vertical bar
#define tx_del       tx_data(8);   // Delete char
#define tx_degree    tx_data(248); // Degree symbol

// prototypes
void serial_config(void);
void tx_data(unsigned char data);
void float_send(float aux);
void json_data(float v, float i, float p);

#endif
