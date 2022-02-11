#include "app.h"
#include "modbus.h"
#include "ui.h"

#include <stdio.h>
#include <string.h>

void write_message(int option) {
  int message_size;
  unsigned char *message;

  switch (option) {
  case SEND_INT:
    message = send_int();
    message_size = 4;
    break;

  case SEND_FLOAT:
    message = send_float();
    message_size = 4;
    break;

  case SEND_STR:
    message = send_string();
    message_size = strlen((char*) message);
    break;

  default:
    message = (unsigned char*) "";
    message_size = 0;
    break;
  }

  send_modbus_message(message, message_size, option);
}