#ifndef UART_H
#define UART_H

int initialize_uart();
void write_in_uart(int uart_filestream, int option);
void read_from_uart(int uart_filestream, int option);
void close_uart(int uart_filestream);

#endif
