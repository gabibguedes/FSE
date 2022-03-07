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
    printf("[ERRO] Não foi possível iniciar a UART.\n");
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
    int count = write(uart_filestream, tx_buffer, size);
    if (count < 0) {
      printf("[ERRO] UART TX error\n");
    } else {
      // printf("Mensagem enviada.\n");
    }
  } else {
    printf("[ERRO] Uart não inicializada!\n");
  }
}

unsigned char *read_uart(){
  unsigned char *rx_buffer;
  rx_buffer = (unsigned char *) malloc(256);

  sleep(1);
  int size = read(uart_filestream, (void *) rx_buffer, 255);

  if (uart_filestream != -1) {
    if (size < 0){
      printf("[ERRO] Erro na leitura. %d\n", size);
    } else if (size == 0){
      printf("[ERRO] Nenhum dado disponível.\n");
    } else {
      rx_buffer[size] = '\0';
    }
  } else {
    printf("[ERRO] Uart não inicializada!\n");
  }
  return rx_buffer;
}

void close_uart(int uart_filestream){
  close(uart_filestream);
}