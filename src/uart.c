#include "uart.h"
#include "ui.h"
#include "app.h"
#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <termios.h>
#include <string.h>
#include <stdlib.h>

static int uart_filestream = -1;

void initialize_uart(){
  uart_filestream = open("/dev/serial0", O_RDWR | O_NOCTTY | O_NDELAY);

  if (uart_filestream == -1) {
    printf("Erro - Não foi possível iniciar a UART.\n");
  } else {
    printf("UART inicializada!\n");
  }

  struct termios options;
  tcgetattr(uart_filestream, &options);
  options.c_cflag = B9600 | CS8 | CLOCAL | CREAD;
  options.c_iflag = IGNPAR;
  options.c_oflag = 0;
  options.c_lflag = 0;
  tcflush(uart_filestream, TCIFLUSH);
  tcsetattr(uart_filestream, TCSANOW, &options);
}

void write_in_uart(unsigned char *tx_buffer, int size) {
  if (uart_filestream != -1) {
    printf("Escrevendo caracteres na UART ...");
    int count = write(uart_filestream, tx_buffer, size);
    if (count < 0) {
      printf("UART TX error\n");
    } else {
      printf("escrito.\n");
    }
  }
}

void read_from_uart(int option){
  UartResponse res;
  sleep(1);

  res = read_buffer(uart_filestream);

  if (uart_filestream != -1 && !res.empty) {
    switch (option) {
    case REQUEST_INT: case SEND_INT:
      read_int(res);
      break;
    case REQUEST_FLOAT: case SEND_FLOAT:
      read_float(res);
      break;

    default:
      printf("%i Bytes lidos : %s\n", res.size, res.buffer);
      break;
    }
  }
}

UartResponse read_buffer(){
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