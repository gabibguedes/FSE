#ifndef UART_H
#define UART_H

void initialize_uart();
void write_in_uart(unsigned char *tx_buffer, int size);
unsigned char *read_uart();
void close_uart();

#endif
