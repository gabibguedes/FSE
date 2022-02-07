#ifndef UART_H
#define UART_H

#define A1 161 // Solicitação de dado inteiro
#define A2 162 // Solicitação de dado real (float)
#define A3 163 // Solicitação de dado do tipo string

#define B1 177 // Envio de um dado no formato integer
#define B2 178 // Envio de um dado no formato float
#define B3 179 // Envio de uma string

typedef struct UartResponse {
  unsigned char buffer[256];
  int size;
  int empty;
}UartResponse;

int initialize_uart();
void write_in_uart(int uart_filestream, int option);
void read_from_uart(int uart_filestream, int option);
UartResponse read_buffer(int uart_filestream);
void read_int(UartResponse response);
void read_float(UartResponse response);
void close_uart(int uart_filestream);

#endif
