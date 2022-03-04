#include <stdio.h>
#include <unistd.h>
#include <signal.h>
#include <string.h>

#include "uart.h"
#include "ui.h"
#include "app.h"
#include "display.h"
#include "sensor.h"
#include "store_data.h"

struct sigaction old_action;

void sigint_handler(int sig_no) {
  printf("Exiting program\n");
  close_csv_file();
  sigaction(SIGINT, &old_action, NULL);
  kill(0, SIGINT);
}

int main(){
  struct sigaction action;
  memset(&action, 0, sizeof(action));
  action.sa_handler = &sigint_handler;
  sigaction(SIGINT, &action, &old_action);

  lcd_init();
  lcdLoc(LINE1);
  typeln("Teste");
  lcdLoc(LINE2);
  typeln("1612");

  open_csv();

  connect_with_sensor();

  close_csv_file();

  return 0;
}
