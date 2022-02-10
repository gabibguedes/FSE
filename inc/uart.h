#ifndef UART_H
#define UART_H

#define REQUEST_INT 0xA1 // Solicitação de dado inteiro
#define REQUEST_FLOAT 0xA2 // Solicitação de dado real (float)
#define REQUEST_STR 0xA3   // Solicitação de dado do tipo string

#define SEND_INT 0xB1 // Envio de um dado no formato integer
#define SEND_FLOAT 0xB2 // Envio de um dado no formato float
#define SEND_STR 0xB3   // Envio de uma string

typedef struct UartResponse {
  unsigned char buffer[256];
  int size;
  int empty;
}UartResponse;

void initialize_uart();
void write_in_uart(int option);
void read_from_uart(int option);
UartResponse read_buffer();
void read_int(UartResponse response);
void read_float(UartResponse response);
void close_uart();

#endif
