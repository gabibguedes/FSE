#include <stdio.h>
#include <unistd.h>
#include "uart.h"
#include "menu.h"

int main(){
  clear();
  int opt = show_menu();

  clear();
  initialize_uart();
  write_in_uart(opt);
  read_from_uart(opt);
  close_uart();

  return 0;
}
