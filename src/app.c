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

void receive_message() {
  int option, size;
  unsigned char *message = NULL;

  message = receive_modbus_message();
  size = strlen((char*) message);

  memcpy(&option, &message[0], 1);

  switch (option){
  case REQUEST_INT: case SEND_INT:
    read_int(&message[1]);
    break;
  case REQUEST_FLOAT: case SEND_FLOAT:
    read_float(&message[1]);
    break;

  default:
    printf("%i Bytes lidos : %s\n", size, &message[2]);
    break;
  }
}

void read_int(unsigned char *res){
  int number;
  memcpy(&number, res, 4);

  printf("Número recebido: %d\n", number);
}

void read_float(unsigned char *res){
  float number;
  memcpy(&number, res, 4);

  printf("Número recebido: %f\n", number);
}
