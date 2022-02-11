#ifndef UART_H
#define UART_H
typedef struct UartResponse {
  unsigned char buffer[256];
  int size;
  int empty;
}UartResponse;

void initialize_uart();
void write_in_uart(unsigned char *tx_buffer, int size);
void read_from_uart(int option);
UartResponse read_buffer();
void read_int(UartResponse response);
void read_float(UartResponse response);
void close_uart();

#endif
