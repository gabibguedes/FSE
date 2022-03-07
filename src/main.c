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
#include "gpio.h"

struct sigaction old_action;
Config program_config;

void sigint_handler(int sig_no) {
  printf("Exiting program\n");
  shut_down(&program_config);

  sigaction(SIGINT, &old_action, NULL);
  kill(0, SIGINT);
}

int main(){
  struct sigaction action;
  memset(&action, 0, sizeof(action));
  action.sa_handler = &sigint_handler;
  sigaction(SIGINT, &action, &old_action);

  program_config = initial_config();

  clear();
  show_menu(&program_config);

  start_app(&program_config);
  app_main_loop(&program_config);

  shut_down(&program_config);

  return 0;
}
