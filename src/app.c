#include "app.h"
#include "modbus.h"
#include "ui.h"

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

unsigned char *get_message(int option) {
  unsigned char *message;

  switch (option) {
  case SEND_INT:
    message = send_int();
    break;

  case SEND_FLOAT:
    message = send_float();
    break;

  case SEND_STR:
    message = send_string();
    break;

  default:
    message = (unsigned char *) "";
    break;
  }
  return message;
}

void write_message(int option) {
  int message_size, pos = 0;
  unsigned char *message, *buffer;

  message = get_message(option);

  if(option >= SEND_INT && option != SEND_STR)
    message_size = 4;
  else
    message_size = strlen((char *)message);

  buffer = malloc(message_size + BUFF_MIN_SIZE);

  buffer[pos++] = option;

  if (option == SEND_STR)
    buffer[pos++] = message_size;

  memcpy(&buffer[pos], message, message_size);
  pos += message_size;

  send_modbus_message(buffer, pos);

  free(buffer);
}

int option_error(int opt_expected, int opt_received) {
  if (opt_expected == opt_received)
    return 0;

  show_error("Opção", opt_expected, opt_received);
  return 1;
}

void receive_message(int option) {
  unsigned char *message = NULL;

  message = receive_modbus_message(option);
  if(message == NULL) return;

  if(option_error(option, message[0]))
    return;

  switch (option){
  case REQUEST_INT: case SEND_INT:
    read_int(&message[1]);
    break;
  case REQUEST_FLOAT: case SEND_FLOAT:
    read_float(&message[1]);
    break;
  case REQUEST_STR: case SEND_STR:
    read_str(&message[1]);
    break;

  default:
    break;
  }
}
