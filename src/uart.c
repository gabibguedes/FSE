#include "uart.h"
#include "menu.h"

#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <termios.h>
#include <string.h>
#include <stdlib.h>

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
  UartResponse res;
  sleep(1);

  res = read_buffer(uart_filestream);

  if (uart_filestream != -1 && !res.empty) {
    switch (option) {
    case A1:
      read_int(res);
      break;
    case A2:
      read_float(res);
      break;

    default:
      printf("%i Bytes lidos : %s\n", res.size, res.buffer);
      break;
    }
  }
}

UartResponse read_buffer(int uart_filestream){
  UartResponse rx;
  rx.empty = 1;
  rx.size = read(uart_filestream, (void *)rx.buffer, 255);
  if (rx.size < 0){
    printf("Erro na leitura.\n");
  } else if (rx.size == 0){
    printf("Nenhum dado disponível.\n");
  } else {
    rx.empty = 0;
    rx.buffer[rx.size] = '\0';
  }
  return rx;
}

void read_int(UartResponse res){
  int number;
  memcpy(&number, &res.buffer[res.size - 4], 4);

  printf("Número recebido: %d\n", number);
}

void read_float(UartResponse res){
  float number;
  memcpy(&number, &res.buffer[res.size - 4], 4);

  printf("Número recebido: %f\n", number);
}

void close_uart(int uart_filestream){
  close(uart_filestream);
}