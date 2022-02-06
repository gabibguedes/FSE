#include <stdio.h>
#include <unistd.h>
#include "uart.h"
#include "menu.h"

int main(){
  clear();

  int opt = show_menu();

  int uart_filestream = initialize_uart();

  write_in_uart(uart_filestream, opt);

  sleep(1);

  read_from_uart(uart_filestream);

  close_uart(uart_filestream);

  return 0;
}
