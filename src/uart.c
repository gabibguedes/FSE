#include "uart.h"

#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <termios.h>

int initialize_uart(){
  int uart0_filestream = -1;

  uart0_filestream = open("/dev/serial0", O_RDWR | O_NOCTTY | O_NDELAY);

  if (uart0_filestream == -1) {
    printf("Erro - Não foi possível iniciar a UART.\n");
  } else {
    printf("UART inicializada!\n");
  }

  struct termios options;
  tcgetattr(uart0_filestream, &options);
  options.c_cflag = B9600 | CS8 | CLOCAL | CREAD;
  options.c_iflag = IGNPAR;
  options.c_oflag = 0;
  options.c_lflag = 0;
  tcflush(uart0_filestream, TCIFLUSH);
  tcsetattr(uart0_filestream, TCSANOW, &options);

  return uart0_filestream;
}

void write_in_uart(int uart_filestream, int option) {
  unsigned char tx_buffer[20];
  unsigned char *p_tx_buffer;

  p_tx_buffer = &tx_buffer[0];
  *p_tx_buffer++ = option;
  *p_tx_buffer++ = 1;
  *p_tx_buffer++ = 6;
  *p_tx_buffer++ = 1;
  *p_tx_buffer++ = 2;

  printf("Buffers de memória criados!\n");

  if (uart_filestream != -1) {
    printf("Escrevendo caracteres na UART ...");
    int count = write(uart_filestream, &tx_buffer[0], (p_tx_buffer - &tx_buffer[0]));
    if (count < 0) {
      printf("UART TX error\n");
    } else {
      printf("escrito.\n");
    }
  }
}

void read_from_uart(int uart_filestream){
  if (uart_filestream != -1) {
    unsigned char rx_buffer[256];
    int rx_length = read(uart_filestream, (void *)rx_buffer, 255);
    if (rx_length < 0) {
      printf("Erro na leitura.\n");
    } else if (rx_length == 0) {
      printf("Nenhum dado disponível.\n");
    } else {
      rx_buffer[rx_length] = '\0';
      printf("%i Bytes lidos : %s\n", rx_length, rx_buffer);
    }
  }
}

void close_uart(int uart_filestream){
  close(uart_filestream);
}