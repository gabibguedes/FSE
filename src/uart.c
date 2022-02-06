#include "uart.h"
#include "menu.h"

#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <termios.h>
#include <string.h>

#define A1 161 // Solicitação de dado inteiro : integer
#define A2 162 // Solicitação de dado real: float
#define A3 163 // Solicitação de dado do tipo string: char[]

#define B1 177 // Envio de um dado no formato integer
#define B2 178 // Envio de um dado no formato float
#define B3 179 // Envio de uma string: char[]

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

  int int_send, str_size;
  float float_send;
  char * str_send;

  p_tx_buffer = &tx_buffer[0];
  *p_tx_buffer++ = option;

  switch (option){
  case B1:
    int_send = send_int();
    *p_tx_buffer++ = int_send;
    break;
  case B2:
    float_send = send_float();
    *p_tx_buffer++ = float_send;
    break;
  case B3:
    str_send = send_string();
    str_size = strlen(str_send);
    *p_tx_buffer++ = str_size;
    for(int i = 0; i < str_size; i++)
      *p_tx_buffer++ = str_send[i];
    break;

  default:
    break;
  }

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

void read_from_uart(int uart_filestream, int option){
  sleep(1);

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