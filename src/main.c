#include <stdio.h>
#include <unistd.h>
#include "uart.h"
#include "ui.h"
#include "app.h"

int main(){
  clear();
  int opt = show_menu();

  clear();
  initialize_uart();
  write_message(opt);
  receive_message(opt);
  close_uart();

  return 0;
}
